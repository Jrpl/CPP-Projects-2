#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
#include <vector>

namespace nwacc {
	template <typename T>
	class sorted_set {
	public:
		// Constructor
		explicit sorted_set(bool order = true) : my_size{ 0 }, my_order{ order }
		{
			init();
		}

		// Copy constructor
		sorted_set(const sorted_set& other) : my_size{ other.my_size }, my_order{ other.my_order }
		{
			head = other->head;
		}

		// Move constuctor - other is what we're moving from, we're moving to "this"
		sorted_set(sorted_set&& other) : my_size{ other.my_size }, my_order{ other.my_order }
		{
			other->head = head;
			other.my_size = 0U;
			other.my_order = true;
		}

		// Assignment operator - making a copy of the reference
		sorted_set& operator=(const sorted_set& rhs)
		{
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		// Move assignment operator - making a full copy
		sorted_set& operator=(sorted_set&& rhs)
		{
			std::swap(this->my_size, rhs.my_size);
			std::swap(this->my_order, rhs.my_order);
			return *this;
		}

		// Destructor
		~sorted_set()
		{
			std::cout << "Destructor called" << std::endl;
			this->clear();
			delete this->head;
		}
	private:
		// Singly Linked List implementation
		struct node {
			T data;

			node* next;

			// Copy constructor
			node(const T& data = T{}, node* next = nullptr)
				: data{ data }, next{ next } { }

			// Move constructor
			node(T&& data, node* next = nullptr)
				: data{ std::move(data) }, next{ next } { }
		};

	public:
		class const_iterator {
		public:
			// Iterators must have begin, end, ++, -- (pre and post ++a or a++), * (dereference)
			// We also need == and != operators
			// current DOES NOT point to the value, but to the node which contains the value. 
			const_iterator() : current{ nullptr } { }

			// Dereference Iterator
			const T& operator*()
			{
				return this->retrieve();
			}

			// ++ Pre Iterator
			const_iterator& operator++()
			{
				this->current = this->current->next;
				return *this;
			}

			// ++ Post Iterator
			const_iterator& operator++(int)
			{
				auto old = *this;
				++(*this); // This is called the pre-increment operator. 
				return old;
			}

			// -- Pre Iterator
			const_iterator& operator--()
			{
				this->current = this->current->previous;
				return *this;
			}

			// -- Post Iterator
			const_iterator& operator--(int)
			{
				auto old = *this;
				--(*this);
				return old;
			}

			// == Iterator
			bool operator==(const const_iterator& rhs) const
			{
				return this->current == rhs.current;
			}

			// != Iterator
			bool operator!=(const const_iterator& rhs) const
			{
				return !(*this == rhs);
			}
		protected:
			node* current;

			T& retrieve() const
			{
				return this->current->data;
			}

			const_iterator(node* position) : current{ position } {}

			friend class sorted_set<T>;
		}; // End of const iterator class

		// Start at first value
		const_iterator begin() const
		{
			return const_iterator(this->head);
		}

		// Stream Insertion Operator
		void print(std::ostream& out = std::cout)
		{
			node* current = this->head->next;
			out << "Set: ";
			while (current != nullptr) {
				out << current->data << " ";
				current = current->next;
			}
			out << std::endl;
		}

		void print_lot(std::vector<T> values, std::ostream& out = std::cout)
		{
			node* current = this->head->next;
			out << "Lot: ";

			// For each value in vector, find the value in the set
			for (T val : values) {
				while (current->next != nullptr && current->next->data != val) {
					current = current->next;
				}
				
				// Check if value exists
				if (current->next == nullptr)
				{
					throw std::out_of_range("\nValue does not exist");
				} // Else, we found the value

				out << val << " ";
			}

			out << std::endl;
		}

		// Check if the sorted set is empty
		bool empty() const
		{
			bool isEmpty = this->my_size == 0U;
			std::cout << "IsEmpty: " << isEmpty << std::endl;
			return isEmpty;
		}

		// Check size
		size_t size() const
		{
			std::cout << "Size: " << this->my_size << std::endl;
			return this->my_size;
		}

		// Remove node containing specific value
		void remove(T&& value)
		{
			// Find value 
			node* current = this->head->next;
			while (current->next != nullptr && current->next->data != value) {
				current = current->next;
			}

			// Check if value exists
			if (current->next == nullptr)
			{
				throw std::out_of_range("\nValue does not exist");
			}

			// Remove node
			current->next = current->next->next;

			--this->my_size;

			return;
		}

		// Check if element exists
		bool contains(T&& value)
		{
			// Find value (same logic as the find in remove)
			node* current = this->head->next;
			while (current->next != nullptr) {
				if (current->data == value) {
					break;
				}
				current = current->next;
			}

			// Check if the value exists
			if (current == nullptr)
			{
				throw std::out_of_range("\nValue does not exist");
				return false;
			} // Else, we found the value

			std::cout << "Found: " << current->data << std::endl;
			return true;
		}

		// Remove the first element, only used for clear method
		void pop_front()
		{
			node* temp = this->head->next;
			this->head->next = temp->next;

			delete temp;
			--this->my_size;
		}

		// Remove all elements from the sorted set
		void clear()
		{
			while (!this->empty()) {
				this->pop_front();
			}
		}

		// Add elements to the list based on order
		bool add(const T& value)
		{
			node* new_node = new node{ value, nullptr };
			node* current;

			// Set current node to head
			current = head;
			
			// If the order is natural, add elements lowest to highest
			if (this->my_order) {
				while (current->next != nullptr && current->next->data < new_node->data)
				{
					current = current->next;
				}
			}
			// If the order is un-natural, add elements highest to lowest
			else if (!this->my_order) {
				while (current->next != nullptr && new_node->data < current->next->data)
				{
					current = current->next;
				}
			}

			new_node->next = current->next;
			current->next = new_node;
			++this->my_size;
			return true;
		}

	private:
		size_t my_size;

		bool my_order;

		node* head;

		void init()
		{
			std::cout << "Natural: " << this->my_order << std::endl;
			this->my_size = 0U;
			this->head = new node;
			this->head->next = nullptr;
		}
	};
}

#endif