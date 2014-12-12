#include <stdio.h>

#include "uni_trie.h"

int main()
{
	int temp[PREFIX_LENGTH];
	int a[FLOOR_SIZE+1];

	UniTrie aa;
	aa.init_trie(&aa.node);
	aa.insert_node(aa.node,temp);
	aa.trieprint(aa.node);
	printf("\n\n");
	aa.leafpush2(aa.node);
	aa.push(aa.node);
	aa.trieprint(aa.node);
	printf("\n\n");
	char b[]="1";
	aa.searchNode(aa.node,b,1);
	printf("\n\n");
	char* prefix2 = "1100";
	aa.insertNode2(aa.node,prefix2,28);
	aa.trieprint(aa.node);
	return 0;

}
