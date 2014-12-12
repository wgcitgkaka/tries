#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node
{
	int left_data;
	int right_data;
	int left_level;
	int right_level;
	struct Node* lchild;
	struct Node* rchild;	
}Node;

#endif
