#ifndef BASE_HPP
# define BASE_HPP

# if !defined(USING_STD)
#  define TESTED_NAMESPACE ft
# else
#  define TESTED_NAMESPACE std
# endif /* !defined(STD) */

# include <iostream>
# include <string>

# include "map.hpp"

// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#endif /* BASE_HPP */
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
	typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
#if !defined(USING_STD)
# include "map.hpp"
#else
# include <map>
#endif /* !defined(STD) */

#define _pair TESTED_NAMESPACE::pair

#include <list>

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_erase(mp, ++mp.begin());

	ft_erase(mp, mp.begin());
	ft_erase(mp, --mp.end());

	//std::cout << "check1: " << (mp.begin())->first << " | "<< (mp.begin())->second << std::endl;
	//std::cout << "check1: " << (++(++(++(mp.begin()))))->first << " | "<< (++(++(++(mp.begin()))))->second << std::endl;
	////ft_erase(mp, mp.begin(),++(mp.begin())); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	
	//mp.print();
	TESTED_NAMESPACE::map<T1, T2>::iterator it1 = ++(++(++(mp.begin())));
	TESTED_NAMESPACE::map<T1, T2>::iterator it2 = ++(++(mp.begin()));
	TESTED_NAMESPACE::map<T1, T2>::iterator it3 = ++(mp.begin());
	TESTED_NAMESPACE::map<T1, T2>::iterator it4 = mp.begin();
	//TESTED_NAMESPACE::map<T1, T2>::iterator it5 = ++mp.begin()++;

	//mp.erase(--(--(--mp.end())), mp.end());
	//TESTED_NAMESPACE::map<T1, T2>::iterator it6 = mp.begin();

	mp.print();
	
	ft_erase(mp, it4);
	mp.print();
	ft_erase(mp, it3);
	mp.print();
	ft_erase(mp, it2);
	mp.print();
	ft_erase(mp, it1);
	mp.print();
	
	//ft_erase(mp, mp.begin(), ++(++(++(mp.begin())))); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	//ft_erase(mp, ++(++(++(mp.begin())))); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	//ft_erase(mp, mp.begin()); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	//ft_erase(mp, mp.begin()); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	//ft_erase(mp, mp.begin()); // pose pb (! ligne modifiee par rapport au test original, () differentes)
	
	
	mp.print();
	//TESTED_NAMESPACE::map<T1, T2>::iterator it4 = mp.end();
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	//mp[10] = "Hello";
	//mp[11] = "Hi there";
	//printSize(mp);
	//ft_erase(mp, --(--(--mp.end())), mp.end());

	//mp[12] = "ONE";
	//mp[13] = "TWO";
	//mp[14] = "THREE";
	//mp[15] = "FOUR";
	//printSize(mp);
	//ft_erase(mp, mp.begin(), mp.end());

	return (0);
}

