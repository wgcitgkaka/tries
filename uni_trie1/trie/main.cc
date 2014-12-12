#include <stdio.h>

#include "uni_trie.h"

int main()
{
	int temp[PREFIX_LENGTH];
	int a[FLOOR_SIZE+1];

	UniTrie aa;
	aa.init_trie(&aa.node);
	aa.insert_node(aa.node,temp);

	aa.leafpush(aa.node);
	aa.push(aa.node);
	aa.trieprint(aa.node);

	return 0;

}
