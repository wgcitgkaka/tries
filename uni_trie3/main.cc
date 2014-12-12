#include <stdio.h>

#include "uni_trie.h"

Node* uni_nodes[100];
int floor[PREFIX_LENGTH];

int main()
{
	for(int i = 0; i < 100; i++)
		uni_nodes[i] = NULL;
	int temp[PREFIX_LENGTH];
	//int a[FLOOR_SIZE+1];

	UniTrie aa;
	aa.init_trie(&aa.node);
	uni_nodes[0] = aa.node;

	aa.insert_node();
	aa.trieprint(0);

	/*printf("\n\n");
	
	aa.leafpush2(0,0);
	aa.push(0,0);
	aa.trieprint(0,0);

	printf("\n\n");

	char b[]="1";
	aa.searchNode(aa.node,b,1);

	printf("\n\n");

	char* prefix2 = "1100";
	aa.insertNode2(aa.node,prefix2,28);
	aa.trieprint(0,0);*/

	return 0;

}
