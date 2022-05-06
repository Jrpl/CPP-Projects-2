#include <vector>
#include <chrono>
#include <algorithm>
#include "sort.h"

int main()
{
	std::vector<std::vector<int>> master_list;
	std::vector<int> list1; nwacc::fill_vector(list1, 50000); master_list.push_back(list1);
	std::vector<int> list2; nwacc::fill_vector(list2, 100000); master_list.push_back(list2);
	std::vector<int> list3; nwacc::fill_vector(list3, 150000); master_list.push_back(list3);
	std::vector<int> list4; nwacc::fill_vector(list4, 200000); master_list.push_back(list4);
	std::vector<int> list5; nwacc::fill_vector(list5, 250000); master_list.push_back(list5);
	std::vector<int> list6; nwacc::fill_vector(list6, 300000); master_list.push_back(list6);
	std::vector<int> list7; nwacc::fill_vector(list7, 350000); master_list.push_back(list7);
	std::vector<int> list8; nwacc::fill_vector(list8, 400000); master_list.push_back(list8);
	std::vector<int> list9; nwacc::fill_vector(list9, 450000); master_list.push_back(list9);
	std::vector<int> list10; nwacc::fill_vector(list10, 500000); master_list.push_back(list10);
	std::vector<int> list11; nwacc::fill_vector(list11, 550000); master_list.push_back(list11);
	std::vector<int> list12; nwacc::fill_vector(list12, 600000); master_list.push_back(list12);
	std::vector<int> list13; nwacc::fill_vector(list13, 650000); master_list.push_back(list13);
	std::vector<int> list14; nwacc::fill_vector(list14, 700000); master_list.push_back(list14);
	std::vector<int> list15; nwacc::fill_vector(list15, 750000); master_list.push_back(list15);
	std::vector<int> list16; nwacc::fill_vector(list16, 800000); master_list.push_back(list16);
	std::vector<int> list17; nwacc::fill_vector(list17, 850000); master_list.push_back(list17);
	std::vector<int> list18; nwacc::fill_vector(list18, 900000); master_list.push_back(list18);
	std::vector<int> list19; nwacc::fill_vector(list19, 950000); master_list.push_back(list19);
	std::vector<int> list20; nwacc::fill_vector(list20, 1000000); master_list.push_back(list20);
	std::vector<int> list21; nwacc::fill_vector(list21, 1100000); master_list.push_back(list21);
	std::vector<int> list22; nwacc::fill_vector(list22, 1200000); master_list.push_back(list22);
	std::vector<int> list23; nwacc::fill_vector(list23, 1300000); master_list.push_back(list23);
	std::vector<int> list24; nwacc::fill_vector(list24, 1400000); master_list.push_back(list24);
	std::vector<int> list25; nwacc::fill_vector(list25, 1500000); master_list.push_back(list25);
	std::vector<int> list26; nwacc::fill_vector(list26, 1600000); master_list.push_back(list26);
	std::vector<int> list27; nwacc::fill_vector(list27, 1700000); master_list.push_back(list27);
	std::vector<int> list28; nwacc::fill_vector(list28, 1800000); master_list.push_back(list28);
	std::vector<int> list29; nwacc::fill_vector(list29, 1900000); master_list.push_back(list29);
	std::vector<int> list30; nwacc::fill_vector(list30, 2000000); master_list.push_back(list30);

	// Insertion Sort
	std::cout << "***Insertion Sort Start***" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < master_list.size() - 18; i++)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::insertion_sort(master_list[i]);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Shell Sort
	std::cout << "***Shell Sort Start***" << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < master_list.size() - 10; i++)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::shell_sort(master_list[i]);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Quick Sort First Element
	std::cout << "***Quick Sort First Element Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_sort(list, 'F');
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Quick Sort Middle Element
	std::cout << "***Quick Sort Middle Element Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_sort(list, 'M');
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Quick Sort Random Element
	std::cout << "***Quick Sort Random Element Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_sort(list, 'R');
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}
	
	// Quick Sort Median of Five
	std::cout << "***Quick Sort Median of Five Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_sort(list, '5');
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Quick Sort Median of Three
	std::cout << "***Quick Sort Median of Three Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_sort(list, '3');
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Quick Shell Sort
	std::cout << "***Quick Shell Sort Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::quick_shell_sort(list);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Merge Sort
	std::cout << "***Merge Sort Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::merge_sort(list);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// Radix Sort
	std::cout << "***Radix Sort Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		nwacc::radix_sort(list);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}

	// C++ Sort
	std::cout << "***C++ Sort Start***" << std::endl;
	std::cout << std::endl;
	for (std::vector<int> list : master_list)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		std::sort(list.begin(), list.end());
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time - start_time).count();
		std::cout << elapsed_time << std::endl;
		std::cout << std::endl;
	}
}