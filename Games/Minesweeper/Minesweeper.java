
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Random;

/**                                                                                                                                   
 * This class represents a Minesweeper game.                                                                                          
 *                                                                                                                                    
 * @author Alex McEntyre                                                                                                  
 */
public class Minesweeper {
    
    private boolean[][] boardTF;
    private String[][] board;
    private int[][] numBoard;
    private int rounds, rows, cols, mines, score;
    private boolean play = true, win = true;
    /**                                                                                                                               
     *                                                                                                                       
     *                                                                                                                                
     * @param seedFile the seed file used to construct the game                                                                                                                                                                                      
    */
    public Minesweeper(File seedFile) {
	try{
	    Scanner scan = new Scanner(seedFile);
	    if(scan.hasNextInt()){
		rows = scan.nextInt();
	    }// if
	    if(scan.hasNextInt()){
		cols = scan.nextInt();
	    }// if
	    if(scan.hasNextInt()){
		mines = scan.nextInt();
	    }// if
	    
	    if((rows <= 10)&&(rows >= 0)&&(cols <= 10)&&(cols >= 0)){
		boardTF = new boolean[rows][cols];
		board = new String[rows][cols];
		numBoard = new int[rows][cols];
		rounds = 0;
		
		for(int i = 0; i < mines; i++){
		    int row = scan.nextInt();
		    int col = scan.nextInt();
		    boardTF[row][col] = true;
		}// for
		for(int i = 0; i < board.length; i++){
		    for(int j = 0; j < board[i].length; j++){
			board[i][j] = " ";
		    }
		}
	    }// if
	    else{
		System.out.println();
		System.out.println("ಠ_ಠ says, \"Cannot create a mine field with that many rows and/or columns!\"");
		System.exit(0);
	    }// else
	}// try
	catch(FileNotFoundException e){
	}// catch                                                                                                            
    } // Minesweeper                                                                                                                  


    /**                                                                                                                               
     * Constructs an object instance of the {@link Minesweeper} class using the                                                       
     * <code>rows</code> and <code>cols</code> values as the game grid's number                                                       
     * of rows and columns respectively. Additionally, One quarter (rounded up)                                                       
     * of the squares in the grid will will be assigned mines, randomly.                                                              
     *                                                                                                                                
     * @param rows the number of rows in the game grid                                                                                
     * @param cols the number of cols in the game grid                                                                                
     */
    public Minesweeper(int rows, int cols) {
	if((rows > 10)||(rows < 0)||(cols > 10)||(cols < 0)){
	    System.out.println();
	    System.out.println("ಠ_ಠ says, \"Cannot create a mine field with that many rows and/or columns!\"");
	    System.exit(0);
	}// if
	boardTF = new boolean[rows][cols];
	board = new String[rows][cols];
	numBoard = new int[rows][cols];
	for(int i = 0; i < board.length; i++){
	    for(int j = 0; j < board[i].length; j++){
		board[i][j] = " ";
	    }// for
	}// for
	
	this.rows = rows;
	this.cols = cols;
	rounds = 0;
	mines = (int) Math.ceil(((double)rows*(double)cols)/10);
	
	Random random = new Random();
	int count = 0;
	while(count < mines){
	    int randomCol = random.nextInt(cols);
	    int randomRow = random.nextInt(rows);
	    if(!boardTF[randomRow][randomCol]){
		count++;
	    }// if
	    boardTF[randomRow][randomCol] = true;
	}// while
    } // Minesweeper
   
 /**
     *Prints the Minesweeper grid using a loop which iterates though
     *each element of the string array
     */    
    public void printRound(){
	System.out.println();
	System.out.println("Rounds Completed: " + rounds);
	System.out.println();
	
	for(int i = 0; i < rows; i++){
	    System.out.print(i + " |");
	    for(int j = 0; j < cols; j++){
		System.out.print(" " + board[i][j] + " |");
	    } //for 2
	    System.out.println();
	} //for
	
	System.out.print("    ");
	for(int i = 0; i < cols; i++){
	    System.out.print(i + "   ");
	}//for
	
	System.out.println();
	System.out.println();
	System.out.print("minesweeper-alpha$ ");
	
    } // printRound

