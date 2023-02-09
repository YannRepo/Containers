#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"


namespace ft
{
	template <typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
	class Map
	{
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const key_type,mapped_type>		value_type;
		typedef Compare 								key_compare;

//value_compare	Nested function class to compare elements	see value_comp
		
		
		typedef Allocator								allocator_type;
		typedef value_type								&reference;

		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		//typedef iterator								
		//typedef	const_iterator							
		//typedef reverse_iterator						
		//typedef const_reverse_iterator					
		typedef std::ptrdiff_t							difference_type;
		typedef size_t									size_type;


//	public: // pour debug TBD remettre en protected a la fin

};



}

#endif
