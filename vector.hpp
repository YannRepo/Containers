#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>


namespace ft
{
	template<typename T,typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T										value_type;
			// typedef Allocator								allocator_type;
			// typedef std::size_t								size_type;
			// typedef std::ptrdiff_t							difference_type;
			// typedef value_type&								reference;
			// typedef	const value_type&						const_reference;
			// typedef Allocator::pointer						pointer;
			// typedef Allocator::const_pointer				const_pointer;
			// //typedef iterator
			// //typedef const_iterator
			// typedef std::reverse_iterator<iterator>			reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		public:
			// template<typename T>
			class iterator
			{
				// public:
					// typedef int								difference_type
				public:
					// constructor / detructor
					iterator()
					{
						this->_pointer = NULL;
						this->_size = 0;
					}
					iterator(const iterator& src)
					{
						*this = src;
					}
					~iterator(){}

					// // functions
					void advance(iterator& it, int n)
					{
						it._pointer += n;
					}
					long distance(iterator first, iterator last)
					{
						return (last._pointer - first._pointer);
					}
					iterator begin()
					{
						return(iterator(*this));
					}
					iterator end()
					{
						advance(*this, this->_size);
						return(*this);
					}
					iterator prev(iterator first, int n)
					{
						return(iterator(*this)--);
					}
					iterator next(iterator first, int n)
					{
						return(iterator(*this)++);
					}

					// // operator overload
					iterator& operator=(const iterator& src)
					{
						this->_pointer = src._pointer;
						this->_size = src._size;
					}
					bool operator==(const iterator& src)
					{
						return (this._pointer == src._pointer);
					}
					bool operator!=(const iterator& src)
					{
						return (this._pointer != src._pointer);
					}
					// bool operator*=(const iterator* src)
					// {
					// 	return (this._pointer* == src._pointer*);
					// }
					// bool operator*!=(const iterator* src)
					// {
					// 	return (this._pointer* != src._pointer*)
					// }
					// iterator& operator->(const iterator& src)
					// {
					// 	// TBD
					// }
					//*a = t
					//*a++
					iterator& operator++()
					{
						this->_pointer++;
						return(this);
					}
					iterator& operator++(int)
					{
						iterator it_copy = *this;
						this->_pointer++;
						return (it_copy);
					}
					iterator& operator--()
					{
						this->_pointer--;
						return(this);
					}
					iterator& operator--(int)
					{
						iterator it_copy = *this;
						this->_pointer--;
						return (it_copy);
					}
					// + - ?


				public: // public pour debug TBD
					T*		_pointer;
					int	_size;

			};

	};
};

#endif
