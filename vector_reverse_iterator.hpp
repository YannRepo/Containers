#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

#include "vector.hpp"
# include "random_access_iterator.hpp"
# include "iterator_traits.hpp"


namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
		public:
			//typedef T												value_type;
			//typedef std::ptrdiff_t									difference_type;
			//typedef T*												pointer;
			//typedef T&												reference;
		

			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type 			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;


		public:
			iterator_type current;

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ constructor / destructor --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
	
		public:
			reverse_iterator(): current(){}
			explicit reverse_iterator (iterator_type it): current(it){}
			reverse_iterator (const reverse_iterator& rev_it): current(rev_it.current){}
			template <typename it2>
			reverse_iterator(const reverse_iterator<it2> &src): current(src.base())
	{}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Fonctions membres --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		public:
			iterator_type base() const
			{
				return (this->current);
			}

			// TBD operator= non membre normalement ? comment faire sans ?
			//reverse_iterator& operator=(const reverse_iterator rhs)
			//{
			//	this->current = rhs.base();
			//	return (*this);
			//}

			reference operator*() const
			{
				Iterator tmp = this->current;
				tmp--;
				return (*tmp);
			}

			reverse_iterator operator+ (difference_type n) const
			{
				reverse_iterator it_copy = *this;
				it_copy += n;
				return (it_copy);
			}

			reverse_iterator& operator++() //++i
			{
				this->current--;
				return (*this);
			}
			reverse_iterator  operator++(int) //i++
			{
				reverse_iterator it_copy = *this;
				this->current--;
				return (it_copy);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				this->current-= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const
			{
				reverse_iterator it_copy = *this;
				it_copy -= n;
				return (it_copy);
			}

			reverse_iterator& operator--()
			{
				current++;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator it_copy = *this;
				current++;
				return (it_copy);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				this->current+= n;
				return (*this);
			}

			pointer operator->() const
			{
				Iterator tmp = this->current;
				tmp--;
				return (&(*tmp));
				//return &(operator*());
			}

			reference operator[] (difference_type n) const
			{
				return (*(this->current - n - 1));
			}

	};

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Fonctions non membres --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
	// TBD check sur cppref la lst

	// norme
	//template <class Iterator>
	//bool operator==(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{
		
	//}

	//template <class Iterator>
	//bool operator<(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//bool operator!=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//bool operator>(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//bool operator>=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//bool operator<=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
	//{

	//}

	//template <class Iterator>
	//reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x)
	//{

	//}

	// recup iterator
	template <typename iterator1, typename iterator2>
	bool operator==(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename iterator1, typename iterator2>
	bool operator!=(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename iterator1, typename iterator2>
	bool operator<(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename iterator1, typename iterator2>
	bool operator>(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename iterator1, typename iterator2>
	bool operator<=(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename iterator1, typename iterator2>
	bool operator>=(const reverse_iterator<iterator1> &lhs, const reverse_iterator<iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename iterator1, typename iterator2>
	typename reverse_iterator<iterator1>::difference_type operator-(const reverse_iterator<iterator1>& lhs, const reverse_iterator<iterator2>& rhs)
	{
		//return (5);
		return (rhs.base() - lhs.base());
	}


}

#endif

// template selon norme 14882:1998
//namespace std
//{
//	template <class Iterator>
//	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
//											 typename iterator_traits<Iterator>::value_type,
//											 typename iterator_traits<Iterator>::difference_type,
//											 typename iterator_traits<Iterator>::pointer,
//											 typename iterator_traits<Iterator>::reference>
//	{
//		protected:
//			Iterator current;

//		public:
			//typedef Iterator
			//	iterator_type;
			//typedef typename iterator_traits<Iterator>::difference_type
			//	difference_type;
			//typedef typename iterator_traits<Iterator>::reference
			//	reference;
			//typedef typename iterator_traits<Iterator>::pointer
			//	pointer;
			//reverse_iterator();
			//explicit reverse_iterator(Iterator x);
			//template <class U>
			//reverse_iterator(const reverse_iterator<U> &u);
			//Iterator base() const; // explicit
			//reference operator*() const;
			//pointer operator->() const;
			//reverse_iterator &operator++();
			//reverse_iterator operator++(int);
			//reverse_iterator &operator--();
			//reverse_iterator operator--(int);
			//reverse_iterator operator+(difference_type n) const;
			//reverse_iterator &operator+=(difference_type n);
			//reverse_iterator operator-(difference_type n) const;
			//reverse_iterator &operator-=(difference_type n);
			//reference operator[](difference_type n) const;
	//};
//	template <class Iterator>
//	bool operator==(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	bool operator<(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	bool operator!=(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	bool operator>(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	bool operator>=(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	bool operator<=(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	typename reverse_iterator<Iterator>::difference_type operator-(
//		const reverse_iterator<Iterator> &x,
//		const reverse_iterator<Iterator> &y);
//	template <class Iterator>
//	reverse_iterator<Iterator> operator+(
//		typename reverse_iterator<Iterator>::difference_type n,
//		const reverse_iterator<Iterator> &x);
//}
