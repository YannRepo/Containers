#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

#include "vector.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
# include "lexicographical_compare.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"


// print title tool
# define COLOR_NORMAL  "\x1B[0m"
# define COLOR_RED  "\x1B[31m"
# define COLOR_GREEN  "\x1B[32m"
# define COLOR_YELLOW  "\x1B[33m"
# define COLOR_BLUE  "\x1B[34m"
# define COLOR_MAGENTA  "\x1B[35m"
# define COLOR_CYAN  "\x1B[36m"
# define COLOR_WHITE  "\x1B[37m"

# define DEBUG_WIDTH 50


void print_title_1(std::string str)
{
	int width = DEBUG_WIDTH;
	int fill = (DEBUG_WIDTH - 4 - str.length()) / 2;
	std::cout <<std::endl;
	std::cout << COLOR_GREEN;
	std::cout << std::setfill('#') << std::setw(width) << "" << std::endl;
	std::cout << std::setfill('#') << std::setw(fill) << "";
	std::cout << "  " + str + "  ";
	std::cout << std::setfill('#') << std::setw(fill) << "" << std::endl;
	std::cout << std::setfill('#') << std::setw(width) << "";
	std::cout << COLOR_NORMAL <<std::endl;
}

void print_title_2(std::string str)
{
	int fill = (DEBUG_WIDTH - 4 - str.length()) / 2;
	std::cout <<std::endl;
	std::cout << COLOR_MAGENTA;
	std::cout << std::setfill('*') << std::setw(fill) << "";
	std::cout << "  " + str + "  ";
	std::cout << std::setfill('*') << std::setw(fill) << "";
	std::cout << COLOR_NORMAL <<std::endl;
}

void print_title_3(std::string str)
{
	int fill = (DEBUG_WIDTH - 4 - str.length()) / 2;
	std::cout << COLOR_BLUE;
	std::cout << std::setfill('-') << std::setw(fill) << "";
	std::cout << "  " + str + "  ";
	std::cout << std::setfill('-') << std::setw(fill) << "";
	std::cout << COLOR_NORMAL <<std::endl;
}

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

template<typename T>
void print_size_capacity(ft::vector<T>& vector_to_print)
{
	std::cout << "size " << vector_to_print.size() << " - capacity " << vector_to_print.capacity() << std::endl;

}

