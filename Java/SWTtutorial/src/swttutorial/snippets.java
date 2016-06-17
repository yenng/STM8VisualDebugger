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
import org.eclipse.swt.widgets.*;

public class snippets {

public static void main (String [] args) {
	Display display = new Display ();
	Shell shell = new Shell(display);
	shell.open ();
	while (!shell.isDisposed ()) {
		if (!display.readAndDispatch ()) display.sleep ();
	}
	display.dispose ();
}
}
