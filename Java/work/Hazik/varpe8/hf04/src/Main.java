import vp.game.*;
import vp.net.*;

public class Main
{
    public static void main(String[] args) throws Exception
    {
        Message message = new Message();
        ClientEngine client_engine = new ClientEngine(message);
        ClientGUI.addMessage(message); // Messaget elöbb kell átadni mint a GUI szálat indítani
        ClientGUI.main(args);
    }
}