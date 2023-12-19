package cn.huidu.device.api.sdk;

import java.util.ArrayList;
import cn.huidu.device.api.sdk.common.BaseClient;
import cn.huidu.device.api.sdk.data.program.ProgramNode;

public class Program extends BaseClient {
    private Object dataEx = null;

    public void setDataEx(Object obj) {
        dataEx = obj;
    }
    
    public String append(String[] id, ProgramNode programNode) {
        return append(id, new ProgramNode[] {programNode});
    }

    public String append(String[] id, ProgramNode[] programNodes) {
        return super.program(id, "append", programNodes, dataEx);
    }

    public String update(String[] id, ProgramNode programNode) {
        return update(id, new ProgramNode[] {programNode});
    }
    public String update(String[] id, ProgramNode[] programNodes) {
        return super.program(id, "update", programNodes, dataEx);
    }

    public String replace(String[] id, ProgramNode programNode) {
        return replace(id, new ProgramNode[] { programNode });
    }
    
    public String replace(String[] id, ProgramNode[] programNodes) {
        return super.program(id, "replace", programNodes, dataEx);
    }

    public String remove(String[] id, String[] programIds) {

        ArrayList<ProgramNode> programNodes = new ArrayList<>();
        for (String programId : programIds) {
            ProgramNode node = new ProgramNode();
            node.setId(programId);
            programNodes.add(node);
        }
        
        return super.program(id, "remove", programNodes.toArray(new ProgramNode[programNodes.size()]), dataEx);
    }

    public String getProgramIds(String[] id) {
        return super.program(id, "getAll", null, null);
    }

}
