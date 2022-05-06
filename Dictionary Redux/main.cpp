#include <iostream>
#include "dictionary.h"

std::string genRandom()  // Random string generator function.
{
	std::string temp_s;

	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	int stringLength = sizeof(alphanum) - 1;

	temp_s += alphanum[rand() % stringLength];

	return temp_s;
}

int main()
{
	nwacc::dictionary<int, std::string> table;
	std::string foo[20] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t" };

	for (int i = 0; i < 20; i++)
	{
		table.put(i, foo[i]);
	}

	table.print();
	std::cout << std::endl;

	// Should remove Key 3, Value d
	table.remove(3);
	table.print();
	std::cout << std::endl;

	// Should remove Value g, Key 6
	table.remove_value("g");
	table.print();
	std::cout << std::endl;

	// Should return true
	table.contains_key(1);
	table.contains_value("b");

	// Should return false
	table.contains_key(3);
	table.contains_value("g");

	// Should return the value b associated with key 1
	table.get(1);


	return 0;
}