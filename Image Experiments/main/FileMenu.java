package cs1302.p2;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javafx.application.Platform;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuItem;
import javafx.stage.FileChooser;

/**
 * Class for a file menu in which its constructor is defined
 *
 */


public class FileMenu extends Menu{
	
	
	MenuItem SaveResultAs = new MenuItem("Save Result As");
	MenuItem Exit = new MenuItem("Exit");
	
	/**
	 * Constructs a file menu which allows the user to load
	 * images to the fist and second image panes
	 * 
	 * @param a first image pane
	 * @param b second image pane
	 * @param c result image pane
	 */
	
public FileMenu(ImagePane a, ImagePane b,ImagePane c){
	super("File");
	OpenMenu open  = new OpenMenu(a,b,c);
	
	getItems().add(open);
		
	getItems().add(SaveResultAs);
	SaveResultAs.setOnAction(event -> {
		//Image image  = c.image ; // assume non-empty		
		FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save Image");  
        File file = new File("image.png");
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("PNG","*.png"),
        										new FileChooser.ExtensionFilter("JPG","*.jpg"),
        										new FileChooser.ExtensionFilter("GIF","*.gif"),
        										new FileChooser.ExtensionFilter("BMP","*.bmp"));
        file = fileChooser.showSaveDialog(null);
        if(file != null)
		{      		
		try {
			BufferedImage bImage = SwingFXUtils.fromFXImage(c.image, null);	
			ImageIO.write(bImage, "png", file);
		} catch (IOException e) {
		
		}
	}
	});//SaveResultAs
	getItems().add(Exit);
	Exit.setOnAction(event -> Platform.exit());
	
}
	
	
}
