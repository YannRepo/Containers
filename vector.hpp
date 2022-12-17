#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>

namespace ft
{
	template<typename T,typename Alloc>
	class vector
	{
		typedef T										value_type
		typedef Allocator								allocator_type
		typedef std::size_t								size_type
		typedef std::ptrdiff_t							difference_type
		typedef value_type&								reference
		typedef	const value_type&						const_reference
		typedef Allocator::pointer						pointer
		typedef Allocator::const_pointer				const_pointer
		//typedef iterator
		//typedef const_iterator
		typedef std::reverse_iterator<iterator>			reverse_iterator
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator

		public:

		private:
		
	};
}

#endif
