/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package readfile;

/**
 *
 * @author Yen
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Paths;

public class ReadFile {
    public static void main(String[] args) throws Exception{
        // TODO code application logic here
        FileReader in = null;
        String  thisLine = null;
        try{
           // open input stream test.txt for reading purpose.
           in = new FileReader("acia.ls");
           BufferedReader br = new BufferedReader(in);
           while ((thisLine = br.readLine()) != null) {
              System.out.println(thisLine);
           }       
        }catch(Exception e){
           e.printStackTrace();
        }
    }
    
}
