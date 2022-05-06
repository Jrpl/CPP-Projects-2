#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace nwacc {
	template<typename K, typename V>
	class dictionary {
	public: 
		explicit dictionary(const size_t size = 20)
		 : data(next_prime(size))
		{
			this->clear();
		}

		// Print the key value pair at each index of the vector containing the vectors
		void print(std::ostream& out = std::cout)
		{
			for (int i = 0; i < my_size; i++)
			{
				out << "Index " << i;

				for (auto& entry : this->data) {
					out << "K: " << entry.key << " V: " << entry.value;
				}
			}

			out << std::endl;
		}
		
		void clear()
		{
			this->my_size = 0U;
			for (auto& entry : this->data) {
				entry.status = k_empty;
			}
		}

		// Pass key and return true if key exists in collection
		bool contains_key(const K& key) const
		{
			return this->find_position(key);
		}

		// Pass value and return true if value exists in collection
		bool contains_value(const V& value) const
		{
			return this->find_position(value);
		}

		// Pass key and return value associated with key
		V& get(const K& key)
		{
			auto position = this->find_position(key);
			if (!position)
			{
				throw std::out_of_range("Key does not exist");
			}
			return this->data[position].value;
		}

		// Pass key and value to be inserted into the collection
		// If the key already exists, overwrite the value
		bool put(const K& key, const V& value)
		{
			// Do we have a duplicate?
			auto position = this->find_position(key);
			if (this->data[position].key == key)
			{
				this->data[position].value = value;
			}
			// Else, its a new value
			else
			{
				this->data[position].key = key;
				this->data[position].value = value;
			}

			auto load_limit = static_cast<size_t>(
							 (static_cast<double>(this->data.size()) * .7));
			if (this->my_size > load_limit) {
				this->rehash();
			}
			
			return true;
		}
		
		// Pass key and remove associate key and value from collection
		bool remove(const K& key)
		{
			auto position = this->find_position(key);
			this->data.erase(position);
			--my_size;
			return true;
		}

		// Pass value and remove all associated keys and values from collection
		bool remove_value(const V& value)
		{
			auto position = this->find_position(value);
			this->data.erase(position);
			--my_size;
			return true;
		}

		// Check if empty
		bool empty() const
		{
			return this->my_size == 0U;
		}

		// Check size
		size_t size() const
		{
			return this->my_size;
		}

		class const_iterator {
		public:
			// Iterators must have begin, end, ++, -- (pre and post ++a or a++), * (dereference)
			// We also need == and != operators
			// current DOES NOT point to the value, but to the node which contains the value. 
			const_iterator() : current{ nullptr } { }

			// Dereference Iterator
			const V& operator*()
			{
				return this->retrieve();
			}

			// ++ Pre Iterator
			const_iterator& operator++()
			{
				current = current->next;
				return *this;
			}

			// -- Pre Iterator
			const_iterator& operator--()
			{

			}

			// ++ Post Iterator
			const_iterator& operator++(int)
			{
				auto old = *this;
				++(*this);
				return old;
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
			std::vector<entry> current;

			V& retrieve() const
			{
				// Get value by de-referencing current
				return this->current->value;
			}

			const_iterator(std::vector<entry> position) : current{ position } {}

			friend class dictionary<K, V>;
		};

		// Return iterator of the beginning of the collection
		const_iterator begin() const
		{
			return const_iterator(data[0]);
		}

		// Return iterator past the end of the collection
		const_iterator end() const
		{
			return const_iterator(data[my_size] + 1);
		}
	
	private:
		struct entry
		{
			K key;
			V value;

			entry(const K& new_key = K{},
				const V& new_value = V{}) :
				key { new_key }, value { new_value }

			entry(K&& new_key,
				V&& new_value) :
				key { std::move(new_key) }, value { std::move(new_value) }
		};

		// Create "size" number of vectors of type entry equal
		data = new std::vector<entry>[my_size];

		size_t my_size;

		size_t find_position(const value) const
		{
			auto offset = 1U;
			auto current_position = this->hash(value);

			while (this->data[current_position].value != value) {
				current_position += offset;
				offset += 2U;
				if (current_position >= this->data.size()) {
					current_position -= this->data.size();
				}
			}

			return current_position;
		}
		
		size_t hash(const K& key) const
		{
			std::hash<K> hash_function;
			return hash_function(key) % this->data.size();
		}
		
		static bool is_prime(const int number)
		{
			if (number == 2 || number == 3) {
				return true;
			}

			if (number == 1 || number % 2 == 0) {
				return false;
			}

			auto counter = 3;
			while (counter * counter <= number) {
				if (number % counter == 0) {
					return false;
				}

				counter++;
			}

			return true;
		}

		int next_prime(const int number) const
		{
			auto copy = number;
			if (copy % 2 == 0) {
				++copy;
			}

			while (!dictionary::is_prime(copy)) {
				copy += 2;
			}

			return copy;
		}

		void rehash()
		{
			auto old_data = this->data;

			this->data.resize(this->next_prime(old_data.size() * 2));
			for (auto& entry : this->data) {
				entry.status = k_empty;
			}

			this->my_size = 0U;
			for (auto& entry : old_data) {
				if (entry.status == k_active) {
					this->insert(entry.value);
				}
			}
		}
	};
}

#endif