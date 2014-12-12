#include "multi_trie.h"

void MultiTrie::Init(MultiBlocks* &bnode)
{
	bnode = new MultiBlocks();

	for(int n=0; n < BLOCK_SIZE; n++)
	{
		bnode->data[n] = -2;
		bnode->child[n] = NULL;
	}
}

int MultiTrie::pow(int i,int j)
{
	if(j == 0)
		return 1;
	else
		return i*pow(i,j-1);	

}

void MultiTrie::makeMB(MultiBlocks* &node,int a[])
{
	MultiBlocks* node1;
	FILE* file;
	char buffer[BUFFR_SIZE];
	int hop;
	char prefix[PREFIX_LENGTH];
	char prefix1[PREFIX_LENGTH];
	char append[PREFIX_LENGTH];
	char a = '0';
	char b = '1';

	bool overlap = false;

	file = fopen("fibtable2.txt","r");
	while(feof(file) == 0)
	{
		node1 = node;
		overlap = false;
		fgets(buffer,BUFFER_SIZE,file);
		sscanf(buffer,"%s %d",prefix,&hop);
		int length = strlen(prefix);

		if(length <= a[0])
		{
			int length_diff = a[0] - length;
			int insert_times = pow(2,length_diff);
			for(int j=0; j < insert_times; j++)
			{
				for(int i=0; i < PREFIX_LENGTH; i++)
				{
					prefix1[i] = prefix[i];
				}
				
				for(int k=0; k <= length_diff; k++)
				{
					prefix1[length+k] = append[k];
				}	
				insert(prefix1);//undo
			}


		}
		else if(length <= a[0]+a[1])
		{
		
		}
		else if(length <= a[0]+a[1]+a[2])
		{
		
		
		}




	
	}
	fclose(file);
}

void MultiTrie::Group(int floor[PREFIX_LENGTH],int n,int temp[FLOOR_SIZE+1])
{
	int i,j,k,m,l,t;
	m = 7;
	int param[PREFIX_LENGTH][n];

	for(i=0; i < n; i++)
	{
		temp[i] = -1;
	}
	
	temp[FLOOR_SIZE] = m-1;
	
	for(i=0; i<n;i++)
	{
		for(j=i,k=0;j>=0;j--)
		{
			k = floor[j] + k;
		}

		param[i][i] = 2*k;
	}

	for(j=1; j<m; j++)
	{
		param[j][0] = floor[0]*pow(2,j+1);
	}

	for(j=1; j<n; j++)
	{
		for(i=j+1; i<m; i++)
		{
			param[i][j] = param[i-1][j-1] + floor[i]*2;

			k = i-1;
			l = 1;
			while(k > j-1)
			{
				k--;
				t = param[k][j-1] +floor[i-l]*pow(2,l+1);

				if(t < param[i][j])
				{
					param[i][j] = t;
					temp[n-1] = k;
				}
				l++;
			}
		}
	}

	for(i=n-1;i >0;i--)
	{
		t = param[temp[i]][i-1];
		j = temp[i];
		k = i-1;
		l = 1;

		while(t < (param[j-1][k-1] + floor[j-1]*pow(2,l)))
		{
			j--;
			l++;
		}

		temp[i-1] = j-1;
	}

}

void MultiTrie::Multi_Step(UniTrie mb,MultiBlocks* &bnode,int temp[FLOOR_SIZE+1])
{
	MultiBlock* b = bnode;
	temp[0] = -1;

	int i,j,k,m,n,p,q;

	for(i = 1; i <= FLOOR_SIZE; i++)
	{
		j = temp[i] - temp[i-1];
		k = pow(2,j);

		while(j > 0)
		{
			if(mb.node != NULL)
			{
				p = 0;
				q = k;
				for(m=p; m < (p+q)/2; m++)
				{
					b->data[m] = mb.node->ldata;
				}

				for(n = (p+q)/2; n<q; n++)
				{
					b->data
				}
			}
		}

	}
}
