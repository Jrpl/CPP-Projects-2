#include <iostream>
#include "set.h"

int main()
{
	nwacc::set<int> set;

	for (int i = 0; i < 50; i++)
	{
		set.insert(rand());
	}

	set.display();

	return 0;
}