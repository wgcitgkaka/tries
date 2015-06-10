#ifndef _UNI_TRIE_H_
#define _UNI_TRIE_H_

#include "common_head.h"
#include "node.h"

class UniTrie
{
  public:
	
	Node* node;
	
	UniTrie(){};
	void init_trie(Node** pnode);
	void insert_node(Node* pnode, int floor[PREFIX_LENGTH]);
	void trieprint(Node* pnode,int level);
};
#endif
