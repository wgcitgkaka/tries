#include "uni_trie.h"
#include "mul_trie.h"

using namespace std;

#define PREFIXLENGTH   32
#define BUFFER_SIZE    256
#define LESS_LENGTH    0

map<string, vector<string> > m_addr2;
char* b;
char* c;
char* d;
char* mysplit(char* a, int spos);
char* mysplit3(char* a, int spos);//addr1
void myinsert(char* addr2,char buffer[256]);


Mnode* mnodes[10000];
int mfloor[PREFIX_LENGTH];

int SPOS = 16;

void m_split(int tmp=16)
{

	FILE* file;
	file = fopen("rrc14_201209010000_v4.txt","r");
	char* buffer;
	char buffer2[BUFFER_SIZE];
	char* addr2;
	char* addr1;
	SPOS = tmp;

	while(fgets(buffer2,BUFFER_SIZE,file))
	{

		buffer = strtok(buffer2," ");
		if(buffer2[strlen(buffer2)-1] == '\n')
			buffer2[strlen(buffer2)-1] = 0;

		addr2 = mysplit(buffer,SPOS);

		if(addr2)
		{
		    addr1 = mysplit3(buffer,SPOS);
			myinsert(addr2,addr1);
			delete[] d;
		}

		delete[] b;
	}


	fclose(file);
}


char* mysplit(char* a, int spos)
{
	int len = strlen(a);
	b = new char[100];
	memset(b,0,100);

	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = SPOS,j = 0; i < len; i++,j++)
	{
		b[j] = a[i];

	}

	return b;

}

char* mysplit3(char* a, int spos)
{
	int len = strlen(a);
	d = new char[50];
	memset(d,0,50);

	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = 0; i < SPOS; i++)
	{
		d[i] = a[i];
    }

	return d;

}

void myinsert(char* addr2,char* addr1)
{
    vector<string> a;
	a.push_back(buffer);

	pair<map<string, vector<string> >::iterator, bool>  ret = m_addr2.insert(make_pair(addr2,a));

	if(!ret.second)
	{
		(ret.first->second).push_back(buffer);
		sort(ret.first->second.begin(),ret.first->second.end());
		ret.first->second.erase(unique(ret.first->second.begin(),ret.first->second.end()),ret.first->second.end());
	}

}

int main()
{
	m_split(16);
	

	printf("\n\n----------multrie\n\n");
	MulTrie bb;

	int group[]={4,14};

	bb.init_mtrie(bb.ppmnode,bb.pow(group[0]));

	mnodes[0] = bb.ppmnode;

	bb.insert_mtrie(group);
	bb.print_mtrie(0,0,group);

	

	return 0;

}
