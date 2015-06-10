#include <stdio.h>
#include <iostream>
#include "uni_trie.h"
using namespace std;

extern int number_nodes;

int main()
{
	int temp[PREFIX_LENGTH];
	int a[FLOOR_SIZE+1];

	UniTrie aa;
	aa.init_trie(&aa.node);
	aa.insert_node(aa.node,temp);
	aa.trieprint(aa.node, 1);

	cout << "num=" << number_nodes << endl;
	cout << "total" << temp[23] << endl;
	return 0;

}
