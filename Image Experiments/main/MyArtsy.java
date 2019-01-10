package cs1302.p2;

import cs1302.effects.Artsy;
import javafx.geometry.Point2D;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.image.PixelReader;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
/**
 * Class that implements MyArtsy and overrides its
 * methods to provide functionality to the GUI
 *
 */
public class MyArtsy implements Artsy {
	/**
	 * This method takes two images and applies
	 * a checker effect to them
	 * 
	 * @param src1	Image 1
	 * @param src2  Image 2
	 * @param size  Width of the checkers
	 * 
	 * @return	Returns the result image after the 
	 * 			checker effect
	 */
    @Override
    public Image doCheckers(Image src1, Image src2, int size) {
    	int x1 = (int)src1.getWidth();
    	int y1= (int)src1.getHeight(); 
    	int j= 0;
    	int i = 0;
    	int range = 0;
    	int range1 = 0;
    	int y = 0;
    	int x = 0;
    	WritableImage ret = new WritableImage(x1, y1); 
    	PixelReader pr1 = src1.getPixelReader(); 
    	PixelReader pr2 = src2.getPixelReader(); 
    	PixelWriter pw = ret.getPixelWriter(); 

    	
    	for (x = 0; x < x1; ++x) { 
    		for (y = 0; y < y1; ++y) 
    		{  
    			pw.setArgb(x, y, pr1.getArgb(x, y)); 
    		}
    		} // for  
    	
    	
    	while(i < y1&& j < y1){   		
    		range = i +size;
    		range1 = j +size;
    		if(range > y1)
    		range = y1;
    		if(range1 > y1)
    			range1 = y1;
    		for(y = j;y < range1; ++y)
    			{
	    			for(x = i;x < range; ++x)
	    			{
	    				pw.setArgb(x, y, pr2.getArgb(x,y));  	    				
	    			}    				    			
    			}
    		i +=size*2;
    		
   			if(x+size >= x1)
 				{
   				i = 0;
   				x = 0;
    			j +=size*2; 
 				}   			
    			}
    	
    	i = size;
    	j = size;
    	range1 = 0;
    	range = 0;
    	while(i < y1 && j < y1){   		
    		range = i +size;
    		range1 = j +size;
    		if(range > y1)
    		range = y1;
    		if(range1 > y1)
    			range1 = y1;
    		for(y = j;y < range1; ++y)
    			{
	    			for(x = i;x < range; ++x)
	    			{
	    				pw.setArgb(x, y, pr2.getArgb(x,y));  	    				
	    			}    				    			
    			}
    		i +=size*2;
   			if(x+size >= x1)
 				{
   				i = size;
   				x = size;
    			j +=size*2; 
 				}   			
    			}
	return ret;
    } // doCheckers

    /**
     * Takes two images and applies a horizontal
     * stripe effect
     * 
     * @param src1	Image 1
     * @param src2	Image 2
     * @param height	Height in pixels of the
     * 					horizontal rows
     * 
     * @return	Returns the result image after
     * 			the stripe effect
     */
    @Override
    public Image doHorizontalStripes(Image src1, Image src2, int height) {
    	int x1 = (int)src1.getWidth();
    	int y1= (int)src1.getHeight(); 
    	int j= 0;
    	int range = 0;
    	WritableImage ret = new WritableImage(x1, y1); 
    	PixelReader pr1 = src1.getPixelReader(); 
    	PixelReader pr2 = src2.getPixelReader(); 
    	PixelWriter pw = ret.getPixelWriter(); 

    	while(j < y1){
    		range = j +height;
    		if(range > y1)
    			range = y1;
    		for(int y = j;y < range; ++y){
    			for(int x = 0; x < x1; ++x){
    				pw.setArgb(x, y, pr2.getArgb(x,y));
    			}
    			}
    			j += height*2;
    			}
    	j = 0;
    	while(j < y1){
    		range = j +height*2;
    		if(range > y1)
    			range = y1;
    		for(int y = j+height;y < range; ++y){
    			for(int x = 0; x < x1; ++x){
    				pw.setArgb(x, y, pr1.getArgb(x,y));
    			}
    			}
    			j += height*2;
    			}	
	return ret;
    } // doHorizontalStripes


    /**
     * This method applies a vertical stripe effect
     * to merge two images
     * 
     * @param src1	Image 1
     * @param src2	Image 2
     * @param width	Width of the vertical stripes in pixels
     * 
     * @return Returns the result image after the vertical
     * 			stripe effect
     */
    @Override
    public Image doVerticalStripes(Image src1, Image src2, int width) {
    	int x1 = (int)src1.getWidth();
    	int y1= (int)src1.getHeight(); 
    	int j= 0;
    	int range = 0;
    	
    	WritableImage ret = new WritableImage(x1, y1); 
    	PixelReader pr1 = src1.getPixelReader(); 
    	PixelReader pr2 = src2.getPixelReader(); 
    	PixelWriter pw = ret.getPixelWriter(); 

    	
    	while(j < x1){
    		range = j +width*2;
    		if(range > x1)
    			range = x1;
    		for(int x = j;x < range; ++x){
    			for(int y = 0; y < y1; ++y){
    				pw.setArgb(x, y, pr2.getArgb(x,y));
    			}
    			}
    			j += width*2;
    			}
    	j = 0;
    	while(j < x1){
    		range = j +width*2;
    		if(range > x1)
    			range = x1;
    		for(int x = j+width;x < range; ++x){
    			for(int y = 0; y < y1; ++y){
    				pw.setArgb(x, y, pr1.getArgb(x,y));
    			}
    			}
    			j += width*2;
    			}
	return ret;
    } // doHorizontalStripes

    /**
     * This method takes one image and rotates
     * it according to a number of degrees provided
     * by the user
     * 
     * @param src	Image to rotate
     * @param degrees Number of degrees to rotate
     * 					the image by
     * 
     * @return	Returns the rotated image
     */
    @Override
    public Image doRotate(Image src, double degrees) {
    	int x = (int)src.getWidth();
    	int y= (int)src.getHeight();    	
    	degrees = degrees* Math.PI/180;
      	
    	WritableImage ret = new WritableImage(x, y); 
    	PixelReader pr = src.getPixelReader(); 
    	PixelWriter pw = ret.getPixelWriter(); 

    	PixelReader pr1 = ret.getPixelReader(); 
    	for(int i = 0; i < x; i++)
    	{
    		for(int j = 0; j < y; j++)
    		{
    			if(pr1.getArgb(i,j) == 0)
    				{
    				int xx = (int) (((i - x/2) * Math.cos(degrees) + (j - y/2) * Math.sin(degrees))+x/2); // new x position 
    	        	int yy = (int) (((-i + x/2) * Math.sin(degrees) + (j - y/2) * Math.cos(degrees))+y/2); // new y position
    	        	if( xx < x && yy <y && xx >= 0 && yy >=0)        	
    	        		pw.setArgb(i,j,pr.getArgb(xx,yy));  				
    				} 				
    		}
    	}
    	return ret;
    } // doVerticalStripes
} // MyArtsy