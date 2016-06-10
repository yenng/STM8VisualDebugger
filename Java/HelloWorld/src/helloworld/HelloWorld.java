/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helloworld;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Yen
 */
public class HelloWorld {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("Hello World!");

     String line = "_xdyjp_bn_qnp_00:00:05,94_00:00:11,41 xD";

  String pattern = "(.*?)(\\d.*?)\\s(.*)";

  Pattern r = Pattern.compile(pattern);

  Matcher m = r.matcher(line);
  if (m.find( )) {
     System.out.println("Found value: " + m.group(1) );
     System.out.println("Found value: " + m.group(2) );
     System.out.println("Found value: " + m.group(3) );
  }
    }
}
