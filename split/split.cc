#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

#define PREFIXLENGTH   32
#define SPOS           14 
#define BUFFER_SIZE    256
#define LESS_LENGTH    0

map<string, vector<string> > mymap;//group key=addr2 value = addr1

vector<string> myvector;

map<string,int > mymap2;//group key=add1 value=count(addr1)

char* b;
char* c;
char* d;

void myinsert(char* addr2,char buffer[256]);

void vec_uniq();
void tongjikey();

void myprint();
void myprint2();

char* mysplit(char* a, int spos);
char* mysplit2(string a, int spos);
char* mysplit3(char* a, int spos);

int cmp(const pair<string,int> &x,const pair<string,int>&y);
void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec);

int main()
{
	
	FILE* file;	
	file = fopen("rrc14_201209010000_v4.txt","r");
//	file = fopen("data_test","r");
	char* buffer; 
	char buffer2[BUFFER_SIZE];
	char* addr2;
	char* addr1;
	
	while(fgets(buffer2,BUFFER_SIZE,file))
//	while(fscanf(file,"%s",buffer2) != -1)
	{
		
		buffer = strtok(buffer2," ");
		if(buffer2[strlen(buffer2)-1] == '\n')
			buffer2[strlen(buffer2)-1] = 0;
//		printf("%s\n",buffer);
//		printf("%s\n",buffer2);
		
		myvector.push_back(buffer);

		addr2 = mysplit(buffer,SPOS);

		if(addr2)
		{
			addr1 = mysplit3(buffer,SPOS);
			myinsert(addr2,addr1);
		//	printf("%s\n",addr2);
			delete[] d;
		}
		//mapprint();
//		printf("-----\n");
		delete[] b;
	}
	
	vec_uniq();
	tongjikey();
	myprint2();
	myprint();

	fclose(file);
	return 0;
}

void vec_uniq()
{
		sort(myvector.begin(),myvector.end());
		myvector.erase(unique(myvector.begin(),myvector.end()),myvector.end());
	
}

void tongjikey()
{
	char* buff;
	for(vector<string>::iterator iter = myvector.begin();iter != myvector.end(); iter++)
	{
		buff = mysplit2(*iter,SPOS);
		if(buff)
		{
			pair<map<string, int>::iterator, bool > ret = mymap2.insert(make_pair(buff,1));
			if(!ret.second)
				++ret.first->second;
		delete[] c;
		}
	}
}


char* mysplit(char* a, int spos)
{
	int len = strlen(a);
//	b=(char*)malloc(256);
	b = new char[100];
	memset(b,0,100);
//	printf("length=%d\n",len);
	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = SPOS,j = 0; i < len; i++,j++)
	{
		b[j] = a[i];
	//	printf("%c\n",a[i]);
		
		//printf("hehe\n");
	}

	return b;

}
char* mysplit2(string a, int spos)
{
	c = new char[50];
	memset(c,0,50);
	if(a.size() <= SPOS)
		return LESS_LENGTH;
	for(int i=0; i < SPOS; i++)
	{
		c[i] =  a[i];
	}
	return c;
}

char* mysplit3(char* a, int spos)
{
	int len = strlen(a);
//	b=(char*)malloc(256);
	d = new char[100];
	memset(d,0,100);
//	printf("length=%d\n",len);
	if(len <= SPOS)
	{
		return LESS_LENGTH;
	}

	for(int i = 0; i < SPOS; i++)
	{
		d[i] = a[i];
	//	printf("%c\n",a[i]);
		
		//printf("hehe\n");
	}

	return d;

}

void myinsert(char* addr2,char buffer[256])
{
	vector<string> a;
	a.push_back(buffer);
	
/*	for(vector<string>::iterator iter = a.begin(); iter != a.end(); ++iter)
	{
//		printf("iter%s\n", (char*) *iter);
		cout << *iter << endl;
		cout << "haha" << endl;
	}
	
*/
	pair<map<string, vector<string> >::iterator, bool>  ret = mymap.insert(make_pair(addr2,a));
	
	if(!ret.second)
	{
		(ret.first->second).push_back(buffer);
		sort(ret.first->second.begin(),ret.first->second.end());
		ret.first->second.erase(unique(ret.first->second.begin(),ret.first->second.end()),ret.first->second.end());
	}

}

int cmp(const pair<string,int> &x,const pair<string,int>&y)
{
	return x.second > y.second;
}

void sortMapbyValue(map<string, int> &t_map, vector<pair<string,int> > &t_vec)
{
	for(map<string,int>::iterator iter = t_map.begin(); iter != t_map.end(); iter++)
	{
		t_vec.push_back(make_pair(iter->first,iter->second));
	}

	sort(t_vec.begin(),t_vec.end(),cmp);
}
void myprint2()
{
	vector<pair<string,int> > v_result2;
	sortMapbyValue(mymap2,v_result2);
	
	vector<pair<string,int> >::iterator it = v_result2.begin();
	while(it != v_result2.end())
	{
		
			ofstream outf("sort_result2.txt",ios::app);
			streambuf *default_buff = cout.rdbuf();

			cout.rdbuf(outf.rdbuf());

			cout<<"key="<<it->first<<"      "<<"count="<< it->second << endl;
			
			outf.flush();
			outf.close();	
			cout.rdbuf(default_buff);
			it++;
	}
}

void myprint()
{
	map<string,int> m_result;
	vector<pair<string,int> > v_result;

	map<string, vector<string> >::iterator it = mymap.begin();
	cout<<"groupid"<<"          "<<"addr2"<<"          "<<"count"<<endl;
	int i = 0;
	string aa;
	string bb = "0";
	string cc = "0";
	while (it != mymap.end())
	{
		int j = 0;
		cc = "0";
		for(vector<string>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
		{
			j++;
			bb = *iter;
			if(bb > cc)
				cc = bb;
		//	cout<< i <<"    " << it->first <<"    "<< *iter <<"    "<< j << endl;
		}
			ofstream outf("result.txt",ios::app);
			streambuf *default_buff = cout.rdbuf();

			cout.rdbuf(outf.rdbuf());

			cout<< i <<"    " << it->first <<"    "<<  j<<"    "<< cc << endl;

			outf.flush();
			outf.close();	
			cout.rdbuf(default_buff);
			
			m_result.insert(make_pair(it->first,j));
			

		i++;
		++it;
	}

	sortMapbyValue(m_result,v_result);
	
	for(int k = 0; k < v_result.size(); k++)
	{
		ofstream outf2("sort_result.txt",ios::app);
		streambuf *default_buff2 = cout.rdbuf();
		cout.rdbuf(outf2.rdbuf());
		
		cout<< k << "    " << v_result[k].first << "    " << v_result[k].second << endl;

		outf2.flush();
		outf2.close();
		cout.rdbuf(default_buff2);

	}

}

















