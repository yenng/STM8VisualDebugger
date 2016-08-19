/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package visual.debugger;

import java.io.BufferedReader;
import java.io.FileReader;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;
/**
 *
 * @author Yen
 */
public class NewMain {

  Display d;

  Shell s;

  NewMain() {
    String fileNameC = "Acia.c";
    FileReader inC = null;
    String thisLine = null;
    int i = 1;
    d = new Display();
    s = new Shell(d);

    
    
    s.setText(fileNameC);
    s.setLayout(new GridLayout());

    Table t = new Table(s, SWT.MULTI|SWT.BORDER|SWT.FULL_SELECTION);
    GridData data = new GridData(SWT.FILL,SWT.FILL,true,true);
    data.heightHint = 200;
    t.setLayoutData(data);
    
    String[] titles = {"No","C code"};
    for(int j = 0; j<2;j++){
        TableColumn tc = new TableColumn(t, SWT.NONE);
        tc.setText(titles[j]);
    }
    t.setHeaderVisible(false);
    t.setLinesVisible(false);
    
    try{
        inC = new FileReader(fileNameC);
        BufferedReader br = new BufferedReader(inC);
        while((thisLine = br.readLine())!= null){
            System.out.println(thisLine);
            TableItem item = new TableItem(t, SWT.NONE);
            item.setText(new String[]{ i+"","\t"+thisLine});
            i++;
        }
    }catch(Exception e){
        e.printStackTrace();
    }
    for(i=0;i<2;i++){
        t.getColumn(i).pack();
    }
    s.pack();
    s.open();
    while (!s.isDisposed()) {
      if (!d.readAndDispatch())
        d.sleep();
    }
    d.dispose();
  }

  public static void main(String[] argv) {
    new NewMain();
  }

}

