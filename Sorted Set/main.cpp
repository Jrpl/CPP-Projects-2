#include <iostream>
#include "sorted_set.h"
#include "vector"

int main()
{
	nwacc::sorted_set<int> set;
	std::vector<int> vect;
	vect.push_back(10);
	vect.push_back(20);

	set.empty();

	set.add(20);
	set.add(5);
	set.add(15);
	set.add(10);

	set.print();

	set.empty();
	set.size();

	set.remove(15);
	set.size();
	set.print();

	set.contains(10);

	set.print_lot(vect);

	set.clear();

	std::cout << std::endl;

	nwacc::sorted_set<int> reverse_set(false);
	std::vector<int> reverse_vect;
	reverse_vect.push_back(6);

	reverse_set.empty();

	reverse_set.add(3);
	reverse_set.add(6);
	reverse_set.add(9);
	reverse_set.add(12);

	reverse_set.print();
	reverse_set.empty();
	reverse_set.size();

	reverse_set.remove(3);
	reverse_set.size();
	reverse_set.print();

	reverse_set.contains(12);

	reverse_set.print_lot(reverse_vect);

	reverse_set.clear();

	std::cout << std::endl;

	nwacc::sorted_set<double> double_set;
	std::vector<double> double_vect;
	double_vect.push_back(4.2);
	double_vect.push_back(6.9);

	double_set.empty();

	double_set.add(2.9);
	double_set.add(4.2);
	double_set.add(6.9);
	double_set.add(7.5);
	double_set.add(9.1);

	double_set.print();

	double_set.empty();
	double_set.size();

	double_set.remove(7.5);
	double_set.size();
	double_set.print();

	double_set.contains(2.9);

	double_set.print_lot(double_vect);

	double_set.clear();

	return 0;
}