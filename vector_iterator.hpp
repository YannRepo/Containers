#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iostream>
#include <vector>

#include "vector.hpp"

namespace ft
{
// ###########################################################################################################
// #########################################   random_access_iterator   ####################################################
// ###########################################################################################################

	template <typename T, typename Allocator = std::allocator<T> >
	class random_access_iterator
	{
		public:
			typedef T											value_type;
			typedef const T*									const_pointer;
			typedef T*											pointer;
			typedef Allocator									allocator_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type&									reference;
			typedef	const value_type&							const_reference;
			// TBD check type def
			//typedef const T*									const_pointer;
			//typedef T											value_type;
			//typedef T*											pointer;

			// ligne MI
			// operator iterator<value_type const>()const{return iterator<value_type const>(_pointer);}

			// public:
			// typedef int								difference_type
		public:
			// constructor / detructor
			random_access_iterator()
			{
				this->_pointer = NULL;
				// this->_size = 0;
			}
			random_access_iterator(pointer vector_pt)
			{
				this->_pointer = vector_pt;
			}
			random_access_iterator(const random_access_iterator &src)
			{
				this->_pointer = src._pointer;
			}
			~random_access_iterator() {}

			// // functions
			void advance(random_access_iterator &it, int n)
			{
				it._pointer += n;
			}
			random_access_iterator prev(random_access_iterator first, int n)
			{
				return (random_access_iterator(*this)--);
			}
			random_access_iterator next(random_access_iterator first, int n)
			{
				return (random_access_iterator(*this)++);
			}

			// // operator overload
			random_access_iterator &operator=(const random_access_iterator &src)
			{
				this->_pointer = src._pointer;
				// this->_size = src._size;
				return (*this);
			}
			bool operator==(const random_access_iterator &src)
			{
				return (this->_pointer == src._pointer);
			}
			bool operator!=(const random_access_iterator &src)
			{
				return (this->_pointer != src._pointer);
			}
			value_type& operator*(void) const
			{
				return (*this->_pointer);
			}
			pointer operator->() const
			{
				return (this->_pointer);
			}
			random_access_iterator &operator++()
			{
				this->_pointer++;
				return (*this);
			}
			random_access_iterator operator++(int)
			{
				random_access_iterator it_copy = *this;
				this->_pointer++;
				return (it_copy);
			}
			random_access_iterator &operator--()
			{
				this->_pointer--;
				return (*this);
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator it_copy = *this;
				this->_pointer--;
				return (it_copy);
			}
			random_access_iterator operator+(int n) const
			{
				return (random_access_iterator(this->_pointer + n));
			}
			difference_type operator+(const  random_access_iterator& it) const
			{
				return (this->_pointer + it._pointer);
			}
			random_access_iterator operator-(int n) const
			{
				return (random_access_iterator(this->_pointer - n));
			}
			difference_type operator-(const  random_access_iterator& it) const
			{
				return (this->_pointer - it._pointer);
			}
			bool operator<(const random_access_iterator &compared) const
			{
				return (this->_pointer < compared._pointer);
			}
			bool operator>(const random_access_iterator &compared) const
			{
				return (this->_pointer > compared._pointer);
			}
			bool operator<=(const random_access_iterator &compared) const
			{
				return (this->_pointer <= compared._pointer);
			}
			bool operator>=(const random_access_iterator &compared) const
			{
				return (this->_pointer >= compared._pointer);
			}
			random_access_iterator &operator+=(int n)
			{
				advance(*this, n);
				return (*this);
			}
			random_access_iterator &operator-=(int n)
			{
				advance(*this, -n);
				return (*this);
			}
			
			reference operator[](int n) const
			{
				return (*(this->_pointer + n));
			}

		public: // public pour debug TBD
			pointer _pointer;
			// int	_size; // TBD a sup
	};

// ###########################################################################################################
// #########################################   const_random_access_iterator   ####################################################
// ###########################################################################################################

	//template <typename T, typename Allocator = std::allocator<T> >
	//class const_random_access_iterator : public ft::random_access_iterator<T>
	//{
	//	public:
	//		typedef T											value_type;
	//		typedef const T*									const_pointer;
	//		typedef T*											pointer;
	//		typedef Allocator									allocator_type;
	//		typedef std::size_t									size_type;
	//		typedef std::ptrdiff_t								difference_type;
	//		typedef value_type&									reference;
	//		typedef	const value_type&							const_reference;
	//	public:
	//		// constructor / detructor
	//		const_random_access_iterator()
	//		{
	//			this->_pointer = NULL;
	//			// this->_size = 0;
	//		}
	//		const_random_access_iterator(pointer vector_pt)
	//		{
	//			this->_pointer = vector_pt;
	//		}
	//		const_random_access_iterator(const_random_access_iterator &src)
	//		{
	//			this->_pointer = src._pointer;
	//		}
	//		// TBD destruct ?
	//		~const_random_access_iterator() {}
	//		// surcharge operateur * pour return const
	//		const value_type &operator*(void) const
	//		{
	//			return (*this->_pointer);
	//		}
	//		const_pointer operator->() const
	//		{
	//			//std::cout << "check2" << std::endl;
	//			const pointer tmp = this->_pointer;
	//			return (tmp);
	//		}
	//		const_reference operator[](int n) const
	//		{
	//			return (*(this->_pointer + n));
	//		}
			
	//	};
}

#endif