// ###########################################################################################################
// #########################################   DEBUT MAIN   #######################################################
// ###########################################################################################################
int main()
{
	// ##############################   Vector   #################################3
	// ------------------------------------------ Constructor destructor -------------------------------------------------------
	print_title_1("VECTOR - Constructor destructor");
		// #### Constructor check ####
	print_title_2("Constructor");
	
	print_title_3("Range avec 2 int");
	// ft::vector<int> vec1(5, 22);
	ft::vector<int> vec1(5, 22);
	vec1.push_back(5);
	//vec1.pop_back();
	//vec1.reserve(50);
	print_myvector2<int>(vec1);

	print_title_3("Range avec iterateurs");
	ft::vector<int> vec_constr_range(2, 2);
	vec_constr_range.push_back(3);
	vec_constr_range.push_back(1);
	print_myvector2<int>(vec_constr_range);
	ft::vector<int> vec_constr_range_copy(vec_constr_range.begin(), vec_constr_range.end());
	print_myvector2<int>(vec_constr_range_copy);

	// ------------------------------------------ Iterators -------------------------------------------------------
	print_title_1("VECTOR - Iterators");
	// ------------------------------------------ Capacity -------------------------------------------------------
	print_title_1("VECTOR - Capacity");
	print_title_2("Resize");
	ft::vector<int> vec_capacity;
	vec_capacity.push_back(1);
	vec_capacity.push_back(2);
	print_size_capacity(vec_capacity);
	print_myvector2<int>(vec_capacity);
	vec_capacity.resize(8);
	print_size_capacity(vec_capacity);
	print_myvector2<int>(vec_capacity);
	vec_capacity.resize(1);
	print_size_capacity(vec_capacity);
	print_myvector2<int>(vec_capacity);



	// ------------------------------------------ Element access -------------------------------------------------------
	print_title_1("VECTOR - Element access");
	// ------------------------------------------ Modifiers -------------------------------------------------------
	print_title_1("VECTOR - Modifiers");

	print_title_2("Insert");
	// test insert position + val
	print_title_3("position + val");
	ft::vector<int> vec_insert_A(1, 1);
	vec_insert_A.push_back(3);
	vec_insert_A.push_back(5);
	vec_insert_A.push_back(7);
	//vec_insert_A.reserve(30);
	print_myvector2<int>(vec_insert_A);
	
	ft::vector<int>::iterator position = vec_insert_A.begin();
	vec_insert_A.insert(position, 2);
	print_myvector2<int>(vec_insert_A);

	position = vec_insert_A.end(); // necessaire car iterator HS si reallocation dans insert
	vec_insert_A.insert(position, 9);
	print_myvector2<int>(vec_insert_A);
	std::cout << "size " << vec_insert_A.size() << " - capacity " << vec_insert_A.capacity() << std::endl;


	// test insert iterator position + size + value
	print_title_3("Position + size + value");
	ft::vector<int> vec_insert_B(1, 1);
	vec_insert_B.push_back(3);
	vec_insert_B.push_back(5);
	vec_insert_B.push_back(7);
	print_myvector2<int>(vec_insert_B);
	ft::vector<int>::iterator position3 = vec_insert_B.begin();
	//ft::vector<int>::iterator position3 = vec_insert_B.begin() + 1; // autres tests possibles
	//ft::vector<int>::iterator position3 = vec_insert_B.end(); // autres tests possibles
	vec_insert_B.insert(position3, 3, 11);
	print_myvector2<int>(vec_insert_B);
	std::cout << "size " << vec_insert_B.size() << " - capacity " << vec_insert_B.capacity() << std::endl;


	// test insert iterator begin + iterator end
	print_title_3("Iterator begin + iterator end");
	ft::vector<int> vec_insert_C(1, 1);
	vec_insert_C.push_back(3);
	vec_insert_C.push_back(5);
	vec_insert_C.push_back(7);
	ft::vector<int> vec_insert_D(1, 11);
	vec_insert_D.push_back(13);
	vec_insert_D.push_back(14);
	vec_insert_D.push_back(15);
	vec_insert_D.push_back(16);
	vec_insert_D.push_back(17);
	vec_insert_D.push_back(18);
	vec_insert_D.push_back(19);

	print_myvector2<int>(vec_insert_C);
	print_myvector2<int>(vec_insert_D);
	
	ft::vector<int>::iterator position2 = vec_insert_C.begin();
	//ft::vector<int>::iterator position2 = vec_insert_C.begin() + 1; // autres tests possibles
	//ft::vector<int>::iterator position2 = vec_insert_C.end(); // autres tests possibles
	vec_insert_C.insert(position2, vec_insert_D.begin(), vec_insert_D.begin() + 5);
	print_myvector2<int>(vec_insert_C);
	print_myvector2<int>(vec_insert_D);
	std::cout << "size " << vec_insert_C.size() << " - capacity " << vec_insert_C.capacity() << std::endl;

	// test assign Assign
	print_title_2("Assign");

	// test assign A
	print_title_3("Range avec 2 int");
	ft::vector<int> vec_assign_A(3, 22);
	vec_assign_A.assign(4, 3);
	print_myvector2<int>(vec_assign_A);

	// test assign B
	print_title_3("Range avec iterateurs");
	ft::vector<int> vec_assign_B(2, 1);
	vec_assign_B.assign(vec_assign_A.begin(), vec_assign_A.end());
	print_myvector2<int>(vec_assign_B);

	// test Erase
	print_title_2("Erase");

	// test Erase position
	print_title_3("Position");
	ft::vector<int> vec_erase_A(1, 1);
	vec_erase_A.push_back(3);
	vec_erase_A.push_back(5);
	vec_erase_A.push_back(7);
	print_myvector2<int>(vec_erase_A);
	//ft::vector<int>::iterator returned = vec_erase_A.erase(vec_erase_A.begin());
	//ft::vector<int>::iterator returned = vec_erase_A.erase(vec_erase_A.end() - 1); // autres tests
	ft::vector<int>::iterator returned = vec_erase_A.erase(vec_erase_A.begin() + 1); // autres tests
	print_myvector2<int>(vec_erase_A);
	std::cout << "return =  " << *(returned) << std::endl;

	// test Erase it first, it last
	print_title_3("it first, it last");
	ft::vector<int> vec_erase_B(1, 1);
	vec_erase_B.push_back(2);
	vec_erase_B.push_back(3);
	vec_erase_B.push_back(4);
	vec_erase_B.push_back(5);
	vec_erase_B.push_back(6);
	vec_erase_B.push_back(7);
	vec_erase_B.push_back(8);
	ft::vector<int>::iterator first = vec_erase_B.begin() + 1;
	ft::vector<int>::iterator last = vec_erase_B.begin() + 3;
	//ft::vector<int>::iterator last = vec_erase_B.end(); // autres tests
	print_myvector2<int>(vec_erase_B);
	ft::vector<int>::iterator returned_B = vec_erase_B.erase(first, last);
	print_myvector2<int>(vec_erase_B);
	std::cout << "return =  " << *(returned_B) << std::endl;
	

	// ##############################   Iterator   #################################3
	print_title_1("ITERATOR");	
	//const iterator
	print_title_2("Const iterator");	
	ft::vector<int> vec2(5, 22);
	ft::vector<int>::const_iterator it = vec2.begin();
	//*it = 4; // decommenter cette ligne doit generer une erreur comme pour la std ci-dessous

	std::vector<int> vec3(5, 22);
	//std::vector<int>::const_iterator it2 = vec3.begin();
	//*it2 = 4; 


	// operator+
	print_title_2("operator+");	
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

	// ##############################   Reverse Iterator   #################################
	print_title_1("REVERSE ITERATOR");
	print_title_2("rbegin, rend");	
	ft::vector<int> vec_reverse_iterator_operator_A(1, 3);
	vec_reverse_iterator_operator_A.push_back(5);
	vec_reverse_iterator_operator_A.push_back(6);
	vec_reverse_iterator_operator_A.push_back(9);
	print_myvector2<int>(vec_reverse_iterator_operator_A);
	ft::vector<int>::reverse_iterator rev_iterator_vec_iterator_operator_plus = vec_reverse_iterator_operator_A.rbegin();
	std::cout << *rev_iterator_vec_iterator_operator_plus << std::endl;
	rev_iterator_vec_iterator_operator_plus++;
	std::cout << *rev_iterator_vec_iterator_operator_plus << std::endl;
	ft::vector<int>::reverse_iterator rev_iterator_vec_iterator_operator_plus_B = vec_reverse_iterator_operator_A.rend(); // autre test
	//std::cout << *rev_iterator_vec_iterator_operator_plus_B << std::endl; // cause invalid read mais ok
	rev_iterator_vec_iterator_operator_plus_B--;
	std::cout << *rev_iterator_vec_iterator_operator_plus_B << std::endl;

	print_title_2("access []");	
	ft::vector<int> vec_reverse_iterator_operator_C(1, 3);
	vec_reverse_iterator_operator_C.push_back(5);
	vec_reverse_iterator_operator_C.push_back(6);
	vec_reverse_iterator_operator_C.push_back(9);
	ft::vector<int>::reverse_iterator rev_iterator_vec_iterator_access = vec_reverse_iterator_operator_C.rbegin(); // autre test
	print_myvector2<int>(vec_reverse_iterator_operator_C);
	rev_iterator_vec_iterator_access++;
	//std::cout << *rev_iterator_vec_iterator_access << std::endl;
	std::cout << rev_iterator_vec_iterator_access[0] << std::endl;
	std::cout << rev_iterator_vec_iterator_access[1] << std::endl;
	std::cout << rev_iterator_vec_iterator_access[2] << std::endl;
	rev_iterator_vec_iterator_access++;
	std::cout << rev_iterator_vec_iterator_access[-1] << std::endl;
	}
