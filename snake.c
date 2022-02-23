#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linkedList.h"
#include "collisionChecks.h"
#include "snake.h"

#define CNFG_IMPLEMENTATION
#include "./rawdraw/CNFG.h"
#include "./rawdraw/os_generic.h"

struct node *Head;

int ctrl=0;

#define PIXEL_SIZE 20

short xmax=0;
short ymax=0;

short xmax_l=0;
short ymax_l=0;

short pill_x=10;
short pill_y=10;

int timeDelta=0;

enum directions {
	up,down,left,right
};
int direction=right;

void getSizeInfo();

void HandleButton( int x, int y, int button, int bDown )
{
	printf( "Button: %d,%d (%d) -> %d\n", x, y, button, bDown );
}

void HandleKey( int keycode, int bDown )
{
	switch(keycode)
	{
		case 65280:
			getSizeInfo();
			break;
		default:
			break;
	}
	if(!bDown)
		return;
	switch(keycode)
	{
		case 65362:
			//printf("up\n");
			if(direction!=up)
				direction=down;
			break;

		case 65364:
			//printf("down\n");
			if(direction!=down)
				direction=up;
			break;

		case 65363:
			//printf("right\n");
			if(direction!=left)
				direction=right;
			break;
		case 65361:
			//printf("left\n");
			if(direction!=right)
				direction=left;
			break;



		case CNFG_KEY_ESCAPE:
			exit(0);
			break;
		default:
			printf( "Key: %d -> %d\n", keycode, bDown );
			break;
	}
}

void HandleMotion(int x, int y, int mask ){}

void HandleDestroy()
{
	printf( "Destroying\n" );
	exit(10);
}


void putLargePixel(int x,int y)
{
	int x1=x*PIXEL_SIZE;
	int y1=y*PIXEL_SIZE;

	int x2=x1+PIXEL_SIZE;
	int y2=y1+PIXEL_SIZE;

	//	printf("x1: %d, x2: %d, y1: %d, y2: %d\n",x1,x2,y1,y2);
	CNFGTackRectangle(x1,y1,x2,y2);
}

void randPill()
{
	pill_x=(rand()%(xmax_l+1));
	pill_y=(rand()%(ymax_l+1));
}
void extendSnake(struct node *head)
{
	struct node *last=getLastNode(head);
	struct node *newnode=addNodeEnd(head);
	newnode->x=last->x;
	newnode->y=last->y;

	//everything is backwards because the origin point in the window is the top left
	switch(direction)
	{
		case up:
			newnode->y--;
			break;
		case down:
			newnode->y++;
			break;
		case left:
			newnode->x++;
			break;
		case right:
			newnode->x--;
			break;
		default:
			printf("no clue what direction to go\n");
			exit(-1);
			break;
	}

}

void getSizeInfo()
{
	CNFGGetDimensions(&xmax,&ymax);
	xmax_l=((xmax)/PIXEL_SIZE)-1;
	ymax_l=((ymax)/PIXEL_SIZE)-1;
}





void movementCycle(struct node **head,int dir)
{
	struct node *oldHead=*head;
	*head=addNode(head); //create new head node for the head of the snake

	switch(dir)
	{
		case up:
			(*head)->x=oldHead->x;
			(*head)->y=oldHead->y+1;
			break;
		case down:
			(*head)->x=oldHead->x;
			(*head)->y=oldHead->y-1;
			break;
		case left:
			(*head)->x=oldHead->x-1;
			(*head)->y=oldHead->y;
			break;
		case right:
			(*head)->x=oldHead->x+1;
			(*head)->y=oldHead->y;
			break;
		default:
			printf("problem occured in movementCycle\n");
			exit(-1);
			break;
	}
	if(aliveCheck(*head))
	{
		printf("you died\n");
		exit(0);
	}
	if(snakeEnlargementPillCheck(*head))
	{
		randPill();
		extendSnake(*head);
	}
	removeLastNode(*head); //we created a new head node so we must remove the back node to create the illusion of the snake moving
}

void gameCycle(struct node **head)
{
	movementCycle(head,direction);

	CNFGColor(0xFF0000FF);
	putLargePixel(pill_x,pill_y);

	struct node *iterator=*head;
	CNFGColor( 0xffffff );
	do {
		putLargePixel(iterator->x,iterator->y);
		iterator=iterator->next;
	} while ( iterator!=NULL );

}

int main()
{
	srand(time(NULL));
	Head=NULL; //addNode() leaves the old heads "next" pointer alone if the head is null

	randPill();

	for(int i=0;i<3;i++)
	{
		Head=addNode(&Head);
		Head->x=i;
		Head->y=0;
	}

	double frameDelay=512;

	double lastTime=0;
	double thisTime=0;

	CNFGBGColor = 0x800000;
	CNFGSetup( "Snake", 400, 400 );
	getSizeInfo();


	while ( 1 ) {

		CNFGHandleInput();
		CNFGClearFrame();
		CNFGColor( 0xffffff );

		gameCycle(&Head);

		CNFGSwapBuffers();
		thisTime = OGGetAbsoluteTime();

		double toWait = (frameDelay-(thisTime-lastTime));

		if(toWait>0)
			usleep(toWait*1000);
		lastTime = thisTime;
	}
}
