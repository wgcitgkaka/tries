#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node
{
	//int left_data;
	//int right_data;
	int data;
	struct Node* lchild;
	struct Node* rchild;	
}Node;

#endif
