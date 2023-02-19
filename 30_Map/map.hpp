#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree.hpp"
# include "red_black_tree_iterator.hpp"



namespace ft
{
	template <typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map
	{
// ###########################################################################################################
// #############################   typedef, class value_compare, attributs   #################################
// ###########################################################################################################
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef pair<const key_type,mapped_type>		value_type;
			typedef Compare 								key_compare;

			typedef Allocator								allocator_type;
			typedef value_type								&reference;

			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			
			typedef std::ptrdiff_t							difference_type;
			typedef size_t									size_type;

		public:
			class value_compare: public std::binary_function<value_type, value_type, bool>
			{
				// pour que map puisse utiliser les elements protected de cette classe
				friend class map<key_type, mapped_type, key_compare, allocator_type>;

				protected:
					Compare comp;
				protected:
					value_compare(Compare c): comp(c){}
				public:
					bool operator()(const value_type& lhs, const value_type& rhs) const
					{
						return (comp(lhs.first, rhs.first));
					}
					bool operator()(const key_type& lhs, const key_type& rhs) const
					{
						return (comp(lhs, rhs));
					}
					// TBD a voir si c'est utile
					//bool operator()(const key_type& lhs, const value_type& rhs) const
					//{ 
					//	return comp(lhs, rhs.first); 
					//}
					//bool operator()(const value_type& lhs, const key_type& rhs) const
					//{ 
					//	return comp(lhs.first, rhs); 
					//}
			};

		public:
			typedef typename ft::Red_black_tree< key_type, value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator														iterator;								
			//typedef	const_iterator							
			//typedef reverse_iterator						
			//typedef const_reverse_iterator					


		public: // pour debug TBD remettre en protected a la fin
			tree_type tree;
		

// ###########################################################################################################
// #########################################   Utils  #######################################################
// ###########################################################################################################
		public: //TBD repasser en protected
			void print()
			{
				this->tree.print();
			}


// ###########################################################################################################
// #################################   Fonctions membres   ##########################################
// ###########################################################################################################
		public:
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ constructor / destructor --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			tree(tree_type(comp, alloc)){}

			template< class InputIterator >
			map( InputIterator first, InputIterator last, const key_compare& comp = Compare(), const allocator_type& alloc = Allocator())
			{
				// TBD avec insert par iterator
			}

	 		map(const map& other)
			{
				// TBD avec insert par iterator

			}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ operator= / get allcoator--------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Element access --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Iterators --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Capacity --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Modifiers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				return(this->tree.insert(value));
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			iterator find (const key_type& key)
			{
				return (this->tree.find(key));
			}
			//const_iterator find (const key_type& k) const
			//{
			//	return (this->tree.find(key));
			//}
			size_type erase(const key_type& key)
			{
				return (this->tree.erase(key));
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Observers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------


// ###########################################################################################################
// #################################   Fonctions membres   ###################################################
// ###########################################################################################################

	};

// ###########################################################################################################
// #################################   Fonctions non membres   ###############################################
// ###########################################################################################################

}

#endif
