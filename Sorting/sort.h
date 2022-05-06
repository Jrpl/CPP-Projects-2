#ifndef SORT_H_
#define SORT_H_

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include <stdlib.h>

// Very good visualization of these sorts - 
// https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/tutorial/

// Another good visualization of sorts - 
// http://algostructure.com/index.php

namespace nwacc
{
	void fill_vector(std::vector<int>& list, size_t size)
	{
		list.clear();
		for (auto index = 0U; index < size; index++)
		{
			list.push_back(index % 10);
		}
	}

	inline void shuffle(std::vector<int>& list)
	{
		std::shuffle(list.begin(), list.end(), 
			std::mt19937(std::random_device()()));
	}

	inline bool is_sorted(std::vector<int>& list)
	{
		return std::is_sorted(list.begin(), list.end());
	}

	void print(const std::vector<int>& list, std::ostream& out = std::cout)
	{
		for (auto element : list) {
			out << element << " ";
		}

		out << std::endl;
	}

	void radix_sort(std::vector<int>& list, const int digit_count = 10)
	{
		const int k_radix = 10;
		auto vector_index = 0U;
		auto queue_index = 0U;
		std::queue<int> queues[k_radix]; // 0 - 9 queue locations.
		for (auto digit_index = 0, factor = 1;
			digit_index < digit_count;
			factor *= k_radix,
			digit_index++) {
			// As we go through this loop (factor - 1, 10, 100, 1000, etc...)
			for (vector_index = 0U; vector_index < list.size(); vector_index++) {
				queues[(list[vector_index] / factor) % k_radix].push(list[vector_index]);
			}

			for (vector_index = queue_index = 0; 
				vector_index < k_radix; 
				vector_index++) {
				while (!queues[vector_index].empty()) {
					list[queue_index++] = queues[vector_index].front();
					queues[vector_index].pop();
				}
			}
		}
	}

	
	// Donald Shell developed the shell sort which works on gaps.
	// large gaps to 1. (a gap of 1 IS the insertion sort).
	// The original gaps sequence developed by Shell is not good.
	template <typename T>
	void shell_sort(std::vector<T>& list)
	{
		for (auto gap = list.size() / 2; gap > 0; gap /= 2) {
			// we repeat the insertion sort code.
			for (auto index = gap; index < list.size(); index++) {
				auto temp = std::move(list[index]);
				auto inner_index = index;
				for(; inner_index >= gap &&
					temp < list[inner_index - gap];
					inner_index -= gap) {
					list[inner_index] = std::move(list[inner_index - gap]);
				}
				list[inner_index] = std::move(temp);
			}
		}
	}

	
	// This method is "slow", but this method is good for N (size)
	// N <= 10. If the data is "almost" sorted then this a very good sort.
	// We call this the insertion sort because - when we find something
	// out of order we "insert" it into the correct position by shifting
	// the elements down by one. Remember we start sorting at index 1. 
	template <typename T>
	void insertion_sort(std::vector<T>& list)
	{
		for (auto index = 1U; index < list.size(); index++) {

			// create a temp value for my insertion value.
			auto temp = std::move(list[index]);
			auto inner_index = 0U;
			for (inner_index = index; 
				inner_index > 0 && 
				temp < list[inner_index - 1];
				inner_index--) {
				// Here we shift the values to the right. 
				list[inner_index] = std::move(list[inner_index - 1]);
			}
			// I have moved everything and I have my location,
			// I can "insert" the temp value.
			list[inner_index] = std::move(temp);
		}
	}

	// This will be insertion sort, but only for PART of a list.
	// The values from left to right will sorted. 
	template <typename T>
	void insertion_sort(std::vector<T>& list, int left, int right)
	{
		for (auto index = left + 1; index <= right; index++) {
			auto temp = std::move(list[index]);
			auto inner_index = index;
			for (inner_index = index; 
				inner_index > left &&
				temp < list[inner_index - 1]; inner_index--) {
				list[inner_index] = std::move(list[inner_index - 1]);
			}
			list[inner_index] = std::move(temp);
		}
	}
	
	template <typename T>
	const T& median_of_three(std::vector<T>& list, int left, int right)
	{
		auto center = (left + right) / 2;
		if (list[center] < list[left]) {
			std::swap(list[left], list[center]);
		} // else, the center and left are in order do_nothing();

		if (list[right] < list[left]) {
			std::swap(list[left], list[right]);
		} // else, the right value is in the correct place, do_nothing();

		if (list[right] < list[center]) {
			std::swap(list[center], list[right]);
		} // else, the items are in order do_nothing();

		std::swap(list[center], list[right - 1]);
		return list[right - 1];
	}

	template <typename T>
	const T& median_of_five(std::vector<T>& list, int left, int right)
	{
		auto center = (left + right) / 2;
		auto left_center = (left + center) / 2;
		auto right_center = (center + right) / 2;
		if (list[left_center] < list[left]) {
			std::swap(list[left], list[left_center]);
		} // else, the left_center and the left are in order do_nothing();

		if (list[center] < list[left]) {
			std::swap(list[left], list[center]);
		} // else, the center and left are in order do_nothing();

		if (list[right_center] < list[left]) {
			std::swap(list[left], list[right_center]);
		} // else, the right_center and left are in order do_nothing();

		if (list[right] < list[left]) {
			std::swap(list[left], list[right]);
		} // else, the right value is in the correct place do_nothing();

		if (list[right_center] < list[center]) {
			std::swap(list[center], list[right_center]);
		} // else, the right_center is in the correct place do_nothing();

		if (list[right] < list[center]) {
			std::swap(list[center], list[right]);
		} // else, the items are in order do_nothing();

		std::swap(list[center], list[right - 1]);
		return list[right - 1];
	}
	
