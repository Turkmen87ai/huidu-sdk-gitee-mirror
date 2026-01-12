package cn.huidu.device.sdk.common;

import java.util.ArrayList;
import java.util.List;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import cn.huidu.device.sdk.data.program.ProgramNode;
import cn.huidu.device.sdk.data.program.area.AreaNode;
import cn.huidu.device.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.sdk.data.program.other.FileInfo;

public class BaseClient {
    private HttpApi client = new HttpApi();

    public void setHosrUrl(String hostUrl) {
        client = new HttpApi(hostUrl);
    }

    public String getDevice() {
        return toJsonObject(client.deviceList());
    }

    public String device(String[] devIds, String method) {
        return device(devIds, method, null);
    }

    public String device(String[] devIds, String method, Object data) {
        JSONObject jsonMethod = new JSONObject();
        jsonMethod.put("method", method);
        jsonMethod.put("data", data);

        if (devIds.length > 0) {
            // Put in body's id field
            String devId = String.join(",", devIds);
            jsonMethod.put("id", devId);
        }

        return toJsonObject(client.device(jsonMethod.toString()));
    }

    public String program(String[] devIds, String method, ProgramNode[] programNodes, Object dataEx) {

        JSONObject retJsonObject = uploadAndUpdateFiles(programNodes);
        if (!retJsonObject.getString("message").equals("ok")) {
            return retJsonObject.toString();
        }

        JSONObject jsonMethod = new JSONObject();
        jsonMethod.put("method", method);
        jsonMethod.put("data", programNodes);
        if (null != dataEx) {
            jsonMethod.put("dataEx", dataEx);
        }

        if (devIds.length > 0) {
            // Put in body's id field
            String devId = String.join(",", devIds);
            jsonMethod.put("id", devId);
        }

        return toJsonObject(client.program(jsonMethod.toString()));
    }

    public String file(String filePath) {
        return toJsonObject(client.uploadFile(filePath));
    }

    protected JSONObject uploadAndUpdateFiles(ProgramNode[] programNodes) {

        JSONObject retJsonObject = new JSONObject();
        retJsonObject.put("message", "ok");

        boolean ret = true;
        List<FileInfo> fileInfos = new ArrayList<FileInfo>();
        if (null != programNodes) {
            for (ProgramNode programNode : programNodes) {
                FileInfo[] files = programNode.getFilesInfo();
                if (files != null && files.length > 0) {
                    for (FileInfo info : files) {
                        // Deduplicate
                        if (!fileInfos.contains(info)) {
                            fileInfos.add(info);
                        }
                    }
                }

                AreaNode[] areaNodes = programNode.getArea();
                if (null == areaNodes) {
                    continue;
                }

                for (AreaNode area : areaNodes) {
                    files = area.getFilesInfo();
                    if (files != null && files.length > 0) {
                        for (FileInfo info : files) {
                            // Deduplicate
                            if (!fileInfos.contains(info)) {
                                fileInfos.add(info);
                            }
                        }
                    }

                    ContentNode[] items = area.getItem();
                    if (null == items) {
                        continue;
                    }

                    for (ContentNode contentNode : items) {
                        files = contentNode.getFilesInfo();
                        if (files != null && files.length > 0) {
                            for (FileInfo info : files) {
                                // Deduplicate
                                if (!fileInfos.contains(info)) {
                                    fileInfos.add(info);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (FileInfo info : fileInfos) {
            // If it's a URL, no need to upload file
            if (isURL(info.localFile) && info.md5.length() > 0 && info.size > 0) {
                info.url = info.localFile;
                continue; // No need to process
            }

            String jsonBody = file(info.localFile);
            JSONObject jsonObject = JSON.parseObject(jsonBody);
            if (!jsonObject.containsKey("message") || !jsonObject.getString("message").equals("ok")) {
                ret = false;
                retJsonObject.put("data", jsonObject);
                break;
            }

            JSONArray dataArray = jsonObject.getJSONArray("data");
            if (null == dataArray || dataArray.size() == 0) {
                ret = false;
                retJsonObject.put("data", jsonObject);
                break;
            }

            JSONObject dataObject = dataArray.getJSONObject(0);
            if (dataObject == null || !dataObject.containsKey("message")
                    || !dataObject.getString("message").equals("ok")) {
                ret = false;
                retJsonObject.put("data", jsonObject);
                break;
            }

            info.md5 = dataObject.getString("md5");
            info.size = dataObject.getIntValue("size");
            info.url = dataObject.getString("data");
        }

        if (ret && fileInfos.size() > 0) {
            FileInfo[] files = fileInfos.toArray(new FileInfo[fileInfos.size()]);
            for (ProgramNode programNode : programNodes) {
                programNode.updateFilesInfo(files); // Update program files
                for (AreaNode area : programNode.getArea()) {
                    area.updateFilesInfo(files); // Update area files
                    for (ContentNode contentNode : area.getItem()) {
                        contentNode.updateFilesInfo(files);// Update content files
                    }
                }
            }
        }

        if (false == ret) {
            retJsonObject.put("message", "failed");
        }

        return retJsonObject;
    }

    /**
     * Determine if a string is a URL
     *
     * @param str String string
     * @return boolean whether it is a URL
     * @author peng1 chen
     **/
    public static boolean isURL(String str) {
        // Convert to lowercase
        str = str.toLowerCase();
        String regex = "^((https|http)?://)" // https、http
                + "?(([0-9a-z_!~*'().&=+$%-]+: )?[0-9a-z_!~*'().&=+$%-]+@)?" // http user@
                + "(([0-9]{1,3}\\.){3}[0-9]{1,3}" // IP format URL - e.g.: 199.194.52.184
                + "|" // Allow IP and DOMAIN
                + "([0-9a-z_!~*'()-]+\\.)*" // Domain - www.
                + "([0-9a-z][0-9a-z-]{0,61})?[0-9a-z]\\." // Second level domain
                + "[a-z]{2,6})" // first level domain- .com or .museum
                + "(:[0-9]{1,5})?" // Port number maximum 65535, 5 digits
                + "((/?)|" // a slash isn't required if there is no file name
                + "(/[0-9a-z_!~*'().;?:@&=+$,%#-]+)+/?)$";
        return str.matches(regex);
    }

    private String toJsonObject(String data) {
        JSONObject jsonObject = null;
        try {
            jsonObject = JSONObject.parseObject(data);
        } catch (Exception e) {
            jsonObject = new JSONObject();
            jsonObject.put("message", "failed");
            jsonObject.put("data", e.toString());
        } finally {
            if (null == jsonObject) {
                jsonObject = new JSONObject();
                jsonObject.put("message", "failed");
                jsonObject.put("data", data);
            }
        }

        return jsonObject.toString();
    }

}
