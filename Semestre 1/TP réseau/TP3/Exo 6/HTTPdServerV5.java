import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ThreadLocalRandom;

public class HTTPdServerV5 {

    public static void main(String[] args){

        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
            serverSocket.setSoTimeout(10000);
        }
        catch(IOException e){
            System.err.println("Le port spécifié n'est pas disponible.");
            return;
        }
        
        System.err.println("Instance du server est lancé sur le port " + port);
    
        try(
            Socket clientSocket = serverSocket.accept();
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        )
        {
            while (true) {       
                System.err.println("écoute...");

                String filename;
                String inReq = in.readLine();
                if(inReq.split("/")[1].startsWith(" ")){
                    int randomNum = ThreadLocalRandom.current().nextInt(0, 1 + 1);
                    if(randomNum == 1){
                        filename = "chromium.html";
                    }else{
                        filename = "iceweasel.html";
                    }
                }else {
                    filename = inReq.split("/")[1].split(" ")[0];     
                }
                System.out.printf("Nom du fichier chargé :%s \n", filename);          
                InputStream indexFile = new FileInputStream(filename);

                byte[] buffer=new byte[4096];
                int size;
                String fileString;

                out.write("HTTP/1.0 200 OK\r\n");
                out.write("Server: HandMade ESIEA\r\n");
                out.write("Content-Type: text/html\r\n");
                out.write("Content-Length: 59\r\n");
                out.write("\r\n");

                while ((size = indexFile.read(buffer)) > 0){
                    fileString = new String(buffer, StandardCharsets.UTF_8);
                    out.write(fileString, 0, size);
                }
                indexFile.close();
                
                System.err.println("Fin de communication.");
                in.close();
                out.close();
                clientSocket.close();
            }
        }
        catch(Exception e) {
            System.err.printf("Fermeture de la session du server : \n%s", e);
            try {
                serverSocket.close();
            }
            catch(IOException y){
                System.err.println("Erreur lors de la fermeture du server");
            }
            
        }
        
    }
}
