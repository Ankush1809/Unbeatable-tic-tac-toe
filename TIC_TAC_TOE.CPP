#include <stdio.h>
#include <conio.h>
void gridChar(int i, int x)
{
    switch(i)
    {
	case -1:
	    printf(" X");
	    break;
	case 0:
	    printf(" %d",x+1);
	    break;
	case 1:
	    printf(" O");
	    break;
    }
}

void draw(int b[9],int x)
{
    printf("\t\t\t\tTIC TAC TOE\n");
    if(x==1)
	printf("\nYou:X\tComputer:O\n\n");
    else
	printf("\nPlayer 1:X\tPlayer 2:O\n\n");
    gridChar(b[0],0);printf(" |");gridChar(b[1],1);printf(" |");gridChar(b[2],2);printf("\n");
    printf("---+---+---\n");
    gridChar(b[3],3);printf(" |");gridChar(b[4],4);printf(" |");gridChar(b[5],5);printf("\n");
    printf("---+---+---\n");
    gridChar(b[6],6);printf(" |");gridChar(b[7],7);printf(" |");gridChar(b[8],8);printf("\n");
}

int win(const int board[9])
{

    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i)
    {
	if(board[wins[i][0]] != 0 &&
	   board[wins[i][0]] == board[wins[i][1]] &&
	   board[wins[i][0]] == board[wins[i][2]])
	    return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player)
{

    int winner = win(board);
    if(winner != 0)
	return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i)
    {
	if(board[i] == 0)
	{
	    board[i] = player;
	    int thisScore = -minimax(board, player*-1);
	    if(thisScore > score)
	    {
		score = thisScore;
		move = i;
	    }
	    board[i] = 0;
	}
    }
    if(move == -1) return 0;
    return score;
}

int computerMove(int board[9])
{
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i)
    {
	if(board[i] == 0)
	{
	    board[i] = 1;
	    int tempScore = -minimax(board, -1);
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

void playerMove(int board[9])
{
    printf("\nYour turn");
    int move = 0;
    do
    {
	printf("\nInput move (1 - 9): ");
	scanf("%d",&move);
	if(move>9 || move<=0)
	{
	    printf("\nInvalid move!");
	    continue;
	}
	if(board[move-1]!=0)
	{
	    printf("Position already occupied!");
	    continue;
	}

	printf("\n");
    }
    while (move > 9 || move <= 0 || board[move-1]!=0);
    board[move-1] = -1;
}

int playerMove(int board[9], int player)
{
    int move=0;
    if(player==1)
	printf("\nPlayer 1's turn");
    else
	printf("\nPlayer 2's turn");
    do
    {
	printf("\nInput move(1 - 9): ");
	scanf("%d",&move);
	if(move>9 || move <=0)
	{
	    printf("\nInvalid move!");
	    continue;
	}
	if(board[move-1]!=0)
	{
	    printf("Position already occupied!");
	    continue;
	 }
    }
    while(move>9 || move<=0 || board[move-1]!=0);
    if(player==1)
	board[move-1]=-1;
    else
	board[move-1]=1;
    return move;
}
void main()
{
    clrscr();
    int ch=0;
    while(ch!=3)
    {
	int board[9] = {0,0,0,0,0,0,0,0,0};
	clrscr();
	printf("\n1.Player VS Computer\n2.Player VS Player\n3.Exit\n");
	printf("\nEnter your choice:");
	scanf("%d",&ch);
	clrscr();
	switch(ch)
	{
	    case 1:
	    {
		printf("\nPlay (1)st or (2)nd? ");
		int player=0;
		scanf("%d",&player);
		printf("\n");
		unsigned turn;
		for(turn = 0; turn < 9 && win(board) == 0; ++turn)
		{
		    clrscr();
		    if((turn+player) % 2 == 0)
		    {
			int move;
			move=computerMove(board);
			draw(board,1);
			printf("\nComputer played at %d.\n",move+1);
			printf("Press enter to continue.\n");
			getch();
		    }
		    else
		    {
		    draw(board,1);
		    playerMove(board);
		    }
		}
		switch(win(board))
		{
		    case 0:
			clrscr();
			draw(board,1);
			printf("\nA draw.\n");
			break;
		    case 1:
			clrscr();
			draw(board,1);
			printf("\nYou lose.\n");
			break;
		    case -1:
			clrscr();
			draw(board,1);
			printf("\nYou win.Inconceivable!\n");
			break;
		}
		break;
	    }
	    case 2:
	    {
		int turn,move;
		for(turn=1;turn<=9 && win(board)==0;turn++)
		{
		    clrscr();
		    if((turn)%2!=0)
		    {
			draw(board,2);
			move=playerMove(board,1);
			clrscr();
			draw(board,2);
			printf("\nPlayer 1 played at %d.",move);
			printf("\nPress enter to continue.");
			getch();
		    }
		    else
		    {
			draw(board,2);
			move=playerMove(board,2);
			clrscr();
			draw(board,2);
			printf("\nPlayer 2 played at %d.",move);
			printf("\nPress enter to continue.");
			getch();
		    }
		}
		switch(win(board))
		{
		    case 0:
			clrscr();
			draw(board,2);
			printf("\nA draw. Good game.");
			break;
		    case 1:
			clrscr();
			draw(board,2);
			printf("\nPlayer 2 wins.");
			break;
		    case -1:
			clrscr();
			draw(board,2);
			printf("\nPlayer 1 wins.");
			break;
		}
		break;
	    }
	    case 3:
		printf("\nThanks for playing. You will be missed.\n");
		break;
	    default:
		printf("\nInvalid choice!\nPress enter to enter choice again.");
	}
	getch();
    }
}
