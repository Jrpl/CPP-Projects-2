#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>

namespace nwacc {

    template <typename K, typename V>
    class dictionary {
    public:

        dictionary() : root{ nullptr } {}

        dictionary(const dictionary& rhs) : root{ nullptr }
        {
            this->root = this->copy(rhs.root);
        }

        dictionary(dictionary&& rhs) : root{ rhs.root }
        {
            rhs.root = nullptr;
        }

        ~dictionary()
        {
            this->empty();
        }

        dictionary& operator=(const dictionary& rhs)
        {
            auto copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        dictionary& operator=(dictionary&& rhs)
        {
            std::swap(this->root, rhs.root);
            return *this;
        }

        bool is_empty() const
        {
            return this->root == nullptr;
        }

        void empty()
        {
            this->clear(this->root);
        }

        // Return true if the map contains the key, otherwise false
        bool contains_key(const K& key) const
        {
            if (this->find_key(key, this->root))
            {
                std::cout << "true" << std::endl;
                return this->find_key(key, this->root);
            }

            std::cout << "false" << std::endl;
            return this->find_key(key, this->root);
        }

        // Return true if the map contains the value, otherwise false
        bool contains_value(const V& value) const
        {
            if (this->find_value(value, this->root))
            {
                std::cout << "true" << std::endl;
                return this->find_value(value, this->root);
            }

            std::cout << "false" << std::endl;
            return this->find_value(value, this->root);
        }

        const V& find_min() const
        {
            if (this->is_empty()) {
                throw new std::range_error("Tree is empty");
            }
            else {
                return this->find_min(this->root)->value;
            }
        }

        const V& find_max() const
        {
            if (this->is_empty()) {
                throw new std::range_error("Tree is empty");
            }
            else {
                return this->find_max(this->root)->value;
            }
        }

        void put(const K& key, const V& value)
        {
            this->put(key, value, this->root, nullptr);
        }

        void put(K&& key, V&& value)
        {
            this->put(std::move(key), std::move(value), this->root, nullptr);
        }

        void get(const K& key, std::ostream& out = std::cout) const
        {
            V value = this->get(key);
            out << value << std::endl;
        }

        void remove(const K& key)
        {
            this->remove(key, this->root);
        }

        void remove_value(const V& value)
        {
            this->remove_value(value, this->root);
        }

        void print(std::ostream& out = std::cout) const
        {
            if (this->is_empty()) {
                out << "Empty tree" << std::endl;
            }
            else {
                this->print(this->root, out);
            }
        }

    private:
        struct node {
            K key;
            V value;
            node* parent;
            node* left;
            node* right;
            int height;

            node(const K& the_key,
                const V& the_value,
                node* the_parent,
                node* left_node,
                node* right_node,
                int node_height = 0)
                : key{ the_key },
                value{ the_value },
                parent{ the_parent },
                left{ left_node },
                right{ right_node },
                height{ node_height } {}

            node(const K&& the_key,
                const V&& the_value,
                node* the_parent,
                node* left_node,
                node* right_node,
                int node_height = 0)
                : key{ std::move(the_key) },
                value{ std::move(the_value) },
                parent{ the_parent },
                left{ left_node },
                right{ right_node },
                height{ node_height } {}
        };

        node* root;

        // We need four rotate methods (left, right, left->right, right->left)
        // These methods will rotate nodes AND change the height.
        // nullptr has a height of -1
        // Parent height is what : height of the largest child + 1
        // First we start with a simple height method to get the height of any node
        // including nullptr.
        int height(node* position) const
        {
            return position == nullptr ? -1 : position->height;
        }

        // rotate left
        void rotate_with_right_child(node*& current)
        {
            auto* temp = current->right;
            current->right = temp->left;
            temp->left = current;

            current->height = std::max(
                this->height(current->left),
                this->height(current->right)) + 1;

            temp->height = std::max(
                this->height(temp->left),
                current->height) + 1;
            current = temp;
        }

        // rotate right
        void rotate_with_left_child(node*& current)
        {
            auto* temp = current->left;
            current->left = temp->right;
            temp->right = current;

            current->height = std::max(
                this->height(current->left),
                this->height(current->right)) + 1;

            temp->height = std::max(
                this->height(temp->left),
                current->height) + 1;
            current = temp;
        }

        // double rotate - first rotate the left child with its right child
        // then with the new left child. 
        void double_rotate_with_left_child(node*& current)
        {
            this->rotate_with_right_child(current->left);
            this->rotate_with_left_child(current);
        }

        void double_rotate_with_right_child(node*& current)
        {
            this->rotate_with_left_child(current->right);
            this->rotate_with_right_child(current);
        }

        node* find_min(node* position) const
        {
            if (position == nullptr) {
                return nullptr;
            } // else, we are not nullptr, do_nothing();

            if (position->left == nullptr) {
                return position;
            } // else, not the min, do_nothing();

            return this->find_min(position->left);
        }

        node* find_max(node* position) const
        {
            if (position != nullptr) {
                while (position->right != nullptr) {
                    position = position->right;
                }
            }
            return position;
        }

        // Pass a key and remove the node associated with the key
        void remove(const K& key, node*& position)
        {
            if (position == nullptr) {
                return; // this means the key was not found. 
            } // else, we are not null, do_nothing();

            if (key < position->key) {
                this->remove(key, position->left);
            }
            else if (position->key < key) {
                this->remove(key, position->right);
            }
            else if (position->left != nullptr &&
                position->right != nullptr) {
                position->key = this->find_min(position->right)->key;
                this->remove(position->key, position->right);
            }
            else {
                auto* old_node = position;
                position = (position->left != nullptr) ?
                    position->left :
                    position->right;
                delete old_node;
            }

            this->rebalance(position);
        }

        // Pass a value and remove each node associated with the value
        void remove_value(const V& value, node*& position)
        {
            if (position == nullptr) {
                return; // this means the key was not found. 
            } // else, we are not null, do_nothing();

            if (value < position->value) {
                this->remove(value, position->left);
            }
            else if (position->value < value) {
                this->remove(value, position->right);
            }
            else if (position->left != nullptr &&
                position->right != nullptr) {
                position->value = this->find_min(position->right)->value;
                this->remove(position->value, position->right);
            }
            else {
                auto* old_node = position;
                position = (position->left != nullptr) ?
                    position->left :
                    position->right;
                delete old_node;
            }

            this->rebalance(position);
        }

        // Pass a key and a value, insert them into the map
        // If the key already exists, replace the value at that key
        void put(const K& key, const V& value, node*& position, node* parent)
        {
            if (position == nullptr) {
                position = new node{ key, value, parent, nullptr, nullptr};
            }
            else if (key < position->key) {
                this->put(key, value, position->left, position);
            }
            else if (position->key < key) {
                this->put(key, value, position->right, position);
            } 
            else {
                position->value = value;
            }

            this->rebalance(position);
        }

        void put(const K&& key, const V&& value, node*& position, node* parent)
        {
            if (position == nullptr) {
                position = new node{ std::move(key), std::move(value), parent, nullptr, nullptr};
            }
            else if (key < position->key) {
                this->put(std::move(key), std::move(value), position->left, position);
            }
            else if (position->key < key) {
                this->put(std::move(key), std::move(value), position->right, position);
            }
            else {
                position->value = std::move(value);
            }

            this->rebalance(position);
        }

        // Pass a key, return the value associated with the key
        // If the key does not exist, throw out of range error
        V* get(K& key, node* position) const 
        {
            while (position != nullptr) {
                if (key < position->key) {
                    position = position->left;
                }
                else if (position->key < key) {
                    position = position->right;
                }
                else {
                    return position->value;
                }
            }

            throw std::out_of_range("Key does not exist");
        }

        bool find_key(const K& key, node* position) const
        {
            while (position != nullptr) {
                if (key < position->key) {
                    position = position->left;
                }
                else if (position->key < key) {
                    position = position->right;
                }
                else {
                    return true;
                }
            }

            return false;
        }

        bool find_value(const V& value, node* position) const
        {
            while (position != nullptr) {
                if (value < position->value) {
                    position = position->left;
                }
                else if (position->value < value) {
                    position = position->right;
                }
                else {
                    return true;
                }
            }

            return false;
        }

        void print(node* position, std::ostream& out) const
        {
            if (position != nullptr) {
                this->print(position->left, out);
                out << "(" << position->key << ", " << position->value << ")";
                this->print(position->right, out);
            } // else, I am done with this node, do_nothing();
        }

        void rebalance(node*& current)
        {
            if (current == nullptr) {
                return;
            } // else, I have a valid node, do_nothing();

            if (this->height(current->left) -
                this->height(current->right) > 1) {
                // left side of the tree is larger.
                // Here we have two cases - single rotation (rotate right - rotate
                // with left children).
                // or a double rotation. If it is not the first case, then it
                // MUST BE the second case. I do not need to test for both cases.

                if (this->height(current->left->left) >=
                    this->height(current->left->right)) {
                    this->rotate_with_left_child(current);
                }
                else {
                    // here I have a double rotation.
                    this->double_rotate_with_left_child(current);
                }
            }
            else if (this->height(current->right) -
                this->height(current->left) > 1) {
                // right side of the tree is larger.
                if (this->height(current->right->right) >=
                    this->height(current->right->left)) {
                    this->rotate_with_right_child(current);
                }
                else {
                    // here I have a double rotation.
                    this->double_rotate_with_right_child(current);
                }

            } // else, the tree is balanced within 1, do_nothing();

            // I did no rotations (maybe). I need to update the heights.
            current->height = std::max(
                this->height(current->left),
                this->height(current->right)) + 1;
        }

        void clear(node*& position)
        {
            if (position != nullptr) {
                this->clear(position->left);
                this->clear(position->right);
                delete position;
            } // else, we have hit an end, do_nothing();

            position = nullptr;
        }

        node* copy(node* position) const
        {
            return position == nullptr ?
                nullptr :
                new node{ position->key,
                          position->value,
                          this->copy(position->left),
                          this->copy(position->right),
                          position->height };
        }

    public:
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
				if (current == nullptr)
				{
					// Get the root of the tree
					current = dictionary->root;

					//  Find the smallest value in the tree
					while (current->left != nullptr) {
						current = current->left;
					}
				}
				else if (current->right != nullptr)
				{
					// Find furthest left node in right subtree
					current = current->right;

					while (current->left != nullptr) {
						current = current->left;
					}
				}
				else
				{
					// Left and right subtree processed, find parent where current is the left child
					node* par = current->parent;
					while (par != nullptr && current == par->right)
					{
						current = par;
						par = par->parent;
					}

					current = par;
				}

				return *this;
			}

			// ++ Post Iterator
			const_iterator& operator++(int)
			{
				auto old = *this;
				++(*this);
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

            V& retrieve() const
            {
                // Get value by de-referencing current
                return this->current->value;
            }

            const_iterator(node* position) : current{ position } {}

            friend class dictionary<K, V>;
        };

		// Return iterator of the first item in the tree
        const_iterator begin() const
        {
            return const_iterator(find_min(root), this);
        }

		// Return iterator past the end of the tree
		const_iterator end() const
		{
			return const_iterator(nullptr, this);
		}
    };
}

#endif