#ifndef _MUL_TRIE_H_
#define _MUL_TRIE_H_

#include "node.h"
#include "common_head.h"
class MulTrie
{
	public:
		Mnode* ppmnode;

	MulTrie(){};
	
	void init_mtrie(Mnode* &pmnode,int n);
	void insert_mtrie(int group[FLOOR_SIZE]);
	void insert2(Mnode* pmnode, char* prefix, int hop, int group[FLOOR_SIZE]);
	void leafpush(int index, int nexthop, int mlength,int flag,int group[FLOOR_SIZE]);
	void print_mtrie(int index,int flag,int group[FLOOR_SIZE]);
	int pow(int n);
};
#endif
