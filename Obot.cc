#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


class game{
char board[16][8][8];
int heuristics[8][8];
int alpha_beta[20];
	

public:
	game()
	{
		int i,j,k;
		for(k=0;k<13;k++)
		{	
			for(i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{
					board[k][i][j]='X';;
					heuristics[i][j]=1;
				}		
			}
		}
	board[0][3][3]=board[0][4][4]='W';
	board[0][3][4]=board[0][4][3]='B';
	

	heuristics[0][0]=heuristics[7][7]=heuristics[0][7]=heuristics[7][0]=7;
	heuristics[1][1]=heuristics[1][6]=heuristics[6][1]=heuristics[6][6]=1;
	for(i=2;i<=5;i++)
		{
			heuristics[i][0]=heuristics[i][7]=heuristics[0][i]=heuristics[7][i]=4;
		}
	heuristics[0][1]=heuristics[1][0]=heuristics[6][0]=heuristics[7][1]=heuristics[0][6]=heuristics[1][7]=heuristics[7][6]=heuristics[6][7]=4;		
	heuristics[2][3]=heuristics[2][4]=heuristics[5][3]=heuristics[5][4]=2;
	heuristics[3][2]=heuristics[4][2]=heuristics[3][5]=heuristics[4][5]=2;
	}
	int score_report(int );
	int move_maker(int level,int xpos,int ypos);
	int make_change(int level,int ,int ,char);
	void game_play();
	void print_board(int );
	int board_status();
	void final_score();
	//only thing remaining is to write code to find out if the human player has no move to make
	//and declare it as a pass for the human player..
	//int user_move_possible();
};


/*
int game::user_move_possible()
{
int i,j,possible;
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			board[6][i][j]=board[0][i][j];	
		}
	}
	possible=move_maker(6,-1,-1);
}
*/

void game::print_board(int l)
{
int i,j;
int a=0,b=0;
cout<<"\n";
cout<<"    0  1  2  3  4  5  6  7\n";	
	for(i=0;i<=7;i++)
	{
		cout<<"\n"<<i<<" ";
		for(j=0;j<=7;j++)
		{
			if(board[l][i][j]=='W')
			{
			a++;
			cout<<"  "<<"O";
			}
			else if(board[l][i][j]=='B')
			{
			cout<<"  "<<(char)128;	
			b++;
			}
			else
			cout<<"  "<<"-";		
		}
	}
cout<<"\nScore:    BOT:"<<a<<"   Player:"<<b<<"\n";
}

void game::final_score()
{
int i,j;
int player=0;
int computer=0;
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(board[0][i][j]=='W')
			computer++;
			else if(board[0][i][j]=='B')
			player++;	
		}
	}
cout<<"\n\nFINAL SCORE:\nPlayer:"<<player<<"\nBOT:"<<computer;
if(player>computer)
cout<<"\n\nPlayer Wins!\n\n";
else if(player<computer)
cout<<"\n\nBot Wins!!\n\n";
else
cout<<"Draw";


}

int game::board_status()
{
int i,j;
int a=0,b=0;
int c=0;
for(i=0;i<8;i++)
{
	for(j=0;j<8;j++)
	{
		if(board[0][i][j]=='X')
		c++;
		if(board[0][i][j]=='W')
		b++;	
		if(board[0][i][j]=='B')
		a++;
if(a!=0 && b!=0 && c!=0)
return 1;
	}

}
return 0;
}

void game::game_play()
{
	int i,j;
	int xpos,ypos;
	int move;
	int valid=0;
	print_board(0);
	while(1)
	{
	while(1)	//call a function which will be 
	{	
	if(!board_status())
	{
		break;
	}
	valid=0;	
	cout<<"\nPlease enter the x position for your move player or -1 to pass"<<char(128)<<":";
	cin>>xpos;
	if(xpos==-1)
	{
		ypos=-1;
		cout<<"\nPass for player..\n";
		break;
	}
	cout<<"Please enter the y position for your move player "<<char(128)<<":";
	cin>>ypos;
	if(xpos>=0 && xpos<8 && ypos>=0 && ypos<8 && board[0][xpos][ypos]=='X')
		{
			valid=make_change(0,xpos,ypos,'B');
			if(valid==1)
				break;
			else
				board[0][xpos][ypos]='X';
		}
	cout<<"\nPlease enter a valid move!\n";
	print_board(0);
	}
	system("clear");
	cout<<"Your Move: ["<<xpos<<" , "<<ypos<<"]\n";
	print_board(0);
	if(!board_status())
	{
		break;
	}
	cout<<"\n\nTHINKING ... ... ... \n";
	for(i=0;i<20;i++)
	{
		if(i%2==0)
			alpha_beta[i]=-10000;
		else
			alpha_beta[i]=10000;
	}
	move=move_maker(0,-1,-1);	
	cout<<"Computers's Turn: ";
		if(move!=-1)
		{	
			cout<<"["<<(move-move%10)/10<<" , "<<move%10<<"]\n";
			make_change(0,(move-move%10)/10,move%10,'W');
		}
		else
		{
			cout<<"Computer Pass";
			if(xpos==-1)
			break;	
		}
	print_board(0);
	}

}


