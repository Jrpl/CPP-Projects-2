#ifndef TEST_H
#define TEST_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace nwacc {
	template<typename K, typename V>
	class dictionary {
	public:
		void hash(int b)
		{
			data = new std::vector<entry>[b];
		}

		bool put(const K& key, const V& value)
		{
			int index = hash_function(key);
			data[index].push_back(new entry(key, value));
		}

		int hash_function(int value) 
		{
			return (value % BUCKET);
		}

		void print()
		{
			for (int i = 0; i < BUCKET; i++) 
			{
				std::cout << "Index " << i;
				for (auto element : data[i])
				{
					std::cout << element.key << element.value;
				}
				std::cout << std::endl;
			}
		}

	private:
		struct entry
		{
			K key;
			V value;

			entry(const K& new_key = K{},
				const V& new_value = V{}) :
				key{ new_key }, value{ new_value }

			entry(K&& new_key,
				V&& new_value) :
				key{ std::move(new_key) }, value{ std::move(new_value) }
		};

		std::vector<entry> data;
	};
}

#endif