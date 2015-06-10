#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>
#include <list>
using namespace std;



#define BUFFER_SIZE    256
vector<string> myvector;// addr vector
void myprint();

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
		if(buffer)
		{
			
			if(find(myvector.begin(),myvector.end(),buffer) == myvector.end())
               			myvector.push_back(buffer);
			
		}
		
		
	}
	
	myprint();
	
	fclose(file);
	return 0;
}

void myprint()
{
	
	ofstream outf("./unique_ipv4.txt",ios::app);
	streambuf *default_buff = cout.rdbuf();
	cout.rdbuf(outf.rdbuf());
	
	vector<string>::iterator it = myvector.begin();
	while(it != myvector.end())
	{
	
		cout<< *it << endl;						
		it++;
	
	}
	
	outf.flush();
	outf.close();	
	cout.rdbuf(default_buff);
}



