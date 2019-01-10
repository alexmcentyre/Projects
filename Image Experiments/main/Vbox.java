package cs1302.p2;

import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Vbox extends VBox{
	/**
	 * This class allows for the construction of a
	 * vbox which contributes to the layout of the GUI
	 *
	 */
		public Vbox(ImagePane a, ImagePane b,ImagePane c){
		super();
		AppMenuBar menuBar = new AppMenuBar(a,b,c);
		
		HBox hb1 = new HBox();
	    hb1.getChildren().add(menuBar);
	   	    
	    HBox hb2 = new HBox();
	    Button button1 = new Button("Checkers");
	    Button button2 = new Button("Horizontal Stripes");
	    Button button3 = new Button("Vertical Stripes");
	    button1.setOnAction(event ->{
	    	doChecker(a,b,c);	    	
	    });
	    button2.setOnAction(event ->{			
	    	horizontal(a,b,c);   	
	    });
	    
	    button3.setOnAction(event ->{
	    	vertical(a,b,c);
	    });
	    
	      
	    hb2.setSpacing(10);    
	    button1.setPrefSize(100,1);
	    button2.setPrefSize(150,1);
	    button3.setPrefSize(150,1);
	    hb2.getChildren().addAll(button1,button2,button3);	    
	    getChildren().addAll(hb1,hb2);		
	}
		
		/**
		 * Option window that appears to help the user customize
		 * the horizontal stripe effect
		 * 
		 * @param a	Image pane 1
		 * @param b	Image pane 2
		 * @param c	Image pane 3
		 */
		private void horizontal(ImagePane a, ImagePane b,ImagePane c){			
			Stage stage = new Stage();
			VBox vb = new VBox();
			Label label = new Label("Please enter the desired stripe height, in pixels.");
			TextField textField = new TextField();
			vb.setPadding(new Insets(20));
			 HBox hb  = new HBox();				 
			 Button cancel = new Button("Cancel");
			 Button ok = new Button("OK");
			 
			 ok.setOnAction(event->{
				 int number = 0;
				String text = textField.getText();
				 try {
						  number =Integer.parseInt(text);
						  if(number > 0)
						  c.doHorizontalStripes(a.image, b.image, number);    	
						  else
							c.error();  
					  } catch (Exception nfe) { 
					    	{
					    	c.error();}
					    } // try		
				 stage.close();
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
		     stage.setTitle("Horizontal Stripe Options");
		     stage.initModality(Modality.APPLICATION_MODAL);
		     stage.sizeToScene();
		     stage.show();
			
		}
		/**
		 * Window that appears allowing the user
		 * to specify the size of vertical stripes
		 * 
		 * @param a	Image pane 1
		 * @param b Image pane 2
		 * @param c Image pane 3
		 */
		private void vertical(ImagePane a, ImagePane b,ImagePane c){			
			Stage stage = new Stage();
			VBox vb = new VBox();
			Label label = new Label("Please enter the desired stripe height, in pixels.");
			TextField textField = new TextField();
			vb.setPadding(new Insets(20));
			 
			 HBox hb  = new HBox();				 
			 Button cancel = new Button("Cancel");
			 Button ok = new Button("OK");
			 
			 ok.setOnAction(event->{
				 int number = 0;
				String text = textField.getText();
			
				 try {
						  number =Integer.parseInt(text);
						  if(number > 0)
						  c.doVerticalStripes(a.image, b.image, number);  
						  else
							  c.error();
					    } catch (NumberFormatException nfe) { 
					    	c.error();
					    } // try		
				 stage.close();				
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
		     stage.setTitle("Vertical Stripe Options");
		     stage.initModality(Modality.APPLICATION_MODAL);
		     stage.sizeToScene();
		     stage.show();
			
		}
		/**
		 * Creates a window that allows the user to specify
		 * the size of checker for the result image
		 * 
		 * @param a Image pane 1
		 * @param b	Image pane 2
		 * @param c	Image pane 3
		 */
		private void doChecker(ImagePane a, ImagePane b,ImagePane c){			
			Stage stage = new Stage();
			VBox vb = new VBox();
			Label label = new Label("Please enter the desired checker width, in pixels.");
			TextField textField = new TextField();
			vb.setPadding(new Insets(20));
			 
			 HBox hb  = new HBox();				 
			 Button cancel = new Button("Cancel");
			 Button ok = new Button("OK");
			
			 
			 ok.setOnAction(event->{
				 int number = 0;
				 String text = textField.getText();	
				 try {
						  number =Integer.parseInt(text);
						  if(number >0)
						  c.doChecker(a.image, b.image, number);  
						  c.error();
					  } catch (Exception nfe) { 
					    	{
					    	c.error();}
					    } // try		
				 stage.close();				
				
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
		     stage.setTitle("Checkers Options");
		     stage.initModality(Modality.APPLICATION_MODAL);
		     stage.sizeToScene();
		     stage.show();
			
		}
		
	
	
}
