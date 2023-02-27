#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <vector>
# include <memory>

# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
# include "lexicographical_compare.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef const T*										const_pointer;
			typedef T*												pointer;
			typedef Allocator										allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef T&												reference;
			typedef	const value_type&								const_reference;
			typedef ft::random_access_iterator<T>					iterator;
			typedef ft::random_access_iterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			

	protected:
		Allocator myAllocator;

		T *_vector_pointer;
		size_t _vector_size;
		size_t _vector_capacity;

	// ###########################################################################################################
	// #########################################   UTILS   #######################################################
	// ###########################################################################################################
	private:
		void copy_vector(size_type len_to_copy, value_type *src, value_type *dest)
		{
			for (size_type i = 0; i < len_to_copy; i++)
			{
				dest[i] = src[i];
			}
		}
		template <class InpputIterator>
		difference_type distance(InpputIterator first, InpputIterator last)
		{
			difference_type distance = 0;
			while (first != last)
			{
				distance++;
				first++;
			}
			return (distance);
		}

	// ###########################################################################################################
	// #########################################   Fonctions membres   ###########################################
	// ###########################################################################################################
	// -----------------------------------------------------------------------------------------------------------
	// ------------------------------------ constructor / destructor --------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------
	public:
		explicit vector(const allocator_type &alloc = allocator_type())
		{
			this->myAllocator = alloc;
			this->_vector_pointer = NULL;
			this->_vector_size = 0;
			this->_vector_capacity = 0;
		}
		explicit vector(size_type size, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{
			this->myAllocator = alloc;
			this->_vector_pointer = this->myAllocator.allocate(size); // TBD check size
			this->_vector_size = size;
			this->_vector_capacity = size;
			for (size_t i = 0; i < size; i++)
			{
				this->myAllocator.construct(&_vector_pointer[i], val);
				// this->_vector_pointer[i] = val;
			}
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_t size;
			this->myAllocator = alloc;
			size = distance(first, last);
			this->_vector_capacity = 0;
			this->_vector_size = 0;
			this->_vector_pointer = NULL;
			reserve(size);			
			size_t i = 0;
			while (first != last)
			{
				i++;
				push_back(*first);
				first++;
			}
		}
		vector(const vector &src)
		{
			//*this = src;
			this->myAllocator = src.myAllocator;
			this->_vector_pointer = this->myAllocator.allocate(src.size());
			this->_vector_size = 0;
			this->_vector_capacity = 0;
			this->insert(this->begin(), src.begin(), src.end());
		}
		~vector()
		{
			this->clear();
			this->myAllocator.deallocate(this->_vector_pointer, this->_vector_capacity);
		}

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Iterators -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------
		// Iterator
		iterator begin()
		{
			return (iterator(_vector_pointer));
		}
		
		const_iterator begin() const
		{
			return (const_iterator(_vector_pointer));
		}

		iterator end()
		{
				return (iterator(&this->_vector_pointer[this->_vector_size]));
		}
		const_iterator end() const
		{
			return (const_iterator(&this->_vector_pointer[this->_vector_size]));
		}

		// Reverse Iterator
		reverse_iterator rbegin()
		{
			return (reverse_iterator(&this->_vector_pointer[this->_vector_size]));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(&this->_vector_pointer[this->_vector_size]));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_vector_pointer));

		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_vector_pointer));

		}

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Capacity -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------
	public:
		size_t size() const
		{
			return (this->_vector_size);
		}

		size_type max_size() const
		{
			return (this->myAllocator.max_size());
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw (std::length_error("vector::resize"));
			if (n <= this->_vector_size)
			{
				size_type i = n;
				while (i < this->_vector_size)
				{
					this->myAllocator.destroy(&this->_vector_pointer[i]);
					i++;
				}
				this->_vector_size = n;
			}
			else
			{
				this->insert(this->end(), n - this->_vector_size, val);
			}
		}
		size_type capacity() const
		{
			return (this->_vector_capacity);
		}
		bool empty() const
		{
			return (this->_vector_size == 0);
		}
		void reserve(size_type n)
		{
			if (n > this->max_size())
	    		throw std::length_error("vector::reserve");
			if (n > _vector_capacity)
			{
				if (n > this->max_size())
					std::length_error(__N("vector::reserve"));
				value_type *new_pt_tmp = this->myAllocator.allocate(n);
				if (this->_vector_size > 0)
				{
					for (size_t i = 0; i < this->_vector_size; i++)
					{
						this->myAllocator.construct(&new_pt_tmp[i], this->_vector_pointer[i]);
						this->myAllocator.destroy(&this->_vector_pointer[i]);
					}
					if (this->_vector_pointer) // peut etre inutil car redondant avec test size > 0. Mais a garder au cas ou pour le vecteur est vide
						this->myAllocator.deallocate(this->_vector_pointer, this->_vector_capacity);
				}
				this->_vector_capacity = n;
				this->_vector_pointer = new_pt_tmp;
			}
		}

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Element access -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------
		reference operator[](size_t n)
		{
			return (this->_vector_pointer[n]);
		}
		const_reference operator[] (size_type n) const
		{
			return (this->_vector_pointer[n]);
		}
		reference at(size_type n)
		{
			if (n >= this->size())
				throw(std::out_of_range("out of range"));
			return (this->_vector_pointer[n]);
		}
		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw(std::out_of_range("out of range"));
			return (this->_vector_pointer[n]);
		}
		
		reference front()
		{
			return (*this->begin());
		}
		const_reference front() const
		{
			return (*this->begin());
		}

		reference back()
		{
			return (*(this->end()-1));
		}
		const_reference back() const
		{
			return (*(this->end()-1));
		}

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Modifier -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------
		vector &operator=(const vector &src)
		{
			this->myAllocator = src.myAllocator;
			this->_vector_size = src._vector_size;
			this->_vector_capacity = src._vector_capacity;
			this->_vector_pointer = this->myAllocator.allocate((_vector_capacity) * sizeof(value_type));
			for (size_type i = 0; i < this->_vector_size; i++)
			{
				this->_vector_pointer[i] = src._vector_pointer[i];
			}
			return (*this);
		}

		template <class InputIterator>  
		void assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			InputIterator it;
			size_t size;
			size = 0;
			for (it = first; it != last; it++)
			{
				size++;
			}
			this->reserve(size);
			this->_vector_size = size;
			size_t i = 0;
			for (it = first; it != last; it++)
			{
				this->myAllocator.construct(&this->_vector_pointer[i], *it);
				i++;
			}
		}

		void assign(size_type n, const value_type &val)
		{
			this->reserve(n);
			this->_vector_size = n;
			for (size_t i = 0; i < n; i++)
			{
				this->myAllocator.construct(&this->_vector_pointer[i], val);
			}
		}

		void push_back(const T value)
		{
			if (this->_vector_size + 1 > this->_vector_capacity)
			{
				if (this->_vector_capacity == 0)
					this->reserve(1);
				else
					this->reserve(this->_vector_capacity * 2);
			}
			this->myAllocator.construct(&this->_vector_pointer[this->_vector_size], value);
			this->_vector_size += 1;
		}

		void pop_back()
		{
			if (this->_vector_size > 0)
			{
				this->myAllocator.destroy(&this->_vector_pointer[this->_vector_size]);
				this->_vector_size--;
			}
		}

		iterator insert (iterator position, const value_type& val)
		{
			difference_type insertion_distance = distance (this->begin(), position);
			if (this->_vector_size + 1 > this->_vector_capacity)
			{
				if (this->_vector_capacity == 0)
					this->reserve(1);
				else
					this->reserve(this->_vector_capacity * 2);
			}
			this->_vector_size++;
			iterator it_end = this->end() - 1;
			difference_type i = this->_vector_size - 1;
			while (i != insertion_distance)
			{
				*it_end = *(it_end - 1);
				it_end--;
				i--;
			}
			*it_end = val;
			return (this->begin() + insertion_distance);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			ft::vector<value_type> tmp_vec(n, val);
			this->insert(position, tmp_vec.begin(), tmp_vec.end());
			
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			difference_type insertion_distance = distance(this->begin(), position);
			difference_type insertion_size = distance(first, last);
 			if (insertion_size == 0)
				return;

			if (this->_vector_size + this->distance(first, last) > this->_vector_capacity)
			{
				this->reserve(this->_vector_size + this->distance(first, last));
			}
			this->_vector_size += insertion_size;
			// copie des valeurs apres position, a la fin du vecteur
			iterator it_end = this->end() - 1;
			difference_type i = this->_vector_size - 1;
			while (i != insertion_distance + insertion_size - 1)
			{
				*it_end = *(it_end - insertion_size);
				it_end--;
				i--;
			}
			// insertion des nouvelles valeurs [first, last) a la position
			iterator it = this->begin() + insertion_distance;
			while (first != last)
			{
				*it = *first;
				it++;
				first++;
			}
		}

		iterator erase (iterator position)
		{
			iterator it = position;
			this->myAllocator.destroy(&(*position));
			while (it + 1 != this->end())
			{
				*(it) = *(it + 1); 
				it++;
			}
			this->_vector_size--;
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			while (first != last)
			{
				erase (first);
				last--; // on recule last car indirectement first avance avec la suppression
			}
			return (first);
		}

		void swap (vector& x)
		{
			T *_vector_pointer_tmp = x._vector_pointer;
			size_t _vector_size_tmp = x._vector_size;
			size_t _vector_capacity_tmp = x._vector_capacity;

			x._vector_pointer = this->_vector_pointer;
			x._vector_size = this->_vector_size;
			x._vector_capacity = this->_vector_capacity;

			this->_vector_pointer = _vector_pointer_tmp;
			this->_vector_size = _vector_size_tmp;
			this->_vector_capacity = _vector_capacity_tmp;
		}

		void clear()
		{
			this->resize(0);
		}
	};

// ###########################################################################################################
// #########################################   Fonctions non membres   #######################################
// ###########################################################################################################

// surcharges faites en dehors de la classe car ce sont des fct non membres sur les vectors
	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	//	{
	//		while (first1 != last1)
	//		{
	//			if (*first1 != *first2)
	//				return (false);
	//			++first1;
	//			++first2;
	//		}
	//		return (true);
	//}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}
};
#endif
