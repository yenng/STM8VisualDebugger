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
import org.eclipse.swt.graphics.*;
import org.eclipse.swt.widgets.*;

public class listSnippet {

public static void main (String [] args) {
	Display display = new Display ();
	Shell shell = new Shell (display);
	final List list = new List (shell, SWT.BORDER | SWT.MULTI | SWT.V_SCROLL);
	for (int i=0; i<=10; i++) list.add ("Item " + i);
	Rectangle clientArea = shell.getClientArea ();
	list.setBounds (clientArea.x, clientArea.y, 100, 100);
	list.addListener (SWT.Selection, e -> {
		String string = "";
		int [] selection = list.getSelectionIndices ();
		for (int i=0; i<selection.length; i++) string += selection [i] + " ";
		System.out.println ("Selection={" + string + "}");
	});
	list.addListener (SWT.DefaultSelection, e -> {
		String string = "";
		int [] selection = list.getSelectionIndices ();
		for (int i=0; i<selection.length; i++) string += selection [i] + " ";
		System.out.println ("DefaultSelection={" + string + "}");
	});
	shell.pack ();
	shell.open ();
	while (!shell.isDisposed ()) {
		if (!display.readAndDispatch ()) display.sleep ();
	}
	display.dispose ();
}
}