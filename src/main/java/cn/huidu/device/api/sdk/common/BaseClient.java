package cn.huidu.device.api.sdk.common;

import java.util.ArrayList;
import java.util.List;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import cn.huidu.device.api.sdk.data.program.ProgramNode;
import cn.huidu.device.api.sdk.data.program.area.AreaNode;
import cn.huidu.device.api.sdk.data.program.area.content.ContentNode;
import cn.huidu.device.api.sdk.data.program.other.FileInfo;

public class BaseClient {
    private HttpApi client = new HttpApi();

    public void setHosrUrl(String hostUrl) {
        client = new HttpApi(hostUrl);
    }
   
    protected String getDevice() {
        return toJsonObject(client.deviceList());
    }
   
    protected String device(String[] devIds, String method) {
        return device(devIds, method, null);
    }

    protected String device(String[] devIds, String method, Object data) {   
        JSONObject jsonMethod = new JSONObject();
        jsonMethod.put("method", method);
        jsonMethod.put("data", data);
           
        if (devIds.length > 0) {
            // 放在body的id字段
            String devId = String.join(",", devIds);
            jsonMethod.put("id", devId);
        }
        
        return toJsonObject(client.device(jsonMethod.toString()));
    }

    protected String program(String[] devIds, String method, ProgramNode[] programNodes) {

        JSONObject retJsonObject = uploadAndUpdateFiles(programNodes);
        if (!retJsonObject.getString("message").equals("ok")) {
            return retJsonObject.toString();
        }

        JSONObject jsonMethod = new JSONObject();
        jsonMethod.put("method", method);
        jsonMethod.put("data", programNodes);

        if (devIds.length > 0) {
            // 放在body的id字段
            String devId = String.join(",", devIds);
            jsonMethod.put("id", devId);
        }

        return toJsonObject(client.program(jsonMethod.toString()));
    }

    protected String file(String filePath) {
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
                        // 去重
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
                            // 去重
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
                                // 去重
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
                programNode.updateFilesInfo(files); // 更新节目文件
                for (AreaNode area : programNode.getArea()) {
                    area.updateFilesInfo(files); // 更新区域文件
                    for (ContentNode contentNode : area.getItem()) {
                        contentNode.updateFilesInfo(files);// 更新内容文件
                    }
                }
            }
        }

        if (false == ret) {
            retJsonObject.put("message", "failed");
        }

        return retJsonObject;
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
