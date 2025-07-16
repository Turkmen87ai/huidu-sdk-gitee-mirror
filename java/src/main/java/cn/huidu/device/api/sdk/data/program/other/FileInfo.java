package cn.huidu.device.api.sdk.data.program.other;

import java.nio.file.Path;
import java.nio.file.Paths;

public class FileInfo {
    public String localFile;
    public String url;
    public int size;
    public String md5;

    public FileInfo(String localFile) {
        size = 0;
        this.localFile = localFile;
    }
    
    @Override
    public boolean equals(Object obj) {

        boolean ret = false;
        try {
            do { 
                if (obj == null) {
                    break;
                }

                if (this == obj) {
                    ret = true;
                    break;
                }

                if (getClass() != obj.getClass()) {
                    break;
                }

                FileInfo Info = (FileInfo) obj;
                if (localFile == Info.localFile && !localFile.isEmpty()) {
                    ret = true;
                    break;
                } 
                
                Path p1 = Paths.get(localFile);
                Path p2 = Paths.get(Info.localFile);
                ret = p1.equals(p2);
                
            } while (false);
        } catch (Exception e) {
            ret = false;
        }

        return ret;
    }
}