    /**
     *If the player reveals a mine, this method displays a makeshift game over
     *visual then proceeds to exit the program.
     */
    
    public void playerLost(){
	System.out.println();
	System.out.println("Oh no... You revealed a mine!");
	System.out.println(" ");
	System.out.println("  __ _  __ _ _ __ ___   ___    _____   _____ _ __");
	System.out.println(" / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|");
	System.out.println("| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |");
	System.out.println(" \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|");
	System.out.println(" |___/");
	System.out.println();
	
	System.exit(0);
	
    }// playerLost

    /**
     *If the player chooses to quit a simple message is displayed
     *and the program exits.
     */
    
    public void playerQuit(){
	System.out.println();
	System.out.println("ლ(ಠ_ಠლ)");
	System.out.println("Y U NO PLAY MORE?");
	System.out.println("Bye!");
	System.exit(0);
  
    }// playerQuit
    
    /**
     *If the player's grid at any point meets the requirements to win
     *Minesweeper a doge visual is displayed, the player's score is calculated
     *and the program exits.
     */
    public void playerWon(){
	score = (rows * cols) - mines - rounds;
	
	System.out.println();
	System.out.println("░░░░░░░░░▄░░░░░░░░░░░░░░▄░░░░ \"So Doge\"");
	System.out.println("░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌░░░");
	System.out.println("░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐░░░ \"Such Score\"");
	System.out.println("░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐░░░");
	System.out.println("░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐░░░ \"Much Minesweeping\"");
	System.out.println("░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌░░░");
	System.out.println("░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌░░ \"Wow\"");
	System.out.println("░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐░░");
	System.out.println("░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌░");
	System.out.println("░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌░");
	System.out.println("▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐░");
	System.out.println("▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌");
	System.out.println("▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐░");
	System.out.println("░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌░");
	System.out.println("░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐░░");
	System.out.println("░░▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌░░");
	System.out.println("░░░░▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀░░░ CONGRATULATIONS!");
	System.out.println("░░░░░░▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀░░░░░ YOU HAVE WON!");
	System.out.println("░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▀▀░░░░░░░░ SCORE: " + score);
	
	System.exit(0);
	
    }// playerWon

    /**
     *If the player uses the help command this method is used to print
     *a list of the commands availabe in the Minesweeper game.
     */
    public void printHelp(){
	System.out.println();
	System.out.println("Commands Available...");
	System.out.println(" - Reveal: r/reveal row col");
	System.out.println(" -   Mark: m/mark   row col");
	System.out.println(" -  Guess: g/guess  row col");
	System.out.println(" -   Help: h/help");
	System.out.println(" -   Quit: q/quit");
	
    }// printHelp
  
    /**
     *This method is called during each round to check if the user's
     *grid meets the requirements to win the Minesweeper game. If the
     *requirements are not met, the method will set a boolean value to false.
     */
    public void winCheck(){
	win = true;
	
	for(int i = 0; i < board.length; i++){
	    for(int j = 0; j < board[i].length; j++){
		if((board[i][j] == "?")||(board[i][j] == " ")){
		    win = false;
		}// if
	    }// for
	}// for
	
	for(int i = 0; i < boardTF.length; i++){
	    for(int j = 0; j < boardTF[i].length; j++){
		if((boardTF[i][j])&&(board[i][j] != "F")){
		    win = false;
		}// if
	    }// for
	}// for
	
	
	
    }
    
