#include <stdio.h>

#include "uni_trie.h"
#include "mul_trie.h"

Node* uni_nodes[100];
int floor[PREFIX_LENGTH];

Mnode* mnodes[100];
int mfloor[PREFIX_LENGTH];

int main()
{
	for(int i = 0; i < 100; i++)
		uni_nodes[i] = NULL;

	UniTrie aa;
	aa.init_trie(&aa.node);
	uni_nodes[0] = aa.node;

	aa.insert_node();
	aa.trieprint(0);

	
	for(int j = 0; j < 100; j++)
	{
		mnodes[j] = NULL;
	}

	printf("\n\n----------multrie\n\n");
	MulTrie bb;

	int group[]={3,2,2,0,0,0,0};
	//printf("1\n");

	bb.init_mtrie(bb.ppmnode,bb.pow(group[0]));
	//printf("2\n");
	mnodes[0] = bb.ppmnode;

	//printf("3\n");
	bb.insert_mtrie(group);
	//printf("4\n");

	//bb.convert_u_to_m(group);

	bb.print_mtrie(0,0,group);

	

	return 0;

}
