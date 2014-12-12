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
	void leafpush(Node* pnode);
	void leafpush2(Node* pnode);
	void push(Node* pnode);
	void deleteNode(Node* pnode);
	void insertNode2(Node* pnode, char* prefix, int nexthop);
	void searchNode(Node* pnode,char* arr, int n);
	void trieprint(Node* pnode);
};
#endif