int game::move_maker(int level,int xpos,int ypos)
{
		char c;
		char d;
		int move=-1;
		int score=0;
		int move_count=0;
		int i,j;
		int x,y,z;
		int flag;
		int temp;
		int smart=0;
		int k,l;

		if((level%2)==0)
			{
				c='W';
				d='B';
				score=-10000;
			}
		else{
				c='B';
				d='W';
				score=10000;
			}
		
		for(i=level+1;i<20;i++)
		{
		if((i%2)==0)
			alpha_beta[i]=-10000;
		else
			alpha_beta[i]=10000;
		}

		if(level!=0)
		{	
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				board[level][i][j]=board[level-1][i][j];
			}
		}
		}

		if(xpos!=-1)
		{	
		//effect of the move should be reflected on the board	
		board[level][xpos][ypos]=d;
		make_change(level,xpos,ypos,d);
		}
		
		if(!board_status())
		{
				return score_report(level);
		}

		//assemble board with the move
		//need to find out all possible moves that c can be making now
		if(level!=9)
		{	
				for(i=0;i<8;i++)
				{
					for(j=0;j<8;j++)
					{
					//for each square in the grid perform the checks
						if(board[level][i][j]==c)
						{
								if(j<6)	//check for move to the right of the grid
								{
									if(board[level][i][j+1]==d)
									{
										flag=1;
										x=j+2;
										while(board[level][i][x]!='X' && x<8)
										{
											if(board[level][i][x]==c)
											{
												flag=0;
												break;
											}	
										x++;
										}	
										if(flag==1 && x<8)
										{
										smart=1;
										temp=move_maker(level+1,i,x);	
										//cout<<"[Score:"<<temp<<"]";
										
										y=x;
										x=i;
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]<score)
															{
															//cout<<"Breaking due to pruning";
															return score;	
															}
														}
													
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
															//cout<<"Breaking due to pruning";
															return score;	
															}
														}	
													
											}	
										}
									}	

								}//checking move to the right of the grid	
								if(j>1)//check to the left of the grid
								{
									if(board[level][i][j-1]==d)
									{
										flag=1;
										x=j-2;
										while(board[level][i][x]!='X' && x>=0)
										{
											if(board[level][i][x]==c)
											{
												flag=0;
												break;
											}	
										x--;
										}	
										if(flag==1 && x>=0)
										{
										smart=1;
										temp=move_maker(level+1,i,x);	
										//cout<<"[Score:"<<temp<<"]";
										
										y=x;
										x=i;
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
															{
																if(alpha_beta[k]<score)
																{
																//cout<<"Breaking due to pruning";
																return score;	
																}
															}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
															//cout<<"Breaking due to pruning";
															return score;	
															}
														}
											

											}
										}
									}

								}//checking move to the left of the grid	
								if(i<6)//check to the bottom
								{

									if(board[level][i+1][j]==d)
									{
										flag=1;
										x=i+2;
										while(board[level][x][j]!='X' && x<8)
										{
											if(board[level][x][j]==c)
											{
												flag=0;
												break;
											}	
										x++;
										}	
										if(flag==1 && x<8)
										{
										smart=1;
										temp=move_maker(level+1,x,j);	
										//cout<<"[Score:"<<temp<<"]";
										y=j;
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]<score)
															{
															//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
												//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
															//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											

											}
										}
									}	

								}//checking move to the bottom of the grid
								if(i>1)//check above
								{
									if(board[level][i-1][j]==d)
									{
										flag=1;
										x=i-2;
										while(board[level][x][j]!='X' && x>=0)
										{
											if(board[level][x][j]==c)
											{
												flag=0;
												break;
											}	
										x--;
										}	
										if(flag==1 && x>=0)
										{
											smart=1;
										temp=move_maker(level+1,x,j);	
										//cout<<"[Score:"<<temp<<"]";
										
										y=j;
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]<score)
															{
															//cout<<"Breaking due to pruning";
															return score;	
															}
														}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
															//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											
											}
										}
									}	

								}//checking move above in the grid	
								if(j<6 && i>1)//top right
								{
									if(board[level][i-1][j+1]==d)
									{
										flag=1;
										x=i-2;
										y=j+2;
										while(board[level][x][y]!='X' && x>=0 && y<8)
										{
											if(board[level][x][y]==c)
											{
												flag=0;
												break;
											}	
										x--;
										y++;
										}	
										if(flag==1 && x>=0 && y<8)
										{
										smart=1;
										temp=move_maker(level+1,x,y);	
										//cout<<"[Score:"<<temp<<"]";
										
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
															//cout<<"\nChecking for alpha beat pruning";
														
															for(k=(level-1);k>=0;k=k-2)
															{
															if(alpha_beta[k]<score)
															{
																//cout<<"Breaking due to pruning";
																return score;	
															}
															}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
											
														//cout<<"\nChecking for alpha beat pruning";
														
															for(k=(level-1);k>=0;k=k-2)
															{
																if(alpha_beta[k]>score)
																{
																//cout<<"Breaking due to pruning";
																return score;	
																}
															}
											
											}
										}
									}	
								}//checking move in the top right corner
								if(j>1 && i>1)//top left
								{
									if(board[level][i-1][j-1]==d)
									{
										flag=1;
										x=i-2;
										y=j-2;
										while(board[level][x][y]!='X' && x>=0 && y>=0)
										{
											if(board[level][x][y]==c)
											{
												flag=0;
												break;
											}	
										x--;
										y--;
										}	
										if(flag==1 && x>=0 && y>=0)
										{
											smart=1;
										temp=move_maker(level+1,x,y);	
										//cout<<"[Score:"<<temp<<"]";
										
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
												//cout<<"\nChecking for alpha beat pruning";
														
															for(k=(level-1);k>=0;k=k-2)
															{
																if(alpha_beta[k]<score)
																{
																	//cout<<"Breaking due to pruning";
																	return score;	
																}
															}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
																//cout<<"\nChecking for alpha beat pruning";
														
																for(k=(level-1);k>=0;k=k-2)
																{
																	if(alpha_beta[k]>score)
																	{
																	//cout<<"Breaking due to pruning";
																	return score;	
																	}
																}
											
											}
										}
									}	
								}//checking move in the top left corner
								if(j<6 && i<6)//bottom right
								{
									if(board[level][i+1][j+1]==d)
									{
										flag=1;
										x=i+2;
										y=j+2;
										while(board[level][x][y]!='X' && x<8 && y<8)
										{
											if(board[level][x][y]==c)
											{
												flag=0;
												break;
											}	
										x++;
										y++;
										}	
										if(flag==1 && x<8 && y<8)
										{
											smart=1;
										temp=move_maker(level+1,x,y);	
										//cout<<"[Score:"<<temp<<"]";
										
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]<score)
															{
																//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
															//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											
											}
										}
									}	


								}//checking move in the bottom right corner	
								if(j>1 && i<6)//bottom left
								{
									if(board[level][i+1][j-1]==d)
									{
										flag=1;
										x=i+2;
										y=j-2;
										while(board[level][x][y]!='X' && x<8 && y>=0)
										{
											if(board[level][x][y]==c)
											{
												flag=0;
												break;
											}	
										x++;
										y--;
										}	
										if(flag==1 && x<8 && y>=0)
										{
											smart=1;
										temp=move_maker(level+1,x,y);	
										//cout<<"[Score:"<<temp<<"]";
										
											if((level%2)==0)
											{
												if(temp>score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]<score)
															{
															//cout<<"Breaking due to pruning";
																return score;	
															}
														}
											
											}
											else{
												if(temp<score)
												{
													score=temp;
													move=((10*x)+y);
													alpha_beta[level]=temp;
												}
														//cout<<"\nChecking for alpha beat pruning";
														
														for(k=(level-1);k>=0;k=k-2)
														{
															if(alpha_beta[k]>score)
															{
																//cout<<"Breaking due to pruning";
															return score;	
															}
														}
											

											}
										}
									}	
								}//checking move in the bottom left corner				
						}		
					}

				}
		


			if(smart==0 && level==0)
			{
				return -1;
			}	
			else if(smart==0){
				return move_maker(level+1,-1,-1);	
			}

		}		
		
		if(level==9)
		{
			return score_report(level);
		}
		if(level==0)
		return move;
		else
		return score;		
}



