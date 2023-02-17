#include <vector>
#include <map>
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
# include "red_black_tree_iterator.hpp"




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

ft::Red_black_tree<int, ft::pair <int, int> > create_rbt_A()
{
	ft::Red_black_tree<int, ft::pair <int, int> > rbt;
	rbt.insert_node(ft::make_pair(1,42));
	rbt.insert_node(ft::make_pair(2,43));
	rbt.insert_node(ft::make_pair(8,45));
	rbt.insert_node(ft::make_pair(4,46));
	rbt.insert_node(ft::make_pair(20,47));
	rbt.insert_node(ft::make_pair(-5,48));
	rbt.insert_node(ft::make_pair(-4,49));
	rbt.insert_node(ft::make_pair(-6,50));
	return (rbt);
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
	print_title_2("Insert et print");
	ft::Red_black_tree<int, ft::pair <int, int> > rbt1 = create_rbt_A();

	//rbt1.print();
	
	print_title_1("RBT iterator ");
	print_title_2("operator++ / --");
	ft::Red_black_tree<int, ft::pair <int, int> > rbt2 = create_rbt_A();

	rbt2.print();

	print_title_3("check operation ++ ");
	ft::Red_black_tree<int, ft::pair <int, int> >::iterator it_insert_print_A(rbt2.get_tree_head());
	//ft::Rbt_iterator<int, ft::Red_black_tree<int, ft::pair <int, int> >::Node<ft::pair <int, int> >* > it_insert_print_A(rbt2.get_tree_head());
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	++it_insert_print_A;
	it_insert_print_A++;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//++it_insert_print_A;
	it_insert_print_A++;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//++it_insert_print_A;
	it_insert_print_A++;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//++it_insert_print_A;
	it_insert_print_A++;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//++it_insert_print_A;
	//it_insert_print_A++;
	//std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.first << std::endl;
	//std::cout << "key/value begin: " << rbt2.tree_begin->value.first << "/" << rbt2.tree_begin->value.first << std::endl;
	
	print_title_3("check operation -- ");
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//--it_insert_print_A;
	it_insert_print_A--;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//--it_insert_print_A;
	it_insert_print_A--;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//--it_insert_print_A;
	it_insert_print_A--;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//--it_insert_print_A;
	it_insert_print_A--;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	//--it_insert_print_A;
	it_insert_print_A--;
	std::cout << "it key/value: " << it_insert_print_A.base()->value.first << "/" << it_insert_print_A.base()->value.second << std::endl;
	std::cout << "key/value begin: " << rbt2.tree_begin->value.first << "/" << rbt2.tree_begin->value.second << std::endl;
	
	
	print_title_2("check return");
	//rbt2.print();
	ft::Red_black_tree<int, ft::pair <int, int> >::iterator it_insert_print_C(rbt2.get_tree_head());
	std::cout << "-it key : " << (it_insert_print_A).base()->value.first << std::endl;
	std::cout << "it key: " << (it_insert_print_A++).base()->value.first << std::endl;
	std::cout << "it key: " << (it_insert_print_A++).base()->value.first << std::endl;
	std::cout << "it key: " << (++it_insert_print_A).base()->value.first << std::endl;
	std::cout << "-it key: " << (it_insert_print_A).base()->value.first << std::endl;
	std::cout << "it key: " << (it_insert_print_A--).base()->value.first << std::endl;
	std::cout << "-it key: " << (it_insert_print_A).base()->value.first << std::endl;
	std::cout << "it key: " << (--it_insert_print_A).base()->value.first << std::endl;
	//std::cout << "it found: " << (*it_insert_print_A).first << std::endl;
	
	print_title_2("find");
	ft::Red_black_tree<int, ft::pair <int, int> > rbt3 = create_rbt_A();
	rbt3.print();
	ft::Red_black_tree<int, ft::pair <int, int> >::iterator it_found;
	it_found = rbt3.find(-7);
	//std::cout << "it found: " << *it_found.base()->value.first << std::endl;


	// test creation iterator avec node_pointer (2e ligne ne marche pas ?)
	ft::Red_black_tree<int, ft::pair <int, int> >::iterator 	testA(rbt2.get_tree_head());
	ft::map<int, int>::iterator 								testB;
	ft::map<int, int>::iterator 								testC(rbt2.get_tree_head());




	//// test avec STD pour comparaison
	//std::map<int, int> mymap;
	//mymap.insert(std::make_pair(1, 42));
	//mymap.insert(std::make_pair(2, 43));
	//mymap.insert(std::make_pair(3, 44));
	//std::map<int, int>::iterator it = mymap.end();
	//it--;
	////it++;
	////it--;
	////it++;
	//std::cout << "check end std: " << (*it).second << std::endl;

	//std::cout << "check end std: " << it->first << " - " << it->second << std::endl;



	
	
	//// ##############################   Map   ###################################
	//// ------------------------------------------ Constructor destructor -------------------------------------------------------
	//print_title_1("Test compare");
	

	//print_title_2("Map - Constructor destructor");

	
}
