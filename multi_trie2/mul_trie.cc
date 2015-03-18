#include "mul_trie.h"

extern Mnode*  mnodes[100];
extern int mfloor[IP_LENGTH];
extern Node* uni_nodes[100];

void MulTrie::init_mtrie(Mnode* &pmnode,int n)
{
	int i;
	pmnode = new Mnode();
	pmnode->info = new int[n];
	pmnode->length = new int[n];
	for(i=0; i < n; i++)
	{
		pmnode->info[i] = 0;
		pmnode->length[i] = 0;
	}
}
void MulTrie::insert_mtrie(int group[FLOOR_SIZE])
{
	//printf("debug");
	Mnode* pmnode1 = NULL;
	FILE* file = NULL;
	char buffer[BUFFER_SIZE];
	char prefix[PREFIX_LENGTH];
	int hop;
	int temp = 0;
	mfloor[0] = 1;
	for(temp = 1; temp < IP_LENGTH;temp++)
	{
		mfloor[temp] = 0;
	}
	//printf("debug1");

	file = fopen("fibtable.txt","r");
	//printf("debug2");

	while(feof(file) == 0)
	{
		pmnode1 = mnodes[0];
		fgets(buffer,BUFFER_SIZE,file);
		sscanf(buffer,"%s %d",prefix,&hop);
		//printf("debug");
		insert2(pmnode1,prefix,hop,group);
	}
	fclose(file);
	
}
void MulTrie::insert2(Mnode* pmnode, char* prefix, int nexthop, int group[FLOOR_SIZE])
{
	char *p, *q;
	p = q = NULL;
	int start, end;
	Mnode* pmnode1 = pmnode;
	
	p = prefix;

	start = 0;
	end = pow(group[0]);
	
	int count = 0;
	int flag = 0;
	int num = 0;
	int index_nodes = 0;
	int temp = 0;
	int temp1 = 0;
	while(*p != '\0')
	{
		if(*p == '0')
		{
			end = (start + end)/2;
		}
		else if(*p == '1')
		{
			start = (start + end)/2;
		}
		count++;
		num++;
		if(num == group[flag])
		{
			q = p;
			q++;
			
			if(*q != '\0')
			{
				num = 0;
				flag++;
				if(pmnode->info[start]%2 == 0)
				{
					index_nodes = 0;
					for(int i=0;i < IP_LENGTH;i++)
					{
						index_nodes = index_nodes + mfloor[i];
					}
			
					init_mtrie(mnodes[index_nodes],pow(group[flag]));
					
					temp1 = start;

					start = 0;
					end = pow(group[flag]);
					for (int j = start; j < end; j++)
					{
						mnodes[index_nodes]->info[j] = pmnode->info[temp1];
						mnodes[index_nodes]->length[j] = pmnode->length[temp1];
					}
					pmnode->info[temp1] = index_nodes * 2 + 1;
					pmnode->length[temp1] = 0;
					pmnode = mnodes[index_nodes];
					temp++;
					mfloor[temp]++;
				}
				else
				{
					
					index_nodes = pmnode->info[start] / 2 ;
					pmnode = mnodes[index_nodes];
					start = 0;
					end = pow(group[flag]);
					temp++;
				}
			}	
		}
		p++;
	}

	for(int k = start; k < end; k++)
	{
		if(pmnode->info[k] % 2 == 0)
		{
			if(pmnode->length[k] < count)
			{
				pmnode->info[k] = nexthop * 2;
				pmnode->length[k] = count;
			//	leafpush(pmnode->info[k]);
			}

		}
		else
		{
			index_nodes = pmnode->info[k]/2;
			leafpush(index_nodes,nexthop,count,flag+1,group);
}
	}


}

void MulTrie::leafpush(int index, int nexthop, int mlength,int flag,int group[FLOOR_SIZE])
{
	int start, end;
	start = 0;
	end = pow(group[flag]);
	Mnode* mnode = mnodes[index];

	for(int i =start;i < end; i++)
	{
		if(mnode->info[i] % 2 == 0)
		{	
			if(mnode->length[i] < mlength)
			{
				mnode->info[i] = nexthop * 2;
				mnode->length[i] = mlength;
			}
		}
		else
		{
			index = mnode->info[i]/2;
			leafpush(index,nexthop,mlength,flag+1,group);
		}
	}

}

void MulTrie::convert_u_to_m(int group[FLOOR_SIZE])
{	
	mfloor[0] = 1;
	
	for(int i = 1; i < IP_LENGTH; i++)
	{
		mfloor[i] = 0;
	}
	
	convert2(uni_nodes[0], mnodes[0],group,0, pow(group[0]),1,0);
	
		
}

