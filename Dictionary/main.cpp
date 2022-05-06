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
	nwacc::dictionary<int, std::string> map;
	std::string foo[20] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t" };

	for (int i = 0; i < 20; i++)
	{
		map.put(i, foo[i]);
	}

	map.print();
	std::cout << std::endl;

	// Should remove "e"
	map.remove(3);

	map.print();
	std::cout << std::endl;

	// Should be true
	map.contains_key(10);
	map.contains_value("d");

	// Should be false
	map.contains_key(3);
	map.contains_value("e");

	// Should replace "c" with "new"
	map.put(2, "new");

	map.print();
	std::cout << std::endl;

	return 0;
}