#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"

# define BLACK 0
# define RED 1

namespace ft
{

	template <typename Key, typename Val , class Compare = std::less<Key>, class Allocator = std::allocator<Val> >
	class Red_black_tree
	{
// ###########################################################################################################
// #########################################   typedef, class Node, attributs   #######################################################
// ###########################################################################################################

		public:// public pour debug, repasser en private
			template <typename K, typename V>
			struct Node;

		public:
			typedef Key								key_type;
			typedef Val								mapped_type;
			typedef Allocator						allocator_type;

			public:// public pour debug, repasser en private
			typedef Node<Key, Val>						node;
			typedef Node<Key, Val>*						node_pointer;

		public: // public pour debug, repasser en private
			template <typename K, typename V>
			struct Node
			{
				K					key;
				V					value;
				node_pointer		left;
				node_pointer		right;
				node_pointer		parent;
				int					color;

				Node(): value(mapped_type()), left(NULL), right(NULL), parent(NULL), color(RED){}
				Node(key_type key_, mapped_type value_): key (key_), value(value_), left(NULL), right(NULL), parent(NULL), color(RED){}
				
				bool has_right_child()
				{
					if (this->right)
						return (true);
					return (false);
				}
				node_pointer get_right_child()
				{
					return (this->right);
				}
				bool has_left_child()
				{
					if (this->left)
						return (true);
					return (false);
				}
				node_pointer get_left_child()
				{
					return (this->left);
				}
				bool has_parent()
				{
					if (this->parent)
						return (true);
					return (false);
				}
				node_pointer get_parent()
				{
					return (this->parent);
				}
				bool is_left_child() // return false si pas de parent
				{
					if (!this->has_parent())
						return (false);
					if (this == this->get_parent()->get_left_child())
						return (true);
					return (false);
				}
				bool is_right_child() // return false si pas de parent
				{
					if (!this->has_parent())
						return (false);
					if (this == this->get_parent()->get_right_child())
						return (true);
					return (false);
				}

	// get_tree_root

			};

		// TBD check si ca corrige pb
		//-- Create a new type of allocator that is bound to the 'Node' type and uses the same 
		//   memory ressource as the original 'allocator_type'.
		typedef typename Allocator::template rebind<Node<Key, Val> >::other   node_allocator;

		public: // public pour debug, repasser en private
			node_pointer	tree_head;
			node_pointer	tree_end;
			node_allocator	myAllocator;
			Compare			mycompare;
		
// ###########################################################################################################
// #########################################   Constructeur / destructeur  #######################################################
// ###########################################################################################################

	Red_black_tree(const Compare& comp = Compare(), const allocator_type &alloc = allocator_type()):
	tree_head(NULL), myAllocator(alloc), mycompare(comp)
	{
		this->tree_head = myAllocator.allocate(1);
		this->myAllocator.construct(this->tree_head, node(666, 777)); // 666 et 777 valeurs random pour debug du noeud fantome
		this->tree_end = tree_head;
		this->tree_head->parent = tree_head; // ref sur lui-meme au depart;

	}

// ###########################################################################################################
// #########################################   Tools   #######################################################
// ###########################################################################################################
	private:
		void update_end(node_pointer last_elemement)
		{
			if (this->tree_end->parent->right == this->tree_end)
				this->tree_end->parent->right = NULL;
			this->tree_end->parent = last_elemement;
			last_elemement->right = this->tree_end;
			//// TBD
			//node_pointer search_ptr;
			//search_ptr = this->tree_head;
			//while ()
		}

// ###########################################################################################################
// #########################################   Fonctions membres   #######################################################
// ###########################################################################################################
	
	public: // TBD voir les fct a repasser en private
		node_pointer get_tree_head() // voir si cette fct est utile 
		{
			return (this->tree_head);
		}
		void insert_node(pair<key_type, mapped_type> added_pair)
		{
			if (this->tree_head == this->tree_end)
			{
				//this->myAllocator.construct(tree_head, node());
				node_pointer new_node = this->myAllocator.allocate(1);
				this->myAllocator.construct(new_node, node(added_pair.first, added_pair.second)); // TBD check construction
				this->tree_head = new_node;
				update_end(new_node);
			}
			else
				insert_node_algo(this->tree_head, added_pair);
		}
		void insert_node_algo(node_pointer insert_position, pair<key_type, mapped_type> added_pair)
		{	
			if (mycompare(added_pair.first, insert_position->value) == mycompare(insert_position->value, added_pair.first))
			{
				std::cout << "ERROR: cle identique lors de l'insertion" << std::endl;
				return;
			}
			// insertion a gauche
			else if (mycompare(added_pair.first, insert_position->key))
			{
				if (insert_position->left)
					insert_node_algo(insert_position->left, added_pair);
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, node(added_pair.first, added_pair.second));
					new_node->parent = insert_position;
					insert_position->left = new_node;

				}
				return;
			}
			// insertion a droite
			else if (mycompare(insert_position->key, added_pair.first))
			{
				if (insert_position->right and insert_position->right != this->tree_end)
					insert_node_algo(insert_position->right, added_pair);
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, node(added_pair.first, added_pair.second));
					new_node->parent = insert_position;
					insert_position->right = new_node;
					if (this->tree_end->parent == new_node->parent) // update end si on ajoute sous l'element final (a droite)
						update_end(new_node);

				}
				return;
			}
			std::cout << "DEBUG ERROR : cas inconnnu : cette ligne ne devrait pas etre executee " << std::endl;
		}

		void print()
		{
			print_recursive(this->tree_head, "", false);
		}
		void print_recursive(node_pointer root, std::string indent, bool last)
		{
			if (root != 0)// and root != tree_head)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R---- ";
					indent += "   ";
				}
				else
				{
					std::cout << "L---- ";
					indent += "|  ";
				}
				std::string sColor = root->color ? "RED" : "BLACK";
				std::cout << root->key << "/" << root->value << "(" << sColor << ")" << std::endl;
				this->print_recursive(root->left, indent, false);
				this->print_recursive(root->right, indent, true);
			}
		}


//if (root->color == RED)
//                        std::cout << root->value.second << REDCOLOR << "(RED)" << CLEAR << std::endl;
//                    else
//                        std::cout << root->value.second << "(BLACK)" << std::endl;	


	};
// ###########################################################################################################
// #########################################   Fonctions non membres   #######################################################
// ###########################################################################################################
// TBD

}


#endif
