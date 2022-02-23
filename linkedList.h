#ifndef LINKEDLIST
#define LINKEDLIST

enum BlockType {
	snakeHead,
	snakeTail,
	extension
};

struct node {
	int x;
	int y;
	enum BlockType type;
	struct node *next;
};
struct node *addNode(struct node **head);
void removeLastNode(struct node *head);
struct node * addNodeEnd(struct node *head);
struct node *getLastNode(struct node *head);

int terribleSearch(struct node *head,int x,int y);

#endif
