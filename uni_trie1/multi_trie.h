#ifndef _MULTI_TRIE_H_
#define _MULTI_TRIE_H_
#include <string.h>
#include <stdio.h>

#include "common_head.h"
#incldue "uni_trie.h"

class MultiTrie
{
	pulic:
		typedef struct MultiBlocks
		{
			char data[BLOCK_SIZE];
			struct Multiblocks* child[BLOCK_SIZE];
		}MultiBlocks;

		void Init(MultiBlocks* &bnode);
		void Group(int temp[PREFIX_LENGTH],int n,int temp[FLOOR_SIZE+1]);
		void Multi_Step(UniTrie mb,MultiBlocks* &bnode,int temp[FLOOR_SIZE+1]);
		int pow(int i,int j);
		
		void makeMB(MultiBlocks* &node,int a[]);
	
		MultiBlocks* node;

};
#endif
