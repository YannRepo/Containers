#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>
#include <memory>


namespace ft
{
	template<typename T,typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef value_type*								pointer;
			// typedef std::ptrdiff_t							difference_type;
			// typedef value_type&								reference;
			// typedef	const value_type&						const_reference;
			// typedef Allocator::pointer						pointer;
			// typedef Allocator::const_pointer				const_pointer;
			// //typedef iterator
			// //typedef const_iterator
			// typedef std::reverse_iterator<iterator>			reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

// ###########################################################################################################
// #########################################   ITERATOR   ####################################################
// ###########################################################################################################
		public:
			class iterator
			{
				//typedef T*									pointer;

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
						//this->_size = src._size;
						return (*this);
					}
					bool operator==(const iterator& src)
					{
						return (this->_pointer == src._pointer);
					}
					bool operator!=(const iterator& src)
					{
						return (this->_pointer != src._pointer);
					}
					value_type& operator*(void)
					{
						return (*this->_pointer);
					}
					//value_type& operator*(const iterator& src)
					//{
					//	return (*this->_pointer);
					//}
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
						//iterator it_copy = *this;
						//this->_pointer++;
						//return (it_copy);
						this->_pointer++;
						return (*this);
					}
					iterator& operator--()
					{
						this->_pointer--;
						return(*this);
					}
					iterator& operator--(int)
					{
						iterator it_copy = *this;
						this->_pointer--;
						return (it_copy);
					}
					// + - ?


				public: // public pour debug TBD
					pointer		_pointer;
					//int	_size; // TBD a sup

			};

// ###########################################################################################################
// #########################################   UTILS   #######################################################
// ###########################################################################################################
		public: // publiv pour debug, repasser en private TBD
			void	check_vector_capacity_and_allocate_and_copy(size_type size)
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
					value_type* previous_vector = this->_vector_pointer;
					this->_vector_pointer = this->myAllocator.allocate((size) * sizeof(value_type));
					copy_vector(previous_capacity, previous_vector, this->_vector_pointer);
					delete this->_vector_pointer;
				}
			}
			void	copy_vector(size_type len_to_copy, value_type* src,  value_type* dest)
			{
				for(size_type i = 0; i < len_to_copy; i++)
				{
					dest[i] = src[i];
				}
			}

// ###########################################################################################################
// #########################################   VECTOR   ######################################################
// ###########################################################################################################
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ constructor / destructor --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		public:
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				this->myAllocator = alloc;
				this->_vector_pointer = NULL;
				this->_vector_size = 0;
				this->_vector_capacity = 0;


			}
			explicit vector (size_type size, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->myAllocator = alloc;
				this->_vector_pointer = this->myAllocator.allocate((size) * sizeof(value_type));
				this->_vector_size = size;
				this->_vector_capacity = size;
				for(size_t i = 0; i < size; i++)
				{
					this->myAllocator.construct(&_vector_pointer[i], val);
					//this->_vector_pointer[i] = val;
				}
			}
			// TBD
			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			// {
				// faire fct difference entre 2 iterateur (fct distance dans iterator)
			// 	std::cout << "prout2" << std::endl;

			// 	// TBD
			// }
			vector(const vector& src)
			{
				*this = src;
			}
			~vector()
			{
				std::cout << "destructor" << std::endl;
				delete this->_vector_pointer;
				// this->_vector_pointer = NULL;
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------------ Iterators -------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		iterator begin()
		{
			return(iterator(&this->_vector_pointer[0]));
		}
		iterator end()
		{
			//iterator ite = iterator(&this->_vector_pointer[0]);
			//iterator::advance(&ite, this->_vector_size);
			//return(ite);
			return (&this->_vector_pointer[this->_vector_size]);
		}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------------ Capacity -------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		public:
		size_t size()
		{
			return (this->_vector_size);
		}
		
		size_type max_size() const
		{
			return(this->myAllocator.max_size());
		}


		//resize(size_type n, value_type val = value_type())
		//{

		//}

		void reserve (size_type n)
		{
			if(n > _vector_capacity)
			{
				value_type* new_pt_tmp = this->myAllocator.allocate((n) * sizeof(value_type));
				for (size_t i = 0; i < this->_vector_size; i++)
				{
					this->myAllocator.construct(&new_pt_tmp[i], this->_vector_pointer[i]);
					this->myAllocator.destroy(&this->_vector_pointer[i]);
				}
				this->myAllocator.deallocate(this->_vector_pointer, this->_vector_capacity );
				this->_vector_capacity = n;
				this->_vector_pointer = new_pt_tmp;
			}
		}

		// --- TBD
		//max_size
		//resize
		//capacity
		//empty
		//reserve
		//shrink_to_fit-- (pas a faire car c++11)

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------------ Modifier -------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------



			// surcharge operateur
			vector& operator=(const vector& src)
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
			}
			T& operator[](size_t i) const
			{
				return (this->_vector_pointer[i]);
			}


			// modifier
			void	assign(iterator first, iterator last)
			{
				
				//TBD
			}
			void	push_back(const T value)
			{
				//T*		previous_vector_pointer = this->_vector_pointer;
				if (this->_vector_size + 1 > this->_vector_capacity)
				{
					this->reserve(this->_vector_capacity * 2);
				}
				this->myAllocator.construct(&this->_vector_pointer[this->_vector_size], value);
				this->_vector_size += 1;

				//this->_vector_pointer = myAllocator.allocate((_vector_size + 1) * sizeof(T));
				//for (size_t i = 0; i < this->_vector_size; i++)
				//	this->_vector_pointer[i] = previous_vector_pointer[i];
				//(this->_vector_pointer)[_vector_size - 1] = value;
				//std::cout << "_vector_pointer:"  << (this->_vector_pointer)[_vector_size - 1] << std::endl;
				//this->myAllocator.destroy(&previous_vector_pointer);
			}
			void	pop_back()
			{
				if (this->_vector_size > 0)
				{
					this->myAllocator.destroy(&this->_vector_pointer[this->_vector_size]);
					this->_vector_size--;
				}
				//T	pop_element = this->_vector_pointer[this->_vector_size - 1];
				//T*		previous_vector_pointer = this->_vector_pointer;
				//this->_vector_pointer = myAllocator.allocate((_vector_size - 1) * sizeof(T));
				//for (size_t i = 0; i < this->_vector_size - 1; i++)
				//	this->_vector_pointer[i] = previous_vector_pointer[i];
				//this->_vector_size -= 1;
				//delete previous_vector_pointer;
				//return (pop_element);
			}
			// insert	Insert elements (public member function)
			// erase	Erase elements (public member function)
			// swap	Swap content (public member function)
			// clear	Clear content (public member function)
			// emplace	Construct and insert element (public member function)
			// emplace_back

		public: // public pour debug TBD repasser en private
			Allocator myAllocator;

			T*		_vector_pointer;
			size_t	_vector_size;
			size_t	_vector_capacity;
	};

	// surcharge affichage // TBD check cas erreur sur class
	// template<typename T>
	// const

};


#endif
