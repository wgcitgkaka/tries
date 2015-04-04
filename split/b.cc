#include<iostream>
#include<iterator>
#include<list>
#include<iterator>
#include <algorithm>
using namespace std;
void show_list(list<int> a)
{
 
    for(list<int>::iterator i = a.begin(); i != a.end(); i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
}
list<int> operator+(list<int> a, list<int> b)
{
    list<int> c;
    c = b;
    for(list<int>::iterator i = a.begin(); i != a.end(); i++)
    {
         c.push_back(*i);
    }
    return c;
}
list<int> operator-(list<int> a, list<int> b)
{
    list<int> c;
    c = a;
    for(list<int>::iterator i = b.begin(); i != b.end(); i++)
    {
         if(find(c.begin(),c.end(),*i) != c.end())
               c.erase(i);
    }
    return c;
}
list<int> operator*(list<int>& a, list<int>& b)
{
    list<int> c,d;
    c = a;
    for(list<int>::iterator i = b.begin(); i != b.end(); i++)
    {
         if(find(a.begin(),a.end(),*i) != a.end())
               d.push_back(*i);
    }
    return d;
}
 
int main()
{
    list<int> a;
    list<int> b;
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    a.push_back(9);
 
    b.push_back(3);
    b.push_back(0);
    b.push_back(7);
    b.push_back(8);
  
    cout<<"A's Set : ";
    show_list(a);
    cout<<endl;
    cout<<"B's Set : ";
    show_list(b);
    cout<<endl;
    cout<<"A + B : ";
    list<int> c0 = a + b;
    show_list(c0);
    cout<<endl;
    cout<<"A - B : ";
    list<int> c1 = a - b;
    show_list(c1);
    cout<<endl;
    cout<<"A * B : ";
    list<int> c2 = a * b;
    show_list(c2);
    cout<<endl;
 
    cout<<"A += B : ";
    list<int> c3 = a + b;
    list<int> d0 = c3;
    show_list(d0);
    cout<<endl;
    cout<<"A -= B : ";
    list<int> c4 = a - b;
    list<int> d1 = c4;
    show_list(d1);
    cout<<endl;
    cout<<"A *= B : ";
    list<int> c5 = a * b;
    list<int> d2 = c5;
    show_list(d2);
    cout<<endl;
	cout << a.front() << a.back() << endl;
    return 0;
}
