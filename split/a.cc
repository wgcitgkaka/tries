#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;
#define kaka 22
/*int aaa = 0;

void func()
{
	int a1 = 9;	
	aaa = a1;
}*/

unsigned long int pow(unsigned long int i,unsigned long int j)
{
	if (j == 0)
         return 1;
     else 
         return i * pow(i,j-1);  
}
int main()
{
 /*string a = "\0";
 cout << a;
int c = sizeof(int);
int b = sizeof(long int);
cout << c << "   " << b << endl;
cout << pow(2,32)<< endl;

vector<int> aa;
cout << aa.size() << endl;

func();

cout<< aaa << endl;*//*
for(int i = 0; i < 2;i++)
{
vector<unsigned long int> a;
a.push_back(1);

for(vector<unsigned long int>::iterator it = a.begin(); it < a.end();it++)
	cout<< *it<<endl;
cout << i <<"------------------"<< endl;
}*/

unsigned long int b = pow((unsigned long)2,(unsigned long)10);
unsigned long int c = 0;
string a = "1000000000";
for(int i = a.size()-1,j =0 ; i >= 0; i--,j++)
{
	if(a[i] == '1')
	{
		c = c + pow((unsigned long)2,(unsigned long)j);
	}
}
cout << b<< "   "<< c << endl;
kaka = 5;
return 0;
}
