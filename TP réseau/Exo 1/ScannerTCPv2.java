import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class ScannerTCPv2 {

    public static int []openPorts = new int[81];
    public static String remoteHost;

    public static boolean isRemotePortAvailable(int port){
        try {
            (new Socket(remoteHost, port)).close();
            return true;
        }
        catch(IOException e){
            return false;
        }
    }

    public static void main(String []args){
        int [] portList = java.util.stream.IntStream.rangeClosed(0, openPorts.length).toArray();
        remoteHost = "149.62.158.51";
        System.out.printf("Voici les ports ouverts :\n");

        for(int i = 0; i < portList.length; i++ ){
            if(isRemotePortAvailable(i)){
                openPorts[i] = portList[i];
                System.out.printf("%d Open\n", i);
            }
        }
    }
}