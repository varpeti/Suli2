package vp.game;

import vp.net.Message;
import vp.game.GUI.Scenes;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.animation.Animation;
import javafx.util.Duration;
import javafx.stage.Stage;

import java.util.*;

public class ClientGUI extends Application
{
    static private Message message;
    static private Stage stage;

    static private class checkMSG implements EventHandler<ActionEvent>
    {
        private Message message;

        private void handle(Message.Packet input)
        {
            System.out.println("LOG.ClientGUI.handle: "+input.getMsg());
    
            ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");
            
            if (Objects.equals(cmd.get(0),"timeout"))
            {
                stage.setScene(Scenes.mainmenu());
            }
            else if (Objects.equals(cmd.get(0),"pong") && Objects.equals(cmd.get(1),"game"))
            {
                if (!Objects.equals(Scenes.scene_String,"game")) stage.setScene(Scenes.game());
                Scenes.Game.setTable(input.getMsg());
            }
            else if (Objects.equals(cmd.get(0),"wait4players"))
            {
                if (!Objects.equals(Scenes.scene_String,"pleasewait wait4players")) stage.setScene(Scenes.pleasewait("wait4players"));
                Scenes.pleasewait_str_Text.setText("Waiting for other players to connect ("+cmd.get(2)+"/"+cmd.get(1)+")");
            }
            else if (Objects.equals(cmd.get(0),"error")) 
            {
                if (Objects.equals(cmd.get(1),"gameisfull"))
                {
                    message.socketWrite(new Message.Packet("stop"));
                    stage.setScene(Scenes.mainmenu());
                }
                else if (Objects.equals(cmd.get(1),"setServerInvaildInput"))
                {
                    stage.setScene(Scenes.startserver());
                }

            }
        }

        @Override
        public void handle(ActionEvent e) 
        {
            ArrayList<Message.Packet> input = message.guiRead();

            for (int i=0;i<input.size();i++) 
            {
                handle(input.get(i));
            }
        }

        checkMSG(Message _message)
        {
            message = _message;
        }
    }

    @Override
    public void start(Stage primaryStage) 
    {
        stage = primaryStage;
        Scenes.addStage(stage);

        stage.setTitle("Torpedo by Vp");

        //Message érkezését vizsgálja
        Timeline timeline = new Timeline();
        timeline.setCycleCount(Animation.INDEFINITE);
        KeyFrame keyFrame = new KeyFrame(Duration.seconds(1.0000),new checkMSG(message)); //Másodpercenként nézi
        timeline.getKeyFrames().add(keyFrame);
        timeline.play();

        stage.setScene(Scenes.welcome());
        stage.show();
    }

    @Override
    public void stop()
    {
        System.out.println("LOG.ClientGUI.stop: GUI closed");
        System.exit(0); //TODO ?esteleg egy message a szálaknak, hogy álljanak le és nem kegyetlenül meggyilkolni őket?
    }

    public static void main(String[] args) 
    {
        launch(args);
    }

    static public void addMessage(Message _message)
    {
        message = _message;
        Scenes.addMessage(_message); //Tovább adja
    } 
}