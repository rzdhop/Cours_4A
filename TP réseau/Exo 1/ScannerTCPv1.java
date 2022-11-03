import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class ScannerTCPv1 {

    public static int []openPorts = new int[65535];

    public static boolean isPortAvailable(int port){
        try {
            (new Socket("localhost", port)).close();
            return true;
        }
        catch(Exception e){
            return false;
        }
    }

    public static void main(String []args){
        int [] portList = java.util.stream.IntStream.rangeClosed(1024, openPorts.length).toArray();

        System.out.printf("Voici les ports ouverts :\n");
        for(int i = 0; i < portList.length; i++ ){
            if(isPortAvailable(i)){
                openPorts[i] = portList[i];
                System.out.printf("%d Open\n", i);
            }
        }
    }
}