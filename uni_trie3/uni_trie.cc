#include <stdio.h>
#include "uni_trie.h"

extern Node* uni_nodes[100];
extern int floor[PREFIX_LENGTH];


void UniTrie::init_trie(Node** pnode)
{
	*pnode = new Node();
//	(*pnode)->left_data = (*pnode)->right_data = 0;
	(*pnode)->left_length = (*pnode)->right_length = 0;
	(*pnode)->left_info = (*pnode)->right_info = 0;
//	(*pnode)->lchild = (*pnode)->rchild = 0;
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
		
		insertNode2(node,prefix,hop);
		/*while(*p != '\0')
		{
			q = p;
			q++;

			if((*p == '0')&&(*q != '\0'))
			{
				if(node->left_info == 0)
				{
					index_nodes = 0;
					for(int i=0;i < PREFIX_LENGTH; i++)
					{
						index_nodes += floor[i];
					}
					init_trie(&uni_nodes[index_nodes]);
					//node->lchild = index_nodes;
					node->left_info = index_nodes * 2 +1;
					node = 	uni_nodes[index_nodes];

					temp++;
					floor[temp]++;
				}
				else
				{
					if(node->left_info%2 == 1)
						node = uni_nodes[node->left_info/2];
					else
					{
						index_nodes = 0;
						for(int i=0;i < PREFIX_LENGTH; i++)
						{
						index_nodes += floor[i];
						}
						init_trie(&uni_nodes[index_nodes]);
						//node->lchild = index_nodes;
						node->left_info = index_nodes * 2 +1;
						node = 	uni_nodes[index_nodes];									}
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
					node->left_length = count;
				}
				else if(*p == '1')
				{
					node->right_data = hop;
					node->right_length = count;
					
				}
				break;
			}

		}*/
		
	}
	fclose(file);
}
/*
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
			if(((uni_nodes[node->lchild]->left_data == 0)&&(node->left_data != 0))||((uni_nodes[node->lchild]->left_data != 0)&&(node->left_data != 0)&&(uni_nodes[node->lchild]->left_length < node->left_length)))
			{
				uni_nodes[node->lchild]->left_data = node->left_data;
				uni_nodes[node->lchild]->left_length = node->left_length;
			}
			if(((uni_nodes[node->lchild]->right_data == 0)&&(node->left_data != 0))||((uni_nodes[node->lchild]->right_data != 0)&&(node->left_data != 0)&&(uni_nodes[node->lchild]->right_length < node->left_length)))
			{
				uni_nodes[node->lchild]->right_data = node->left_data;
				uni_nodes[node->lchild]->right_length = node->left_length;
			}
		}

		if(node->rchild != 0)
		{
			if(((uni_nodes[node->rchild]->left_data == 0)&&(node->right_data != 0))||((uni_nodes[node->rchild]->left_data != 0)&&(node->right_data != 0)&&(uni_nodes[node->rchild]->left_length < node->right_length)))
			{
				uni_nodes[node->rchild]->left_data = node->right_data;
				uni_nodes[node->rchild]->left_length = node->right_length;
			}
			if(((uni_nodes[node->rchild]->right_data == 0)&&(node->right_data != 0))||((uni_nodes[node->rchild]->right_data != 0)&&(node->right_data != 0)&&(uni_nodes[node->rchild]->right_length < node->right_length)))
			{			
				uni_nodes[node->rchild]->right_data = node->right_data;
				uni_nodes[node->rchild]->right_length = node->right_length;
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
			node->left_data = 0;
		if(node->rchild != 0)
			node->right_data = 0;
		count++;

		push(node->lchild,count);
		push(node->rchild,count);
	}
}*/

void UniTrie::leafpush(int index,int nexthop,int length)
{
	Node* node = uni_nodes[index];
	
	if((node->left_info%2 == 0) && (node->right_info%2 != 0))
	{		
		if(node->left_length < length)
		{
			node->left_info = nexthop * 2;
			node->left_length = length;
			node->right_length = 0;
		}
		leafpush(node->right_info/2,nexthop,length);
	}

	if((node->left_info%2 != 0) && (node->right_info%2 == 0))
	{
		if(node->right_length < length)
		{
			node->right_info = nexthop * 2;
			node->right_length = length;
			node->left_length = 0;
		}
		leafpush(node->left_info/2,nexthop,length);
	}
		//count++;
	if((node->left_info%2 != 0) && (node->right_info%2 != 0))
 	{
		
		leafpush(node->left_info/2,nexthop,length);
		leafpush(node->right_info/2,nexthop,length);
	}
	
	if((node->left_info%2 == 0) && (node->right_info%2 == 0))
	{
		if(node->right_length < length)
		{
			node->right_info = nexthop * 2;
			node->right_length = length;
		}
		if(node->left_length < length)
		{
			node->left_info = nexthop * 2;
			node->left_length = length;
		}
	}

}

