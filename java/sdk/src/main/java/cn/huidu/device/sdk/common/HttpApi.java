package cn.huidu.device.sdk.common;

import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpRequestBase;
import org.apache.http.entity.ContentType;
import org.apache.http.entity.StringEntity;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import com.alibaba.fastjson.JSONObject;

import java.io.File;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Date;
import java.util.UUID;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class HttpApi {
    private String sdkKey = null;
    private String sdkSecret = null;
    private String devApiUrl = null;
    private String fileApiUrl = null;
    private String programApiUrl = null;

    // Environment initialization
    protected HttpApi() {
        this.sdkKey = Config.sdkKey;
        this.sdkSecret = Config.sdkSecret;
        this.devApiUrl = Config.host + "/api/device/";
        this.fileApiUrl = Config.host + "/api/file/";
        this.programApiUrl = Config.host + "/api/program/";
    }

    protected HttpApi(String hostUrl) {
        this.sdkKey = Config.sdkKey;
        this.sdkSecret = Config.sdkSecret;
        this.devApiUrl = hostUrl + "/api/device/";
        this.fileApiUrl = hostUrl + "/api/file/";
        this.programApiUrl = hostUrl + "/api/program/";
    }

    protected String deviceList() {
        String apiUrl = devApiUrl + "list/";
        return get(apiUrl);
    }

    protected String device(String body) {
        return post(devApiUrl, body);
    }

    protected String program(String body) {
        return post(programApiUrl, body, 60);
    }

    protected String uploadFile(String filePath) {
        return file(filePath);
    }

    private String file(String filePath) {

        File locFilePath = new File(filePath);
        if (false == locFilePath.exists()) {
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("message", "failed");
            jsonObject.put("data", "Not found file [" + filePath + "]");
            return jsonObject.toString();
        }

        String errString = null;
        String responseString = null;
        try (CloseableHttpClient httpClient = HttpClients.createDefault()) {
            Path path = Paths.get(filePath);
            File fileToUpload = path.normalize().toFile();
            String fileName = fileToUpload.getName();
            if (fileName != null) {
                try {
                    fileName = URLEncoder.encode(fileName, "UTF-8");
                } catch (Exception e) {
                } finally {
                }
            }

            HttpPost httpRequest = new HttpPost(this.fileApiUrl);
            // Sign
            signHeader(httpRequest, null);

            // Build multipart request entity
            MultipartEntityBuilder builder = MultipartEntityBuilder.create();
            builder.addPart("file", new FileBody(fileToUpload, ContentType.DEFAULT_BINARY, fileName));

            HttpEntity multipart = builder.build();
            httpRequest.setEntity(multipart);

            // Execute request and get response
            CloseableHttpResponse response = httpClient.execute(httpRequest);
            try {
                HttpEntity responseEntity = response.getEntity();
                if (responseEntity != null) {
                    responseString = EntityUtils.toString(responseEntity);
                }
            } catch (Exception e) {
                errString = e.toString();
            } finally {
                response.close();
            }
        } catch (Exception e) {
            errString = e.toString();
        } finally {
            if (null == responseString || responseString.length() == 0) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("message", "failed");
                jsonObject.put("data", errString);
                responseString = jsonObject.toString();
            }
        }

        return responseString;
    }

    private String post(String hostUrl, String body) {
        return post(hostUrl, body, 0);
    }

    private String post(String hostUrl, String body, int timeoutMs) {

        String errString = null;
        String responseString = null;
        try (CloseableHttpClient httpClient = HttpClients.createDefault()) {

            HttpPost httpRequest = new HttpPost(hostUrl);
            // Server response timeout
            if (timeoutMs > 0) {
                httpRequest.addHeader("timeout", Integer.toString(timeoutMs));
            }

            // Sign
            signHeader(httpRequest, body);

            // Build JSON request entity
            StringEntity stringEntity = new StringEntity(body, ContentType.APPLICATION_JSON);
            httpRequest.setEntity(stringEntity);

            // Execute request and get response
            CloseableHttpResponse response = httpClient.execute(httpRequest);
            try {
                HttpEntity responseEntity = response.getEntity();
                if (responseEntity != null) {
                    responseString = EntityUtils.toString(responseEntity);
                }
            } catch (Exception e) {
                errString = e.toString();
            } finally {
                response.close();
            }
        } catch (Exception e) {
            errString = e.toString();
        } finally {
            if (null == responseString || responseString.length() == 0) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("message", "failed");
                jsonObject.put("data", errString);
                responseString = jsonObject.toString();
            }
        }

        return responseString;
    }

    private String get(String hostUrl) {

        String errString = null;
        String responseString = null;
        try (CloseableHttpClient httpClient = HttpClients.createDefault()) {

            HttpGet httpRequest = new HttpGet(hostUrl);
            // Sign
            signHeader(httpRequest, null);
            CloseableHttpResponse response = httpClient.execute(httpRequest);
            try {
                HttpEntity responseEntity = response.getEntity();
                if (responseEntity != null) {
                    responseString = EntityUtils.toString(responseEntity);
                }
            } catch (Exception e) {
                errString = e.toString();
            } finally {
                response.close();
            }
        } catch (Exception e) {
            errString = e.toString();
        } finally {
            if (null == responseString || responseString.length() == 0) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("message", "failed");
                jsonObject.put("data", errString);
                responseString = jsonObject.toString();
            }
        }

        return responseString;
    }

    private Boolean signHeader(HttpRequestBase httpRequest, String body) {
        if (null == httpRequest) {
            return false;
        }

        // Generate unique identifier
        UUID uuid = UUID.randomUUID();
        String cuid = uuid.toString();
        httpRequest.addHeader("requestId", cuid);
        // Set sdkKey header field
        httpRequest.addHeader("sdkKey", this.sdkKey);
        // Add time header field
        Date date = new Date();
        httpRequest.addHeader("date", date.toString());
        // Add signature header field
        if (null == body) {
            httpRequest.addHeader("sign", hmacmd5(this.sdkKey + date.toString(), this.sdkSecret));
        } else {
            httpRequest.addHeader("sign", hmacmd5(body + this.sdkKey + date.toString(), this.sdkSecret));
        }

        return true;
    }

    private String hmacmd5(String data, String key) {
        String md5Hash = null;
        try {
            // Convert key to byte array
            byte[] keyBytes = key.getBytes(StandardCharsets.UTF_8);

            // Create HMAC-MD5 algorithm instance and initialize with key
            Mac hmacMD5 = Mac.getInstance("HmacMD5");
            SecretKeySpec keySpec = new SecretKeySpec(keyBytes, "HmacMD5");
            hmacMD5.init(keySpec);

            // Convert data to byte array
            byte[] dataBytes = data.getBytes(StandardCharsets.UTF_8);

            // Calculate HMAC-MD5
            byte[] hmacResult = hmacMD5.doFinal(dataBytes);

            // Convert result to hexadecimal string representation
            StringBuilder sb = new StringBuilder();
            for (byte b : hmacResult) {
                sb.append(String.format("%02x", b));
            }
            md5Hash = sb.toString();
        } catch (Exception e) {
        }

        return md5Hash;
    }

}
