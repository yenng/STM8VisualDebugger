/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package visual.debugger;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
/**
 *
 * @author Yen
 */
public class ExtractAddress {
    
    public ExtractAddress() {}

    public static void ExtractAddress(String file, HashMap addressMap) throws Exception{
        HashMap<String, AddressItem> addMap;
        addMap = addressMap;
        String fileName_t = null;
        String fileName_temp = null;
        //HashMap<String,String> fileNameMap = new HashMap<>();
        //x.put(1, new AddressItem());
        
        //AddressItem myStr = x.get(1);
        //FileReader in = null;
        FileReader in1 = null;
        //String  thisLine = null;
        String  thisLine1 = null;
        //String findAddName = "(\\d+)(.+)switch(\\s+)(\\S+)";
        //group(2) = address starting point, group(5) = length, group(8) = segment name.
        String findAddValue = "start(\\s+)(\\S+)(.+)length(\\s+)(\\d+)(\\s+)section(\\s+)(\\S+)";
        //get the file name.
        String findFileName = "(\\w+).o:";
        //Pattern rAdd = Pattern.compile(findAddName);
        Pattern rAddName = Pattern.compile(findAddValue);
        Pattern rGetFile = Pattern.compile(findFileName);
        try{
            //in = new FileReader(file);
            in1 = new FileReader(file);
            //BufferedReader br = new BufferedReader(in);
            BufferedReader br1 = new BufferedReader(in1);
            //read from map file
            while((thisLine1 = br1.readLine()) != null){
                Matcher mAddItem = rAddName.matcher(thisLine1);
                Matcher mGetFile = rGetFile.matcher(thisLine1);
                if(mGetFile.find()){
                    fileName_t = mGetFile.group(1);
                }
                if(mAddItem.find()){
                    int length = Integer.parseInt(mAddItem.group(5));
                    String start = mAddItem.group(2);
                    fileName_temp = fileName_t+mAddItem.group(8);
                    //System.out.println(fileName_temp);
                    addMap.put(fileName_temp,new AddressItem(start,length));
                }
            }
            /*
            //read from list file
            while ((thisLine = br.readLine()) != null) {
                //thisLine;
                Matcher mAdd = rAdd.matcher(thisLine);
                if(mAdd.find()){
                    int location = Integer.parseInt(mAdd.group(1));
                    realAddMap.put(i,new RealAdd(location,mAdd.group(4)));
                    i++;
                }
            }
*/
            //RealAdd myStr1 = realAddMap.get(0);
            //System.out.println(myStr1.location + "   " + myStr1.segment);
            AddressItem myStr = addMap.get(".text");
            //System.out.println(".text\t" + myStr.length + "\t" + myStr.addr);
            myStr = addMap.get(".bss");
            //System.out.println(".bss\t" + myStr.length + "\t" + myStr.addr);
            
        }catch(Exception e){
            e.printStackTrace();
        }
    }
   
    
}
