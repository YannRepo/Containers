#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

//# include "/20_Vector/vector.hpp"
//# include "20_Vector/random_access_iterator.hpp"
# include "iterator_traits.hpp"


namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type 			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			iterator_type current;

// ###########################################################################################################
// ##################################   Constructeurs / destructeurs   #######################################
// ###########################################################################################################
		public:
			reverse_iterator(): current(){}
			explicit reverse_iterator (iterator_type it): current(it){}
			reverse_iterator (const reverse_iterator& rev_it): current(rev_it.current){}
			template <typename it2>
			reverse_iterator(const reverse_iterator<it2> &src): current(src.base()){}

// ###########################################################################################################
// ###################################   Fonctions membres   #################################################
// ###########################################################################################################
		public:
			iterator_type base() const
			{
				return (this->current);
			}

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
			}

			reference operator[] (difference_type n) const
			{
				return (*(this->current - n - 1));
			}
	};

// ###########################################################################################################
// ###################################   Fonctions non membres   #############################################
// ###########################################################################################################
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
		return (rhs.base() - lhs.base());
	}

	template <typename iterator1, typename iterator2>
	typename reverse_iterator<iterator1>::difference_type operator+(const reverse_iterator<iterator1>& lhs, const reverse_iterator<iterator2>& rhs)
	{
		return (rhs.base() + lhs.base());
	}
}
#endif
