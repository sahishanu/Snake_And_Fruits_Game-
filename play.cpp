# include<iostream>
#include<stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;


int kbhit(void);


/* 

Class game:
* --dimension of boundry length X width
* -- change(ch) gets char ch as argument and decide the direction of motion of snake head
* -- display()  display in the screen the current state of the game

*/

class game 
{
	int length,width,head_x,head_y;
public:


game()
{
	length=30;
	width=50;
	head_x=1;
	head_y=1;
}
void change(char ch)
{
	switch(ch)
	{
		case 'w':head_x=max(1,head_x-1);break;			// move up
		case 's':head_x=min(head_x+1,length-2);break;	// move down
		case 'a':head_y=max(1,head_y-1);break;			// move left
		case 'd':head_y=min(head_y+1,width-2);break;	//move right
	}
}
void display()
{
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i==0 || i==length-1 || j==0 || j==width-1)
			{
				cout<<"#";//display boundry by '#'
			}
			
			else if(i==head_x && j==head_y)
			{
				cout<<"@"; //display head by '@'
			}
			else
			cout<<" "; // display air by ' '
		}
		cout<<"\n";
	}
}
};



int main()
{
	game play;
	
	char ch=' ';
	while(true)
	{	if(kbhit()!=0)
		{
			ch=getchar();
			if(ch=='q')
			break;
		}
		usleep(100000);
		system("clear");
		play.change(ch);
		play.display();
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
