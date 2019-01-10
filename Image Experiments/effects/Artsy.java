package cs1302.effects;

import javafx.scene.image.Image;

/**
 * This interface describes artsy effects that can be applied to Images.
 */
public interface Artsy {

	/**
	 * Given two Images, this method returns a new Image, the contents of which
	 * is composed of the source images alternating horizontally and vertically at the specified 
	 * size, in pixels. This causes the images to appear woven together in a checkered fashion. 
	 * 
	 * @param src1 the first Image
	 * @param src2 the second Image
	 * @param height the height, in pixels, of the horizontal stripes.
	 * @return a Image with the horizontal stripes effect
	 */
	public Image doCheckers(Image src1, Image src2, int size);
	
	/**
	 * Given two Images, this method returns a new Image, the contents of which
	 * is composed of the source images alternating horizontally at the specified pixel height. 
     *
	 * @param src1 the first Image
	 * @param src2 the second Image
	 * @param height the height, in pixels, of the horizontal stripes.
	 * @return a Image with the horizontal stripes effect
	 */
	public Image doHorizontalStripes(Image src1, Image src2, int height);
	
	/**
	 * Given two Images, this method returns a new Image, the contents of which
	 * is composed of the source images alternating vertically at the specified pixel width.
	 * 
	 * @param src1 the first Image
	 * @param src2 the second Image
	 * @param width the width, in pixels, of the vertical stripes.
	 * @return a Image with the vertical stripes effect
	 */
	public Image doVerticalStripes(Image src1, Image src2, int width);
	
	/**
	 * Given a Image, this method returns a new Image which contains
	 * the source image rotated clockwise by a certain number of degrees. The image
	 * should be rotated about the center of the image.
     * 
	 * @param src     the source Image
	 * @param degrees the degrees to rotate the image, in degrees (not radians)
	 * @return a new Image containing a rotated version of the source image
	 */
	public Image doRotate(Image src, double degrees);
	
} // Artsy
