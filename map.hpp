#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include <string>


# include "pair.hpp"
# include "red_black_tree.hpp"
# include "red_black_tree_iterator.hpp"
# include "red_black_tree.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"


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
			class value_compare: public std::less<Key> // sup heritage ?
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
			typedef typename tree_type::reverse_iterator									reverse_iterator; 
			typedef typename tree_type::const_reverse_iterator								const_reverse_iterator;				


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
				//this->tree.insert(first, last); // TBD voir si constructeur rbt fait le taff
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
		// TBD remettre en forme

			reverse_iterator rbegin() { return reverse_iterator(tree.rbegin()); }

			const_reverse_iterator  rbegin() const { return const_reverse_iterator(tree.rbegin()); }

			reverse_iterator rend() { return reverse_iterator(tree.rend()); }

			const_reverse_iterator rend() const { return const_reverse_iterator(tree.rend()); }
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
			void erase (iterator first, iterator last)
			{
				this->tree.erase(first, last);
			}
			size_type erase(const key_type& key)
			{
				return (this->tree.erase(key));
			}

			void swap(map& map_to_swap)
			{
				this->tree.swap(map_to_swap.tree);
			}
			void clear()
			{
				this->tree.clear();
			}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
			iterator find (const key_type& key) const
			{
				return (this->tree.find(key));
			}
			//const_iterator find (const key_type& k) const
			//{
			//	return (this->tree.find(key));
			//}
			size_type count (const key_type& k) const
			{
				return (this->tree.count(k));
			}

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

	};

// ###########################################################################################################
// #################################   Fonctions non membres   ###############################################
// ###########################################################################################################
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Swap  --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Comparison operator  --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{
				//std::cout << "ope=1" << std::endl;
		//return (true);
		if (lhs.size() != rhs.size())
			return (false);

		typename map<Key, T, Compare, Alloc>::const_iterator begin_1 = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator begin_2 = rhs.begin();
	
		while (begin_1 != lhs.end())
		{
			if (*begin_1 != *begin_2)
				return (false);
			begin_1++;
			begin_2++;
		}
		//if (begin_2 != rhs.end())
		//	return (false);
		return (true);
	}
			
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc > 
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs) && lhs != rhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
}

#endif
