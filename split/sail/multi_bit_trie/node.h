#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node
{
	//int left_data;
	//int right_data;
	int left_length;
	int right_length;
	//int lchild;
	//int rchild;
	int left_info;
	int right_info;	
}Node;

typedef struct Mnode
{
	int* info;
	int* length;
	vector<vector<string> > next_hop;
	//string addr2;
}Mnode;
#endif
