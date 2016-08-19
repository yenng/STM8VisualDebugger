/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package visual.debugger;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;

/**
 *
 * @author Yen
 */
public class VisualDebugger {
     

public static void main (String [] args) throws Exception {
    Display display = new Display( );
    Shell shell = new Shell(display);
    Shell s = new Shell(shell);
    Shell s1 = new Shell(shell);
    HashMap<String, String> lineNo = new HashMap<>();
    HashMap<String, ArrayList> lineNo1 = new HashMap<>();
    Table t = new Table(s, SWT.MULTI|SWT.BORDER|SWT.FULL_SELECTION);
    Table t1 = new Table (s1, SWT.MULTI | SWT.BORDER | SWT.FULL_SELECTION);
    Color blue = display.getSystemColor(SWT.COLOR_BLUE);
    shell.setSize(500,500);
    Button Astep = new Button (shell, SWT.PUSH);
    Astep.setText ("Assembly Step");
    Astep.addSelectionListener(new SelectionAdapter() {
            @Override
            public void widgetSelected(SelectionEvent e) {
                int Aline = t1.getSelectionIndex();
                if(Aline<0)
                    t1.setSelection(0);
                else
                    t1.setSelection(++Aline);
                new SelectAssembly(t1,t,lineNo,lineNo1);
            }
    });
    Button close = new Button (shell, SWT.PUSH);
    close.setText ("Close");
    close.addSelectionListener(new SelectionAdapter() {
            @Override
            public void widgetSelected(SelectionEvent e) {
                display.dispose ();
            }
    });
    shell.setDefaultButton (close);
    shell.setLayout (new RowLayout ());
    
    
    
    
    shell.open( );
    
    new DisplayC("Acia.c",shell,s,t);
    new DisplayAssembly("acia.ls",shell,s1,t1,lineNo,lineNo1);
    
    
    
    t.addListener (SWT.Selection, e -> {
            String string = "";
            TableItem [] selection = t.getSelection ();
            for (int i=0; i<selection.length; i++) 
                string += selection [i];
            String lineC = string.substring(11,string.length()-1);
            
            
    });
    
    //press on the assembly code.
    t1.addListener (SWT.Selection, e -> {
        TableItem item = (TableItem)e.item;
        item.setBackground(blue);
        new SelectAssembly(t1,t,lineNo,lineNo1);
    });
    t1.addListener (SWT.DefaultSelection, e -> {
        new SelectAssembly(t1,t,lineNo,lineNo1);
    });
    
    t1.setSelection(0);
    s.open();
    s1.open();
    while (!shell.isDisposed ()) {
            if (!display.readAndDispatch ()) display.sleep ();
    }
    display.dispose ();
}

    private static class SelectAssembly {
        public SelectAssembly(Table AssemblyTable, Table CTable, HashMap<String, String> lineNo,HashMap<String, ArrayList> lineNo1) {
            String string = "";
            TableItem [] selection = AssemblyTable.getSelection ();
            int Aline = AssemblyTable.getSelectionIndex();
            for (int i=0; i<selection.length; i++) 
                string += selection [i];
            String lineAssembly = string.substring(11,string.length()-1);
            String lineC = lineNo.get(lineAssembly);
            
            ArrayList x = lineNo1.get(lineC);
            int index = x.indexOf(lineAssembly);
            int size = x.size()-index-1;
            
            AssemblyTable.select(Aline-index,Aline+size);
            //if(lineAssembly==lineNo1.get(lineC).assemblyLine)
            //int index = AssemblyTable.getSelectionIndex();
            //System.out.println (lineAssembly + "," + lineC +","+ index);
            CTable.setSelection(Integer.parseInt(lineC)-1);
        }
    }
}