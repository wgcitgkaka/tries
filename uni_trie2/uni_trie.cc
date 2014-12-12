#include <stdio.h>
#include "uni_trie.h"

extern Node* uni_nodes[100];
extern int floor[PREFIX_LENGTH];


void UniTrie::init_trie(Node** pnode)
{
	*pnode = new Node();
	(*pnode)->left_data = (*pnode)->right_data = 0;
	(*pnode)->left_longth = (*pnode)->right_longth = 0;
	(*pnode)->lchild = (*pnode)->rchild = 0;
} 

void UniTrie::insert_node()
{
	Node* node = NULL;
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
	int index_nodes = 0;
	int count = 0;

	while(feof(file) == 0)
	{
		
		//node = pnode;
		node = uni_nodes[0];
		temp = 0;
		fgets(buffer,BUFFER_SIZE,file);
		sscanf(buffer,"%s %d",prefix,&hop);
		p = prefix;
		count = 0;
		
		while(*p != '\0')
		{
			q = p;
			q++;

			if((*p == '0')&&(*q != '\0'))
			{
				if(node->lchild == 0)
				{
					index_nodes = 0;
					for(int i=0;i < PREFIX_LENGTH; i++)
					{
						index_nodes += floor[i];
					}
					init_trie(&uni_nodes[index_nodes]);
					node->lchild = index_nodes;
					node = 	uni_nodes[node->lchild];
					
					temp++;
					floor[temp]++;
				}
				else
				{
					node = uni_nodes[node->lchild];
					temp++;
				}
			}
			
			if((*p == '1')&&(*q != '\0'))
			{
				if(node->rchild == 0)
				{
					index_nodes = 0;
					for(int i=0;i < PREFIX_LENGTH; i++)
					{
						index_nodes += floor[i];
					}
					init_trie(&uni_nodes[index_nodes]);
					node->rchild = index_nodes;
					node = uni_nodes[node->rchild];

					temp++;
					floor[temp]++;
				}
				else
				{
					node = uni_nodes[node->rchild];
					temp++;
				}
			}
			p++;
			count++;
			if(*q == '\0')
			{
				p--;
				if(*p == '0')
				{
					node->left_data = hop;
					node->left_longth = count;
				}
				else if(*p == '1')
				{
					node->right_data = hop;
					node->right_longth = count;
					
				}
				break;
			}

		}
		
	}
	fclose(file);
}

void UniTrie::leafpush(int index,int count)
{
	Node* node = uni_nodes[index];
	if(index != 0)
	{
		if(node->lchild != 0)
		{		
			if(uni_nodes[node->lchild]->left_data == 0)
				uni_nodes[node->lchild]->left_data = node->left_data;
			if(uni_nodes[node->lchild]->right_data == 0)
				uni_nodes[node->lchild]->right_data = node->left_data;
		}

		if(node->rchild != 0)
		{
			if(uni_nodes[node->rchild]->left_data == 0)
				uni_nodes[node->rchild]->left_data = node->right_data;
			if(uni_nodes[node->rchild]->right_data == 0)
				uni_nodes[node->rchild]->right_data = node->right_data;
		}
		count++;
		
		leafpush(node->lchild,count);
		leafpush(node->rchild,count);

	}

}

void UniTrie::leafpush2(int index,int count)
{
	Node* node = uni_nodes[index];
	if(index != 0 || count == 0)
	{
		if(node->lchild != 0)
		{		
			if(((uni_nodes[node->lchild]->left_data == 0)&&(node->left_data != 0))||((uni_nodes[node->lchild]->left_data != 0)&&(node->left_data != 0)&&(uni_nodes[node->lchild]->left_longth < node->left_longth)))
			{
				uni_nodes[node->lchild]->left_data = node->left_data;
				uni_nodes[node->lchild]->left_longth = node->left_longth;
			}
			if(((uni_nodes[node->lchild]->right_data == 0)&&(node->left_data != 0))||((uni_nodes[node->lchild]->right_data != 0)&&(node->left_data != 0)&&(uni_nodes[node->lchild]->right_longth < node->left_longth)))
			{
				uni_nodes[node->lchild]->right_data = node->left_data;
				uni_nodes[node->lchild]->right_longth = node->left_longth;
			}
		}

		if(node->rchild != 0)
		{
			if(((uni_nodes[node->rchild]->left_data == 0)&&(node->right_data != 0))||((uni_nodes[node->rchild]->left_data != 0)&&(node->right_data != 0)&&(uni_nodes[node->rchild]->left_longth < node->right_longth)))
			{
				uni_nodes[node->rchild]->left_data = node->right_data;
				uni_nodes[node->rchild]->left_longth = node->right_longth;
			}
			if(((uni_nodes[node->rchild]->right_data == 0)&&(node->right_data != 0))||((uni_nodes[node->rchild]->right_data != 0)&&(node->right_data != 0)&&(uni_nodes[node->rchild]->right_longth < node->right_longth)))
			{			
				uni_nodes[node->rchild]->right_data = node->right_data;
				uni_nodes[node->rchild]->right_longth = node->right_longth;
			}
		}
		count++;
		
		leafpush2(node->lchild,count);
		leafpush2(node->rchild,count);

	}

}

