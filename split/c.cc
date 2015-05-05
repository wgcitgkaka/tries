#include <iostream>
#include <string>
#include <limits>
using namespace std;
struct my
{
	int a;
	int b;
	string c;
};
int main()
{
	/*string a = "";
	int b = sizeof(a);
	cout << b << endl;

	if(a == "")
		cout << "haha1" << endl;
	for(int i = 0; i < 5; i++)
	{
		int d = 8;
		cout << d << endl;
		if(d == 8)
			continue;
	}*/
	struct my* aa = new my();
	cout << aa->a << endl;
	cout << aa->b << endl;
	cout << aa->c << endl;
	unsigned int a;
	cout << "\t最大值：" << (numeric_limits<unsigned int>::max)() << endl;
	return 0;
}
