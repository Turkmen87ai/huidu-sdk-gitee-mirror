package cn.huidu.device.sdk.data.program.area.content;

import com.alibaba.fastjson.annotation.JSONField;

import cn.huidu.device.sdk.data.program.other.FileInfo;

public class VideoNode extends ContentNode {
    private String localPath;
    private String file;
    private int fileSize;
    private String fileMd5;
    private Boolean aspectRatio;

    public VideoNode() {
        super();
        setType("video"); // Video content
        aspectRatio = false; // Default value: false
    }

    public VideoNode(String localPath) {
        this();
        this.localPath = localPath;
    }

    public VideoNode(String url, int fileSize, String fileMd5) {
        this(url);
        this.fileSize = fileSize;
        this.fileMd5 = fileMd5;
    }

    public VideoNode(String url, int fileSize, String fileMd5, Boolean aspectRatio) {
        this(url, fileSize, fileMd5);
        this.aspectRatio = aspectRatio;
    }

    public VideoNode(String localPath, Boolean aspectRatio) {
        this(localPath);
        this.aspectRatio = aspectRatio;
    }

    public VideoNode(VideoNode other) {
        super(other);
        this.localPath = other.localPath;
        this.file = other.file;
        this.fileSize = other.fileSize;
        this.fileMd5 = other.fileMd5;
        this.aspectRatio = other.aspectRatio;
    }

    @Override
    @JSONField(serialize = false)
    public FileInfo[] getFilesInfo() {

        FileInfo fileInfo = new FileInfo(localPath);
        fileInfo.md5 = fileMd5;
        fileInfo.size = fileSize;
        fileInfo.url = file;
        return new FileInfo[] { fileInfo };
    }

    @Override
    public void updateFilesInfo(FileInfo[] filesinfo) {

        FileInfo locfileInfo = new FileInfo(localPath);
        for (FileInfo fileInfo : filesinfo) {
            if (locfileInfo.equals(fileInfo)) {
                fileMd5 = fileInfo.md5;
                fileSize = fileInfo.size;
                file = fileInfo.url;
                break;
            }
        }
    }

    public String getFile() {
        return file;
    }

    public void setFile(String file) {
        this.file = file;
    }

    public int getFileSize() {
        return fileSize;
    }

    public void setFileSize(int fileSize) {
        this.fileSize = fileSize;
    }

    public String getFileMd5() {
        return fileMd5;
    }

    public void setFileMd5(String fileMd5) {
        this.fileMd5 = fileMd5;
    }

    public Boolean getAspectRatio() {
        return aspectRatio;
    }

    public void setAspectRatio(Boolean aspectRatio) {
        this.aspectRatio = aspectRatio;
    }
}
