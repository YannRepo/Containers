#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
		class stack
		{
			public:
				typedef T							value_type;
				typedef	Container					container_type;
				typedef Container::size_type		size_type;

			protected:
				container_type c;

			public:
				explicit stack (const container_type& ctnr = container_type()): c(ctnr){}
				~stack(){}

		};
}

#endif
