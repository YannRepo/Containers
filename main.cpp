#include "vector.hpp"

int main()
{
	ft::vector<int>::iterator it;
	int* tab = new int[4];
	tab[0] = 0;
	tab[1] = 11;
	tab[2] = 22;
	tab[3] = 33;
	it._pointer = tab;
	it._size = 3;
	std::cout << *it._pointer << std::endl;
	// it.advance(it, 2);
	std::cout << *it._pointer << std::endl;
	std::cout << *it.begin()._pointer << std::endl;
	std::cout << *it.end()._pointer << std::endl;





}
