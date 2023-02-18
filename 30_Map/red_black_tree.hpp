#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree_iterator.hpp"

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
			template <typename V>
			struct Node;

		public:
			typedef Key								key_type;
			typedef Val								value_type;
			typedef Allocator						allocator_type;

			public:// public pour debug, repasser en private
			typedef Node<Val>						node;
			typedef Node<Val>*						node_pointer;

		public: // public pour debug, repasser en private
			template <typename V>
			struct Node
			{
				V					value;
				node_pointer		left;
				node_pointer		right;
				node_pointer		parent;
				int					color;

				Node(): left(NULL), right(NULL), parent(NULL), color(RED){}
				Node(value_type value_): value(value_), left(NULL), right(NULL), parent(NULL), color(RED){}
				Node(value_type value_, bool col): value(value_), left(NULL), right(NULL), parent(NULL), color(col){}
				
				bool has_right_child()
				{
					if (this->right)
						return (true);
					return (false);
				}
				bool has_left_child()
				{
					if (this->left)
						return (true);
					return (false);
				}
				bool has_parent()
				{
					if (this->parent)
						return (true);
					return (false);
				}
				bool is_left_child() // return false si pas de parent
				{
					if (!this->has_parent())
						return (false);
					if (this == this->parent->left)
						return (true);
					return (false);
				}
				bool is_right_child() // return false si pas de parent
				{
					if (!this->has_parent())
						return (false);
					if (this == this->parent->right)
						return (true);
					return (false);
				}
			};

		// TBD check si ca corrige pb
		//-- Create a new type of allocator that is bound to the 'Node' type and uses the same 
		//   memory ressource as the original 'allocator_type'.
		public:
			typedef typename Allocator::template rebind<Node<Val> >::other		node_allocator;

			typedef typename ft::Rbt_iterator<value_type, node_pointer, Compare>			iterator;


		public: // public pour debug, repasser en private
			node_pointer	tree_head;
			node_pointer	tree_end;
			node_pointer	tree_begin;
			node_allocator	myAllocator;
			Compare			mycompare;
		
// ###########################################################################################################
// #########################################   Constructeur / destructeur  #######################################################
// ###########################################################################################################
	public:
		Red_black_tree(const Compare& comp = Compare(), const allocator_type &alloc = allocator_type()):
		tree_head(NULL), myAllocator(alloc), mycompare(comp)
		{
			this->tree_head = myAllocator.allocate(1);
			this->myAllocator.construct(this->tree_head, node(make_pair(666,777))); // 666 et 777 valeurs random pour debug du noeud fantome
			this->tree_end = tree_head;
			this->tree_begin = NULL;
			this->tree_head->parent = tree_head; // ref sur lui-meme au depart;

		}

// ###########################################################################################################
// #########################################   Utils RBT   #######################################################
// ###########################################################################################################
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Divers--------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

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

		// TBD check si utilise (non testee encore)
		void update_begin()
		{
			// pour retrouver begin depuis racine (moins opti)
			tree_begin  = tree_head;
			while (tree_begin->left)
			{
				tree_begin = tree_begin->left;
			}
		}
	
	public: // TBD voir les fct a repasser en private
		node_pointer get_tree_head() // voir si cette fct est utile 
		{
			return (this->tree_head);
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
				std::string sColor = root->color ? "\x1B[31mRED\x1B[0m" : "\x1b[30mBLACK\x1B[0m";
				std::cout << root->value.first << "/" << root->value.second << "(" << sColor << ")" << std::endl;
				this->print_recursive(root->left, indent, false);
				this->print_recursive(root->right, indent, true);
			}
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Rotations--------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

		void rotate_left(node_pointer x)
		{
//			(x)          (y)
//			  \    =>    /
//			  (y)      (x)
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != NULL)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				this->tree_head = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void rotate_right(node_pointer x)
		{
//			  (y)       (x)
//			  /      =>   \
//			(x)           (y)
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != NULL)
			{
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				this->tree_head = y;
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y;
			}
			else
			{
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Insert ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		void fix_insertion(node_pointer k)
		{
			node_pointer u;
			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u != NULL && u->color == RED) //SF
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							rotate_right(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						rotate_left(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;
					if (u != NULL && u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							rotate_left(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						rotate_right(k->parent->parent);
					}
				}
				if (k == tree_head)
				{
					break;
				}
			}
			tree_head->color = BLACK;
		}

// ###########################################################################################################
// #############################   Fonctions membres de map   #######################################################
// ###########################################################################################################
	public:
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
		ft::pair<iterator, bool> insert(const value_type added_pair)
		{
			if (this->tree_head == this->tree_end) // 1er insertion
			{
				//this->myAllocator.construct(tree_head, node());
				node_pointer new_node = this->myAllocator.allocate(1);
				this->myAllocator.construct(new_node, node(added_pair, BLACK)); // TBD check construction
				this->tree_head = new_node;
				update_end(new_node);
				this->tree_begin = new_node;
				return (ft::make_pair(iterator(new_node), true));

			}
			else
				return(insert_algo(this->tree_head, added_pair));
		}

		ft::pair<iterator, bool> insert_algo(node_pointer insert_position,const value_type added_pair)
		{	
			if (mycompare(added_pair.first, insert_position->value.first) == mycompare(insert_position->value.first, added_pair.first))
			{
				std::cout << "ERROR: cle identique lors de l'insertion" << std::endl;
				return (ft::make_pair(iterator(insert_position), false));
			}
			// insertion a gauche
			else if (mycompare(added_pair.first, insert_position->value.first))
			{
				if (insert_position->left)
					return (insert_algo(insert_position->left, added_pair));
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, node(added_pair));
					new_node->parent = insert_position;
					insert_position->left = new_node;
					if (insert_position == this->tree_begin)
						this->tree_begin = new_node;
					fix_insertion(new_node);
					return (ft::make_pair(iterator(new_node), true));
				}
			}
			// insertion a droite
			else if (mycompare(insert_position->value.first, added_pair.first))
			{
				if (insert_position->right and insert_position->right != this->tree_end)
					return (insert_algo(insert_position->right, added_pair));
					
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, node(added_pair));
					new_node->parent = insert_position;
					insert_position->right = new_node;
					if (this->tree_end->parent == new_node->parent) // update end si on ajoute sous l'element final (a droite)
						update_end(new_node);
					fix_insertion(new_node);
					return (ft::make_pair(iterator(new_node), true));
				}
			}
			std::cout << "DEBUG ERROR : cas inconnnu : cette ligne ne devrait pas etre executee " << std::endl;
			return(ft::make_pair(iterator(), false)); // inutile, juste pour warning compilation
		}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		iterator find (const key_type& k)
		{
			node_pointer search_node = tree_head;
			while (search_node && search_node != this->tree_end)
			{
				if (!mycompare(search_node->value.first, k) && !mycompare(k, search_node->value.first))
					return (search_node);
				if (mycompare(k, search_node->value.first))
					search_node = search_node->left;
				else
					search_node = search_node->right;
			}
			return (this->tree_end);

			// TBD en cours
		}

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Observers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------


	};
// ###########################################################################################################
// #########################################   Fonctions non membres   #######################################################
// ###########################################################################################################
// TBD

}


#endif
