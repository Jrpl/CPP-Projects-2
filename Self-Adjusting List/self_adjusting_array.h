#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace nwacc {

	// list - a collection of items with possible duplicate values.
	// set - a collection of items with NO duplicate values.
	// the array_list is a vector.
	// vector - the problem it solves is the static nature of arrays.
	// arrays are static because the size cannot change.
	// arrays are only good at one thing - random access (the elements - items - are indexed).
	// vectors provide the fast random access but can grow as needed.
	// array_list will be our implementation of the vector. 

	template <typename T>
	class array_list {
	public:

		explicit array_list(size_t initial_size = 14) :
			my_size{ 0 }, my_capacity{ initial_size + 2 }
		{
			// explicit - in c++ char data type is really an integer value.
			// Lets say the explicit is removed. array_list('A');
			// The reason it would work, is because the 'A' could be turned into an integer.
			// When we place explicit in the constructor, it requires the initial_size param
			// to be that type explicitly. array_list('A') would no longer compile.
			// on line 24 we are setting the values of the attributes.
			// my_size = 0 and my_capacity = 16 this syntax is called an object initializer.
			// my_size(0) is the same as my_size { 0 }
			// we still need to allocate the memory.
			this->data = new T[this->my_capacity];
		}

		// Copy constructor - creates new array list as copy of old one
		array_list(const array_list& other) :
			my_size{ other.my_size }, my_capacity{ other.my_capacity }, data{ nullptr }
		{
			this->data = new T[this->my_capacity];
			for (auto index = 0U; index < this->my_size; index++) {
				this->data[index] = other.data[index];
			}
		}

		// Move constuctor - other is what we're moving from, we're moving to "this"
		array_list(array_list&& other) :
			my_size{ other.my_size }, my_capacity{ other.my_capacity }, data{ other.data }
		{
			other.data = nullptr;
			other.my_size = 0U;
			other.my_capacity = 0U;
		}

		// Assignment operator - making a copy of the reference
		array_list& operator=(const array_list& rhs)
		{
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		// Move assignment operator - making a full copy
		array_list& operator=(array_list&& rhs)
		{
			std::swap(this->my_size, rhs.my_size);
			std::swap(this->my_capacity, rhs.my_size);
			std::swap(this->data, rhs.data);
			return *this;
		}

		// Destructor
		~array_list()
		{
			// If I say delete this->data it ONLY delete the pointer at that position.
			// delete[] deletes all the allocated memory in the array, not just index 0. 
			delete[] this->data;
		}

		T& operator[](int index)
		{
			// We will assume index is valid. We will fix this later
			// TODO ADD exception for index out of range. 
			return this->data[index];
		}

		const T& operator[](int index) const
		{ // Here the const at the end of the method header tells C++ this method WILL NOT CHANGE STATE.
			// We will assume index is valid. We will fix this later
			// TODO ADD exception for index out of range.
			return this->data[index];
		}

		// check if empty
		bool empty() const
		{
			return this->my_size == 0;
		}

		// check size
		size_t size() const
		{
			return this->my_size;
		}

		void reserve(int new_capacity)
		{
			// Allocate new memory
			// Move the values from the old memory
			// Delete the old memory
			// Change capacity

			if (new_capacity < this->my_size) {
				return; // current number of elements is larger than the new_capacity
			} // else, the new capacity will increase

			T* new_data = new T[new_capacity]; // Allocating new memory

			for (auto index = 0U; index < this->my_size; index++) {
				new_data[index] = std::move(this->data[index]); // Move old data to new_data
			}

			this->my_capacity = new_capacity;
			std::swap(this->data, new_data); //new_data is larger but my attribute is data. Swap and delete.
			delete[] new_data;
		}

		// Find value in the array list and move it to the front
		bool find(T value)
		{
			T temp;

			// Only concern is if the list is empty
			if (this->empty()) {
				throw std::out_of_range("List is empty");
			} // else, we have values

			// Loop through to find the value
			for (auto index = 0U; index < this->my_size; index++) {
				// If we find the value move it to the front
				if (this->data[index] == value) {
					std::cout << "Value found" << std::endl;

					temp = this->data[index];

					// Move all other values in the array back one
					for (int i = index; i < this->my_size; i++) {
						this->data[i] = this->data[i + 1];
					}

					this->my_size--;

					// Re-insert the value at the front of the array
					push_front(temp);

					return true;
				} // Else, do nothing
			}

			std::cout << "Value not found" << std::endl;
			return false;
		}

		// Insert values at the front of the array list
		void push_front(T value)
		{
			if (this->my_size == this->my_capacity) {
				// I'm out of space, increase the size
				this->reserve((this->my_capacity * 3) / 2);
			} // else, we have space do_nothing();

			// Insert the new value at the beginning and move all other values back 1
			for (int index = this->my_size - 1; index > -1; index--) {
				this->data[index + 1] = this->data[index];
			}

			this->data[0U] = value;
			this->my_size++;
		}

		void push_back(const T& value)
		{
			if (this->my_size == this->my_capacity) {
				// I'm out of space, increase the size
				this->reserve((this->my_capacity * 3) / 2);
			} // else, we have space do_nothing();

			this->data[this->my_size++] = value;
		}

		// push_back vs emplace_back?
		void emplace_back(T&& value) // && r value declarator
		{
			if (this->my_size == this->my_capacity) {
				this->reserve((this->my_capacity * 3) / 2);
			}

			this->data[this->my_size++] = std::move(value);
		}

		void pop_back() // pop_back "removes" the value from the list
		{
			// Only concern is if the list is empty
			if (this->empty()) {
				throw std::out_of_range("List is empty");
			} // else, we have values

			--this->my_size;
		}

		// pop_back vs back?
		const T& back() const // returns the value without removing it
		{
			// Only concern is if the list is empty
			if (this->empty()) {
				throw std::out_of_range("List is empty");
			} // else, we have values

			return this->data[this->my_size - 1];
		}

		// We need two iterators - const and non-const iterator
		typedef T* iterator; // This creates an alias so iterator means T*
		typedef const T* const_iterator; // const_iterator means const T*

		iterator begin()
		{
			return &this->data[0U];
		}

		// What does this means - the list WILL NOT BE CHANGED! 
		friend std::ostream& operator<<(std::ostream& out, const array_list& list)
		{
			// Because the array_list is const, the ONLY methods (behaviors) it can use
			// are those methods which are also defined as CONST! 
			out << "Size " << list.my_size << std::endl;
			out << "Capacity " << list.my_capacity << std::endl;

			// Here if we say auto index = 0; the 0 tells C++ to make index an integer.
			// But, what is list.my_size? size_t (unsigned int).
			// How can I declare index AS an size_t using auto?
			// What 0U mean? an unsigned int! (size_t is a typedef).
			// a typedef is an alias for something. 
			for (auto index = 0U; index < list.my_size; index++) {
				out << list[index] << " "; // here I am applying an operation which is NOT const. 
				// out << list.data[index] << " ";
				// << Stream insertion operator (defined) Line 45.
				// [] array subscript operator. WHERE did we define how this works?
			}

			for (auto index = list.my_size; index < list.my_capacity; index++) {
				out << "nill ";
			}

			out << std::endl;
			return out;
		}

	private:
		// what do we need. We need a pointer to some data. - this will be our dynamic array.
		// remember in c++ arrays do not know their own size. We need a size attribute.
		// We need to have an array which bigger than the current number of elements. Capacity.
		// size - number of elements in our array_list (public)
		// capacity - number of spaces I have available before I have to resize my array. (private)
		size_t my_size;

		// size_t - unsigned int. No negative values. 
		size_t my_capacity;

		// This will be the pointer to our dynamic memory which holds the values. 
		T* data;
	};
}

#endif