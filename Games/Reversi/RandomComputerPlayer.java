import java.util.Random;
public class RandomComputerPlayer extends ComputerPlayer{
	Random rand = new Random();
	/**
	 * generate random number for computer move
	 * 
	 * 
	 */
	
	
public void randomMove(boolean [][] array){
	try{
		Thread.sleep(1000);
		}
		catch (InterruptedException a){
		}

	int tempA = 0;
	int tempB = 0;
	do{
		tempA = rand.nextInt(8) + 1;
		tempB = rand.nextInt(8) + 1;			 
	  }while(!array[tempA][tempB]);
		this.col = tempA;
		this.row = tempB;
	}
/**
 * print out computer move
 */
 public void computerMove(){
	 
	 System.out.print(col + " ");
	 System.out.println(row); 
 }

}
