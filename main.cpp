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

# ifndef TEST_CHOICE
#  define TEST_CHOICE 1
# endif

# if TEST_CHOICE
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

template<typename key, typename T>
void print_map(TESTED_NAMESPACE::map<key, T> map)
{
	std::cout << "[";
	for (typename TESTED_NAMESPACE::map<key, T>::iterator it=map.begin(); it != map.end();)
	{
		std::cout << (it->first);
		if(++it != map.end())
			std::cout << ", ";


	}
	std::cout << "]" << std::endl;
}

template<typename key>
void print_set(TESTED_NAMESPACE::set<key> set)
{
	std::cout << "[";
	for (typename TESTED_NAMESPACE::set<key>::const_iterator it=set.begin(); it != set.end();)
	{
		std::cout << (*it);
		if(++it != set.end())
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
		print_title_2("Functions verifications");
		print_title_2("Constructor");
		TESTED_NAMESPACE::vector<int> vector_c1;
		vector_c1.push_back(1);
		vector_c1.push_back(2);
		vector_c1.push_back(3);
		vector_c1.push_back(3);
		vector_c1.push_back(4);
		TESTED_NAMESPACE::vector<int> vector_c2(5, 43);
		TESTED_NAMESPACE::vector<int> vector_c3(++vector_c2.begin(), vector_c2.end());
		TESTED_NAMESPACE::vector<int> vector_c4(vector_c3);

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
		std::cout << "insert: " <<         *(vector_4.insert(++vector_4.begin(), 5))      << std::endl;
		vector_4.insert(vector_4.begin(), 10,42);
		vector_4.insert(++vector_4.begin(), vector_1.begin(), vector_1.end());
		print_vector(vector_4);
		std::cout << "erase: " <<    *(vector_4.erase(vector_4.begin()))      << std::endl;
		std::cout << "erase: " <<    *(vector_4.erase(--(--(--(--vector_4.end()))), --vector_4.end()))      << std::endl;
		print_vector(vector_1);
		print_vector(vector_4);
		vector_1.swap(vector_4);
		print_vector(vector_1);
		print_vector(vector_4);
		TESTED_NAMESPACE::vector<int> vector_5(vector_4);
		print_vector(vector_5);
		vector_5.clear();
		print_vector(vector_5);

		std::cout << "vector_1 < vector_4? : " << (vector_1 < vector_4) << std::endl;
		std::cout << "vector_1 < vector_4? : " << (vector_1 <= vector_4) << std::endl;
		std::cout << "vector_1 < vector_4? : " << (vector_1 > vector_4) << std::endl;
		std::cout << "vector_1 < vector_4? : " << (vector_1 >= vector_4) << std::endl;
		std::cout << "vector_1 < vector_4? : " << (vector_1 == vector_4) << std::endl;
		std::cout << "vector_1 < vector_4? : " << (vector_1 != vector_4) << std::endl;

		print_title_2("Iterators verifications");
		TESTED_NAMESPACE::vector<int>::iterator it1 = vector_1.begin();
		TESTED_NAMESPACE::vector<int>::const_iterator it2 = ++vector_1.begin();
		std::cout << "*it1 : " << *it1 << std::endl;
		std::cout << "it1 > it2? : " << (it1 > it2) << std::endl;
		std::cout << "it1 > it2? : " << (it1 > it2) << std::endl;
		std::cout << "it1 >= it2? : " << (it1 > it2) << std::endl;
		std::cout << "it1 < it2? : " << (it1 < it2) << std::endl;
		std::cout << "it1 <= it2? : " << (it1 < it2) << std::endl;
		std::cout << "it1 <== it2? : " << (it1 < it2) << std::endl;
		std::cout << "it1 != it2? : " << (it1 < it2) << std::endl;

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

// -----------------------------------------------------------------------------------------------------------
// --------------------------------------------- Map ---------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
void map_tests(int nb_of_tests)
{
	print_title_1("Map");

	// time test at the end
	clock_t time;
	time = clock();

	for(int i = 0; i < nb_of_tests; i++)
	{
		print_title_2("Functions verifications");
		print_title_3("Constructor");
		TESTED_NAMESPACE::map<int, std::string> map_1;
		map_1.insert(TESTED_NAMESPACE::make_pair(1,"un"));
		map_1.insert(TESTED_NAMESPACE::make_pair(2,"deux"));
		map_1.insert(TESTED_NAMESPACE::make_pair(3,"trois"));
		map_1.insert(TESTED_NAMESPACE::make_pair(4,"quatre"));
		TESTED_NAMESPACE::map<int, std::string> map_2(++map_1.begin(), --map_1.end());
		TESTED_NAMESPACE::map<int, std::string> map_3(map_2);
		print_map(map_1);
		print_map(map_2);
		print_map(map_3);
		
		print_title_3("operator=");
		TESTED_NAMESPACE::map<int, std::string> map_4 = map_2;
		print_map(map_4);

		print_title_3("Iterators (begin/end)");
		std::cout << "begin:" << (*(map_1.begin())).first << std::endl;
		std::cout << "end:" << (*(--map_1.end())).first << std::endl; //-- car end non alloué
		std::cout << "rbegin:" << (*(map_1.rbegin())).first << std::endl;
		std::cout << "rend:" << (*(--map_1.rend())).first << std::endl;//-- car rend non alloué

		print_title_3("Capacity");
		std::cout << "empty:" << map_1.empty() << std::endl;
		std::cout << "size:" << map_1.size() << std::endl;
		std::cout << "max size:" << map_1.max_size() << std::endl;

		print_title_3("Element access");
		std::cout << "operator[]: " << map_1[1] << std::endl;
	
		print_title_3("Modifiers");
		//insert
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			mymap.insert ( TESTED_NAMESPACE::pair<char,int>('a',100) );
			mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',200) );
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,bool> ret;
			ret = mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',500) );
			if (ret.second==false) {
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			}
			TESTED_NAMESPACE::map<char,int>::iterator it = mymap.begin();
			mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('b',300));
			mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('c',400));
			TESTED_NAMESPACE::map<char,int> anothermap;
			anothermap.insert(mymap.begin(),mymap.find('c'));
			std::cout << "mymap contains:\n";
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
			std::cout << "anothermap contains:\n";
			for (it=anothermap.begin(); it!=anothermap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		// erase
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::map<char,int>::iterator it;
			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;
			mymap['d']=40;
			mymap['e']=50;
			mymap['f']=60;
			it=mymap.find('b');
			mymap.erase (it);                   // erasing by iterator
			mymap.erase ('c');                  // erasing by key
			it=mymap.find ('e');
			mymap.erase ( it, mymap.end() );    // erasing by range
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		// swap
		{
			TESTED_NAMESPACE::map<char,int> foo,bar;
			foo['x']=100;
			foo['y']=200;
			bar['a']=11;
			bar['b']=22;
			bar['c']=33;
			foo.swap(bar);
			std::cout << "foo contains:\n";
			for (TESTED_NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
			std::cout << "bar contains:\n";
			for (TESTED_NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		}
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			mymap['x']=100;
			mymap['y']=200;
			mymap['z']=300;
			std::cout << "mymap contains:\n";
			for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
			mymap.clear();
			mymap['a']=1101;
			mymap['b']=2202;
			std::cout << "mymap contains:\n";
			for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		}
		print_title_3("Observers");
		// key compare
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::map<char,int>::key_compare mycomp = mymap.key_comp();
			mymap['a']=100;
			mymap['b']=200;
			mymap['c']=300;
			std::cout << "mymap contains:\n";
			char highest = mymap.rbegin()->first;     // key value of last element
			TESTED_NAMESPACE::map<char,int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while ( mycomp((*it++).first, highest) );
			std::cout << '\n';
		}
		print_title_3("Operations");
		// find
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::map<char,int>::iterator it;
			mymap['a']=50;
			mymap['b']=100;
			mymap['c']=150;
			mymap['d']=200;
			it = mymap.find('b');
			if (it != mymap.end())
			mymap.erase (it);
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';
		}
		// count 
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			char c;
			mymap ['a']=101;
			mymap ['c']=202;
			mymap ['f']=303;
			for (c='a'; c<'h'; c++)
			{
			std::cout << c;
			if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
			else 
			std::cout << " is not an element of mymap.\n";
			}
		}
		// lowerbound
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::map<char,int>::iterator itlow,itup;
			mymap['a']=20;
			mymap['b']=40;
			mymap['c']=60;
			mymap['d']=80;
			mymap['e']=100;
			itlow=mymap.lower_bound ('b');  // itlow points to b
			itup=mymap.upper_bound ('d');   // itup points to e (not d!)
			mymap.erase(itlow,itup);        // erases [itlow,itup)
			for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		}
		// uperbound
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::map<char,int>::iterator itlow,itup;
			mymap['a']=20;
			mymap['b']=40;
			mymap['c']=60;
			mymap['d']=80;
			mymap['e']=100;
			itlow=mymap.lower_bound ('b');  // itlow points to b
			itup=mymap.upper_bound ('d');   // itup points to e (not d!)
			mymap.erase(itlow,itup);        // erases [itlow,itup)
			for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		}
		// equal_range
		{
			TESTED_NAMESPACE::map<char,int> mymap;
			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,TESTED_NAMESPACE::map<char,int>::iterator> ret;
			ret = mymap.equal_range('b');
			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';
			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';
		}
		print_title_3("Allocator");
		// get_allocator
		{
			int psize;
			TESTED_NAMESPACE::map<char,int> mymap;
			TESTED_NAMESPACE::pair<const char,int>* p;
			// allocate an array of 5 elements using mymap's allocator:
			p=mymap.get_allocator().allocate(5);
			// assign some values to array
			psize = sizeof(TESTED_NAMESPACE::map<char,int>::value_type)*5;
			std::cout << "The allocated array has a size of " << psize << " bytes.\n";
			mymap.get_allocator().deallocate(p,5);
		}	
	}
	print_title_2("Time test");
	time = clock() - time;
	double time_ms = ((double)time)/CLOCKS_PER_SEC*1000;
	std::cout << "Map execution time for " << TESTED_NAMESPACE_STR << " = " << time_ms << "ms \n" << std::endl;
}

