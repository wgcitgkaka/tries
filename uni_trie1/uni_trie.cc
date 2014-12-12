#include <stdio.h>
#include "uni_trie.h"

void UniTrie::init_trie(Node** pnode)
{
	*pnode = new Node();
	(*pnode)->left_data = (*pnode)->right_data = -1;
	(*pnode)->left_level = (*pnode)->right_level = 0;
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

	while(feof(file) == 0)
	{
		
		node = pnode;
		temp = 0;
		fgets(buffer,BUFFER_SIZE,file);
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

void UniTrie::leafpush2(Node* pnode)
{
	Node* node = pnode;
	if(node != NULL)
	{
		if(node->lchild != NULL)
		{		
			if(((node->lchild->left_data == -1)&&(node->left_data != -1))||((node->lchild->left_data != -1)&&(node->left_data != -1)&&(node->lchild->left_level > node->left_level)))
			{
				node->lchild->left_data = node->left_data;
				node->lchild->left_level = node->left_level + 1;
			}
			if(((node->lchild->right_data == -1)&&(node->left_data != -1))||((node->lchild->right_data != -1)&&(node->left_data != -1)&&(node->lchild->right_level > node->left_level)))
			{
				node->lchild->right_data = node->left_data;
				node->lchild->right_level = node->left_level + 1;
			}
		}

		if(node->rchild != NULL)
		{
			if(((node->rchild->left_data == -1)&&(node->right_data != -1))||((node->rchild->left_data != -1)&&(node->right_data != -1)&&(node->rchild->left_level > node->right_level)))
			{
				node->rchild->left_data = node->right_data;
				node->rchild->left_level = node->right_level + 1;
			}
			if(((node->rchild->right_data == -1)&&(node->right_data != -1))||((node->rchild->right_data != -1)&&(node->right_data != -1)&&(node->rchild->right_level > node->right_level)))
			{			
				node->rchild->right_data = node->right_data;
				node->rchild->right_level = node->right_level + 1;
			}
		}
		
		leafpush2(node->lchild);
		leafpush2(node->rchild);

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
		printf("left_level=%d,right_level=%d\n",node->left_level,node->right_level);
		trieprint(node->lchild);
		trieprint(node->rchild);
	}
}

void UniTrie::deleteNode(Node* pnode)
{

}

void UniTrie::insertNode2(Node* pnode,char* prefix, int nexthop)
{
	Node* node = pnode;
	char* p = prefix;
	char* q = NULL;
	
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
			}
			else
			{
				node = node->lchild;
				
			}
		}
		
		if((*p == '1')&&(*q != '\0'))
		{
			if(node->rchild == NULL)
			{
				init_trie(&node->rchild);
				node = node->rchild;

			}
			else
			{
				node = node->rchild;
			}
		}
		p++;
		if(*q == '\0')
		{
			p--;
			if(*p == '0')
			{
				if(node->lchild == NULL)
					node->left_data = nexthop;
				if((node->left_data == -1)&&(node->lchild != NULL))
				{
					node->left_data = nexthop;
					leafpush2(node);
					push(node);
				}
			}
			else if(*p == '1')
			{
				if(node->rchild == NULL)
					node->right_data = nexthop;
				if((node->right_data == -1)&&(node->rchild != NULL))
				{
					node->right_data = nexthop;
					leafpush2(node);
					push(node);
				}
			}
			break;
		}
	}


}
	
void UniTrie::searchNode(Node* pnode,char* arr, int n)
{
	Node* node = pnode;
	Node* node1 = node;
	int i;

	for(i = 0; i < n ;i++)
	{
		if(arr[i] == '0')
		{
			//printf("nexthop:%d",node->left_data);
			node1 = node;
			node = node->lchild;
			if(node == NULL)
			{
				printf("nexthop:%d\n",node1->left_data);
				return;
			}
		}
		if(arr[i] == '1')
		{
			//printf("nexthop:%d\n",node->rightt_data);
			node1 = node;
			node = node->rchild;
			if(node == NULL)
			{
				printf("nexthop:%d\n",node1->right_data);
				return;
			}
		}

	}

	if(arr[n-1] == '0')
	{
		printf("%d\n",node1->left_data);
	}
	else
		printf("%d\n",node1->right_data);

}



