/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package visual.debugger;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author Yen
 */
public class GetAddress {
    public GetAddress() {}
    public static void GetAddress(String thisLine) throws Exception{
        String findAddName = "(\\d+)(.+)switch(\\s+)(\\S+)";
        Pattern r = Pattern.compile(findAddName);
        
        try{
            Matcher m = r.matcher(thisLine);
            if(m.find()){
                int length = Integer.parseInt(m.group(5));
                int start = Integer.parseInt(m.group(2));

                //System.out.println(mAddItem.group(8));
            }
            
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
