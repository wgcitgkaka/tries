#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

#define PREFIXLENGTH   32
#define SPOS           14
#define BUFFER_SIZE    32

map<string, vector<string> > mymap;

int main()
{
	
	FILE* file;	
	file = fopen("data_test","r");
	char buffer[BUFFER_SIZE]; 
	char addr1[BUFFER_SIZE];
	
	while(feof(file) == 0)
	{
		fgets(buffer,BUFFER_SIZE,file);		
		printf("%s",buffer);
		
		addr1 = split(buffer,SPOS);	
				
	}

	fclose(file);
	return 0;
}

char* split(char* a, int spos)
{
	
}
