package cs1302.p2;

import javafx.scene.control.MenuBar;


public class AppMenuBar extends MenuBar{	
	/**
	 * Constructs a menu bar and adds a file menu which can
	 * load images into the first and second image panes
	 * 
	 * @param a Assigns first image pane to file menu
	 * @param b	Assigns second image pane to file menu
	 * @param c Assigns result image pane to file menu
	 */
	public AppMenuBar(ImagePane a, ImagePane b,ImagePane c){
		super();
		FileMenu file = new FileMenu(a,b,c);
	    MenuBar menuBar = new MenuBar();   
	    getMenus().add(file);
				
	}
	
	
	
}