void MulTrie::convert2(Node* pnode, Mnode* pmnode,int group[FLOOR_SIZE],int start, int end, int flag1, int flag2)
{
	int index_nodes = 0;
	Node* pnode1 = pnode;
	Mnode* pmnode1 = pmnode;
	Mnode* pmnode2 = NULL;
	int start1,end1;
	int k = 0;
	
	if(pnode1->left_info%2 == 0)
	{
		for(int i = start; i < (start+end)/2; i++)
		{
			pmnode1->info[i] = pnode1->left_info;
			pmnode1->length[i] = pnode1->left_length;
				
		}
	}
	if(pnode1->right_info%2 == 0)
	{
		for(int j = (start+end)/2; j < end; j++)
		{
			pmnode1->info[j] = pnode1->right_info;
			pmnode1->length[j] = pnode1->right_length;
		}
	}
	if((flag1 == group[flag2])&&((pnode1->left_info%2 == 1) || (pnode1->right_info%2 == 1)))
	{
		if(pnode1->left_info%2 == 1)
		{	
			flag2++;
			if(pmnode->info[start]%2 == 0)
			{
				index_nodes = 0;
				for(int i=0;i < IP_LENGTH;i++)
				{
					index_nodes = index_nodes + mfloor[i];
				}
			
				init_mtrie(mnodes[index_nodes],pow(group[flag2]));

				pmnode1->info[start] = index_nodes*2 + 1;
				pmnode2 = pmnode1;
				pmnode1 = mnodes[index_nodes];
				mfloor[flag2]++;
			}
			else
			{
				index_nodes = pmnode->info[start]/2;
				pmnode2 = pmnode1;
				pmnode1 = mnodes[index_nodes];
			}
			start1 = start;
			end1 = end;
			start = 0;
			end = 2*pow(group[flag2]);
			flag1 = 0;

		}

		if(pnode1->right_info%2 == 1)
		{	
			if(pnode1->left_info%2 == 1)
			{
				if(pmnode->info[end1-1]%2 == 0)
				{
					index_nodes = 0;
					for(int i=0;i < IP_LENGTH;i++)
					{
						index_nodes = index_nodes + mfloor[i];
					}
					init_mtrie(mnodes[index_nodes],pow(group[flag2]));
					pmnode->info[end1-1] = index_nodes*2 + 1;
					pmnode2 = mnodes[index_nodes];
					mfloor[flag2]++;
				}
				else
				{
					index_nodes = pmnode->info[end1-1]/2;
					pmnode2 = mnodes[index_nodes];
				}
				end1 = pow(group[flag2]);
				start1 = -end1;
				k = 1;
			}
			else
			{
				flag2++;
				if(pmnode->info[end-1]%2 == 0)
				{
					index_nodes = 0;
					for(int i=0;i < IP_LENGTH;i++)
					{
						index_nodes = index_nodes + mfloor[i];
					}
					init_mtrie(mnodes[index_nodes],pow(group[flag2]));
					pmnode->info[end-1] = index_nodes*2 + 1;
					pmnode1 = mnodes[index_nodes];
					mfloor[flag2]++;
				}
				else
				{
					index_nodes = pmnode->info[end-1]/2;
					pmnode1 = mnodes[index_nodes];
				}
				end = pow(group[flag2]);
				start = -end;
				flag1 = 0;
			}
			
		}
		
	}

	flag1++;
	if(pnode1->left_info%2 == 1)
		convert2(uni_nodes[pnode1->left_info/2],pmnode1,group,start,(start+end)/2,flag1,flag2);
	if(pnode1->right_info%2 == 1)
	{
		if(k == 0)
			convert2(uni_nodes[pnode1->right_info/2],pmnode1,group,(start + end)/2,end,flag1,flag2);
		else
			convert2(uni_nodes[pnode1->right_info/2],pmnode2,group,(start1 + end1)/2,end1,flag1,flag2);
	}

}

void MulTrie::print_mtrie(int index,int flag,int group[FLOOR_SIZE])
{
	int start,end;
	start = 0;
	end = pow(group[flag]);
	Mnode* mnode = mnodes[index];
	int index2 = 0;
	for(int i = start; i < end; i++)
	{
		printf("info=%d,length=%d,level=%d\n",mnodes[index]->info[i],mnodes[index]->length[i],flag);
		
		if(mnode->info[i]%2 != 0)
		{
			index2 = mnode->info[i]/2;
			print_mtrie(index2,flag+1,group);
		}
	}
}
int MulTrie::pow(int n)
{
	if(n == 0)
	{
		return 1;
	}
	else
	{
		return 1<<n;
	}
}