void UniTrie::push(int index, int count)
{
	Node* node = uni_nodes[index];
	if(index != 0 || count == 0)
	{
		if(node->lchild != 0)
		{
			node->left_data = 0;
			node->left_longth = 0;
		}
		if(node->rchild != 0)
		{
			node->right_data = 0;
			node->right_longth = 0;
		}
		count++;

		push(node->lchild,count);
		push(node->rchild,count);
	}
}

void UniTrie::trieprint(int index, int count)
{
	Node* node = uni_nodes[index];

	if(index != 0 || count == 0)
	{
		printf("left=%d,right=%d\n",node->left_data,node->right_data);
		printf("left_longth=%d,right_longth=%d\n",node->left_longth,node->right_longth);
		printf("lchild=%d,rchild=%d\n",node->lchild,node->rchild);
		printf("\n");
		count++;

		trieprint(node->lchild,count);
		trieprint(node->rchild,count);
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
	char* r = NULL;
	int index_nodes = 0;
	int temp = 0;
	int count = 0;
	
	while(*p != '\0')
	{
		q = p;
		q++;

		if((*p == '0')&&(*q != '\0'))
		{
			if(node->lchild == 0)
			{
				index_nodes = 0;
				for(int i=0;i < PREFIX_LENGTH; i++)
				{
					index_nodes += floor[i];
				}
				init_trie(&uni_nodes[index_nodes]);
				node->lchild = index_nodes;
				node = 	uni_nodes[node->lchild];

				temp++;
				floor[temp]++;
			}
			else
			{
				index_nodes = node->lchild;
				node = uni_nodes[node->lchild];
				
				temp++;
				
			}
		}
		
		if((*p == '1')&&(*q != '\0'))
		{
			if(node->rchild == 0)
			{
				index_nodes = 0;
				for(int i=0;i < PREFIX_LENGTH; i++)
				{
					index_nodes += floor[i];
				}
				init_trie(&uni_nodes[index_nodes]);
				node->rchild = index_nodes;
				node = uni_nodes[node->rchild];

				temp++;
				floor[temp]++;
			}
			else
			{
				index_nodes = node->rchild;
				node = uni_nodes[node->rchild];
				temp++;
			}
		}
		p++;
		count++;
		if(*q == '\0')
		{
			p--;
			if(*p == '0')
			{
				if(node->lchild == 0)
					node->left_data = nexthop;
				if((node->left_data == 0)&&(node->lchild != 0))
				{
					node->left_data = nexthop;
					node->left_longth = count;
					leafpush2(index_nodes,0);
					push(index_nodes,0);
				}
			}
			else if(*p == '1')
			{
				if(node->rchild == 0)
					node->right_data = nexthop;
				if((node->right_data == 0)&&(node->rchild != 0))
				{
					node->right_data = nexthop;
					node->right_longth = count;
					leafpush2(index_nodes,0);
					push(index_nodes,0);
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
			node = uni_nodes[node->lchild];
			if(node->lchild == 0)
			{
				printf("nexthop:%d\n",node1->left_data);
				return;
			}
		}
		if(arr[i] == '1')
		{
			//printf("nexthop:%d\n",node->rightt_data);
			node1 = node;
			node = uni_nodes[node->rchild];
			if(node->rchild == 0)
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



