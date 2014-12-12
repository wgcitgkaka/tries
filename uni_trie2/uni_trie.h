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
	void insert_node();
	void leafpush(int index,int count);
	void leafpush2(int index,int count);
	void push(int index,int count);
	void deleteNode(Node* pnode);
	void insertNode2(Node* pnode, char* prefix, int nexthop);
	void searchNode(Node* pnode,char* arr, int n);
	void trieprint(int index,int count);
};
#endif