// -----------------------------------------------------------------------------------------------------------
// --------------------------------------------- Stack ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
void stack_tests(int nb_of_tests)
{
	print_title_1("Map");

	// time test at the end
	clock_t time;
	time = clock();

	for(int i = 0; i < nb_of_tests; i++)
	{
		print_title_2("Functions verifications");
		print_title_3("constructor");
		{
			std::vector<int> myvector (2,200);        // vector with 2 elements
			TESTED_NAMESPACE::stack<int> first;                    // empty stack
			TESTED_NAMESPACE::stack<int,std::vector<int> > third;  // empty stack using vector
			TESTED_NAMESPACE::stack<int,std::vector<int> > fourth (myvector);
			std::cout << "size of first: " << first.size() << '\n';
			std::cout << "size of third: " << third.size() << '\n';
			std::cout << "size of fourth: " << fourth.size() << '\n';
		}
		print_title_3("empty");
		{
			TESTED_NAMESPACE::stack<int> mystack;
			int sum (0);
			for (int i=1;i<=10;i++) mystack.push(i);
			while (!mystack.empty())
			{
				sum += mystack.top();
				mystack.pop();
			}
			std::cout << "total: " << sum << '\n';
		}
		print_title_3("size");
		{
			TESTED_NAMESPACE::stack<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';
			for (int i=0; i<5; i++) myints.push(i);
			std::cout << "1. size: " << myints.size() << '\n';
			myints.pop();
			std::cout << "2. size: " << myints.size() << '\n';
		}
		print_title_3("top");
		{
			TESTED_NAMESPACE::stack<int> mystack;
			mystack.push(10);
			mystack.push(20);
			mystack.top() -= 5;
			std::cout << "mystack.top() is now " << mystack.top() << '\n';
		}
		print_title_3("push");
		{
			TESTED_NAMESPACE::stack<int> mystack;
			for (int i=0; i<5; ++i) mystack.push(i);
			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
			std::cout << ' ' << mystack.top();
			mystack.pop();
			}
			std::cout << '\n';
		}
		print_title_3("pop");
		{
			TESTED_NAMESPACE::stack<int> mystack;
			for (int i=0; i<5; ++i) mystack.push(i);
			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
			std::cout << ' ' << mystack.top();
			mystack.pop();
			}
			std::cout << '\n';
		}
		print_title_3("relational operators");
		{
			TESTED_NAMESPACE::stack<int> stack_1;
			stack_1.push(1);
			stack_1.push(2);
			stack_1.push(3);
			stack_1.push(4);
			stack_1.push(5);
			TESTED_NAMESPACE::stack<int> stack_2(stack_1);
			std::cout << "stack_1 < stack_2? : " << (stack_1 < stack_2) << std::endl;
			std::cout << "stack_1 < stack_2? : " << (stack_1 <= stack_2) << std::endl;
			std::cout << "stack_1 < stack_2? : " << (stack_1 > stack_2) << std::endl;
			std::cout << "stack_1 < stack_2? : " << (stack_1 >= stack_2) << std::endl;
			std::cout << "stack_1 < stack_2? : " << (stack_1 == stack_2) << std::endl;
			std::cout << "stack_1 < stack_2? : " << (stack_1 != stack_2) << std::endl;
		}
		print_title_3("swap (non member)");
		{
			TESTED_NAMESPACE::stack<int> foo,bar;
			foo.push (10); foo.push(20); foo.push(30);
			bar.push (111); bar.push(222);

			swap(foo,bar);

			std::cout << "size of foo: " << foo.size() << '\n';
			std::cout << "size of bar: " << bar.size() << '\n';
		}
	}

	print_title_2("Time test");
	time = clock() - time;
	double time_ms = ((double)time)/CLOCKS_PER_SEC*1000;
	std::cout << "Stack execution time for " << TESTED_NAMESPACE_STR << " = " << time_ms << "ms \n" << std::endl;
}

