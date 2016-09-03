/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package demo_jni;

/**
 *
 * @author Yen
 */
public class Main {
    
    static{
        System.load("C:\\Users\\Yen\\Desktop\\JNI\\Demo_JNILib\\dist\\Demo_JNI.dll");
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Main().sayHelloWorld();
    }
    private native void sayHelloWorld();
}
