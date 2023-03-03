#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
		class stack
		{
			public:
				typedef T									value_type;
				typedef	Container							container_type;
				typedef typename Container::size_type		size_type;

			protected:
				container_type c;

			public:
				explicit stack (const container_type& ctnr = container_type()): c(ctnr){}
				~stack(){}

				bool empty() const { return c.empty(); }
				size_type size() const { return c.size(); }
				value_type &top() { return c.back(); }
				const value_type &top() const { return c.back(); }
				void push(const value_type &x) { c.push_back(x); }
				void pop() { c.pop_back(); }

				template <class X, class Y>
				friend bool operator==(const stack<X, Y> &x, const stack<X, Y> &y);

				template <class X, class Y>
				friend bool operator< (const stack<X, Y> &x, const stack<X, Y> &y);

				template <class X, class Y>
				friend bool operator!=(const stack<X, Y> &x, const stack<X, Y> &y);

				template <class X, class Y>
				friend bool operator> (const stack<X, Y>& x, const stack<X, Y> &y);

				template <class X, class Y>
				friend bool operator>=(const stack<X, Y>& x, const stack<X, Y> &y);

				template <class X, class Y>
				friend bool operator<=(const stack<X, Y>& x, const stack<X, Y> &y);
		};

		template <class T, class Container>
		bool operator==(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c == y.c);
		}
		template <class T, class Container>
		bool operator<(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c < y.c);
		}
		template <class T, class Container>
		bool operator!=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c != y.c);
		}
		template <class T, class Container>
		bool operator>(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c > y.c);
		}
		template <class T, class Container>
		bool operator>=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c >= y.c);
		}
		template <class T, class Container>
		bool operator<=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			return (x.c <= y.c);
		}
}

#endif
