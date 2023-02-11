#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

# include "../10_Tools/reverse_iterator.hpp"
# include "../10_Tools/iterator_traits.hpp"
# include "../10_Tools/lexicographical_compare.hpp"
# include "../10_Tools/is_integral.hpp"
# include "../10_Tools/enable_if.hpp"

# include "map.hpp"
# include "pair.hpp"
# include "red_black_tree.hpp"




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
	int width = DEBUG_WIDTH;
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
	int width = DEBUG_WIDTH;
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
	// ##############################   Pair / make pair  ###################################
	print_title_1("Pair / make pair ");
	std::string str_A = "Hello";
	float float_A = 1.5;
	ft::pair<std::string, float> pair_A(str_A, float_A);
	std::cout << "pair_A : first = " << pair_A.first << " - second = " << pair_A.second << std::endl;
	ft::pair<float, std::string> pair_B = ft::make_pair(float_A, str_A);
	//auto pair_B = ft::make_pair(float_A, str_A); // version simplifiee;
	std::cout << "pair_B : first = " << pair_B.first << " - second = " << pair_B.second << std::endl;


	// ##############################   RBT  ##################################
	print_title_1("RBT");
	// --------------------- Constructor destructor -------------------------------------------------------
	print_title_2("Insert et print");
	ft::Red_black_tree<int, int> rbt1;
	rbt1.insert_node(rbt1.tree_head, ft::make_pair(1,42));
	rbt1.insert_node(rbt1.tree_head, ft::make_pair(2,43));

	rbt1.print();



	
	
	// ##############################   Map   ###################################
	// ------------------------------------------ Constructor destructor -------------------------------------------------------
	print_title_1("Test compare");
	

	print_title_2("Map - Constructor destructor");

	
}
