/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package swttutorial;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
/**
 *
 * @author Yen
 */
public class MnemonicEx {

    public MnemonicEx(Display display) {

        initUI(display);
    }
    
    private void initUI(Display display) {
        
        Shell shell = new Shell(display, SWT.SHELL_TRIM | SWT.CENTER);
        RowLayout layout = new RowLayout();
        layout.marginLeft = 30;
        layout.marginTop = 30;
        layout.marginBottom = 150;
        layout.marginRight = 150;
        
        shell.setLayout(layout);
        
        Button btn = new Button(shell, SWT.PUSH);
        btn.setText("&Button");
        btn.setLayoutData(new RowData(80, 30));
        btn.addListener(SWT.Selection, event -> System.out.println("Button clicked"));

        shell.setText("Mnemonic");
        shell.pack();
        shell.open();
        
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch())
                display.sleep();
        }        
    }
    
    @SuppressWarnings("unused")
    public static void main(String[] args) {

        Display display = new Display();
        MnemonicEx ex = new MnemonicEx(display);
        display.dispose();
    }
}
