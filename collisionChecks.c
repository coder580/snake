#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "snake.h"
//check if snake ran into itself
int selfCollisionCheck(struct node *head)
{
        if(head->next==NULL)
        {
                printf("selfCollisionCheck: head->next is null\n");
                exit(-1);
        }

        struct node *iterator=head->next;
        do {
                if(head->x==iterator->x && head->y==iterator->y)
                        return 1;
                iterator=iterator->next;
        } while ( iterator!=NULL );
        return 0;
}

//check if snake ran into a a wall
int wallCollisionCheck(struct node *head)
{
        if((head->x < 0 || head->x > xmax_l) || (head->y < 0 || head->y > ymax_l))
                return 1;
        return 0;
}

//check if the snake killed itself yet
int aliveCheck(struct node *head)
{
        return (selfCollisionCheck(head) || wallCollisionCheck(head));
}


int snakeEnlargementPillCheck(struct node *head)
{
        if(head->x==pill_x && head->y==pill_y)
                return 1;
        return 0;
}

