#ifndef RED_BLACK_TREE_ITERATOR_HPP
# define RED_BLACK_TREE_ITERATOR_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template<typename T, typename node_pointer, class Compare>
	class Rbt_iterator
	{
		private:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	iterator;
		public:
			typedef T											value_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef typename iterator::difference_type			difference_type;
			typedef typename iterator::pointer					pointer;
			typedef typename iterator::reference				reference;

		public: //TBD remettre en protected
			node_pointer	current_node;

	// ###########################################################################################################
	// #########################################   Constructeur / destructeur  #######################################################
	// ###########################################################################################################
		public:
			Rbt_iterator(): current_node(){}
			Rbt_iterator(node_pointer ptr): current_node(ptr){}
			~Rbt_iterator(){}

			operator Rbt_iterator<const T, node_pointer, Compare>() const 
			{
				return Rbt_iterator<const T, node_pointer, Compare>(current_node);
			}

	// ###########################################################################################################
	// #########################################   Tools  #######################################################
	// ###########################################################################################################
	// TBD


	// ###########################################################################################################
	// #########################################   Fonction membres  #######################################################
	// ###########################################################################################################
		node_pointer base()
		{
			return (this->current_node);
		}

		Rbt_iterator& operator=(const Rbt_iterator& rhs)
		{
			this->current_node = rhs.current_node;
			return (*this);
		}

		Rbt_iterator& operator++() // ++i
		{
			// Si un noeud a droite
				// descendre noeud
				// explorer a gauche jusque pas d'enfant a gauche
			// Sinon
				// remonter jusqu'a ce qu'on vienne d'un left child
				// Si ca n'arrive pas c'est le dernier noeud -> renvoyer Null ?


			if (this->current_node->has_right_child())
			{
				this->current_node = this->current_node->right;
				while (this->current_node->has_left_child())
				{
					this->current_node = this->current_node->left;
				}
				return (*this);
			}
			else
			{
				while(this->current_node->has_parent() && this->current_node->is_right_child())
					this->current_node = this->current_node->parent;
				if (!this->current_node->has_parent())
				{
					this->current_node = NULL; // TBD check return
					return (*this);
				}
				this->current_node = this->current_node->parent;
				return (*this);
			}
		}

		Rbt_iterator operator++(int) // i++
		{
			Rbt_iterator it_copy = *this;
			++(*this);
			return(it_copy);
		}

		Rbt_iterator& operator--() // --i
		{
			// Si un noeud a gauche
				// descendre noeud
				// explorer a droite jusque pas d'enfant a droite
			// Sinon
				// remonter jusqu'a ce qu'on vienne d'un right child
				// Si ca n'arrive pas c'est le premier noeud -> renvoyer Null ?

			if (this->current_node->has_left_child())
			{
				this->current_node = this->current_node->left;
				while (this->current_node->has_right_child())
				{
					this->current_node = this->current_node->right;
				}
				return (*this);
			}
			else
			{
				while(this->current_node->has_parent() && this->current_node->is_left_child())
					this->current_node = this->current_node->parent;
				if (!this->current_node->has_parent())
				{
					this->current_node = NULL; // TBD check return
					return (*this);
				}
				this->current_node = this->current_node->parent;
				return (*this);
			}
		}
		Rbt_iterator operator--(int) // i--
		{
			Rbt_iterator it_copy = *this;
			--(*this);
			return(it_copy);
		}

		reference operator*() const
		{
			return (this->current_node->value);
		}

		pointer operator->() const
		{
			return (&(this->current_node->value));
		}

		bool operator==(const Rbt_iterator& rhs) const
		{
			return (this->current_node == rhs.current_node);
		}

		bool operator!=(const Rbt_iterator& rhs) const
		{
			return (this->current_node != rhs.current_node);
		}

	};
}

#endif
