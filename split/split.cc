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
map<string, vector<string> > mymap;
char* b;

char* mysplit(char* a, int spos);
void myinsert(char* addr2,char buffer[256]);
void myprint();

int main()
{
	
	FILE* file;	
	file = fopen("rrc14_201209010000_v4.txt","r");
	char* buffer; 
	char buffer2[BUFFER_SIZE];
	char* addr2;
	
	while(fgets(buffer2,BUFFER_SIZE,file))
//	while(fscanf(file,"%s",buffer2) != -1)
	{
		
		buffer = strtok(buffer2," ");
		if(buffer2[strlen(buffer2)-1] == '\n')
			buffer2[strlen(buffer2)-1] = 0;
//		printf("%s\n",buffer);
//		printf("%s\n",buffer2);
		
		
		addr2 = mysplit(buffer,SPOS);

		if(addr2)
		{
			myinsert(addr2,buffer);
		//	printf("%s\n",addr2);
		}
		//mapprint();
//		printf("-----\n");
	}
	myprint();

	fclose(file);
	return 0;
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
void myprint()
{
	map<string,int> m_result;
	vector<pair<string,int> > v_result;

	map<string, vector<string> >::iterator it = mymap.begin();
	cout<<"groupid"<<"          "<<"addr2"<<"          "<<"count"<<endl;
	int i = 0;
	while (it != mymap.end())
	{
		int j = 0;
		for(vector<string>::iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
		{
			j++;
		//	cout<< i <<"    " << it->first <<"    "<< *iter <<"    "<< j << endl;
		}
			ofstream outf("result.txt",ios::app);
			streambuf *default_buff = cout.rdbuf();

			cout.rdbuf(outf.rdbuf());

			cout<< i <<"    " << it->first <<"    "<<  j << endl;

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

















