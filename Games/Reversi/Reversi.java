
public class Reversi {
	
	public static void main(String[] args) {
		ReversiBoard game = new ReversiBoard();	
		String player1 = "";
		String player2 = "";
		try{
		player1 = args[0];
		player2 = args[1];
		}
		catch (ArrayIndexOutOfBoundsException a){
		System.out.println("WRONG COMMAND");
		System.exit(0);
		}
		
		if(player1.equals("Human") && player2.equals("Human"))
		{		
		game.PlayerVsPlayer();
		}
		else if(player1.equals("Human") && player2.equals("RandomComputerPlayer"))
		{
		game.PlayerVsComputerPlayer();
		}
		else if(player1.equals("RandomComputerPlayer") && player2.equals("RandomComputerPlayer"))
		{
		game.ComputerPlayerVsComputerPlayer();
		}
		else if(player1.equals("RandomComputerPlayer") && player2.equals("Human"))
		{
		game.RandomComputerPlayerVsPlayer();
		}
		else
		{
			System.out.println("WRONG COMMAND");
			System.exit(0);
		}
		
	}
}