void UniTrie::trieprint(int index)
{
	Node* node = uni_nodes[index];
	
	if((node->left_info%2 != 0) && (node->right_info%2 == 0))
	{
		printf("left=%d,right=%d\n",node->left_info,node->right_info);
		printf("left_length=%d,right_length=%d\n",node->left_length,node->right_length);
		printf("\n");
		trieprint(node->left_info/2);
	}
	
	if((node->left_info%2 == 0) && (node->right_info%2 != 0))
	{		
		printf("left=%d,right=%d\n",node->left_info,node->right_info);
		printf("left_length=%d,right_length=%d\n",node->left_length,node->right_length);
		printf("\n");
		trieprint(node->right_info/2);
	}

	
		//count++;
	if((node->left_info%2 != 0) && (node->right_info%2 != 0))
 	{
		printf("left=%d,right=%d\n",node->left_info,node->right_info);
		printf("left_length=%d,right_length=%d\n",node->left_length,node->right_length);
		printf("\n");
		trieprint(node->left_info/2);
		trieprint(node->right_info/2);

	}
	
	if((node->left_info%2 == 0) && (node->right_info%2 == 0))
	{
		printf("left=%d,right=%d\n",node->left_info,node->right_info);
		printf("left_length=%d,right_length=%d\n",node->left_length,node->right_length);
		printf("\n");
	}

}

void UniTrie::deleteNode(Node* pnode)
{

}

void UniTrie::insertNode2(Node* pnode,char* prefix, int nexthop)
{
	Node* node = pnode;
	Node* pre_node = pnode;
	char* p = prefix;
	char* q = NULL;
	char* r = NULL;
	int index_nodes = 0;
	int temp = 0;
	int count = 0;
	int info = 0;
	
	while(*p != '\0')
	{
		q = p;
		q++;

		if((*p == '0')&&(*q != '\0'))
		{
			if(node->left_info%2 == 0)
			{
				index_nodes = 0;
				for(int i=0;i < PREFIX_LENGTH; i++)
				{
					index_nodes += floor[i];
				}
				init_trie(&uni_nodes[index_nodes]);
				//node->lchild = index_nodes;
				info = node->left_info;
				node->left_info = index_nodes * 2 + 1;
				pre_node = node;
				node = 	uni_nodes[index_nodes];				
				node->left_info = info;
				node->right_info = info;
				node->left_length = pre_node->left_length;
				node->right_length = pre_node->left_length;
				pre_node->left_length = 0;
				//pre_node->right_length = 0;
				

				temp++;
				floor[temp]++;
			}
			else
			{
				index_nodes = node->left_info / 2;
				node = uni_nodes[index_nodes];
				temp++;
				
			}
		}
		
		if((*p == '1')&&(*q != '\0'))
		{
			if(node->right_info%2 == 0)
			{
				index_nodes = 0;
				for(int i=0;i < PREFIX_LENGTH; i++)
				{
					index_nodes += floor[i];
				}
				init_trie(&uni_nodes[index_nodes]);
				info = node->right_info;
				node->right_info = index_nodes * 2 + 1;
				pre_node = node;
				node = 	uni_nodes[index_nodes];
				node->left_info = info;
				node->right_info = info;
				node->left_length = pre_node->right_length;
				node->right_length = pre_node->right_length;
				//pre_node->left_length = 0;
				pre_node->right_length = 0;

				temp++;
				floor[temp]++;
			}
			else
			{
				index_nodes = node->right_info / 2;
				node = uni_nodes[index_nodes];
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
				if((node->left_info % 2 == 0)&&(node->left_length < count))
				{
					node->left_info = nexthop * 2;
					node->left_length = count;
				}
				else
				{
					//node->left_data = nexthop;
					//node->left_length = count;
					index_nodes = node->left_info / 2;
					leafpush(index_nodes,nexthop,count);
					//push(index_nodes,0);
				}
			}
			else if(*p == '1')
			{
				if((node->right_info % 2 == 0)&&(node->right_length < count))
				{
					node->right_info = nexthop * 2;
					node->right_length = count;
				}
				else
				{
					//node->right_data = nexthop;
					//node->right_length = count;
					index_nodes = node->right_info / 2;
					leafpush(index_nodes,nexthop,count);
					//push(index_nodes,0);
				}
			}
			break;
		}
	}


}
/*	
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
*/


