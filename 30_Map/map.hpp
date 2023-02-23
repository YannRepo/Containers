#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include <string>


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
			typedef ft::pair<const key_type,mapped_type>	value_type;
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
			typedef typename tree_type::const_iterator													const_iterator;
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
			map( InputIterator first, InputIterator last, const key_compare& comp = Compare(), const allocator_type& alloc = Allocator()):
			tree(first, last, value_compare(comp), alloc)
			{
				//this->tree.insert(first, last); TBD voir si constructeur rbt fait le taff
			}

			//Constructeur par copie
	 		map(const map<Key, T, Compare, allocator_type>& other): // TBD voir si ok suppression <>
			tree(other.begin(), other.end(), value_compare(other.value_comp()), other.tree.get_allocator())
			//tree(other.begin(), other.end(), value_compare(other.value_comp()), other.get_allocator())
			{
				// TBD avec insert par iterator

			}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ operator= --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			map& operator= (const map& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->tree.clear();
				insert(rhs.begin(), rhs.end());
				return(*this);
			}

	
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Element access --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Iterators --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			iterator begin()
			{
				//return (this->tree.tree_begin);// TBD check si updade ok
				return (this->tree.begin());

			}
			const_iterator begin() const
			{
				//return (this->tree.tree_begin); // TBD check si updade ok
				return (this->tree.begin());

			}
			iterator end() // update avec fct end() de tree
			{
				return (this->tree.tree_end);
			}
			const_iterator end() const
			{
				return (this->tree.tree_end);
			}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Capacity --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			bool empty() const
			{
				return (this->tree.empty());
			}
			size_type size() const
			{
				return (this->tree.size());
			}
			size_type max_size() const
			{
				return (this->tree.max_size());
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Element access --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			mapped_type& operator[] (const key_type& k)
			{
				return ((this->tree.insert(ft::make_pair(k, mapped_type())).first)->second);
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Modifiers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				return(this->tree.insert(val));
			}
			iterator insert (iterator position, const value_type& val)
			{
				return(this->tree.insert(position, val));
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				this->tree.insert(first, last);
			}

			void erase (iterator position)
			{
				this->tree.erase(position);
			}
			size_type erase(const key_type& key)
			{
				return (this->tree.erase(key));
			}
			//void erase (iterator first, iterator last)
			//{
			//	this->tree.erase(first, last);
			//}
			void erase (iterator first, iterator last)
			{
				if (first == begin() && last == end())
					{
						this->tree.clear();
						return ;
					}
				while (first != last)
				{
					this->tree.erase(first++);
					//first++; //pas incrementer apres sinon le first n'est plus valide
				}
			}

			void clear()
			{
				this->tree.clear();
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


			iterator lower_bound (const key_type& k)
			{
				return(this->tree.lower_bound(k));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return(this->tree.lower_bound(k));
			}
			iterator upper_bound (const key_type& k)
			{
				return(this->tree.upper_bound(k));
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return(this->tree.upper_bound(k));
			}
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (this->tree.equal_range(k));
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (this->tree.equal_range(k));
			}


// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Observers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			key_compare key_comp() const
			{
				return (key_compare());
			}
			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Allocator --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			allocator_type get_allocator() const
			{
				//return (allocator_type()); // TBD check ancienn version
				return value_compare(tree.key_comp());

			}

// ###########################################################################################################
// #################################   Fonctions membres   ###################################################
// ###########################################################################################################

	};

// ###########################################################################################################
// #################################   Fonctions non membres   ###############################################
// ###########################################################################################################

}

#endif
