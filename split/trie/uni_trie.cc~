#include <stdio.h>
#include "uni_trie.h"

void UniTrie::init_trie(Node** pnode)
{
	*pnode = new Node();
	(*pnode)->left_data = (*pnode)->right_data = -1;
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
	file = fopen("fibtable.txt","r");
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
					node->left_data = hop;
				}
				else if(*p == '1')
				{
					node->right_data = hop;
				}
				break;
			}

		}
		
	}
	fclose(file);
}

void UniTrie::leafpush(Node* pnode)
{
	Node* node = pnode;
	if(node != NULL)
	{
		if(node->lchild != NULL)
		{		
			if(node->lchild->left_data == -1)
				node->lchild->left_data = node->left_data;
			if(node->lchild->right_data == -1)
				node->lchild->right_data = node->left_data;
		}

		if(node->rchild != NULL)
		{
			if(node->rchild->left_data == -1)
				node->rchild->left_data = node->right_data;
			if(node->rchild->right_data == -1)
				node->rchild->right_data = node->right_data;
		}
		
		leafpush(node->lchild);
		leafpush(node->rchild);

	}

}

void UniTrie::push(Node* pnode)
{
	Node* node = pnode;
	if(node != NULL)
	{
		if(node->lchild != NULL)
			node->left_data = -1;
		if(node->rchild != NULL)
			node->right_data = -1;

		push(node->lchild);
		push(node->rchild);
	}
}

void UniTrie::trieprint(Node* pnode)
{
	Node* node = pnode;

	if(pnode != NULL)
	{
		printf("left=%d,right=%d\n",node->left_data,node->right_data);
		trieprint(node->lchild);
		trieprint(node->rchild);
	}
}




















