# include<iostream>
#include<stdlib.h>
#include <stdlib.h> 
#include<time.h> 
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;


int kbhit(void);


/* 

Class game:
* --dimension of boundry length X width.
* -- change(ch) gets char ch as argument and decide the direction of motion of snake head
* -- display()  display in the screen the current state of the game

*/

class game 
{
	int length,width,head_x,head_y,fruit_x,fruit_y,snake_length;
	char map[50][50];
public:


game()
{
	length=30;
	width=50;
	snake_length=1;
	head_x=1;
	head_y=1;
	create_fruit();
	load_map();
	
}
void create_fruit()
{
	 srand(time(0));
	 fruit_x=max(1 , rand()%length-1);
	 fruit_y=max(1 , rand()%width-1);
	 map[fruit_x][fruit_y]='*';
	
}

void load_map()
{
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i==0 || j==0 || i==length-1 || j==width-1)
			{
				map[i][j]='#';
			}
			else
			{
				map[i][j]=' ';
			}
		}
	}
}
void change(char ch)
{
	int n=snake_length;
	while(n--){
	map[head_x][head_y]='$';
	}
	switch(ch)
	{
		case 'w':head_x=max(1,head_x-1);break;			// move up
		case 's':head_x=min(head_x+1,length-2);break;	// move down
		case 'a':head_y=max(1,head_y-1);break;			// move left
		case 'd':head_y=min(head_y+1,width-2);break;	//move right
	}
	if(map[head_x][head_y]=='*')
	{
		snake_length++;
	}
	map[head_x][head_y]='@';
	
	
	
}
void display()
{
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			cout<<map[i][j];
		}
		cout<<"\n";
	}
	cout<<"\n\n SCORE :"<<snake_length-1;
}
};



int main()
{
	game play;
	
	char ch=' ',ch_temp;
	int fruit_time=0;
	while(true)
	{	if(kbhit()!=0)
		{
			ch_temp=getchar();
			if(ch_temp=='q')
			break;
			if(ch_temp=='w' || ch_temp=='s' || ch_temp=='a' || ch_temp=='d')
			{
				ch=ch_temp;
			}
			
		}
		if(fruit_time==50)
		{
			fruit_time=0;
			play.create_fruit();
		}
		usleep(100000);
		system("clear");
		play.change(ch);
		play.display();
		fruit_time++;
	}
	

return(0);
}










int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
