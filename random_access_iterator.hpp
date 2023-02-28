#ifndef RANDOM_ACCESS_ITERATOR
# define RANDOM_ACCESS_ITERATOR

#include <iostream>
#include "vector.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
		public:
			typedef T											value_type;
			typedef std::ptrdiff_t								difference_type;
			typedef std::random_access_iterator_tag				iterator_category;
			typedef T*											pointer;
			typedef T&											reference;

		protected:
			pointer _pointer;
			
// ###########################################################################################################
// ##################################   Constructeurs / destructeurs   #######################################
// ###########################################################################################################
		public:
			random_access_iterator()
			{
				this->_pointer = NULL;
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

// ###########################################################################################################
// ##################################   Fonctions membres   ##################################################
// ###########################################################################################################
		public:
			pointer base() const
			{
				return (this->_pointer);
			}
			random_access_iterator& operator=(const random_access_iterator &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}
			reference operator*(void) const
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
			random_access_iterator &operator+=(int n)
			{
				this->_pointer += n;
				return (*this);
			}
			random_access_iterator &operator-=(int n)
			{
				this->_pointer -= n;
				return (*this);
			}
			reference operator[](int n) const
			{
				return (*(this->_pointer + n));
			}
			operator random_access_iterator<const T>() const
			{
				return random_access_iterator<const T>(this->_pointer);
			}
	};

// ###########################################################################################################
// ################################   Fonctions non membres (surcharges operator)  ###########################
// ###########################################################################################################
	template <class InputIterator>
	InputIterator operator+(int lhs, InputIterator rhs)
	{
		return (rhs + lhs);
	}

	template <typename T1, typename T2>
	bool operator==(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T1, typename T2>
	bool operator!=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T1, typename T2>
	bool operator<(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T1, typename T2>
	bool operator>(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T1, typename T2>
	bool operator<=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T1, typename T2>
	bool operator>=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T1, typename T2>
	inline typename ft::random_access_iterator<T1>::difference_type operator-(const ft::random_access_iterator<T1> &lhs,
	const ft::random_access_iterator<T2> &rhs)
	{
		return lhs.base() - rhs.base();
	}
}

#endif
