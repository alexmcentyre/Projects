package cs1302.p2;
import java.io.File;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
/**
 * Class which contains the constructor
 * for image panes
 *
 */
public class ImagePane extends VBox{
	Image image = new Image("file:resources/default.png");
	ImageView iv ;
	Image Oimage = image;
	Label lable1;
	MyArtsy artsy = new MyArtsy();
	/**
	 * Constructor for an image pane which adds
	 * functions such as rotate
	 * 
	 * @param a Provides a string label for the
	 * 			image pane
	 */
	public ImagePane(String a){
		super();		
		Label lable = new Label(a);
		lable1 = new Label(" ");
		
		HBox hb = new HBox();
		hb.getChildren().addAll(lable,lable1);
		iv = new ImageView();
		iv.setImage(image);
		setPadding(new Insets (5));
		Button rotate = new Button("Rotate");
		Button reset = new Button("Reset");
		
		rotate.setOnAction(event ->{
				rotate();
		});			
		reset.setOnAction(event ->{
			image = Oimage;
			iv.setImage(Oimage);		
		});
		setSpacing(10);	
		getChildren().addAll(hb,iv,rotate,reset);
	}
	
	/**
	 * Opens an image using file chooser and then
	 * sets up an image view with that image
	 */
	public void openImage(){	
		FileChooser fileChooser = new FileChooser();
		fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("PNG","*.png"),
												new FileChooser.ExtensionFilter("JPG","*.jpg"),
												new FileChooser.ExtensionFilter("BMP","*.bmp"),
												new FileChooser.ExtensionFilter("GIF","*.gif"));
		File selectedFile = fileChooser.showOpenDialog(null);
		if(selectedFile != null){	
			 image = new Image(selectedFile.toURI().toString());
			 Oimage = new Image(selectedFile.toURI().toString());
			 iv.setImage(image);
			 String  fileName = selectedFile.getName();
			 lable1.setText(fileName);
		}

}
	/**
	 * Creates a pop up option box when the user
	 * chooses to rotate an image. This box asks
	 * for an angle (in degrees) by which to rotate
	 * the selected image
	 */
	private void rotate(){
		
		Stage stage = new Stage();
		VBox vb = new VBox();
		Label label = new Label("Please enter a your angel, in degress:");
		TextField textField = new TextField();
		vb.setPadding(new Insets(20));
		 
		 HBox hb  = new HBox();				 
		 Button cancel = new Button("Cancel");
		 Button ok = new Button("OK");
		 
		 ok.setOnAction(event->{
			 double number = 0;
			String text = textField.getText();
			 try {
					 number = Double.parseDouble(text);
					 if(number >0 && image != new Image("https://raw.githubusercontent.com/mepcotterell-cs1302/cs1302-artsy/master/resources/default.png"))
					 image = artsy.doRotate(image, number);
					 else
						 error();
				    } catch (NumberFormatException nfe) { 
				    	error();// line intentionally left blank
				    } // try		
			 stage.close();
			
				
				iv.setImage(image);
		 });
		 
		 cancel.setOnAction(event ->{
			 stage.close();
		 });
		 hb.setSpacing(10);
		 hb.setPadding(new Insets(20));
		 hb.getChildren().addAll(cancel,ok);
		 
		 vb.getChildren().addAll(label,textField,hb);
		 
		 Scene scene = new Scene(vb);
	     stage.setScene(scene);
	     stage.setTitle("Rotate Image Options");
	     stage.initModality(Modality.APPLICATION_MODAL);
	     stage.sizeToScene();
	     stage.show();
		
	}
	/**
	 * In case of an error in the pop up box
	 * this method handles it appropriately by
	 * prompting the user again.
	 */
	public void error(){
		Stage stage = new Stage();
		VBox hb = new VBox();
		Label label = new Label("Invalid input! \nPlease input Integer Number larger than 0");		
		hb.setPadding(new Insets(20));		
		Button button = new Button("OK");
		button.setOnAction(event ->{
			stage.close();
		});
		hb.getChildren().addAll(label,button);
		 Scene scene = new Scene(hb);
		 stage.setScene(scene);
	     stage.setTitle("ERROR");
	     stage.initModality(Modality.APPLICATION_MODAL);
	     stage.sizeToScene();
	     stage.show();				
	}
	/**
	  * This method is used to call the method which
	  * applies the HorizontalStripe effect two the two selected
	  * images, resulting in one image.
	  * 
	  * @param src1 Image number 1
	  * @param src2 Image number 2
	  * @param width Desired width of the HorizontalStripe
	  */
	 public void doHorizontalStripes(Image src1, Image src2, int height) {
			 image =artsy.doHorizontalStripes(src1, src2, height);
			 Oimage = image;
		 iv.setImage(image);		
	 }
	 /**
	  * This method is used to call the method which
	  * applies the VerticalStripe effect two the two selected
	  * images, resulting in one image.
	  * 
	  * @param src1 Image number 1
	  * @param src2 Image number 2
	  * @param width Desired width of the VerticalStripe
	  */
	 public void doVerticalStripes(Image src1, Image src2, int width) {
		 image =artsy.doVerticalStripes(src1, src2, width);
		 Oimage = image;
    	 iv.setImage(image);		
}
	
	 /**
	  * This method is used to call the method which
	  * applies the checker effect two the two selected
	  * images, resulting in one image.
	  * 
	  * @param src1 Image number 1
	  * @param src2 Image number 2
	  * @param width Desired width of the checkers
	  */
 public void doChecker(Image src1, Image src2, int width) {
	 image =artsy.doCheckers(src1, src2, width);
	 Oimage = image;
    	 iv.setImage(image);		
}
}
