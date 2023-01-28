#include <vector>
#include "vector.hpp"

// fct debug
template<typename T>
void print_myvector(ft::vector<T>& vector_to_print, size_t tmp_nb_value)
{
	std::cout << "[";
	for(size_t i = 0; i < tmp_nb_value; i++)
	{
		if (i != tmp_nb_value - 1)
			std::cout << vector_to_print[i] << ", ";
		else
			std::cout << vector_to_print[i];
	}
	std::cout << "]" << std::endl;
}


int main()
{
	// ft::vector<int>::iterator it;
	// int* tab = new int[4];
	// tab[0] = 0;
	// tab[1] = 11;
	// tab[2] = 22;
	// tab[3] = 33;
	// it._pointer = tab;
	// it._size = 3;
	// std::cout << *it._pointer << std::endl;
	// // it.advance(it, 2);
	// std::cout << *it._pointer << std::endl;
	// std::cout << *it.begin()._pointer << std::endl;
	// std::cout << *it.end()._pointer << std::endl;


	// std::allocator<int> myAllocator;

	// int* arr = myAllocator.allocate(5);
	// arr[0] = 4;
	// std::cout << arr[0] << std::endl;

	// std::vector<int> vec_int;
	// vec_int.push_back(1);
	// vec_int.push_back(2);
	// std::cout << "vec:"  << *vec_int.end() << std::endl;

	// ft::vector<int> my_vec;
	// my_vec.push_back(2);
	// my_vec.push_back(3);
	// my_vec.push_back(4);
	// my_vec.push_back(5);
	// // my_vec._vector_pointer[1] = 22;
	// std::cout << "my_vec:"  << my_vec._vector_pointer[0] << std::endl;
	// std::cout << "my_vec:"  << my_vec._vector_pointer[1] << std::endl;
	// std::cout << "my_vec:"  << my_vec._vector_pointer[2] << std::endl;
	// std::cout << "my_vec:"  << my_vec._vector_pointer[3] << std::endl;
	// std::cout << "my_vec:"  << my_vec.pop_back() << std::endl;
	// std::cout << "my_vec:"  << my_vec._vector_pointer[3] << std::endl;


	// std::cout << "my_vec:"  << my_vec._vector_pointer[4] << std::endl;

	// #### Constructor check ####
	// ft::vector<int> vec1(5, 22);
	ft::vector<int> vec1(5, 22);
	vec1.push_back(5);
	//vec1.pop_back();
	//vec1.reserve(50);
	print_myvector<int>(vec1, vec1._vector_size);

	// begin / end -> return un iterator ? = un pointeur ?

	}
