package vp.game.GUI;

import vp.net.Message;

import java.util.*;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.util.converter.NumberStringConverter;
import javafx.stage.Stage;
import javafx.beans.value.*;

public class Scenes 
{   
    static private Message message;
    static private Stage stage;
    static public String scene_String;

      //------//
     //Sceens//
    //------//

    //Welcome scene

    static private TextField welcome_name_TextField;

    static private class Welcome_name_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            message.engineWrite(new Message.Packet("setname "+welcome_name_TextField.getText() ));
            stage.setScene(mainmenu());
        }
    }

    static public Scene welcome()
    {
        scene_String = "welcome";
        scene_String = "welcome";
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Welcome");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label name_Label = new Label("User Name:");
        grid.add(name_Label, 0, 1);

        welcome_name_TextField = new TextField();
        grid.add(welcome_name_TextField, 1, 1);
        welcome_name_TextField.setOnAction(new Welcome_name_EventHandler()); //Enter

        Button name_Button = new Button("OK");
        grid.add(name_Button, 2, 1);
        name_Button.setOnAction(new Welcome_name_EventHandler()); //Kattintás

        return new Scene(grid, 1024, 512);
    }

    //Main menu scene

    static private class mainmenu_startserver_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            stage.setScene(startserver());
        }
    }

    static private class mainmenu_joingame_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            stage.setScene(joingame());
        }
    }

    static public Scene mainmenu()
    {
        scene_String = "mainmenu";
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        HBox mainmenu_hbox = new HBox();
        mainmenu_hbox.setAlignment(Pos.CENTER);
        Text mainmenu_Text = new Text("Main Menu");
        mainmenu_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        mainmenu_hbox.getChildren().addAll(mainmenu_Text);
        grid.add(mainmenu_hbox, 0, 0);

        HBox startserver_hbox = new HBox();
        startserver_hbox.setAlignment(Pos.CENTER);
        Button startserver_Button = new Button("Create Game");
        startserver_Button.setOnAction(new mainmenu_startserver_EventHandler());
        startserver_hbox.getChildren().addAll(startserver_Button);
        grid.add(startserver_hbox,0,1);

        HBox joingame_hbox = new HBox();
        joingame_hbox.setAlignment(Pos.CENTER);
        Button joingame_Button = new Button("Join Game");
        joingame_Button.setOnAction(new mainmenu_joingame_EventHandler());
        joingame_hbox.getChildren().addAll(joingame_Button);
        grid.add(joingame_hbox,0,2);

        HBox exit_hbox = new HBox();
        exit_hbox.setAlignment(Pos.CENTER);
        Button exit_Button = new Button("Exit");
        exit_Button.setOnAction(new exit_EventHandler());
        exit_hbox.getChildren().addAll(exit_Button);
        grid.add(exit_hbox,0,3);

        return new Scene(grid, 1024, 512);
    }

    //Start server scene

    static private TextField startserver_players_TextField;
    static private TextField startserver_ship2_TextField;
    static private TextField startserver_ship3_TextField;
    static private TextField startserver_ship4_TextField;
    static private TextField startserver_ship5_TextField;
    static private TextField startserver_port_TextField;

    static private class startserver_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            //Szerver oldalon és ClientEnginben történik az ellenőrzés
            //Ha valaki 80-as porton akarja futtatni, tegye, nem tilos.
            message.engineWrite(new Message.Packet("startserver"
                + " " + startserver_players_TextField.getText()
                + " " + startserver_ship2_TextField.getText() 
                + " " + startserver_ship3_TextField.getText() 
                + " " + startserver_ship4_TextField.getText() 
                + " " + startserver_ship5_TextField.getText()
                + " " + startserver_port_TextField.getText()
            ));

            stage.setScene(pleasewait("Creating server"));
        }
    }

    static public Scene startserver()
    {
        scene_String = "startserver";
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Settings");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label address_Label = new Label("Players:");
        grid.add(address_Label, 0, 1);
        startserver_players_TextField = new TextField("2");
        startserver_players_TextField.textProperty().addListener(new NumberField(startserver_players_TextField));
        grid.add(startserver_players_TextField, 1, 1);

        Label port_Label = new Label("Server port:");
        grid.add(port_Label, 0, 2);
        startserver_port_TextField = new TextField();
        startserver_port_TextField.textProperty().addListener(new NumberField(startserver_port_TextField));
        startserver_port_TextField.setText("3773");
        grid.add(startserver_port_TextField, 1, 2);

        Label ships_Label = new Label("Ships:");
        grid.add(ships_Label, 0, 3, 2, 1);

        Label ship2_Label = new Label("Small (2):");
        grid.add(ship2_Label, 0, 4);
        startserver_ship2_TextField = new TextField("1");
        startserver_ship2_TextField.textProperty().addListener(new NumberField(startserver_ship2_TextField));
        grid.add(startserver_ship2_TextField, 1, 4);

        Label ship3_Label = new Label("Normal (3):");
        grid.add(ship3_Label, 0, 5);
        startserver_ship3_TextField = new TextField("1");
        startserver_ship3_TextField.textProperty().addListener(new NumberField(startserver_ship3_TextField));
        grid.add(startserver_ship3_TextField, 1, 5);

        Label ship4_Label = new Label("Medium (4):");
        grid.add(ship4_Label, 0, 6);
        startserver_ship4_TextField = new TextField("1");
        startserver_ship4_TextField.textProperty().addListener(new NumberField(startserver_ship4_TextField));
        grid.add(startserver_ship4_TextField, 1, 6);

        Label ship5_Label = new Label("Large (5):");
        grid.add(ship5_Label, 0, 7);
        startserver_ship5_TextField = new TextField("1");
        startserver_ship5_TextField.textProperty().addListener(new NumberField(startserver_ship5_TextField));
        grid.add(startserver_ship5_TextField, 1, 7);


        HBox start_hbox = new HBox();
        start_hbox.setAlignment(Pos.CENTER);
        Button start_Button = new Button("Start Server");
        start_Button.setOnAction(new startserver_EventHandler());
        start_hbox.getChildren().addAll(start_Button);
        grid.add(start_hbox,1,8);

        //TODO: win mode

        HBox to_mainmenu_hbox = new HBox();
        to_mainmenu_hbox.setAlignment(Pos.CENTER);
        Button to_mainmenu_Button = new Button("Back");
        to_mainmenu_Button.setOnAction(new to_mainmenu_EventHandler());
        to_mainmenu_hbox.getChildren().addAll(to_mainmenu_Button);
        grid.add(to_mainmenu_hbox,1,9);

        return new Scene(grid, 1024, 512);
    }

    // Joing game scene

    static private TextField joingame_address_TextField;
    static private TextField joingame_port_TextField;

    static private class joingame_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            message.engineWrite(new Message.Packet("startclient"
                + " " + joingame_address_TextField.getText()
                + " " + joingame_port_TextField.getText()
            ));

            stage.setScene(pleasewait("Connecting"));
        }
    }

    static public Scene joingame()
    {
        scene_String = "joingame";
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Settings");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label address_Label = new Label("Ip/Domain:");
        grid.add(address_Label, 0, 1);
        joingame_address_TextField = new TextField("localhost");
        grid.add(joingame_address_TextField, 1, 1);

        Label port_Label = new Label("Port:");
        grid.add(port_Label, 0, 2);
        joingame_port_TextField = new TextField("3773");
        joingame_port_TextField.textProperty().addListener(new NumberField(joingame_port_TextField));
        grid.add(joingame_port_TextField, 1, 2);

        HBox join_hbox = new HBox();
        join_hbox.setAlignment(Pos.CENTER);
        Button join_Button = new Button("Join Game");
        join_Button.setOnAction(new joingame_EventHandler());
        join_hbox.getChildren().addAll(join_Button);
        grid.add(join_hbox,1,3);

        HBox to_mainmenu_hbox = new HBox();
        to_mainmenu_hbox.setAlignment(Pos.CENTER);
        Button to_mainmenu_Button = new Button("Back");
        to_mainmenu_Button.setOnAction(new to_mainmenu_EventHandler());
        to_mainmenu_hbox.getChildren().addAll(to_mainmenu_Button);
        grid.add(to_mainmenu_hbox,1,4);

        return new Scene(grid, 1024, 512);
    }

    // pleasewait sceen

    static public Text pleasewait_str_Text;

    static public Scene pleasewait(String str)
    {
        scene_String = "pleasewait "+str;
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        HBox pleasewait_hbox = new HBox();
        pleasewait_hbox.setAlignment(Pos.CENTER);
        Text pleasewait_Text = new Text("Please wait..."); //TODO animate it: . | .. | ... |
        pleasewait_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        pleasewait_hbox.getChildren().addAll(pleasewait_Text);
        grid.add(pleasewait_hbox, 0, 0);

        HBox str_hbox = new HBox();
        str_hbox.setAlignment(Pos.CENTER);
        pleasewait_str_Text = new Text(str);
        pleasewait_str_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 16));
        str_hbox.getChildren().addAll(pleasewait_str_Text);
        grid.add(str_hbox, 0, 1);

        //TODO Cancel button (nem fontos)
        /*HBox to_mainmenu_hbox = new HBox();
        to_mainmenu_hbox.setAlignment(Pos.CENTER);
        Button to_mainmenu_Button = new Button("Cancel");
        to_mainmenu_Button.setOnAction(new to_mainmenu_EventHandler());
        to_mainmenu_hbox.getChildren().addAll(to_mainmenu_Button);
        grid.add(to_mainmenu_hbox,0,3);*/

        return new Scene(grid, 1024, 512);
    }

    // Game class

    static public class Game
    {
        static public String name = "";
        static public int size = 0;
        static public GridPane grid;

        static public void setTable(String input)
        {
            try
            {
                ArrayList<String> cmd = Message.split(input,"\\s");
                Game.size = Integer.parseInt(cmd.get(2));
                Game.name = cmd.get(3);
                if (!Objects.equals(cmd.get(4),"t:")) return;
                for (int x=0;x<Game.size;x++) 
                {
                    for (int y=0;y<Game.size;y++) 
                    {
                        int i = x*Game.size+y;
                        // 0 water, 1 foo's ship, 2 foo's destoryed ship, 3 your ship, 4 your destroyed ship
                        // TODO: kicserélni szimbólumokra
                        Button button = new Button(cmd.get(i+5)); 
                        button.setId(x+" "+y);
                        button.setOnAction(new game_button_EventHandler());
                        Game.grid.add(button,x,y);
                    }
                }
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
    }

    // Game scene

    static private class game_button_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            Object source = e.getSource();
            if (source instanceof Button) { //should always be true
                Button button = (Button) source;
                System.out.println("LOG.Scenes.game_button_EventHandler: "+button.getId());
            }
        }
    }

    static public Scene game()
    {
        scene_String = "game";
        Game.grid = new GridPane();
        Game.grid.setAlignment(Pos.CENTER);
        Game.grid.setHgap(10);
        Game.grid.setVgap(10);
        Game.grid.setPadding(new Insets(25, 25, 25, 25));


        return new Scene(Game.grid, 1024, 512);
    }

      //------//
     //Events//
    //------//

    //To main menu event

    static private class to_mainmenu_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e)
        {
            stage.setScene(mainmenu());
        }
    }

    //Exit event

    static private class exit_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e)
        {
            System.out.println("LOG.ClientGUI.exit: exit pressed");
            System.exit(0); //TODO ?esteleg egy message a szálaknak, hogy álljanak le és nem kegyetlenül meggyilkolni őket?
        }
    }

    // Number TextField

    static private class NumberField implements ChangeListener<String> 
    {
        private TextField textField;
        @Override
        public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) 
        {
            if (!newValue.matches("\\d+")) 
            {
                textField.setText(newValue.replaceAll("[^\\d]", ""));
            }
        }

        public NumberField(TextField _textField)
        {
            textField = _textField;
        }
    }

      //--------//
     //Settings//
    //--------//

    static public void addMessage(Message _message)
    {
        message = _message;
    }

    static public void addStage(Stage _stage)
    {
        stage = _stage;
    }
}