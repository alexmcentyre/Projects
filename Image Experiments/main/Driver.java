package cs1302.p2;

import java.io.IOException;

import cs1302.effects.Artsy;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
/**
 * This is the driver for this application.
 */
public class Driver extends Application {
	/**
	 * The main method which executes when the application launches.
	 * This method is responsible for the creation and layout of the
	 * graphical user interface
	 */
    @Override
    public void start(Stage stage) throws IOException {
    	VBox root = new VBox();
    	    	
    	ImagePane image1 = new ImagePane("Image 1: ");
    	ImagePane image2 = new ImagePane("Image 2: ");
    	ImagePane image3 = new ImagePane("Result");
    	HBox hb = new HBox();
    	hb.getChildren().addAll(image1,image2,image3);//imagePane
    	
        Vbox vb = new Vbox(image1,image2,image3);// menu, checkers and stripes
   
        root.getChildren().addAll(vb,hb);
        
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Artsy!");
        stage.sizeToScene();
        stage.show();
        
    } // createAndShowGUI

    /**
	 * Launches the GUI application
	 * @param args
	 */
	
    public static void main(String[] args) {
        launch(args);
    } // main

} // Driver