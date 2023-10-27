package cn.huidu.device.api.sdk.data.program.area.content;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;

import cn.huidu.device.api.sdk.data.program.other.FileInfo;

public class VideoNode extends ContentNode {
    private String localPath;
    private String file;
    private int fileSize;
    private String fileMd5;
    private Boolean aspectRatio;

    public VideoNode() {
        super();
        setType("video");      // 视频内容
        aspectRatio = false;        // 默认值：false
    }
    
    public VideoNode(String localPath) {
        this();
        this.localPath = localPath;
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
    public FileInfo[] getFilesInfo() {
        File locFilePath = new File(localPath);
        if (false == locFilePath.exists()) {
            return null;
        }

        FileInfo fileInfo = new FileInfo();
        fileInfo.localFile = localPath;
        fileInfo.md5 = fileMd5;
        fileInfo.size = fileSize;
        fileInfo.url = file;
        return new FileInfo[] { fileInfo };
    }

    @Override
    public void updateFilesInfo(FileInfo[] filesinfo) {
        Path locFilePath = Paths.get(localPath);
        for (FileInfo fileInfo : filesinfo) {
            Path p2 = Paths.get(fileInfo.localFile);
            if (locFilePath.equals(p2)) {
                fileMd5 = fileInfo.md5;
                fileSize = fileInfo.size;
                file = fileInfo.url;
                break;
            }
        }
    }

    public String getLocalPath() {
        return localPath;
    }

    public void setLocalPath(String localPath) {
        this.localPath = localPath;
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