int game::score_report(int a)
{
int i,j;
int score=0;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(board[a][i][j]=='W')
				score=score+heuristics[i][j]+2;
		}
	
	}
return score;

}

int game::make_change(int level,int x,int y,char sym)
{
	int i,j,k,l;
	int use;
	char c=sym;
	char d;
	int flag=0;
	int intflag=0;

	if(c=='W')
		d='B';
	else if(c=='B')
		d='W';
	//code for changing pieces
	
	board[level][x][y]=c;

	flag=0;
	if(y>1)	//check for pieces to the left
	{
		if(board[level][x][y-1]==d)
		{
			i=y-1;
			while(board[level][x][i]==d && i>0)
			{
				flag=1;
				i--;
			}	
			if(board[level][x][i]==c && flag==1)
			{
				intflag=1;
				for(use=i;use<=y;use++)
					board[level][x][use]=c;
			}	
		}	
	}//check for elements to the left ends

	flag=0;
	if(y<6)	//check for pieces to the right
	{
		if(board[level][x][y+1]==d)
		{
			i=y+1;
			while(board[level][x][i]==d && i<7)
			{
				flag=1;
				i++;
			}	
			if(board[level][x][i]==c && flag==1)
			{
				intflag=1;
				for(use=i;use>=y;use--)
					board[level][x][use]=c;
			}	
		}	
	}//check for elements to the right ends

	flag=0;
	if(x<6)	//check for pieces to the bottom
	{
		if(board[level][x+1][y]==d)
		{
			i=x+1;
			while(board[level][i][y]==d && i<7)
			{
				flag=1;
				i++;
			}	
			if(board[level][i][y]==c && flag==1)
			{
				intflag=1;
				for(use=i;use>=x;use--)
					board[level][use][y]=c;
			}	
		}	
	}//check for elements to the bottom

	flag=0;
	if(x>1)	//check for pieces to the top
	{
		if(board[level][x-1][y]==d)
		{
			i=x-1;
			while(board[level][i][y]==d && i>0)
			{
				flag=1;
				i--;
			}	
			if(board[level][i][y]==c && flag==1)
			{
				intflag=1;
				for(use=i;use<=x;use++)
					board[level][use][y]=c;
			}	
		}	
	}//check for elements to the top

	flag=0;
	if(x<6 && y<6)//check for elements in the bottom right
	{
		if(board[level][x+1][y+1]==d)
		{
			i=x+1;
			j=y+1;
			while(board[level][i][j]==d && i<7 && j<7)
			{
				flag=1;
				i++;
				j++;
			}
			if(board[level][i][j]==c && flag==1)
			{
				intflag=1;
				while(i>=x && j>=y)
				{
					board[level][i][j]=c;	
					i--;
					j--;
				}
			}
		}
	}//check for elements in the bottom right	

	flag=0;
	if(x>1 && y>1)//check for elements in the top left
	{
		if(board[level][x-1][y-1]==d)
		{
			i=x-1;
			j=y-1;
			while(board[level][i][j]==d && i>0 && j>0)
			{
				flag=1;
				i--;
				j--;
			}
			if(board[level][i][j]==c && flag==1)
			{
				intflag=1;
				while(i<=x && j<=y)
				{
					board[level][i][j]=c;	
					i++;
					j++;
				}
			}
		}
	}//check for elements in the top left side

	flag=0;
	if(x>1 && y<6)//check for elements in the top right
	{
		if(board[level][x-1][y+1]==d)
		{
			i=x-1;
			j=y+1;
			while(board[level][i][j]==d && i>0 && j<7)
			{
				flag=1;
				i--;
				j++;
			}
			if(board[level][i][j]==c && flag==1)
			{
				intflag=1;
				while(i<=x && j>=y)
				{
					board[level][i][j]=c;	
					i++;
					j--;
				}
			}
		}
	}//check for elements in the top right	

	flag=0;
	if(x<6 && y>1)//check for elements in the bottom left
	{
		if(board[level][x+1][y-1]==d)
		{
			i=x+1;
			j=y-1;
			while(board[level][i][j]==d && i<7 && j>0)
			{
				flag=1;
				i++;
				j--;
			}
			if(board[level][i][j]==c && flag==1)
			{
				intflag=1;
				while(i>=x && j<=y)
				{
					board[level][i][j]=c;	
					i--;
					j++;
				}
			}
		}
	}//check for elements in the bottom left	
return intflag;
cout<<"Intflag:"<<intflag;
}




int main(){
game g;
g.game_play();
g.final_score();
}