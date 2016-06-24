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
	table.setLinesVisible (true);
	table.setHeaderVisible (true);
	GridData data = new GridData(SWT.FILL, SWT.FILL, true, true);
	data.heightHint = 200;
        
        //pattern will detect {integers, " ", integers, " ", 
        String pattern = "(\\d+)(\\s+)(\\d+)(\\s+)(\\w+)(\\s+)(\\w+)(\\s+)";
	Pattern r = Pattern.compile(pattern);
        
        table.setLayoutData(data);
	String[] titles = {"Column 0", "Column 1", "Column 2", "Column 3"};
	for (int i=0; i<titles.length; i++) {
		TableColumn column = new TableColumn (table, SWT.NONE);
		column.setText (titles [i]);
        }
        try{
           // open input stream test.txt for reading purpose.
           in = new FileReader("acia.ls");
           BufferedReader br = new BufferedReader(in);
           while ((thisLine = br.readLine()) != null) {
              Matcher m = r.matcher(thisLine);
              //System.out.println(thisLine);
              if(m.find()){
                //System.out.println(m.group(0));
                String[] part= m.group().split("(\\d+)(\\s+)(\\d+)(\\s+)(\\w+)(\\s+)(\\w+)");	
              }
           }       
        }catch(Exception e){
           e.printStackTrace();
        }
	for (int i=0; i<10; i++) {
		TableItem item = new TableItem (table, SWT.NONE);
		item.setText (0, "a"+i+"0");
		item.setText (1, "a"+i+"1");
		item.setText (2, "a"+i+"2");
		item.setText (3, "a"+i+"3");
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
