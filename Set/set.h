#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>

namespace nwacc {
	template <typename T>
	class set {
	private:
		struct node {
			T data;
			node* left;
			node* right;
			node* parent;

			node(const T& the_data, node* left_node, node* right_node, node* parent_node)
				: data{ the_data }, left{ left_node }, right{ right_node }, parent{ parent_node } {}

			node(const T&& the_data, node* left_node, node* right_node, node* parent_node)
				: data{ std::move(the_data) }, left{ left_node }, right{ right_node }, parent{ parent_node } {}
		};

		node* root;

		node* find_min(node* position) const
		{
			if (position == nullptr) {
				return nullptr;
			} // else, we are not nullptr, do_nothing();

			if (position->left == nullptr) {
				// What does this mean? I am at the smallest value!
				return position;
			} // else, not the min, do_nothing();

			return this->find_min(position->left);
		}

		node* insert(const T& value, node*& position, node* par)
		{
			if (position == nullptr) {
				position = new node{ value, nullptr, nullptr, par };
				return position;
			}
			else if (value < position->data) {
				return this->insert(value, position->left, position);
			}
			else if (position->data < value) {
				return this->insert(value, position->right, position);
			}
			else {
				return nullptr;
			}
		}

		void print(node* position, std::ostream& out) const
		{
			if (position != nullptr) {
				this->print(position->left, out);
				out << position->data << " ";
				this->print(position->right, out);
			} // else, I am done with this node, do_nothing();
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
				if (current == nullptr)
				{
					// Get the root of the tree
					current = set->root;

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

            T& retrieve() const
            {
                // Get value by de-referencing current
                return this->current->data;
            }

            const_iterator(node* position) : current{ position } {}

            friend class set<T>;
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

		set() : root{ nullptr } { }

		set(const set& rhs) : root{ nullptr }
		{
			this->root = this->copy(rhs.root);
		}

		set(set&& rhs) : root{ rhs.root } { rhs.root = nullptr; }

		void insert(const T& value)
		{
			this->insert(value, this->root, nullptr);
		}

		void clear()
		{
			this->clear(this->root);
		}

		bool is_empty() const
		{
			return this->root == nullptr;
		}

		~set()
		{
			this->clear();
		}

		void display(std::ostream& out = std::cout) const
		{
			if (is_empty()) 
			{
				out << "Empty tree" << std::endl;
			}
			else 
			{
				this->print(this->root, out);
			}
		}
	};
}

#endif
