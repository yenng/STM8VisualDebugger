/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package visual.debugger;

import java.util.ArrayList;
import java.util.HashMap;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableItem;

/**
 *
 * @author Yen
 */
class SelectAssembly {

    public static void SelectAssembly(Table AssemblyTable,TableItem item, Table CTable, HashMap<String, String> lineNo
    ,HashMap<String,ArrayList> lineNo1,Color gray) {
        String string = "";
        int Aline = AssemblyTable.getSelectionIndex();
        System.out.println(Aline);
        TableItem [] selection = AssemblyTable.getSelection ();
        for (int i=0; i<selection.length; i++) 
            string += selection [i];
        String lineAssembly = string.substring(11,string.length()-1);
        String lineC = lineNo.get(lineAssembly);
        
        ArrayList x = lineNo1.get(lineC);
        int selectNo = x.size();
        int y = x.indexOf(lineAssembly);
        int down = selectNo-y;
        while(selectNo>0){
            selectNo--;
            int k = selectNo;
            while(down>0){
               // item.setForeground(Aline-down, gray);
                down--;
            }
            while(k>0){
               // item.setForeground(Aline+k,gray);
                k--;
            }
            //item.setForeground(Aline,gray);
        }
        //System.out.println (lineAssembly + "," + lineC +","+ index);
        CTable.setSelection(Integer.parseInt(lineC)-1);
        }

    SelectAssembly(Table t1, TableItem item, Table t, HashMap<String, String> lineNo, HashMap<String, ArrayList> lineNo1) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    
}
