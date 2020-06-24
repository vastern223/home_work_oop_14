#include <iostream>
#include "List.h"
using namespace std;


int main()
{
	List<int> lt;

	lt.AddToHead(150);
	lt.AddToHead(170);
	lt.AddToHead(160);
	lt.AddToHead(200);
	lt.Print(); cout << endl;

	system("pause");
	return 0;
}