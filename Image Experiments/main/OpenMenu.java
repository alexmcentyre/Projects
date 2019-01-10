package cs1302.p2;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;

import javafx.embed.swing.SwingFXUtils;
import javafx.geometry.Insets;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuItem;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;

public class OpenMenu extends Menu{
	
	/**
	 * This constructs a menu for opening images
	 * 
	 * @param a Image pane 1
	 * @param b Image pane 2
	 * @param c Image pane 3
	 */
	public OpenMenu(ImagePane a, ImagePane b,ImagePane c){	
	super("Open");
	MenuItem OpenImage1 = new MenuItem("Open Image 1");
	MenuItem OpenImage2 = new MenuItem("Open Image 2");
	getItems().add(OpenImage1);
	getItems().add(OpenImage2);
	
	OpenImage1.setOnAction(event -> {
	a.openImage();
	
	});
	OpenImage2.setOnAction(event -> {	
  	b.openImage();
		
	});
	
	
}
	
	

	
	
}
