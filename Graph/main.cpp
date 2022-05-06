#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "unweighted_graph.h"

int main() {
	std::vector<std::string> outputOne;
	std::vector<std::string> outputTwo;
	std::ifstream infileOne("C:\\Users\\Justin\\Desktop\\graph_one.txt");
	std::ifstream infileTwo("C:\\Users\\Justin\\Desktop\\graph_two.txt");
	std::string temp;
	while (std::getline(infileOne, temp)) {
		outputOne.push_back(temp);
	}
	while (std::getline(infileTwo, temp)) {
		outputTwo.push_back(temp);
	}

	nwacc::unweighted_graph graphOne(stoi(outputOne[0]));
	nwacc::unweighted_graph graphTwo(stoi(outputTwo[0]));

	for (int i = 0; i < stoi(outputOne[0]); i++)
	{
		graphOne.add_vertex(static_cast<char>(i), i);
	}

	for (int i = 0; i < stoi(outputTwo[0]); i++)
	{
		graphTwo.add_vertex(static_cast<char>(i), i);
	}

	for (int i = 1; i < stoi(outputOne[0]); i++)
	{
		int a = -1, b = -1, c = -1, d = -1, e = -1;

		std::stringstream ss(outputOne[i]);
		ss >> a >> b >> c >> d >> e;

		if (b != -1)
		{
			graphOne.add_edge(a, b);
		}
		if (c != -1)
		{
			graphOne.add_edge(a, c);
		}
		if (d != -1)
		{
			graphOne.add_edge(a, d);
		}
		if (e != -1)
		{
			graphOne.add_edge(a, e);
		}
	}

	for (int i = 1; i < stoi(outputTwo[0]); i++)
	{
		int a = -1, b = -1, c = -1, d = -1, e = -1;

		std::stringstream ss(outputTwo[i]);
		ss >> a >> b >> c >> d >> e;

		if (b != -1)
		{
			graphOne.add_edge(a, b);
		}
		if (c != -1)
		{
			graphOne.add_edge(a, c);
		}
		if (d != -1)
		{
			graphOne.add_edge(a, d);
		}
		if (e != -1)
		{
			graphOne.add_edge(a, e);
		}
	}

	std::vector<char> dfs_result_one;
	std::vector<char> dfs_result_two;

	graphOne.dfs(dfs_result_one);
	graphTwo.dfs(dfs_result_two);

	std::string dfs_result_one_str(dfs_result_one.begin(), dfs_result_one.end());
	std::string dfs_result_two_str(dfs_result_two.begin(), dfs_result_two.end());
	
	std::ofstream outfileOne;
	std::ofstream outfileTwo;

	outfileOne.open("C:\\Users\\Justin\\Desktop\\graph_one_result.txt");
	outfileOne << graphOne.print() << "\n";
	outfileOne << dfs_result_one_str << "\n";
	outfileOne << graphOne.bfs() << "\n";
	outfileOne.close();

	outfileTwo.open("C:\\Users\\Justin\\Desktop\\graph_two_result.txt");
	outfileTwo << graphTwo.print() << "\n";
	outfileTwo << dfs_result_two_str << "\n";
	outfileTwo << graphTwo.bfs() << "\n";
	outfileTwo.close();

	return 0;
}