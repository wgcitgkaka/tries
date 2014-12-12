#include "mul_trie.h"

extern Mnode*  mnodes[100];
extern int mfloor[IP_LENGTH];

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