    /**
     *This method considers the spaces around a particular square and
     *keeps count of how many mines it encounters in doing so.
     *<p>
     *This method returns a string representation of the number of mines
     *located adjacent to the square whose coordinates are passed into 
     *the method.
     *
     *@param  row  the value of the row containing the considered square
     *@param  col  the value of the column containing the considered square
     *@return      a string representation of the number of adjacent mines
     */
    public String numAdjacentMines(int row, int col){
	int count = 0;
	try{
	    if(boardTF[row][col+1])
		count++;
	}// try 1
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row][col-1])
		count++;
	}// try 2
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row+1][col])
		count++;
	}// try 3
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row-1][col])
		count++;
	}// try 4
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row+1][col+1])
		count++;
	}// try 5
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row+1][col-1])
		count++;
	}// try 6
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row-1][col+1])
		count++;
	}// try 7
	catch(ArrayIndexOutOfBoundsException e){}
	try{
	    if(boardTF[row-1][col-1])
		count++;
	}// try 8
	catch(ArrayIndexOutOfBoundsException e){}
	
	String num = Integer.toString(count);
	return num;
    
    }// numAdjacentMines
    
    /**                                                                                                           
     * Starts the game and execute the game loop.                                                                                     
     */
    public void run() {
	Scanner user = new Scanner(System.in);
	String input = "";
	int testR = 0, testC = 0;
	
	System.out.println("        _");
	System.out.println("  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __");
	System.out.println(" /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|");
	System.out.println("/ /\\/\\ \\ | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |");
	System.out.println("\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|");
	System.out.println("                                     ALPHA |_| EDITION");
	System.out.println();
	
	while(play){
	    printRound();
	    input = user.next();
	    
	    if((input.equalsIgnoreCase("h"))||(input.equalsIgnoreCase("help"))){
		printHelp();
		rounds++;
	    }// if
	    else if((input.equalsIgnoreCase("q"))||(input.equalsIgnoreCase("quit"))){
		playerQuit();
	    }// else if
	    else if((input.equalsIgnoreCase("r"))||(input.equalsIgnoreCase("reveal"))){
		if(user.hasNextInt())
		    testR = user.nextInt();
		if(user.hasNextInt())
		    testC = user.nextInt();
		
		if(boardTF[testR][testC]){
		    playerLost();
		}// if
		else{
		    board[testR][testC] = numAdjacentMines(testR,testC);
		}
		rounds++;
	    }// else if
	    else if((input.equalsIgnoreCase("g"))||(input.equalsIgnoreCase("guess"))){
		if(user.hasNextInt())
		    testR = user.nextInt();
		if(user.hasNextInt())
		    testC = user.nextInt();
		
		board[testR][testC] = "?";
		rounds++;
	    }// else if
	    else if((input.equalsIgnoreCase("m"))||(input.equalsIgnoreCase("mark"))){
		if(user.hasNextInt())
		    testR = user.nextInt();
		if(user.hasNextInt())
		    testC = user.nextInt();
		
		board[testR][testC] = "F";
		rounds++;
	    }// else if
	    else{
		System.out.println();
		System.out.println("ಠ_ಠ says, \"Command not recognized!\"");
		rounds++;
	    }// else
	    
	    winCheck();
	    if(win)
		playerWon();
	    
	    
	    
	}// while
	
       
	// TODO implement                                                                                                             

    } // run                                                                                                                          


    /**                                                                                                                               
     * The entry point into the program. This main methnd line arguments. If two integers are provided                                                        
     * as arguments, then a Minesweeper game is created and started with a                                                            
     * grid size corresponding to the integers provided and with 10% (rounded                                                         
     * up) of the squares containing mines, placed randomly. If a                           
     *                                                                                                                                
     * @param args the shell arguments provided to the program                                                                        
     */
    public static void main(String[] args) {
        /*                                                                                                                            
																      The following swit */

	Minesweeper game = null;

	switch (args.length) {

	    // random game                                                                                                                
	case 2:

	    int rows, cols;

	    // try to parse the arguments and create a game                                                                           
	    try {
		rows = Integer.parseInt(args[0]);
		cols = Integer.parseInt(args[1]);
		game = new Minesweeper(rows, cols);
		break;
	    } catch (NumberFormatException nfe){
	    }
	case 1:	    
	   String filename = args[0];
	     File file = new File(filename);

		     if (file.isFile()) {
			 game = new Minesweeper(file);
			 break;
		     } // if                                                                                                                   

		     // display usage statement                                                                                                    
	    default:

		     System.out.println("Usage: java Minesweeper [FILE]");
		     System.out.println("Usage: java Minesweeper [ROWS] [COLS]");
		     System.exit(0);
		     }// switch
	    // if all is good, then run the game
	    game.run();
	}



} // Minesweeper