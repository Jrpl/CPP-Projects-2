#include <iostream>
#include "offset_array.h"

int main()
{
	// Testing constructor
	std::cout << "Initialize int offset_array called int_data" << std::endl;
	nwacc::offset_array<int, 47, 59> int_data;

	std::cout << "EXPECT: Size 0, Capacity 13" << std::endl;
	std::cout << int_data << std::endl;

	std::cout << "Initialize char offset_array called char_data" << std::endl;
	nwacc::offset_array<char, 23, 29> char_data;

	std::cout << "EXPECT: Size 0, Capacity 7" << std::endl;
	std::cout << char_data << std::endl;

	// Testing subscript operator overload
	int_data[48] = 8;
	std::cout << "EXPECT: Size 1, Capacity 13, 8" << std::endl;
	std::cout << int_data << std::endl;

	int_data[50] = -5;
	std::cout << "EXPECT: Size 2, Capacity 13, 8 -5" << std::endl;
	std::cout << int_data << std::endl;

	int_data[53] = 10;
	std::cout << "EXPECT: Size 3, Capacity 13, 8 -5 10" << std::endl;
	std::cout << int_data << std::endl;

	char_data[25] = 'H';
	std::cout << "EXPECT: Size 1, Capacity 7, H" << std::endl;
	std::cout << char_data << std::endl;

	char_data[28] = 'T';
	std::cout << "EXPECT: Size 2, Capacity 7, H T" << std::endl;
	std::cout << char_data << std::endl;

	return 0;
}