// -----------------------------------------------------------------------------------------------------------
// --------------------------------------------- Stack ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
void set_tests(int nb_of_tests)
{
	print_title_1("Set");

	// time test at the end
	clock_t time;
	time = clock();

	for(int i = 0; i < nb_of_tests; i++)
	{
		print_title_2("Functions verifications");
		print_title_3("Constructor");
		{
			TESTED_NAMESPACE::set<int> first;                           // empty set of ints
			int myints[]= {10,20,30,40,50};
			TESTED_NAMESPACE::set<int> second (myints,myints+5);        // range
			TESTED_NAMESPACE::set<int> third (second);                  // a copy of second
			TESTED_NAMESPACE::set<int> fourth (second.begin(), second.end());  // iterator ctor.
			print_set(first);
			print_set(second);
			print_set(third);
			print_set(fourth);
		}

		print_title_3("operator=");
		{
			int myints[]={ 12,82,37,64,15 };
			std::set<int> first (myints,myints+5);   // set with 5 ints
			std::set<int> second;                    // empty set
			second = first;                          // now second contains the 5 ints
			first = std::set<int>();                 // and first is empty
			std::cout << "Size of first: " << int (first.size()) << '\n';
			std::cout << "Size of second: " << int (second.size()) << '\n';
		}
		print_title_3("Iterators");
		{

			int myints[]= {10,20,30,40,50};
			TESTED_NAMESPACE::set<int> set_1 (myints,myints+5);        // range
			std::cout << "begin:" << *(set_1.begin()) << std::endl;
			std::cout << "end:" << *(--set_1.end()) << std::endl; //-- car end non alloué
			std::cout << "rbegin:" << *(set_1.rbegin()) << std::endl;
			std::cout << "rend:" << *(--set_1.rend()) << std::endl;//-- car rend non alloué
		}

		print_title_3("Capacity");
		// empty
		{
			std::set<int> myset;
			myset.insert(20);
			myset.insert(30);
			myset.insert(10);
			std::cout << "myset contains:";
			while (!myset.empty())
			{
				std::cout << ' ' << *myset.begin();
				myset.erase(myset.begin());
			}
			std::cout << '\n';
		}
		// size
		{
			std::set<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';
			for (int i=0; i<10; ++i) myints.insert(i);
			std::cout << "1. size: " << myints.size() << '\n';
			myints.insert (100);
			std::cout << "2. size: " << myints.size() << '\n';
			myints.erase(5);
			std::cout << "3. size: " << myints.size() << '\n';
		}
		// max_size
		{
			int i;
			std::set<int> myset;
			if (myset.max_size()>1000)
			{
			for (i=0; i<1000; i++) myset.insert(i);
			std::cout << "The set contains 1000 elements.\n";
			}
			else std::cout << "The set could not hold 1000 elements.\n";
		}

		print_title_3("Modifiers");
		// insert
		{
			std::set<int> myset;
			std::set<int>::iterator it;
			std::pair<std::set<int>::iterator,bool> ret;
			// set some initial values:
			for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50
			ret = myset.insert(20);               // no new element inserted
			if (ret.second==false) it=ret.first;  // "it" now points to element 20
			myset.insert (it,25);                 // max efficiency inserting
			myset.insert (it,24);                 // max efficiency inserting
			myset.insert (it,26);                 // no max efficiency inserting
			int myints[]= {5,10,15};              // 10 already in set, not inserted
			myset.insert (myints,myints+3);
			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		// erase
		{
			std::set<int> myset;
			std::set<int>::iterator it;
			// insert some values:
			for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90
			it = myset.begin();
			++it;                                         // "it" points now to 20
			myset.erase (it);
			myset.erase (40);
			it = myset.find (60);
			myset.erase (it, myset.end());
			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		// swap
		{
			int myints[]={12,75,10,32,20,25};
			std::set<int> first (myints,myints+3);     // 10,12,75
			std::set<int> second (myints+3,myints+6);  // 20,25,32
			first.swap(second);
			std::cout << "first contains:";
			for (std::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "second contains:";
			for (std::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		// clear 
		{
			std::set<int> myset;
			myset.insert (100);
			myset.insert (200);
			myset.insert (300);
			std::cout << "myset contains:";
			for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
			myset.clear();
			myset.insert (1101);
			myset.insert (2202);
			std::cout << "myset contains:";
			for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		print_title_3("Observers");
		// key_comp
		{
			std::set<int> myset;
			int highest;
			std::set<int>::key_compare mycomp = myset.key_comp();
			for (int i=0; i<=5; i++) myset.insert(i);
			std::cout << "myset contains:";
			highest=*myset.rbegin();
			std::set<int>::iterator it=myset.begin();
			do {
			std::cout << ' ' << *it;
			} while ( mycomp(*(++it),highest) );
			std::cout << '\n';
		}
		// value_comp
		{
			std::set<int> myset;
			std::set<int>::value_compare mycomp = myset.value_comp();
			for (int i=0; i<=5; i++) myset.insert(i);
			std::cout << "myset contains:";
			int highest=*myset.rbegin();
			std::set<int>::iterator it=myset.begin();
			do {
			std::cout << ' ' << *it;
			} while ( mycomp(*(++it),highest) );
			std::cout << '\n';
		}
		print_title_3("Operations");
		// find 
		{
			std::set<int> myset;
			std::set<int>::iterator it;
			// set some initial values:
			for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50
			it=myset.find(20);
			myset.erase (it);
			myset.erase (myset.find(40));
			std::cout << "myset contains:";
			for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		// count
		{
			std::set<int> myset;
			// set some initial values:
			for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12
			for (int i=0; i<10; ++i)
			{
			std::cout << i;
			if (myset.count(i)!=0)
			std::cout << " is an element of myset.\n";
			else
			std::cout << " is not an element of myset.\n";
			}
		}
		// lower_bound/upper_bound
		{
			std::set<int> myset;
			std::set<int>::iterator itlow,itup;
			for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90
			itlow=myset.lower_bound (30);                //       ^
			itup=myset.upper_bound (60);                 //                   ^
			myset.erase(itlow,itup);                     // 10 20 70 80 90
			std::cout << "myset contains:";
			for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
			std::cout << '\n';
		}
		// equal_range
		{
			std::set<int> myset;
			for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50
			std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
			ret = myset.equal_range(30);
			std::cout << "the lower bound points to: " << *ret.first << '\n';
			std::cout << "the upper bound points to: " << *ret.second << '\n';
		}
		print_title_3("Allocator");
		{
			std::set<int> myset;
			int * p;
			unsigned int i;
			// allocate an array of 5 elements using myset's allocator:
			p=myset.get_allocator().allocate(5);
			// assign some values to array
			for (i=0; i<5; i++) p[i]=(i+1)*10;
			std::cout << "The allocated array contains:";
			for (i=0; i<5; i++) std::cout << ' ' << p[i];
			std::cout << '\n';
			myset.get_allocator().deallocate(p,5);
		}
	}

	print_title_2("Time test");
	time = clock() - time;
	double time_ms = ((double)time)/CLOCKS_PER_SEC*1000;
	std::cout << "Set execution time for " << TESTED_NAMESPACE_STR << " = " << time_ms << "ms \n" << std::endl;
}
// ###########################################################################################################
// #########################################   MAIN   ########################################################
// ###########################################################################################################
int main()
{
	vector_tests(100);
	map_tests(100);
	stack_tests(100);
	set_tests(100);
}
