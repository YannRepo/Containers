#ifndef RED_BLACK_TREE_ITERATOR_HPP
# define RED_BLACK_TREE_ITERATOR_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree.hpp"

namespace ft
{
	template<typename T, typename node_pointer, class Compare = std::less<T> >
	class Rbt_iterator
	{
		typedef T											value_type;

		public: //TBD remettre en protected
			node_pointer	current_node;

	// ###########################################################################################################
	// #########################################   Constructeur / destructeur  #######################################################
	// ###########################################################################################################
		public:
			Rbt_iterator(): current_node(){}
			Rbt_iterator(node_pointer ptr): current_node(ptr){}
			~Rbt_iterator(){}


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

		Rbt_iterator&	operator++() // ++i
		{
			// Si un noeud a droite
				// descendre noeud
				// explorer a gauche jusque pas d'enfant a gauche
			// Sinon
				// remonter jusqu'a ce qu'on vienne d'un left child
				// Si ca n'arrive pas c'est le dernier noeud -> renvoyer Null ?


			if (this->current_node->has_right_child())
			{
				this->current_node = this->current_node->get_right_child();
				while (this->current_node->has_left_child())
				{
					this->current_node = this->current_node->get_left_child();
				}
				return (*this);
			}
			else
			{
				while(this->current_node->has_parent() && this->current_node->is_right_child())
					this->current_node = this->current_node->get_parent();
				if (!this->current_node->has_parent())
				{
					this->current_node = NULL;
					return (*this);
				}
				this->current_node = this->current_node->get_parent();
				return (*this);


			}

			// TBD update
			return (*this);

		}

		Rbt_iterator	operator++(int) // i++
		{
			// pour reutilisation
						Rbt_iterator search_it(this->current_node);
			//if (search_it.current_node->has_right_child())
			//{
			//	search_it.current_node = search_it.current_node->get_right_child();
			//	while (search_it.current_node->has_left_child())
			//	{
			//		search_it.current_node = search_it.current_node->get_left_child();
			//	}
			//	return (search_it);
			//}
			//else
			//{

			//}


		}





	};
}

#endif
