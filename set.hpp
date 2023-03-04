#ifndef SET_HPP
# define SET_HPP

# include "map.hpp"
# include "pair.hpp"
# include "red_black_tree_set.hpp"
# include "red_black_tree_iterator.hpp"
# include "red_black_tree.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"

namespace ft
{

	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
// ###########################################################################################################
// #############################   typedef, class value_compare, attributs   #################################
// ###########################################################################################################
	public:
		typedef Key																						key_type;
		typedef Key																						value_type;

		typedef Compare																					key_compare;
		typedef Compare																					value_compare;
		typedef Allocator																				allocator_type;

		typedef typename ft::Red_black_tree_set<key_type, value_type, key_compare, allocator_type>		tree_type;

		typedef value_type																				&reference;
		typedef const value_type																		&const_reference;

		typedef typename tree_type::const_iterator														iterator;
		typedef typename tree_type::const_iterator														const_iterator;
		typedef typename tree_type::const_reverse_iterator												reverse_iterator;
		typedef typename tree_type::const_reverse_iterator												const_reverse_iterator;

		typedef typename tree_type::size_type															size_type;
		typedef std::ptrdiff_t																			difference_type;

		typedef value_type																				*pointer;

		typedef const value_type																		*const_pointer;

	protected:
		tree_type tree;

// ###########################################################################################################
// #################################   Fonctions membres   ###################################################
// ###########################################################################################################
	public:
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ constructor / destructor ---------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		explicit set(const Compare &comp = Compare(), const Allocator &alloc = Allocator()):
		tree(comp, alloc)
		{
		}

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()):
		tree(comp, alloc)
		{
			tree.insert(first, last); //TBD voir si utile
		}

		set(const set<Key, Compare, Allocator> &x):
		tree(x.begin(), x.end(), x.value_comp(), x.tree.get_allocator())
		{
		}

		~set()
		{
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ operator= ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		set<Key, Compare, Allocator> &operator=(const set<Key, Compare, Allocator> &x)
		{
			if (this == &x)
				return *this;
			clear();
			insert(x.begin(), x.end());
			return (*this);
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Iterators ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

		iterator begin()
		{
			return tree.begin();
		}
		const_iterator begin() const
		{
			return tree.begin();
		}
		iterator end()
		{
			return tree.end();
		}
		const_iterator end() const
		{
			return tree.end();
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(tree.rbegin());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(tree.rbegin());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(tree.rend());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(tree.rend());
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Capacity -------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		bool empty() const
		{
			return tree.empty();
		}
		size_type size() const
		{
			return tree.size();
		}
		size_type max_size() const
		{
			return tree.max_size();
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Modifiers ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		pair<iterator, bool> insert(const value_type &x)
		{
			return tree.insert(x);
		}

		iterator insert(iterator position, const value_type &x)
		{
			(void)position;
			insert(x);
			iterator Found = begin();
			while (begin() != end())
			{
				if (*Found == x)
					break;
				Found++;
			}
			return (Found);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			tree.insert(first, last);
		}

		size_type erase(const value_type &x)
		{
			return tree.erase(x);
		}

		void erase(iterator position)
		{
			const value_type &found = *position;
			tree.erase(found);
		}

		void erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
			{
				this->clear();
				return;
			}
			else
			{
				while (first != last)
				{
					erase(*first++);
				}
			}
			return;
		}

		void swap(set<Key, Compare, Allocator> &x)
		{
			tree.swap(x.tree);
		}

		void clear()
		{
			if (size())
				tree.clear();
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Observers ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare();
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

		iterator find(const key_type &x)
		{
			return (tree.find(x));
		}

		const_iterator find(const key_type &x) const
		{
			return (tree.find(x));
		}

		size_type count(const key_type &x) const
		{
			return (tree.count(x));
		}

		iterator lower_bound(const key_type &x)
		{
			return (tree.lower_bound(x));
		}

		const_iterator lower_bound(const key_type &x) const
		{
			return (tree.lower_bound(x));
		}

		iterator upper_bound(const key_type &x)
		{
			return (tree.upper_bound(x));
		}

		const_iterator upper_bound(const key_type &x) const
		{
			return (tree.upper_bound(x));
		}

		pair<iterator, iterator> equal_range(const key_type &x)
		{
			return (tree.equal_range(x));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &x) const
		{
			return (tree.equal_range(x));
		}

		template <class _T, class _Compare, class _Allocator>
		friend bool operator==(const set<_T, _Compare, _Allocator> &lhs, const set<_T, _Compare, _Allocator> &rhs);

		template <class _T, class _Compare, class _Allocator>
		friend bool operator<(const set<_T, _Compare, _Allocator> &lhs, const set<_T, _Compare, _Allocator> &rhs);

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		allocator_type get_allocator() const
		{
			return allocator_type();
		}
	
	};

// ###########################################################################################################
// #################################   Fonctions non membres   ###############################################
// ###########################################################################################################
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Swap  ----------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
	template <class Key, class Compare, class Allocator>
	void swap(set<Key, Compare, Allocator> &x, set<Key, Compare, Allocator> &y)
	{
		x.swap(y);
	}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Comparison operator  -------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return (x.tree == y.tree);
	}

	template <class Key, class Compare, class Allocator>
	bool operator<(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return (x.tree < y.tree);
	}

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return not(x == y);
	}

	template <class Key, class Compare, class Allocator>
	bool operator>(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return (y < x);
	}

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return not(x < y);
	}

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key, Compare, Allocator> &x, const set<Key, Compare, Allocator> &y)
	{
		return not(y < x);
	}


}
#endif
