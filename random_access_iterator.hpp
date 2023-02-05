#ifndef RANDOM_ACCESS_ITERATOR
# define RANDOM_ACCESS_ITERATOR

#include <iostream>
#include "vector.hpp"

namespace ft
{
// ###########################################################################################################
// #########################################   random_access_iterator   ####################################################
// ###########################################################################################################

	template <typename T>
	class random_access_iterator
	{
		public:
		// TBD check si les typedef commentes ne sont pas utilises
			typedef T											value_type;
			//typedef const T*									const_pointer;
			//typedef T*											pointer;
			//typedef Allocator									allocator_type;
			//typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			//typedef value_type&									reference;
			//typedef	const value_type&							const_reference;
			typedef std::random_access_iterator_tag				iterator_category;


// ajout
			typedef T*												pointer;

			typedef T&										reference;

		public: // public pour debug TBD
			pointer _pointer;
			// int	_size; // TBD a sup
			
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
			pointer base() const
			{
				return (this->_pointer);
			}

			// // operator overload
			random_access_iterator& operator=(const random_access_iterator &rhs)
			{
				this->_pointer = rhs._pointer;
				return (*this);
			}
			//bool operator==(const random_access_iterator &src)
			//{
			//	return (this->_pointer == src._pointer);
			//}
			//bool operator!=(const random_access_iterator &src)
			//{
			//	return (this->_pointer != src._pointer);
			//}
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
			//bool operator<(const random_access_iterator &compared) const
			//{
			//	return (this->_pointer < compared._pointer);
			//}
			//bool operator>(const random_access_iterator &compared) const
			//{
			//	return (this->_pointer > compared._pointer);
			//}
			//bool operator<=(const random_access_iterator &compared) const
			//{
			//	return (this->_pointer <= compared._pointer);
			//}
			//bool operator>=(const random_access_iterator &compared) const
			//{
			//	return (this->_pointer >= compared._pointer);
			//}
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

			// TBD check ces lignes
			operator random_access_iterator<const T>() const
			{
				return random_access_iterator<const T>(this->_pointer);
			}


	};


// ###########################################################################################################
// #########################################   Surcharge hors class vector / iterator   ######################################################
// ###########################################################################################################
	
	// TBD verif si cette surcharge est tjr utile ?
	template <class InputIterator>
	InputIterator operator+(int lhs, InputIterator rhs)
	{
		return (rhs + lhs);
	}



	//template <typename T1>
	//bool operator==(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T1> &rhs)
	//{
	//	return (lhs.base() == rhs.base());
	//}
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

	// TBD ajouter les surcharges pour toutes les combinaisons const / not const 
}



#endif
