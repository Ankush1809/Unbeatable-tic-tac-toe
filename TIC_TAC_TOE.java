import java.applet.*;
import java.awt.*;
import java.awt.event.*;
/*
<applet code="TIC_TAC_TOE" width=500 height=400>
</applet>
*/

class play
{
 int win(int board[],int pos[])
	{
		int wins[][]={{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
		int i;
		for(i=0; i<8; i++)
		{
			if(board[wins[i][0]]!=0 && board[wins[i][0]]==board[wins[i][1]] && board[wins[i][0]]==board[wins[i][2]])
			{
				for(int j=0;j<=2;j++)
					pos[j]=wins[i][j];
				return board[wins[i][2]];	
			}
		}		
		return 0;
	}	

	int minimax(int board[],int player,int pos[])
	{
		int winner = win(board,pos);
		if(winner!=0)
			return winner*player; 	
		int move=-1;
		int score=-2;
		int i;
		for(i=0; i<9; i++)
		{
			if(board[i]==0)
			{
				board[i]=player;
				int thisscore = -minimax(board,player*-1,pos);
				if(thisscore > score)
				{
					score=thisscore;
					move=i;
				}	
				board[i]=0;	
			}	
		}
		if(move==-1)
			return 0;
		return score;
	}

	int computerMove(int board[],int pos[])
	{
    		int move = -1;
    		int score = -2;
    		int i;
    		for(i = 0; i < 9; i++)
   		{
			if(board[i] == 0)
			{
	    			board[i] = 1;
	    			int tempScore = -minimax(board, -1,pos);
	    			board[i] = 0;
	    			if(tempScore > score)
	    			{
					score = tempScore;
					move = i;
	    			}
			}
    		}
   		board[move] = 1;
   		return move;
	}
}


public class TIC_TAC_TOE extends Applet implements ActionListener 
{
	Font myFont = new Font("Dialog",Font.BOLD,25);
	
	Label title = new Label("TIC-TAC-TOE",Label.CENTER);
	Label outcome = new Label("Your Turn",Label.CENTER);
	Label comp = new Label("Computer:0",Label.CENTER);
	Label you = new Label("Player:x",Label.CENTER);

	Button play2;
 	Button reset;
 	Button[] buttons=new Button[9];
 	
	play obj = new play();
 	
	int[] board={0,0,0,0,0,0,0,0,0};
	int[] pos = new int[3];
 	int x,turn=0;

	public void init()
 	{
		setBackground(Color.white);
		setFont(new Font("Dialog",Font.BOLD,30));
		comp.setFont(myFont);
		you.setFont(myFont);
  		
		for(int i=0;i<9;i++)
   			buttons[i]=new Button("");
 		play2=new Button("Play 2nd");
 		reset=new Button("Reset");
  
  		buttons[0].setBounds(50,50,100,100);
 		buttons[1].setBounds(150,50,100,100);
  		buttons[2].setBounds(250,50,100,100);
  		buttons[3].setBounds(50,150,100,100);
  		buttons[4].setBounds(150,150,100,100);
  		buttons[5].setBounds(250,150,100,100);
  		buttons[6].setBounds(50,250,100,100);
  		buttons[7].setBounds(150,250,100,100);
  		buttons[8].setBounds(250,250,100,100);
  		play2.setBounds(360,70,130,40);  
  		reset.setBounds(380,290,90,40);
  		
		outcome.setBounds(50,360,300,30);
  		title.setBounds(50,10,300,30);
		comp.setBounds(350,167,150,30);
		you.setBounds(350,202,150,30);
 
  		for(int i=0;i<9;i++)
  			buttons[i].addActionListener(this);
 		reset.addActionListener(this);
  		play2.addActionListener(this);
 	}
 
	public void paint(Graphics g)
	{
  		add(title);
  		add(outcome);
		add(comp);
		add(you);
  		for(int i=0;i<9;i++)
    			add(buttons[i]);
		add(reset);
  		add(play2);
 	}

 	public void actionPerformed(ActionEvent ae)
 	{
  		for(int i=0;i<9;i++)
  		{
			if(ae.getSource()==buttons[i] && buttons[i].getLabel()=="" && obj.win(board,pos)==0)
			{
         	 		buttons[i].setLabel("x");
				outcome.setText("");
	  			board[i]=-1;
	  			turn++;
	  			if(obj.win(board,pos)==-1)
						outcome.setText("You Win");
	 			else if(turn==9)
         			{
 	  				if(obj.win(board,pos)==0)
						outcome.setText("A Draw");
	  				break;
         			}
	  			x=obj.computerMove(board,pos);
         			buttons[x].setLabel("0");
	  			turn++;
				outcome.setText("Your Turn");
        		}
       
        		if(obj.win(board,pos)==1)
             			{
					outcome.setText("Computer Wins");
					for(int k=0;k<=2;k++)
						buttons[pos[k]].setBackground(Color.red);
				}
			 else if(turn==9)
         		 {
	  			if(obj.win(board,pos)==0)
					outcome.setText("A Draw");
	  			break;
			 }
         	}
   
 		if(ae.getSource()==reset)
  		{
  			for(int i=0;i<9;i++)
  			{
	 			buttons[i].setLabel("");
				buttons[i].setBackground(new Color(224,224,224));
	 			board[i]=0;
			}
			play2.setBackground(new Color(224,224,224));
	 		outcome.setText("Your Turn");
	 		turn=0;
   		}

		if(ae.getSource()==play2)
		{
			if(turn==0)
  				{  
					play2.setBackground(Color.green);
					outcome.setText("");
 	  				x=obj.computerMove(board,pos);
          				buttons[x].setLabel("0");
	  				turn++; 
					outcome.setText("Your Turn");
  				}	
		}
 	} 
}
