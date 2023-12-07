package cn.huidu.device.api.sdk.data.program.area.content;

import cn.huidu.device.api.sdk.data.program.other.Effect;
import cn.huidu.device.api.sdk.data.program.other.FileInfo;

public class ImageNode extends ContentNode {
    private String localPath;
    private String file;
    private int fileSize;
    private String fileMd5;
    private Effect effect;
    private Fit fit;

    public ImageNode() {
        super();
        setType("image");   // 图片内容
        fit = Fit.stretch;      // 默认值：stretch
    }
    
    public ImageNode(String localPath) {
        this();
        this.localPath = localPath;
    }

    public ImageNode(String localPath, Fit fit) {
        this(localPath);
        this.fit = fit;
    }

    public ImageNode(String url, int fileSize, String fileMd5) {
        this(url);
        this.fileSize = fileSize;
        this.fileMd5 = fileMd5;
    }

    public ImageNode(String url, int fileSize, String fileMd5, Fit fit) {
        this(url, fileSize, fileMd5);
        this.fit = fit;
    }

    public ImageNode(ImageNode other) {
        super(other);
        this.localPath = other.localPath;
        this.file = other.file;
        this.fileSize = other.fileSize;
        this.fileMd5 = other.fileMd5;
        this.effect = other.effect;
    }


    public enum Fit {
        fill("fill"), ///< 填充，先将图片等比放大能覆盖完整区域的比例，再截取中间部分显示。
        center("center"), ///< 居中，将图片等比缩小至区域大小，比例不一致时会显示黑边
        stretch("stretch"), ///< 拉伸，可能导致图片变形
        tile("tile"); ///< 平铺

        private final String value;

        public String getValue() {
            return value;
        }

        Fit(String value) {
            this.value = value;
        }
    }
    
    @Override
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

    public Effect getEffect() {
        return effect;
    }

    public void setEffect(Effect effect) {
        this.effect = effect;
    }

    public Fit getFit() {
        return fit;
    }

    public void setFit(Fit fit) {
        this.fit = fit;
    }
}
