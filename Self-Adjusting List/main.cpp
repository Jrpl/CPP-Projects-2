#include <iostream>
#include "self_adjusting_array.h"

int main()
{
	// Here I DO NOT pass an initial size, what is the capacity? 16 (14 + 2).
	// array_list does not define this operator or a conversion to a type acceptable to the predefined operator
	// 1st error was because we failed to provide an overload for the array subscript [] operator. 
	//
	// no operator found which takes a left hand operand of type 'const nwacc::array_list<size_t>'
	// ELI5 - Why did we need the const array subscript operator? 

	nwacc::array_list<int> list(1U);
	std::cout << "Size 0, Cap 3, all nill values" << std::endl;
	std::cout << list << std::endl;

	list.push_back(5);
	list.push_back(3);
	list.emplace_back(10);
	list.emplace_back(7);
	list.emplace_back(13);
	std::cout << "Size 5, Cap 6, 5 3 10 7 13 nill" << std::endl;
	std::cout << list << std::endl;

	list.push_front(1);
	std::cout << "Size 6, Cap 6, 1 5 3 10 7 13" << std::endl;
	std::cout << list << std::endl;

	list.push_front(4);
	std::cout << "Size 7, Cap 9, 4 1 5 3 10 7 13 nill nill" << std::endl;
	std::cout << list << std::endl;

	list.push_front(6);
	std::cout << "Size 8, Cap 9, 6 4 1 5 3 10 7 13 nill" << std::endl;
	std::cout << list << std::endl;

	list.find(3);
	std::cout << "Size 8, Cap 9, 3 6 4 1 5 10 7 13 nill" << std::endl;
	std::cout << list << std::endl;

	list.find(7);
	std::cout << "Size 8, Cap 9, 7 3 6 4 1 5 10 13 nill" << std::endl;
	std::cout << list << std::endl;

	list.find(5);
	std::cout << "Size 8, Cap 9, 5 7 3 6 4 1 10 13 nill" << std::endl;
	std::cout << list << std::endl;

	return 0;
}