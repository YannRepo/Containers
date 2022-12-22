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


		public:
			// constructor / destructor
			vector()
			{
				this->_vector_pointer = NULL;
				this->_vector_size = 0;
				// this->_vector_capacity = 0;

			}
			vector(const vector& src)
			{

			}
			~vector()
			{
				delete this->_vector_pointer;
				this->_vector_pointer = NULL;
			}

			// surcharge operateur
			vector& operator=(const vector& src)
			{
				// TBD
				// this->_vector_size = src._vector_size;
				// for (size_t i = 0; i < this->_vector_size; i++)
				// {
				// 	this->_vector_pointer[i] = src._vector_pointer[i];
				// }
				// this->_vector_pointer = src._vector_pointer;
			}
			T& operator[](size_t i) const
			{
				return (this->_vector_pointer[i]);
			}


			// modifier
			void	assign(iterator first, iterator last)
			{

			}
			void	push_back(const T value)
			{
				T*		previous_vector_pointer = this->_vector_pointer;
				this->_vector_pointer = myAllocator.allocate((_vector_size + 1) * sizeof(T));
				for (size_t i = 0; i < this->_vector_size; i++)
					this->_vector_pointer[i] = previous_vector_pointer[i];
				this->_vector_size += 1;
				(this->_vector_pointer)[_vector_size - 1] = value;
				std::cout << "_vector_pointer:"  << (this->_vector_pointer)[_vector_size - 1] << std::endl;
				delete previous_vector_pointer;
			}
			T	pop_back()
			{
				T	pop_element = this->_vector_pointer[this->_vector_size - 1];
				T*		previous_vector_pointer = this->_vector_pointer;
				this->_vector_pointer = myAllocator.allocate((_vector_size - 1) * sizeof(T));
				for (size_t i = 0; i < this->_vector_size - 1; i++)
					this->_vector_pointer[i] = previous_vector_pointer[i];
				this->_vector_size -= 1;
				delete previous_vector_pointer;
				return (pop_element);
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
			// size_t	_vector_size_allocated;
	};
};

#endif
