#ifndef _LULEA_H_
#define _LULEA_H_

#include "node.h"
#include "common_head.h"
class Lulea
{
	public:
		Lnode* plnode;

	Lulea(){};
	
	void init_lulea(Lulea* &plnode1,int n);
	void convert_m_to_l(int group[FLOOR_SIZE]);
	void convert2();
	void print_ltrie();
	int pow(int n);
};
#endif
