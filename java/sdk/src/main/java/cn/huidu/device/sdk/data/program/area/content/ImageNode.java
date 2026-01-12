package cn.huidu.device.sdk.data.program.area.content;

import com.alibaba.fastjson.annotation.JSONField;

import cn.huidu.device.sdk.data.program.other.Effect;
import cn.huidu.device.sdk.data.program.other.FileInfo;

public class ImageNode extends ContentNode {
    private String localPath;
    private String file;
    private int fileSize;
    private String fileMd5;
    private Effect effect;
    private Fit fit;

    public ImageNode() {
        super();
        setType("image"); // Image content
        fit = Fit.stretch; // Default value: stretch
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
        fill("fill"), /// < Fill, first scale the image proportionally to cover the entire area, then crop the middle part for display.
        center("center"), /// < Center, scale the image proportionally to fit the area size, black borders will appear if aspect ratio is inconsistent
        stretch("stretch"), /// < Stretch, may cause image distortion
        tile("tile"); /// < Tile

        private final String value;

        public String getValue() {
            return value;
        }

        Fit(String value) {
            this.value = value;
        }
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
