/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package swttutorial;

/**
 *
 * @author Yen
 */
import org.eclipse.swt.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class createTable {

public static void main (String [] args) throws Exception {
        FileReader in = null;
        String  thisLine = null;
	Display display = new Display ();
	Shell shell = new Shell (display);
	shell.setLayout(new GridLayout());
	Table table = new Table (shell, SWT.MULTI | SWT.BORDER | SWT.FULL_SELECTION);
	table.setLinesVisible (false);
	table.setHeaderVisible (false);
	GridData data = new GridData(SWT.FILL, SWT.FILL, true, true);
	data.heightHint = 200;
        
        //pattern will detect {integers, " ", integers, " ", heximal, " ", Assembly code, " ", variable.}
        String pattern = "(\\d+)(\\s+)(\\d+)(\\s+)([0-9a-fA-F]+)(\\s+)(\\w+)(\\s)(\\S+)";
        String pattern1 = "(\\d+)(\\s+);(.+)";
	Pattern r = Pattern.compile(pattern);
	Pattern r1 = Pattern.compile(pattern1);//get the C code location to link to assembly code location
        
        table.setLayoutData(data);
        
	String[] titles = {"Column 0", "Column 1", "Column 2", "Column 3","Column4"};
	for (int i=0; i<titles.length; i++) {
		TableColumn column = new TableColumn (table, SWT.NONE);
		column.setText (titles [i]);
        }
        try{
           // open input stream test.txt for reading purpose.
           in = new FileReader("acia.ls");
           BufferedReader br = new BufferedReader(in);
           while ((thisLine = br.readLine()) != null) {
               String[] C_Add = thisLine.split(";");
               Matcher m = r.matcher(thisLine);
               Matcher m1 = r1.matcher(thisLine);
               //System.out.println(thisLine);
               /*
               if(m1.find()){
                   System.out.println(m1.group(0));
               }
                */
               if(m.find()){
                    //System.out.println(m.group(0));
                    String[] part = m.group().split("(\\s+)");
                    TableItem item = new TableItem (table, SWT.NONE);
                    for (int i = 0; i<5;i++)
                        item.setText (i, part[i]);
                    //System.out.println("");
               }
           }       
        }catch(Exception e){
           e.printStackTrace();
        }
        for (int i=0; i<titles.length; i++) {
                table.getColumn (i).pack ();
        }
	shell.pack ();
	shell.open ();
	while (!shell.isDisposed ()) {
		if (!display.readAndDispatch ()) display.sleep ();
	}
	display.dispose ();
    }
} 
