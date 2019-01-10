
import java.util.Scanner;
public class ReversiBoard implements Board{
	protected String [][] reversiBoard = new String [9][9];
	protected boolean [][] AvSpace = new boolean [9][9];
	protected boolean changeRound = true;
	/**
	 * print out the board.
	 * 
	 */
	public void reversiBoard(){
		System.out.print("\n   ");
		for(int i = 1; i < reversiBoard.length ; i++)
			System.out.print(" "+ i);
			System.out.println();
		for(int i = 1; i <reversiBoard.length ; i++)
				{
					System.out.print("  "+ i);				
					for( int j = 1; j < reversiBoard.length ; j++)
						{
						System.out.print(" " + reversiBoard[i][j]);
						}
					System.out.println();	
				}
	}
	/**
	 * computer available space for X Player and count how many available spaces.
	 * 
	 * 
	 * 
	 * @return the number of available spaces for X
	 */
	public int IsLegalMoveX(){
		int i =0;
		int j = 0;
		int count = 0;
		for(i = 1; i <reversiBoard.length; i++)
			{
				for(j = 1; j < reversiBoard.length; j++)
				AvSpace[i][j] = false;
			}
		for(i = 1; i < 9; i++)
		{
			for(j = 1; j < 9; j++)
				{	
					if(reversiBoard[i][j].equals("X"))
					{
						for(int x = i -1; x<= i +1; x++)
						{
						for(int y = j -1; y<=j + 1; y++)
							{	
								if (x >= 1 && x < reversiBoard.length && y >= 1 && y < reversiBoard.length)
								{
									if(reversiBoard[x][y].equals("O"))
									{
										if(x == i && y == j-1)
										{
											for(int jj =y-1; jj >0; jj--)
											{	
												if(reversiBoard[i][jj].equals(".")&&reversiBoard[i][jj+1].equals("O"))
													{
													AvSpace[i][jj] = true;
													break;
													}
											}
										}//horz check Left
										else if(x == i && y == j +1)
										{
											for(int jj =y; jj < 9; jj++)
											{	
												if(reversiBoard[i][jj].equals(".")&&reversiBoard[i][jj-1].equals("O"))
													{
													AvSpace[i][jj] = true;
													break;
													}
											}
										}//horz check
										else if(y == j && x < i)
										{
											for(int jj =x-1; jj >0; jj--)
											{	
												if(reversiBoard[jj][j].equals(".")&&reversiBoard[jj+1][j].equals("O"))
													{
													AvSpace[jj][j] = true;
													break;
													}
											}
										}//verti check
										else if(y == j && x > i)
										{
											for(int jj =x; jj < 9; jj++)
											{	
												if(reversiBoard[jj][j].equals(".")&&reversiBoard[jj-1][j].equals("O"))
													{
													AvSpace[jj][j] = true;
													break;
													}
											}
										}//verti check
										else if(x== i-1 && y == j-1)
										{	int a = x;
											int b = y;
											while(a >1&& b >1)
											{
												a = a -1;
												b = b -1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a+1][b+1].equals("O"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i+1 && y == j-1)
										{	int a = x;
											int b = y;
											while(a < 8 && b > 1 )
											{
												a = a +1;
												b = b -1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a-1][b+1].equals("O"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i-1 && y == j+1)
										{	int a = x;
											int b = y;
											while(a >1&& b < 8)
											{
												a = a -1;
												b = b +1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a+1][b-1].equals("O"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i+1 && y == j+1)
										{	int a = x;
											int b = y;
											while(a < 8&& b < 8)
											{
												a = a +1;
												b = b +1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a-1][b-1].equals("O"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}												
										}
									}
								}
							}					
						}	
					}
				}
		}
		for(i =1; i < 9; i++)
			for(j= 1;j < 9; j++)
			{
				if(AvSpace[i][j])
				count++;
			}
		return count;
		
	}
	/**
	 * computer available space for O Player and count how many available spaces.
	 * 
	 * 
	 * 
	 * @return the number of available spaces for O
	 */
	public int IsLegalMoveO(){

		int i =0;
		int j = 0;
		int count = 0;
		for(i = 1; i <reversiBoard.length; i++)
			{
				for(j = 1; j < reversiBoard.length; j++)
				AvSpace[i][j] = false;
			}
		for(i = 1; i < 9; i++)
		{
			for(j = 1; j < 9; j++)
				{	
					if(reversiBoard[i][j].equals("O"))
					{
						for(int x = i -1; x<= i +1; x++)
						{
						for(int y = j -1; y<=j + 1; y++)
							{	
								if (x >= 1 && x < reversiBoard.length && y >= 1 && y < reversiBoard.length)
								{
									if(reversiBoard[x][y].equals("X"))
									{
										if(x == i && y== j -1)
										{
											for(int jj =y-1; jj >0; jj--)
											{	
												if(reversiBoard[i][jj].equals(".")&&reversiBoard[i][jj+1].equals("X"))
													{
													AvSpace[i][jj] = true;
													break;
													}
											}
										}//horz check Left
										else if(x == i && y == j+1)
										{
											for(int jj =y; jj < 9; jj++)
											{	
												if(reversiBoard[i][jj].equals(".")&&reversiBoard[i][jj-1].equals("X"))
													{
													AvSpace[i][jj] = true;
													break;
													}
											}
										}//horz check
										else if(y == j && x < i)
										{
											for(int jj =x-1; jj >0; jj--)
											{	
												if(reversiBoard[jj][j].equals(".")&&reversiBoard[jj+1][j].equals("X"))
													{
													AvSpace[jj][j] = true;
													break;
													}
											}
										}//verti check
										else if(y == j && x > i)
										{
											for(int jj =x; jj < 9; jj++)
											{	
												if(reversiBoard[jj][j].equals(".")&&reversiBoard[jj-1][j].equals("X"))
													{
													AvSpace[jj][j] = true;
													break;
													}
											}
										}//verti check
										else if(x== i-1 && y == j-1)
										{	int a = x;
											int b = y;
											while(a >1&& b >1)
											{
												a = a -1;
												b = b -1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a+1][b+1].equals("X"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i+1 && y == j-1)
										{	int a = x;
											int b = y;
											while(a < 8 && b > 1 )
											{
												a = a +1;
												b = b -1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a-1][b+1].equals("X"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i-1 && y == j+1)
										{	int a = x;
											int b = y;
											while(a >1&& b < 8)
											{
												a = a -1;
												b = b +1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a+1][b-1].equals("X"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}
												
										}
										else if(x== i+1 && y == j+1)
										{	int a = x;
											int b = y;
											while(a < 8&& b < 8)
											{
												a = a +1;
												b = b +1;
												if(reversiBoard[a][b].equals(".")&&reversiBoard[a-1][b-1].equals("X"))
												{
													AvSpace[a][b] = true;
													break;
												}													
											}												
										}
									}
								}
							}					
						}	
					}
				}
		}
		for(i =1; i < 9; i++)
			for(j= 1;j < 9; j++)
			{
				if(AvSpace[i][j])
				count++;
			}
		return count;
	}
	/**
	 *  flips spaces between two X.
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * @param w row number
	 * @param z col number
	 */

	public void flipX(int w, int z){
		for(int x = w -1; x<= w +1; x++)
		{
		for(int y = z -1; y<=z + 1; y++)
			{	
				if (x >= 1 && x < reversiBoard.length && y >= 1 && y < reversiBoard.length)
				{
					if(reversiBoard[x][y].equals("O"))
					{
						if(x == w && y== z-1)
						{
							for(int jj =y; jj >0; jj--)
							{	
								if(reversiBoard[w][jj].equals("X") && reversiBoard[w][jj+1].equals("O"))	
								{
									for(int i = jj; i < z;i++)
									{
										reversiBoard[w][i] = "X";
									}
								break;
								}
							}
						}//horz check
						else if(x == w && y > z)
						{
							for(int jj =y; jj < 9; jj++)
							{	
								if(reversiBoard[w][jj].equals("X")&& reversiBoard[w][jj-1].equals("O"))
								{
									for(int i = z; i < jj;i++)
									{
										reversiBoard[w][i] = "X";
									}
									break;
								}
									
							}
						}//horz check
						else if(y == z && x < w)
						{
							for(int jj =x-1; jj >0; jj--)
							{	
								if(reversiBoard[jj][z].equals("X")&&reversiBoard[jj+1][z].equals("O"))
									{
									for(int i = jj; i < w;i++)
									{
										reversiBoard[i][z] = "X";
									}
									break;
									}
							}
						}//verti check
						else if(y == z && x > w)
						{
							for(int jj =x; jj < 9; jj++)
							{	
								if(reversiBoard[jj][z].equals("X")&&reversiBoard[jj-1][z].equals("O"))
									{
									for(int i = jj; i > w;i--)
									{
										reversiBoard[i][z] = "X";
									}
									break;
									}
							}
						}//verti check
						else if(x== w-1 && y == z-1)
						{	int a = x;
							int b = y;
							while(a >1&& b >1)
							{
								a = a -1;
								b = b -1;
								if(reversiBoard[a][b].equals("X")&&reversiBoard[a+1][b+1].equals("O"))
								{
									while(a < x || b< y)
									{	a++;
										b++;
										reversiBoard[a][b] = "X";
									}
									break;
								}													
							}
								
						}//up right check
						else if(x== w+1 && y == z-1)
						{	int a = x;
							int b = y;
							while(a >1 && b < 8 && a < 8 && b >1)
							{
								a = a +1;
								b = b -1;
								if(reversiBoard[a][b].equals("X")&&reversiBoard[a-1][b+1].equals("O"))
								{
									while(a < x || b< y)
									{	a--;
										b++;
										reversiBoard[a][b] = "X";
									}
									break;
								}													
							}
								
						}
						else if(x== w-1 && y == z+1)
						{	int a = x;
							int b = y;
							while(a >1 && b < 8 && a < 8 && b >1)
							{
								a = a -1;
								b = b +1;
								if(reversiBoard[a][b].equals("X")&&reversiBoard[a+1][b-1].equals("O"))
								{
									while(a < x || b< y)
									{	a++;
										b--;
										reversiBoard[a][b] = "X";
									}
									break;
								}													
							}
								
						}
						else if(x==w+1 && y == z+1)
						{	int a = x;
							int b = y;
							while(a < 8 && b < 8)
							{
								a = a +1;
								b = b +1;
								if(reversiBoard[a][b].equals("X")&&reversiBoard[a-1][b-1].equals("O"))
								{
									while(a > x && b > y&& a>0 && b >0)
									{	a--;
										b--;
										reversiBoard[a][b] = "X";
									}
									
									break;
								}													
							}
								
						}//right down check

					}
				}
			}					
		}			
	}
	/**
	 *  flips spaces between two O.
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * @param w row number
	 * @param z col number
	 */
	public void flipO(int w, int z){
		for(int x = w -1; x<= w +1; x++)
		{
		for(int y = z -1; y<=z + 1; y++)
			{	
				if (x >= 1 && x < reversiBoard.length && y >= 1 && y < reversiBoard.length)
				{
					if(reversiBoard[x][y].equals("X"))
					{
						if(x == w && y== z-1)
						{
							for(int jj =y; jj >0; jj--)
							{	
								if(reversiBoard[w][jj].equals("O") && reversiBoard[w][jj+1].equals("X"))	
								{
									for(int i = jj; i < z;i++)
									{
										reversiBoard[w][i] = "O";
									}
								break;
								}
							}
						}//horz check
						else if(x == w && y > z)
						{
							for(int jj =y; jj < 9; jj++)
							{	
								if(reversiBoard[w][jj].equals("O")&& reversiBoard[w][jj-1].equals("X"))
								{
									for(int i = z; i < jj;i++)
									{
										reversiBoard[w][i] = "O";
									}
									break;
								}
									
							}
						}//horz check
						else if(y == z && x < w)
						{
							for(int jj =x-1; jj >0; jj--)
							{	
								if(reversiBoard[jj][z].equals("O")&&reversiBoard[jj+1][z].equals("X"))
									{
									for(int i = jj; i < w;i++)
									{
										reversiBoard[i][z] = "O";
									}
									break;
									}
							}
						}//verti check
						else if(y == z && x > w)
						{
							for(int jj =x; jj < 9; jj++)
							{	
								if(reversiBoard[jj][z].equals("O")&&reversiBoard[jj-1][z].equals("X"))
									{
									for(int i = jj; i > w;i--)
									{
										reversiBoard[i][z] = "O";
									}
									break;
									}
							}
						}//verti check
						else if(x== w-1 && y == z-1)
						{	int a = x;
							int b = y;
							while(a >1&& b >1)
							{
								a = a -1;
								b = b -1;
								if(reversiBoard[a][b].equals("O")&&reversiBoard[a+1][b+1].equals("X"))
								{
									while(a < x || b< y)
									{	a++;
										b++;
										reversiBoard[a][b] = "O";
									}
									break;
								}													
							}
								
						}//up right check
						else if(x== w+1 && y == z-1)
						{	int a = x;
							int b = y;
							while(a >1 && b < 8 && a < 8 && b >1)
							{
								a = a +1;
								b = b -1;
								if(reversiBoard[a][b].equals("O")&&reversiBoard[a-1][b+1].equals("X"))
								{
									while(a < x || b< y)
									{	a--;
										b++;
										reversiBoard[a][b] = "O";
									}
									break;
								}													
							}
								
						}
						else if(x== w-1 && y == z+1)
						{	int a = x;
							int b = y;
							while(a >1 && b < 8 && a < 8 && b >1)
							{
								a = a -1;
								b = b +1;
								if(reversiBoard[a][b].equals("O")&&reversiBoard[a+1][b-1].equals("X"))
								{
									while(a < x || b< y)
									{	a++;
										b--;
										reversiBoard[a][b] = "O";
									}
									break;
								}													
							}
								
						}
						else if(x==w+1 && y == z+1)
						{	int a = x;
							int b = y;
							while(a < 8 && b < 8)
							{
								a = a +1;
								b = b +1;
								if(reversiBoard[a][b].equals("O")&&reversiBoard[a-1][b-1].equals("X"))
								{
									while(a > x && b > y&& a>0 && b >0)
									{	a--;
										b--;
										reversiBoard[a][b] = "O";
									}
									
									break;
								}													
							}
								
						}//right down check

					}
				}
			}					
		}			
	}
	/**
	 * is the row and col available for X.
	 * 
	 * 
	 * 
	 * 
	 * @param a  row
	 * @param b  col
	 * @return	true if the col and row match the available space.
	 */
	public boolean isLegalX(int a, int b){
		if(AvSpace[a][b] != true)
		{
			System.out.println("Space is not vaild! \nPlease try again!");
			return false;
		}
		else
		{
			reversiBoard[a][b] = "X";
			return true;
		}			
	}	
	/**
	 * is the row and col available for O.
	 * 
	 * 
	 * 
	 * 
	 * @param a  row
	 * @param b  col
	 * @return	true if the col and row match the available space.
	 */
	public boolean isLegalO(int a, int b){
		if(AvSpace[a][b] != true)
		{
			System.out.println("Space is not vaild! \nPlease try again!");
			return false;
		}
		else
		{
			reversiBoard[a][b] = "O";
			return true;
		}			
	}
	/**
	 * who wins the game.
	 * 
	 */
	public void win(){
		int countX = 0;
		int countO = 0;
		for(int i=1; i < reversiBoard.length; i++)
			for(int j=1; j < reversiBoard.length; j++)
			{
				if(reversiBoard[i][j].equals("X"))
					countX++;
				if(reversiBoard[i][j].equals("O"))
					countO++;
			}
		if(countX > countO)
			System.out.println("X wins");
		else if(countO> countX)
			System.out.println("O wins");
		else if(countO == countX)
			System.out.println("Tie");
	}
	/**
	 * print out all the available move
	 * 
	 * 
	 * @param a  available space
	 */
	public void moveChoice(boolean [][] a){
		System.out.println("Available spaces: ");
		for(int i = 1; i <a.length; i++)
			for(int j = 1; j < a.length; j++)
				if(AvSpace[i][j])
					{
					System.out.print(i+"-");
					System.out.print(j+", ");
					}
	}
	/**
	 * plays the game with two human players.
	 * 
	 * 
	 */
	public void PlayerVsPlayer(){
		HumanPlayer HP = new HumanPlayer();
		boolean isOver = false;
		boolean isInput = true;
		for(int i = 1; i <reversiBoard.length ; i++)
		{
			for( int j = 1; j < reversiBoard.length ; j++)
			reversiBoard[i][j] = ".";
		}
		reversiBoard[4][4] = "X";
		reversiBoard[4][5] = "O";
		reversiBoard[5][4] = "O";
		reversiBoard[5][5] = "X";
		System.out.println("\nWelcome to Reversi!  Moves should be entered in \"[row] [column]\" format.");
		do{
			if(IsLegalMoveX() == 0 && IsLegalMoveO() == 0)
			{	
				reversiBoard();
				System.out.println("\nGame Over");
				isOver = true;
			}
			else
			{
				if(changeRound)
				{
					if(IsLegalMoveX() != 0)
					{
						do{
							reversiBoard();	
							IsLegalMoveX();						
						do{
							moveChoice(AvSpace);
							System.out.print("\nEnter your move, X player:");
							Scanner input = new Scanner(System.in);
							String command = input.nextLine();
							Scanner rowCol = new Scanner(command);
							isInput = HP.Move(rowCol);	
						}while(!isInput);		
						  }while(!isLegalX(HP.col, HP.row));
							flipX(HP.col, HP.row);
						  	changeRound = false;
					}
					else
						{	System.out.println("No available space for X Player. Round Change");
							changeRound = false;
						}
					}
				else if(changeRound == false)
				{				
					if(IsLegalMoveO()!= 0)
					{
					do{
						reversiBoard();
						IsLegalMoveO();						
					do{	
						moveChoice(AvSpace);					
						System.out.print("\nEnter your move, O player:");
						Scanner input1 = new Scanner(System.in);
						String command1 = input1.nextLine();
						Scanner rowCol1 = new Scanner(command1);
						isInput =HP.Move(rowCol1);
						}while(!isInput);
					   }while(!isLegalO(HP.col, HP.row));
						flipO(HP.col, HP.row);
					  	changeRound = true;								
					}				
					else
					{
					System.out.println("No available space for O Player. Round Change");
					changeRound = true;
					}
				}// if there are still space to make move
			}
		}while(isOver == false );
				win();
	};
	/**
	 * plays the game with human and computer player.
	 * 
	 * 
	 */
	public void PlayerVsComputerPlayer(){
		HumanPlayer HP = new HumanPlayer();
		boolean isOver = false;
		boolean isInput = true;
		RandomComputerPlayer RCP = new RandomComputerPlayer();
		for(int i = 1; i <reversiBoard.length ; i++)
		{
			for( int j = 1; j < reversiBoard.length ; j++)
			reversiBoard[i][j] = ".";
		}
		reversiBoard[4][4] = "X";
		reversiBoard[4][5] = "O";
		reversiBoard[5][4] = "O";
		reversiBoard[5][5] = "X";
		System.out.println("\nWelcome to Reversi!  Moves should be entered in \"[row] [column]\" format.");
		do{
			if(IsLegalMoveX() == 0 && IsLegalMoveO() == 0)
			{	
				reversiBoard();
				System.out.println("\nGame Over");
				isOver = true;
			}
			else
			{
				if(changeRound)
				{
					if(IsLegalMoveX() != 0)
					{
						do{
							reversiBoard();	
							IsLegalMoveX();						
						do{
							moveChoice(AvSpace);
							System.out.print("\nEnter your move, X player:");
							Scanner input = new Scanner(System.in);
							String command = input.nextLine();
							Scanner rowCol = new Scanner(command);
							isInput = HP.Move(rowCol);	
						}while(!isInput);		
						  }while(!isLegalX(HP.col, HP.row));
							flipX(HP.col, HP.row);
						  	changeRound = false;
					}
					else
						{	System.out.println("No available space for X Player. Round Change");
							changeRound = false;
						}
					}
				else if(changeRound == false)
				{				
					if(IsLegalMoveO()!= 0)
					{
						reversiBoard();
						IsLegalMoveO();											
						moveChoice(AvSpace);
						System.out.print("\nEnter your move, O player:");
						RCP.randomMove(AvSpace);
						RCP.computerMove();	
						isLegalO(RCP.col, RCP.row);
						flipO(RCP.col, RCP.row);
					  	changeRound = true;								
					}				
					else
					{
					System.out.println("No available space for O Player. Round Change");
					changeRound = true;
					}
				}// if there are still space to make move
			}
		}while(isOver == false );
				win();
	};
	/**
	 * plays the game with two computer players.
	 * 
	 * 
	 */
	public void ComputerPlayerVsComputerPlayer(){
		boolean isOver = false;
		RandomComputerPlayer RCP = new RandomComputerPlayer();
		
		for(int i = 1; i <reversiBoard.length ; i++)
		{
			for( int j = 1; j < reversiBoard.length ; j++)
			reversiBoard[i][j] = ".";
		}
		reversiBoard[4][4] = "X";
		reversiBoard[4][5] = "O";
		reversiBoard[5][4] = "O";
		reversiBoard[5][5] = "X";
		System.out.println("\nWelcome to Reversi!  Moves should be entered in \"[row] [column]\" format.");
		do{
			if(IsLegalMoveX() == 0 && IsLegalMoveO() == 0)
			{	
				reversiBoard();
				System.out.println("\nGame Over");
				isOver = true;
			}
			else
			{
				if(changeRound)
				{
					if(IsLegalMoveX() != 0)
					{
						reversiBoard();
						IsLegalMoveX();											
						moveChoice(AvSpace);
						System.out.print("\nEnter your move, X player:");
						RCP.randomMove(AvSpace);
						RCP.computerMove();	
						isLegalX(RCP.col, RCP.row);
						flipX(RCP.col, RCP.row);
						 changeRound = false;
					}
					else
						{	System.out.println("No available space for X Player. Round Change");
							changeRound = false;
						}
					}
				else if(changeRound == false)
				{				
					if(IsLegalMoveO()!= 0)
					{
						reversiBoard();
						IsLegalMoveO();											
						moveChoice(AvSpace);
						System.out.print("\nEnter your move, O player:");
						RCP.randomMove(AvSpace);
						RCP.computerMove();	
						isLegalO(RCP.col, RCP.row);
						flipO(RCP.col, RCP.row);
					  	changeRound = true;								
					}				
					else
					{
					System.out.println("No available space for O Player. Round Change");
					changeRound = true;
					}
				}// if there are still space to make move
			}
		}while(isOver == false );
				win();
	};
	/**
	 * plays the game with computer player and human.
	 * 
	 * 
	 */
	public void RandomComputerPlayerVsPlayer(){
		HumanPlayer HP = new HumanPlayer();
		RandomComputerPlayer RCP = new RandomComputerPlayer();
		boolean isOver = false;
		boolean isInput = true;
		for(int i = 1; i <reversiBoard.length ; i++)
		{
			for( int j = 1; j < reversiBoard.length ; j++)
			reversiBoard[i][j] = ".";
		}
		reversiBoard[4][4] = "X";
		reversiBoard[4][5] = "O";
		reversiBoard[5][4] = "O";
		reversiBoard[5][5] = "X";
		System.out.println("\nWelcome to Reversi!  Moves should be entered in \"[row] [column]\" format.");
		do{
			if(IsLegalMoveX() == 0 && IsLegalMoveO() == 0)
			{	
				reversiBoard();
				System.out.println("\nGame Over");
				isOver = true;
			}
			else
			{
				if(changeRound)
				{
					if(IsLegalMoveX() != 0)
					{
						reversiBoard();
						IsLegalMoveX();											
						moveChoice(AvSpace);	
						System.out.print("\nEnter your move, X player:");
						RCP.randomMove(AvSpace);
						RCP.computerMove();	
						isLegalX(RCP.col, RCP.row);
						flipX(RCP.col, RCP.row);
						changeRound = false;
					}
					else
						{	System.out.println("No available space for X Player. Round Change");
							changeRound = false;
						}
					}
				else if(changeRound == false)
				{				
					if(IsLegalMoveO()!= 0)
					{
					do{
						reversiBoard();
						IsLegalMoveO();						
					do{	
						moveChoice(AvSpace);					
						System.out.print("\nEnter your move, O player:");
						Scanner input1 = new Scanner(System.in);
						String command1 = input1.nextLine();
						Scanner rowCol1 = new Scanner(command1);
						isInput =HP.Move(rowCol1);
						}while(!isInput);
					   }while(!isLegalO(HP.col, HP.row));
						flipO(HP.col, HP.row);
					  	changeRound = true;								
					}				
					else
					{
					System.out.println("No available space for O Player. Round Change");
					changeRound = true;
					}
				}// if there are still space to make move
			}
		}while(isOver == false );
				win();
	};
}
