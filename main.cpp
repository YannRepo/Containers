#include <vector>
#include "vector.hpp"

// fct debug
template<typename T>
void print_myvector1(ft::vector<T>& vector_to_print, size_t tmp_nb_value)
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
template<typename T>
void print_myvector2(ft::vector<T>& vector_to_print)
{
	int tmp;

	std::cout << "[";
	ft::vector<int>::iterator it;
	for(it = vector_to_print.begin(); it != vector_to_print.end(); it++)
	{
		tmp = *it;
		std::cout << tmp << ", ";
	}
	std::cout << "]" << std::endl;

}

int main()
{
	ft::vector<int> vec2(5, 22);
	ft::vector<int>::const_iterator it = vec2.begin();
	it = vec2.begin();
	*it = 4;
	//std::cout << (*it) << std::endl;
	//it = vec2.begin();
	std::vector<int> vec3(5, 22);

	std::vector<int>::const_iterator it2;
	// = vec3.begin();
	it2 = vec3.begin();
	*it2 = 4;

	//ft::vector<int>::ft::vector_iterator<int> it;
	//ft::vector_iterator<int> it;
	
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

	std::cout << "###########  VECTOR  ##########" << std::endl;
	// #### Constructor check ####
	// ft::vector<int> vec1(5, 22);
	ft::vector<int> vec1(5, 22);
	vec1.push_back(5);
	//vec1.pop_back();
	//vec1.reserve(50);
	print_myvector2<int>(vec1);

	// test assign A
	ft::vector<int> vec_assign_A(3, 22);
	vec_assign_A.assign(4, 3);
	print_myvector2<int>(vec_assign_A);

	// test assign B
	ft::vector<int> vec_assign_B(2, 1);
	vec_assign_B.assign(vec_assign_A.begin(), vec_assign_A.end());
	print_myvector2<int>(vec_assign_B);

	// ##############################   Iterator   #################################3
	std::cout << "###########  ITERATOR  ###########" << std::endl;
	
	// operator+
	std::cout << "Operator+" << std::endl;
	ft::vector<int> vec_iterator_operator_plus(1, 12);
	vec_iterator_operator_plus.push_back(5);
	vec_iterator_operator_plus.push_back(6);
	vec_iterator_operator_plus.push_back(9);
	print_myvector2<int>(vec_iterator_operator_plus);
	ft::vector<int>::iterator iterator_vec_iterator_operator_plus;
	iterator_vec_iterator_operator_plus = vec_iterator_operator_plus.begin();
	iterator_vec_iterator_operator_plus = iterator_vec_iterator_operator_plus + 1;
	iterator_vec_iterator_operator_plus = iterator_vec_iterator_operator_plus + 1;
	std::cout << *iterator_vec_iterator_operator_plus << std::endl;
	iterator_vec_iterator_operator_plus = iterator_vec_iterator_operator_plus - 1;
	std::cout << *iterator_vec_iterator_operator_plus << std::endl;

	//std::cout << *(iterator_vec_iterator_operator_plus + 1) << std::endl;


	// begin / end -> return un iterator ? = un pointeur ?

	}
