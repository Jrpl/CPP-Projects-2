#ifndef OFFSET_ARRAY_H
#define OFFSET_ARRAY_H

#include <iostream>  // std::cerr
#include <stdexcept> // std::out_of_range

namespace nwacc {
	// Declared array index should start at int S and end at int E
	// Array can be of any type specified by the user of the class
	// Indexes should always be an int
	// First index in the array should not be below 0

	template <typename T, size_t S, size_t E>
	class offset_array {
	public:
		// Constructor
		explicit offset_array()
			: size{ 0 }, capacity{ (E - S) + 1 }
		{
			// Initialize array and allocate memory
			this->data = new T[this->capacity]{};
		}

		// Move constructor
		offset_array(offset_array&& other)
			: size{ other.size }, capacity{ other.capacity }, data{ other.data }
		{
			std::cout << "Move constructor called" << std::endl;
			other.data = nullptr;
			other.size = 0U;
			other.capacity = 0U;
		}

		// Copy constructor
		offset_array(const offset_array& other)
			: size{ other.size }, capacity{ other.capacity }, data{ nullptr }
		{
			std::cout << "Copy constructor called" << std::endl;
			this->data = new T[this->capacity];
			for (auto index = 0U; index < this->size; index++) {
				this->data[index] = other.data[index];
			}
		}

		// Assignment operator
		offset_array& operator=(const offset_array& rhs) {
			if (this == &rhs) {
				return *this;
			}
			// Else, the two objects are not the same
			std::cout << "Assignment operator called" << std::endl;
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		// Move assignment operator
		offset_array& operator=(offset_array&& rhs) {
			if (this == &rhs) {
				return *this;
			}
			// Else, the two objects are not the same
			std::cout << "Move assignement operator called" << std::endl;
			std::swap(this->my_size, rhs.my_size);
			std::swap(this->my_capacity, rhs.my_size);
			std::swap(this->data, rhs.data);
			return *this;
		}

		// Destructor
		~offset_array()
		{
			std::cout << "Destructor called" << std::endl;
			delete[] this->data;
		}

		// Subscript operator overload
		T& operator[](int index) {
			if (index < S || index > E)
				throw std::out_of_range("Out of Range");
			this->size++;
			return this->data[index - S];
		}

		// Const Subscript operator overload
		const T& operator[](int index) const {
			if (index < S || index > E)
				throw std::out_of_range("Out of Range");
			return this->data[index - S];
		}

		// Stream Insertion operator overload
		friend std::ostream& operator<<(std::ostream& out, const offset_array& array) {
			out << "Size " << array.size << std::endl;
			out << "Capacity " << array.capacity << std::endl;

			// No way for me to know which indexes are populated so print them all
			for (auto index = S; index <= E; index++) {
				if (array[index] == 0) {
					out << " ";
				}
				else {
					out << array[index] << " ";
				}
			}

			out << std::endl;
			return out;
		}

	private:
		size_t size;

		size_t capacity;

		T* data;
	};
}

#endif // !OFFSET_ARRAY_H