#define CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include"List.h"
int main()
{
	IceCola::list<int> n;
	n.push_back(1);
	n.push_back(2);
	n.push_back(3);
	n.push_back(4);
	IceCola::list<int>::iterator it = n.begin();
	while (it != n.end())
	{
		std::cout << *it<<" ";
		++it;
	}
	n.erase(n.begin());
	std::cout << std::endl;
	for (auto e : n)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	n.insert(++n.begin(), 10);
	for (auto e : n)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	return 0;
}
