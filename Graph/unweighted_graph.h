#ifndef UNWEIGHTED_GRAPH
#define UNWEIGHTED_GRAPH

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

namespace nwacc {
	
	class unweighted_graph {
	private:
		struct vertex
		{
			char label;

			bool was_visited;
			
			vertex(char new_label, bool is_visited) : label{ new_label },
				was_visited{ is_visited } {}
		
			vertex() : label{ 0 }, was_visited{ false } {}
		};

		vertex* vertices;
		size_t number_of_vertices;

		int** matrix; 
	public:
		unweighted_graph(const size_t size)
		{
			this->number_of_vertices = size;

			this->matrix = new int* [this->number_of_vertices];
			for (auto index = 0U; 
				index < this->number_of_vertices;
				index++) 
			{
				this->matrix[index] = new int[this->number_of_vertices];
				for (auto inner_index = 0U; 
					inner_index < this->number_of_vertices;
					inner_index++) {
					this->matrix[index][inner_index] = 0;
				}
			}

			this->vertices = new vertex[this->number_of_vertices];
		}

		~unweighted_graph()
		{
			for (auto index = 0U; index < this->number_of_vertices; index++) {
				delete[] this->matrix[index];
			}

			delete[] this->matrix;
			delete[] this->vertices;
		}

		void add_vertex(const char label, const int index)
		{
			this->vertices[index].label = label;
			this->vertices[index].was_visited = false;
		}

		void add_edge(const int start, const int end)
		{
			this->matrix[start][end] = 1;
			this->matrix[end][start] = 1;
		}

		std::string print(std::ostream& out = std::cout) const
		{
			for (auto row = 0U; row < this->number_of_vertices; row++) {
				for (auto column = 0U; column < this->number_of_vertices; column++) {
					out << this->matrix[row][column] << ' ';
				}
				
				out << std::endl;
			}
			std::stringstream ss;
			ss << out.rdbuf();
			std::string returnString = ss.str();
			return returnString;
		}

		// DFS - Greedy algorithm.
		// The DFS has three steps -
		// Step 1 - "visit" some adjacent unvisited vertex. Mark it as visited.
		// Step 2 - If no adjacent vertex is found, pop up a vertex until we find one
		// Step 3 - Repeat Step 1 adn 2 until all vertices have been visited.

		int get_adjacent_unvisited_vertex(int index)
		{
			for (auto counter = 0U; counter < this->number_of_vertices;
				counter++) {
				if (this->matrix[index][counter] == 1 && 
					!this->vertices[counter].was_visited) {
					return counter;
				} // else, either the vertex was visited or is not connected. 
			}

			// Here, I have found one of two things - no adjacent vertices.
			// OR, I have adjacent vertices but they have been visited.
			return -1;
		}

		std::string bfs(std::ostream& out = std::cout)
		{
			std::queue<int> queue;
			// We can start at "A" which is the "start" of the graph.
			this->vertices[0].was_visited = true;
			queue.push(0);
			out << this->vertices[0].label << ' ';
			while (!queue.empty()) {
				// front DOES NOT remove the item from the queue, it just
				// reads the item. 
				auto current = queue.front();
				queue.pop(); // This will remove the value.
				auto next_index = this->get_adjacent_unvisited_vertex(current);
				while (next_index >= 0) {
					this->vertices[next_index].was_visited = true;
					out << this->vertices[next_index].label << ' ';
					queue.push(next_index);
					next_index = this->get_adjacent_unvisited_vertex(current);
				}
			}
			std::stringstream ss;
			ss << out.rdbuf();
			std::string returnString = ss.str();
			return returnString;
		}

		void dfs(std::vector<char>& result)
		{
			result.clear();
			std::stack<int> stack;
			// I am going to start at 0 (the first vertex in my array). 
			stack.push(0);
			this->vertices[0].was_visited = true;
			//auto result_index = 0U;
			result.push_back(this->vertices[0].label);
			//result[result_index++] = this->vertices[0].label;
			while (!stack.empty()) {
				auto next = this->get_adjacent_unvisited_vertex(stack.top());
				if (next < 0) {
					// I could not find any unvisited adjacent vertices.
					// I am done with this vertex, I can remove it.
					stack.pop();
				} else {
					// Here I found something, some new vertex which is
					// adjacent and unvisited!
					this->vertices[next].was_visited = true;
					result.push_back(this->vertices[next].label);
					stack.push(next);
				}
			}
		}
		
	};
}

#endif