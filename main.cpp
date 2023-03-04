#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <time.h>


#include <vector>
#include <map>
#include <stack>
#include <set>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

// ###########################################################################################################
// #########################################   TOOLS   #######################################################
// ###########################################################################################################
// Colors
# define COLOR_NORMAL  "\x1B[0m"
# define COLOR_RED  "\x1B[31m"
# define COLOR_GREEN  "\x1B[32m"
# define COLOR_YELLOW  "\x1B[33m"
# define COLOR_BLUE  "\x1B[34m"
# define COLOR_MAGENTA  "\x1B[35m"
# define COLOR_CYAN  "\x1B[36m"
# define COLOR_WHITE  "\x1B[37m"

# define DEBUG_WIDTH 50
# if 0
#  define TESTED_NAMESPACE ft
#  define TESTED_NAMESPACE_STR "ft"
# else 
#  define TESTED_NAMESPACE std
#  define TESTED_NAMESPACE_STR "std"
# endif

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


template<typename T>
void print_vector(TESTED_NAMESPACE::vector<T> vec)
{
	std::cout << "[";
	for (typename TESTED_NAMESPACE::vector<T>::iterator it=vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it;
		if(it + 1 != vec.end())
			std::cout << ", ";


	}
	std::cout << "]" << std::endl;
}

// ###########################################################################################################
// #########################################   TESTS   #######################################################
// ###########################################################################################################
// -----------------------------------------------------------------------------------------------------------
// --------------------------------------------- Vector ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
void vector_tests(int nb_of_tests)
{
	print_title_1("Vector");

	// time test at the end
	clock_t vector_time;
	vector_time = clock();

	for(int i = 0; i < nb_of_tests; i++)
	{
		print_title_1("Vector");
		print_title_2("Functions verifications");
		print_title_3("Iterators");
		TESTED_NAMESPACE::vector<int> vector_1;
		vector_1.push_back(1);
		vector_1.push_back(2);
		vector_1.push_back(3);
		std::cout << "begin:" << *(vector_1.begin()) << std::endl;
		std::cout << "end:" << *(--vector_1.end()) << std::endl; //-- car end non alloué
		std::cout << "rbegin:" << *(vector_1.rbegin()) << std::endl;
		std::cout << "rend:" << *(--vector_1.rend()) << std::endl;//-- car rend non alloué

		print_title_3("Capacity");
		std::cout << "size:" << vector_1.size() << std::endl;
		std::cout << "max size:" << vector_1.max_size() << std::endl;
		std::cout << "capacity:" << vector_1.capacity() << std::endl;
		std::cout << "empty:" << vector_1.empty() << std::endl;
		vector_1.reserve(20);

		print_title_3("Element access");
		std::cout << "operator[]: " << vector_1[1] << std::endl;
		std::cout << "at: " << vector_1.at(1) << std::endl;
		std::cout << "front: " << vector_1.front() << std::endl;
		std::cout << "back: " << vector_1.back() << std::endl;
		std::cout << "data: " << *(vector_1.data()) << std::endl;

		print_title_3("Modifiers");
		TESTED_NAMESPACE::vector<int> vector_2;
		vector_2.assign(vector_1.begin(), vector_1.end());
		TESTED_NAMESPACE::vector<int> vector_3;
		vector_3.assign(5, 3);
		print_vector(vector_3);
		vector_2.push_back(42);
		print_vector(vector_2);
		vector_2.push_back(41);
		print_vector(vector_2);
		vector_2.pop_back();
		print_vector(vector_2);


		TESTED_NAMESPACE::vector<int> vector_4(vector_1);
		vector_4.insert(++vector_4.begin(), vector_1.begin(), vector_1.end());
		std::cout << "insert: " <<    *(vector_4.erase(vector_4.begin()))      << std::endl;
		print_vector(vector_1);
		print_vector(vector_4);
		vector_1.swap(vector_4);
		print_vector(vector_1);
		print_vector(vector_4);

		// en cours
		
		//TESTED_NAMESPACE::vector<int> vector_4(vector_4);
		//print_vector(vector_4);
		//vector_4.clear();
		//print_vector(vector_4);

		std::cout << "find" << vector_1.at(1) << std::endl;



		print_title_2("Iterators verifications");
		TESTED_NAMESPACE::vector<int>::iterator it1 = vector_1.begin();
		TESTED_NAMESPACE::vector<int>::const_iterator it2 = ++vector_1.begin();
		std::cout << "it1 > it2? : " << (it1 > it2) << std::endl;
		std::cout << "it1 < it2? : " << (it1 < it2) << std::endl;

		print_title_2("Swap non member verifications");
		TESTED_NAMESPACE::vector<int>::iterator it3 = ++(++(vector_4.begin()));
		TESTED_NAMESPACE::swap(vector_1, vector_4);
		print_vector(vector_1);
		print_vector(vector_4);
		std::cout << "it1: " << *it1 << std::endl;
		std::cout << "it2: " << *it3 << std::endl;
	}

	print_title_2("Time test");
	vector_time = clock() - vector_time;
	double vector_time_time_ms = ((double)vector_time)/CLOCKS_PER_SEC*1000;
	std::cout << "Vector execution time for " << TESTED_NAMESPACE_STR << " = " << vector_time_time_ms << "ms \n" << std::endl;
}


// ###########################################################################################################
// #########################################   MAIN   ########################################################
// ###########################################################################################################
int main()
{
	vector_tests(1);
}


