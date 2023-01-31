#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <memory>

// TBD voir comment interdire les modf de variable sur des *const_iterator
namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef std::size_t									size_type;
		typedef value_type									*pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef value_type&									reference;
		typedef	const value_type&							const_reference;
		// typedef Allocator::pointer						pointer;
		// typedef Allocator::const_pointer				const_pointer;
		// //typedef iterator
		// //typedef const_iterator
		// typedef std::reverse_iterator<iterator>			reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		// typedef typename std::vector<T>::iterator			iterator;
		// typedef typename std::vector<T>::const_iterator		const_iterator;

	// ###########################################################################################################
	// #########################################   ITERATOR   ####################################################
	// ###########################################################################################################
		class iterator
		{
			// TBD check type def
			// typedef const T*									const_pointer;
			typedef T value_type;
			typedef T *pointer;

			// ligne MI
			// operator iterator<value_type const>()const{return iterator<value_type const>(_pointer);}

			// public:
			// typedef int								difference_type
		public:
			// constructor / detructor
			iterator()
			{
				this->_pointer = NULL;
				// this->_size = 0;
			}
			iterator(pointer vector_pt)
			{
				this->_pointer = vector_pt;
			}
			iterator(const iterator &src)
			{
				this->_pointer = src._pointer;
			}
			~iterator() {}

			// // functions
			void advance(iterator &it, int n)
			{
				it._pointer += n;
			}
			// fct distance dans les utils
			//difference_type distance(iterator first, iterator last)
			//{
			//	return (last._pointer - first._pointer);
			//}
			iterator prev(iterator first, int n)
			{
				return (iterator(*this)--);
			}
			iterator next(iterator first, int n)
			{
				return (iterator(*this)++);
			}

			// // operator overload
			iterator &operator=(const iterator &src)
			{
				this->_pointer = src._pointer;
				// this->_size = src._size;
				return (*this);
			}
			bool operator==(const iterator &src)
			{
				return (this->_pointer == src._pointer);
			}
			bool operator!=(const iterator &src)
			{
				return (this->_pointer != src._pointer);
			}
			value_type &operator*(void) const
			{
				return (*this->_pointer);
			}
			// value_type& operator*(const iterator& src)
			//{
			//	return (*this->_pointer);
			// }
			//  bool operator*=(const iterator* src)
			//  {
			//  	return (this._pointer* == src._pointer*);
			//  }
			//  bool operator*!=(const iterator* src)
			//  {
			//  	return (this._pointer* != src._pointer*)
			//  }
			//  iterator& operator->(const iterator& src)
			//  {
			//  	// TBD
			//  }
			//*a = t
			//*a++
			iterator &operator++()
			{
				this->_pointer++;
				return (*this);
			}
			iterator &operator++(int)
			{
				// iterator it_copy = *this;
				// this->_pointer++;
				// return (it_copy);
				this->_pointer++;
				return (*this);
			}
			iterator &operator--()
			{
				this->_pointer--;
				return (*this);
			}
			iterator &operator--(int)
			{
				iterator it_copy = *this;
				this->_pointer--;
				return (it_copy);
			}
			iterator &operator+(int n)
			{
				// TBD voir si il faut ajouter un check sur la taille du vector
				advance(*this, n);
				return (*this);
			}
			iterator &operator-(int n)
			{
				// TBD voir si il faut ajouter un check a 0
				advance(*this, -n);
				return (*this);
			}
			// + - ?

		public: // public pour debug TBD
			pointer _pointer;
			// int	_size; // TBD a sup
		};

		class const_iterator : public ft::vector<T>::iterator
		{
		public:
			// constructor / detructor
			const_iterator()
			{
				this->_pointer = NULL;
				// this->_size = 0;
			}
			const_iterator(pointer vector_pt)
			{
				this->_pointer = vector_pt;
			}
			const_iterator(const iterator &src)
			{
				this->_pointer = src._pointer;
			}
			// TBD destruct ?
			~const_iterator() {}
			// surcharge operateur * pour return const
			const value_type &operator*(void) const
			{
				return (*this->_pointer);
			}
		};

	public:
		// typedef iterator const				const_iterator;

		//		//typedef iterator				iterator;

	// ###########################################################################################################
	// #########################################   UTILS   #######################################################
	// ###########################################################################################################
	public: // publiv pour debug, repasser en private TBD
		void check_vector_capacity_and_allocate_and_copy(size_type size)
		{
			if (size <= this->_vector_capacity)
			{
				return;
			}
			else
			{
				size_type previous_capacity = _vector_capacity;
				if (_vector_capacity == 0)
					_vector_capacity = 1;
				else
					_vector_capacity *= 2;
				value_type *previous_vector = this->_vector_pointer;
				this->_vector_pointer = this->myAllocator.allocate((size) * sizeof(value_type));
				copy_vector(previous_capacity, previous_vector, this->_vector_pointer);
				delete this->_vector_pointer;
			}
		}
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
	// #########################################   VECTOR   ######################################################
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
			this->_vector_pointer = this->myAllocator.allocate((size) * sizeof(value_type));
			this->_vector_size = size;
			this->_vector_capacity = size;
			for (size_t i = 0; i < size; i++)
			{
				this->myAllocator.construct(&_vector_pointer[i], val);
				// this->_vector_pointer[i] = val;
			}
		}
		// TBD
		//template <class InputIterator>
		vector (iterator first, iterator last, const allocator_type& alloc = allocator_type())
		 {
			size_t size;
			this->myAllocator = alloc;
			size = distance(first, last);
			this->_vector_capacity = 0;
			this->_vector_size = 0;
			this->_vector_pointer = NULL;
			reserve(size);			
			//this->_vector_size = 0;
			//this->_vector_capacity = size;

			//InputIterator it = first;
			//while (it != last)
			//{
			//	this->_vector_size++;
			//}


			//it = first;
			size_t i = 0;
			while (first != last)
			{
				i++;
				//this->myAllocator.construct(&this->_vector_pointer[i], *first);

				push_back(*first);
				first++;
			}


		 	// TBD
		 }
		vector(const vector &src)
		{
			*this = src;
		}
		~vector()
		{
			delete this->_vector_pointer;
			// this->_vector_pointer = NULL;
		}

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Iterators -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------
		iterator begin()
		{
			return (iterator(&this->_vector_pointer[0]));
		}
		// TBD check si on laisse des const partout
		const_iterator begin() const
		{
			return (const_iterator(&this->_vector_pointer[0]));
		}

		iterator end()
		{
			// iterator ite = iterator(&this->_vector_pointer[0]);
			// iterator::advance(&ite, this->_vector_size);
			// return(ite);
			return (iterator(&this->_vector_pointer[this->_vector_size]));
		}
		const_iterator end() const
		{
			return (const_iterator(&this->_vector_pointer[this->_vector_size]));
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

		// resize(size_type n, value_type val = value_type())
		//{

		//}
		size_type capacity() const
		{
			return (this->_vector_capacity);
		}
		void reserve(size_type n) // TBD a revoir car met des 0 en trop dans test de constructor range ?
		{
			if (n > _vector_capacity)
			{
				value_type *new_pt_tmp = this->myAllocator.allocate((n) * sizeof(value_type));
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

		// --- TBD
		// max_size
		// resize
		// capacity
		// empty
		// reserve
		// X shrink_to_fit-- (pas a faire car c++11)

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
		// TBD changer check ppour prendre >0 (faire fct in range)
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

		//--- TBD
		//*operator[]
		// *at
		// front
		// back
		// X data (pas a faire)

		// -----------------------------------------------------------------------------------------------------------
		// ------------------------------------------ Modifier -------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------

		// surcharge operateur
		vector &operator=(const vector &src)
		{
			// TBD check fct
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

		void assign(iterator first, iterator last)
		{
			iterator it;
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
			// T*		previous_vector_pointer = this->_vector_pointer;
			if (this->_vector_size + 1 > this->_vector_capacity)
			{
				this->reserve(this->_vector_capacity * 2);
			}
			this->myAllocator.construct(&this->_vector_pointer[this->_vector_size], value);
			this->_vector_size += 1;

			// this->_vector_pointer = myAllocator.allocate((_vector_size + 1) * sizeof(T));
			// for (size_t i = 0; i < this->_vector_size; i++)
			//	this->_vector_pointer[i] = previous_vector_pointer[i];
			//(this->_vector_pointer)[_vector_size - 1] = value;
			// std::cout << "_vector_pointer:"  << (this->_vector_pointer)[_vector_size - 1] << std::endl;
			// this->myAllocator.destroy(&previous_vector_pointer);
		}
		void pop_back()
		{
			if (this->_vector_size > 0)
			{
				this->myAllocator.destroy(&this->_vector_pointer[this->_vector_size]);
				this->_vector_size--;
			}
			// T	pop_element = this->_vector_pointer[this->_vector_size - 1];
			// T*		previous_vector_pointer = this->_vector_pointer;
			// this->_vector_pointer = myAllocator.allocate((_vector_size - 1) * sizeof(T));
			// for (size_t i = 0; i < this->_vector_size - 1; i++)
			//	this->_vector_pointer[i] = previous_vector_pointer[i];
			// this->_vector_size -= 1;
			// delete previous_vector_pointer;
			// return (pop_element);
		}
		// insert	Insert elements (public member function)
		// erase	Erase elements (public member function)
		// swap	Swap content (public member function)
		// clear	Clear content (public member function)
		// emplace	Construct and insert element (public member function)
		// emplace_back

	public: // public pour debug TBD repasser en private
		Allocator myAllocator;

		T *_vector_pointer;
		size_t _vector_size;
		size_t _vector_capacity;
	};

	// surcharge affichage // TBD check cas erreur sur class
	// template<typename T>
	// const

};

#endif
