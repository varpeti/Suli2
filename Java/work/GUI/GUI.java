
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.FlowPane;
import javafx.stage.Stage;

/*
 * Kell legyen egy osztály, amely megvalósítja a JavaFX Application-t,
 * ezzel indul el az egész toolkit.
 */
public class GUI extends Application {

  /**
   * Egy gomb az ablakon.
   */
  private Button disabledButton;

  /**
   * Egy eseménykezelő.
   *
   * Eseménykezelők esemény hatására hívódnak meg, ez ActionEvent típusú
   * eseményeket kezel. Az eseménykezelők a JavaFX Application szálon futnak,
   * tehát rövidnek kell lenniük, viszont módosíthatják a GUI felépítését.
   */
  private class MyActionEventHandler implements EventHandler<ActionEvent> {

    @Override
    public void handle(ActionEvent event) {
      // Az event tartalmaz információkat az eseményről
      System.out.println("Look, an event: " + event);
      disabledButton.setText("Oops!");
      disabledButton.setDisable(false);
    }
  }

  /**
   * Egy másik eseménykezelő, ez egéreseményeket képes kezelni.
   */
  private class MyMouseEventHandler implements EventHandler<MouseEvent> {

    @Override
    public void handle(MouseEvent event) {
      // A MouseEvent objektum tartalmazza a kurzor helyét, az esetlegesen
      // megnyomott egérbillentyűt, stb.
      disabledButton.setDisable(true);
      // Ha elfogyasztjuk az eseményt, akkor az eseményt a többi felületelem
      // nem dolgozza fel. Az aktuális objektum összes event handlere és event
      // filtere még meghívódik.
      // Ez itt most nem sokat csinál.
      event.consume();
    }
  }

  @Override
  public void start(Stage primaryStage) throws Exception {
    // Minden JavaFX alkalmazásnak van egy fő ablaka (Stage), ez csak annyiban
    // tér el a többitől, hogy, ha bezáródik, a JavaFX leáll (a program nem
    // feltétlen).
    // A start() metódus a JavaFX Application szálon hívódik meg, itt építhetjük
    // fel a GUI-t.

    // Ez legfelső panel, ez tartalmazza az összes felületelemet.
    FlowPane root = new FlowPane();
    // Kisebb szüneteket hagyunk a gyerekei között
    root.setHgap(10);
    root.setVgap(10);
    // A getChildren() egy List, amely a gyerekeit tartalmazza
    root.getChildren().add(new Label("For those, who didn't recognise me: " +
                                         "I am a label"));
    Button button = new Button("Please don't press me!");
    // Regisztráljuk a button eseménykezelőjét. Ez akkor hívódik meg, amikor
    // megnyomjuk a gombot.
    button.setOnAction(new MyActionEventHandler());
    disabledButton = new Button("I dare you, I double dare you to press me!");
    // JavaFX-ben nem tiltani kell az engedélyezettséget, hanem engedélyezni a
    // gomb megnyomhatatlanságát.
    disabledButton.setDisable(true);
    // Hozzáadunk egy event filtert, ez az összes egéreseményt kezeli.
    disabledButton.addEventFilter(MouseEvent.ANY,new MyMouseEventHandler());
    // Hozzáadjuk a többi felületelemet
    root.getChildren().addAll(button, disabledButton);

    // A Scene az ablak színtérgráfját tartalmazza; itt lehet megadni többek
    // között a méretét az ablaknak, illetve a felületelemek hierarchiájának
    // gyökérpontját
    Scene scene = new Scene(root, 350, 200);
    // Az ablak címének beállítása
    primaryStage.setTitle("What Is the Title of This Window?");
    // A Scene beállítása
    primaryStage.setScene(scene);
    // És végül megjelenítjük az ablakot.
    primaryStage.show();
  }

  public static void main(String[] args) {
    // A launch() indítja el a JavaFX alkalmazást. Nem lehet egynél többször
    // meghívni.
    launch(args);
  }
}
