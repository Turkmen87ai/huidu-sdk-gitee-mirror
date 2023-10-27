package cn.huidu.device.api.sdk.data.program.other;

import java.nio.file.Path;
import java.nio.file.Paths;

public class FileInfo {
    public String localFile;
    public String url;
    public int size;
    public String md5;

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }

        FileInfo Info = (FileInfo) obj;
        Path p1 = Paths.get(localFile);
        Path p2 = Paths.get(Info.localFile);

        return p1.equals(p2);
    }
}
