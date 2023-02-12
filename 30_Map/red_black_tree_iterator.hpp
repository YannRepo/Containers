#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree.hpp"


template<typename T, typename node_pointer, class Compare>
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

	private:
// has_right_child
// get_right_child
// has_left_child
// get_left_child
// has_parent
// get_parent

// get_tree_root



// ###########################################################################################################
// #########################################   Fonction membres  #######################################################
// ###########################################################################################################

	Rbt_iterator&	operator++() // ++i
	{
		// Si un noeud a droite
			// descendre noeud
			// explorer a gauche jusque pas d'enfant a gauche
		// Sinon
			// remonter jusqu'a ce qu'on vienne d'un left child
			// Si ca n'arrive pas c'est le dernier noeud -> renvoyer Null ?

		node_pointer search_node;

	}

	Rbt_iterator	operator++(int) // i++
	{

	}





}


#endif
