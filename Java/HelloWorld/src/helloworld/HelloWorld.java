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
    public static final String EXAMPLE_TEST = "This is my small example "
      + "string which I'm going to " + "use for pattern matching.";

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String line = "_xdyjp_bn_qnp_00:00:05,94_00:00:11,41 xD";
        String phoneNo = "0111 1223365";
        String pattern = "(.*?)(\\d.*?)\\s(.*)";
        String pattern1 = "(\\d*?)\\s(.*)";
        
        Pattern r = Pattern.compile(pattern);
        Pattern r1 = Pattern.compile(pattern1);
        
        //using matcher to split the lines.
        Matcher m1 = r1.matcher(phoneNo);
        Matcher m = r.matcher(line);
        if (m.find( )) {
           System.out.println("Found value: " + m.group(1) );
           System.out.println("Found value: " + m.group(2) );
           System.out.println("Found value: " + m.group(3) );
        }
        if (m1.find()){
            System.out.println("Phone Number front  : " + m1.group(1));
            System.out.println("Phone Number back   : " + m1.group(2));
        }
        //split the sentence to words
        if(EXAMPLE_TEST.matches("\\w.*")){
            String[] splitString = (EXAMPLE_TEST.split("\\s+"));
            for(int i = 0; i < splitString.length; i++){
                System.out.println(splitString[i]);
            }
        }
        //replace all whitespae with tab
        System.out.println(EXAMPLE_TEST.replaceAll("\\s+", "\t"));
      }
}
