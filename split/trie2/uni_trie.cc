#include <stdio.h>
#include <iostream>
#include "uni_trie.h"
using namespace std;

int number_nodes = 0;

void UniTrie::init_trie(Node** pnode)
{
	*pnode = new Node();
	(*pnode)->data = -1;
	(*pnode)->lchild = (*pnode)->rchild = NULL;
} 

void UniTrie::insert_node(Node* pnode, int floor[PREFIX_LENGTH])
{
	Node* node;
	FILE* file;
	int hop,temp;
	floor[0] = 1;

	for(temp = 1; temp < PREFIX_LENGTH; temp++)
	{
		floor[temp] = 0;
	}

	char buffer[BUFFER_SIZE];
	char prefix[PREFIX_LENGTH];
	file = fopen("unique_ipv4.txt","r");
	char* p = NULL;
	char* q = NULL;	

	while(fgets(buffer,BUFFER_SIZE,file))
	{
		
		node = pnode;
		temp = 0;
		sscanf(buffer,"%s %d",prefix,&hop);
		p = prefix;
		
		while(*p != '\0')
		{
			q = p;
			q++;

			if((*p == '0')&&(*q != '\0'))
			{
				if(node->lchild == NULL)
				{
					init_trie(&node->lchild);
					node = 	node->lchild;
					
					temp++;
					floor[temp]++;
				}
				else
				{
					node = node->lchild;
					temp++;
				}
			}
			
			if((*p == '1')&&(*q != '\0'))
			{
				if(node->rchild == NULL)
				{
					init_trie(&node->rchild);
					node = node->rchild;
					temp++;
					floor[temp]++;
				}
				else
				{
					node = node->rchild;
					temp++;
				}
			}
			p++;
			if(*q == '\0')
			{
				p--;
				if(*p == '0')
				{
					node->data= hop;
				}
				else if(*p == '1')
				{
					node->data = hop;
				}
				break;
			}

		}
		
	}
	fclose(file);
}


void UniTrie::trieprint(Node* pnode,int level)
{
	Node* node = pnode;

	if(pnode != NULL)
	{
		if(level == 24)
		{
			if (pnode->lchild != NULL || node->rchild != NULL)
			{
				++number_nodes;
			}
		}
		trieprint(node->lchild,++level);
		trieprint(node->rchild,++level);
	}
}


