	template <typename T>
	void quick_sort(std::vector<T>& list, int left, int right, char pivot_type)
	{
		T& pivot = list[0];
		switch (pivot_type)
		{
			// First Element
			case 'F':
				pivot = list[0];
			// Middle Element
			case 'M':
				pivot = list[(list.size() - 1) / 2];
			// Random Element
			case 'R':
				pivot = list[std::rand() % list.size()];
			// Median of Five
			case '5':
				pivot = median_of_five(list, left, right);
		    // Median of Three
			case '3':
				pivot = median_of_three(list, left, right);
			default:
				break;
		}

		// 5 is my delta and if I am less than 5 then I can insertion sort.
		// In the real world we seldom have truly random data.
		// Some research which seems to indicate a random pivot is the best. 
		if (left + 5 <= right) { // This 5 makes a big difference in performance. 
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;
			// If you look online, this will be written with a break statement.
			// this is the partition. 
			while (!is_done) {
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index) {
					std::swap(list[left_index], list[right_index]);
				} else {
					is_done = true;
				}
			}

			// The data is partitioned, more sorted.
			// move the pivot back to the center.
			// move it to lefts location.
			std::swap(list[left_index], list[right - 1]);
			// We will not quick sort the left side and the right side.
			quick_sort(list, left, left_index - 1, pivot_type);
			quick_sort(list, left_index + 1, right, pivot_type);
		} else {
			// Here I can run the insertion sort.
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort(std::vector<T>& list, char pivot_type)
	{
		quick_sort(list, 0, list.size() - 1, pivot_type);
	}

	template <typename T>
	void quick_shell_sort(std::vector<T>& list, int left, int right)
	{
		// 2500 is my delta and if I am less than 5 then I can shell sort.
		if (left + 2500 <= right) {
			const T& pivot = median_of_three(list, left, right);
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;

			while (!is_done) {
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index) {
					std::swap(list[left_index], list[right_index]);
				}
				else {
					is_done = true;
				}
			}

			// The data is partitioned, more sorted.
			// move the pivot back to the center.
			// move it to lefts location.
			std::swap(list[left_index], list[right - 1]);
			// We will not quick sort the left side and the right side.
			quick_shell_sort(list, left, left_index - 1);
			quick_shell_sort(list, left_index + 1, right);
		}
		else {
			// Here I can run the shell sort.
			shell_sort(list);
		}
	}

	template <typename T>
	void quick_shell_sort(std::vector<T>& list)
	{
		quick_shell_sort(list, 0, list.size() - 1);
	}

	template <typename T>
	void merge(
		std::vector<T>& list,
		std::vector<T>& temp, 
		int left_index, 
		int right_index, 
		int right_end_index)
	{
		// list - the data to be sorted.
		// temp - the temp place we store the merged values.
		// We merge the data into temp and then copy if from temp back to
		// the list.
		// left_index is the left most start index.
		// Why do I not need to know where the first half ends.
		// Because it will end at right_index - 1
		// right_index is the first index of the second half.
		// right_end_index is the last index of the second half.
		// [left_index, right_index - 1] - [right_index, right_end_index]

		const auto left_end_index = right_index - 1;
		const auto number_of_elements = right_end_index -
			left_index + 1;
		auto temp_index = left_index;

		// The main loop will iterate over both halves of the list.
		while (left_index <= left_end_index &&
			   right_index <= right_end_index) {
			// the value at left is <= value at right, then take left.
			// if not, then take right. 
			if (list[left_index] <= list[right_index]) {
				temp[temp_index++] =
					std::move(list[left_index++]);
			} else {
				temp[temp_index++] =
					std::move(list[right_index++]);
			}
		}
		
		// ALL WE KNOW, is either the left, right, or both are done. 
		// After this loop, what is true about index values?
		// left_index == left_end - end the loop.
		// right_index < right_end.
		// left_index < left_end but right_index == right_end
		// left_index == left_end and right_index == right_end

		// Only one of the while loops will run. 
		// Move anything left in the first half.
		while (left_index <= left_end_index) {
			temp[temp_index++] =
				std::move(list[left_index++]);
		}
		
		// Move anything left in the second half.
		while (right_index <= right_end_index) {
			temp[temp_index++] =
				std::move(list[right_index++]);
		}
		
		// Where are the sorted values? They are in Temp.
		// The values in temp between the index values are SORTED.
		// Now, I can copy the values from temp back into list.
		// OVER the same set of index values.
		// I MUST use right_end_index and count down? Why?
		// Why not start at left_index and count until right_end_index?
		for (
			auto index = 0; 
			index < number_of_elements; 
			++index,
			--right_end_index) {
			list[right_end_index] =
				std::move(temp[right_end_index]);
		}
	}
	
	template <typename T>
	void merge_sort(
		std::vector<T>& list, 
		std::vector<T>& temp,
		int left,
		int right)
	{
		// as long as left is less than right, find the center and split
		// the list. This is not done with iteration (looping).
		// list of size 100, left = 0 and right = 99 center = 49
		// List size 10 - 0 to 9
		// l - 0, r - 9, c - 4
		// l - 0, r - 4, c - 2
		// l - 0, r - 2, c - 1
		// l - 0, r - 1, c - 0
		// l - 0, r - 0 
		if (left < right) {
			auto center = (left + right) / 2;
			// All we are doing is splitting the data up. 
			merge_sort(list, temp, left, center);
			merge_sort(list, temp, center + 1, right);
			merge(list, temp, left, center + 1, right);
		} // else, left is greater than or equal to right do_nothing();
	}
	
	template <typename T>
	void merge_sort(std::vector<T>& list)
	{
		std::vector<T> temp(list.size());
		merge_sort(list, temp, 0, list.size() - 1);
	}
	
}

#endif