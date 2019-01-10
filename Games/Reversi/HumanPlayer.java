import java.util.Scanner;

public class HumanPlayer extends Player{
	/**
	 * 	is the input in the board range.
	 * 
	 * 
	 * 
	 * @param rowCol  scanner user input
	 * @return  true if the input is in the range.
	 */
	 public boolean Move(Scanner rowCol){
		  if(rowCol.hasNextInt())
			{
				col = rowCol.nextInt();
				if(col<1 || col>8)
					{
						System.out.println("Wrong command");
						return false;
					}
				else{
						if(rowCol.hasNextInt())
							{
								row=rowCol.nextInt();
								if(row<1 || row>8)
								{
									System.out.println("Wrong command");
									return false;
								}
								return true;
							}
						else
							{
								System.out.println("Wrong command");
								return false;
							}
					}	
			}
		else
			{
				System.out.println("Wrong command");
				return false;
			}
	  }
}
