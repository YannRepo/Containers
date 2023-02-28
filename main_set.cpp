#include <set>
#include <iostream>
#include <string>
#include <iomanip>
# include <memory>


//# include "reverse_iterator.hpp"
//# include "iterator_traits.hpp"
//# include "lexicographical_compare.hpp"
//# include "is_integral.hpp"
//# include "enable_if.hpp"

//# include "vector.hpp"


# include "set.hpp"
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

# define NAMESPACE ft
//# define NAMESPACE std



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



// ###########################################################################################################
// #########################################   DEBUT MAIN   #######################################################
// ###########################################################################################################
int main()
{
	NAMESPACE::set<int> set1;
	set1.insert(set1.begin(), 3);
	set1.insert(set1.begin(), 2);
	set1.insert(set1.begin(), 1);
	std::cout << "set[0]: " << *set1.begin() << std::endl;
}
