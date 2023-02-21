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
			typedef size_t							size_type;


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

			//typedef typename ft::Rbt_iterator<value_type, node_pointer, Compare>		iterator;

			typedef ft::Rbt_iterator<value_type, node_pointer, Compare>					iterator;
            typedef ft::Rbt_iterator<const value_type, node_pointer, Compare>			const_iterator;
            //typedef ft::reverse_Iterator<iterator>			            reverse_iterator;
	        //typedef ft::reverse_Iterator<const_iterator>	            const_reverse_iterator;


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

		void update_end_erase()
		{
			node_pointer last_elemement;
			last_elemement = maximum_subtree(this->tree_head);
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
					this->myAllocator.construct(new_node, node(added_pair, RED));
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
					this->myAllocator.construct(new_node, node(added_pair, RED));
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
// ------------------------------------ Insert fix ------------------------------------------------------------
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

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Erase fix ------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// version 1 : algo du ste + ajout conditions pour les segfault
//		void fix_deletion_old(node_pointer x)
//{
//			node_pointer s;
//			while (x != this->tree_head && x->color == 0)
//			{
//				//493/128
//				//std::cout << "check: " << x->value.first << std::endl;
//				//std::cout << "check: " << this->tree_head->value.first << std::endl;


//				if (x->parent->right && x->parent->left && x == x->parent->left)
//				{
//					s = x->parent->right;
//					if (s->color == 1)
//					{
//						s->color = 0;
//						x->parent->color = 1;
//						rotate_left(x->parent);
//						s = x->parent->right;
//					}

//					if (s->left && s->right && s->left->color == 0 && s->right->color == 0)
//					{
//						s->color = 1;
//						x = x->parent;
//					}
//					else
//					{
//						if (s->right && s->right->color == 0)
//						{
//							s->left->color = 0;
//							s->color = 1;
//							rotate_right(s);
//							s = x->parent->right;
//						}

//						s->color = x->parent->color;
//						x->parent->color = 0;
//						if (s->right)
//							s->right->color = 0;
//						rotate_left(x->parent);
//						x = this->tree_head;
//					}
//				}
//				else if (x->parent->left && x->parent->right)
//				{
//					s = x->parent->left;
//					if (s->color == 1)
//					{
//						s->color = 0;
//						x->parent->color = 1;
//						rotate_right(x->parent);
//						s = x->parent->left;
//					}

//					if (s->right && s->right->color == 0 && s->right->color == 0)
//					{
//						s->color = 1;
//						x = x->parent;
//					}
//					else
//					{
//						if (s->left && s->left->color == 0)
//						{
//							s->right->color = 0;
//							s->color = 1;
//							rotate_left(s);
//							s = x->parent->left;
//						}

//						s->color = x->parent->color;
//						x->parent->color = 0;
//						if (s->left)
//							s->left->color = 0;
//						rotate_right(x->parent);
//						x = this->tree_head;
//					}
//				}
//			}
//			x->color = 0;
//}

// version 2: Julia avec adaptation code
		//void fix_deletion(node_pointer x)
		//{
		//	node_pointer s;
		//	while (x != 0 and x != tree_head and x->parent != 0 and x->color == BLACK)
		//	{
		//		if (x == x->parent->left)
		//		{
		//			s = x->parent->right;
		//			if (s->color == RED)
		//			{
		//				s->color = BLACK;
		//				x->parent->color = RED;
		//				rotate_left(x->parent);
		//				s = x->parent->right;
		//			}
		//			if (s->left->color == BLACK and s->right->color == BLACK)
		//			{
		//				s->color = RED;
		//				x = x->parent;
		//			}
		//			else
		//			{
		//				if (s->right->color == BLACK)
		//				{
		//					s->left->color = BLACK;
		//					s->color = RED;
		//					rotate_right(s);
		//					s = x->parent->right;
		//				}
		//				s->color = x->parent->color;
		//				x->parent->color = BLACK;
		//				s->right->color = BLACK;
		//				rotate_left(x->parent);
		//				x = tree_head;
		//				//x = _root->parent;
		//			}
		//		}
		//		else if (x == x->parent->right)
		//		{
		//			s = x->parent->left;
		//			if (s->color == RED)
		//			{
		//				s->color = BLACK;
		//				x->parent->color = RED;
		//				rotate_right(x->parent);
		//				s = x->parent->left;
		//				break;
		//			}
		//			if (s->left->color == BLACK and s->right->color == BLACK)
		//			{
		//				s->color = RED;
		//				x = x->parent;
		//				break;
		//			}
		//			else
		//			{
		//				if (s->left->color == BLACK)
		//				{
		//					s->right->color = BLACK;
		//					s->color = RED;
		//					rotate_left(s);
		//					s = x->parent->left;
		//					break;
		//				}
		//				s->color = x->parent->color;
		//				x->parent->color = BLACK;
		//				s->left->color = BLACK;
		//				rotate_right(x->parent);
		//				x = tree_head;
		//				//x = _root->parent;
		//			}
		//		}
		//		if (x)
		//			x->color = BLACK;
		//		//if (_size == 0)
		//		//	clear();
		//	}
		//}

// version 3 :
		void fix_deletion(node_pointer node)
		{
			while((node != tree_head) && (node->color != BLACK) && node->parent && node->parent->color == RED)
			{
				node_pointer uncle = NULL;
				if(node->parent == node->parent->parent->left)
				{
					uncle = node->parent->parent->right;
					if (uncle && uncle->color == RED)
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							rotate_left(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_right(node->parent->parent);
					}
				}
				else
				{
					uncle = node->parent->parent->left;
					if (uncle && uncle->color == RED)
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left)
					{
						node = node->parent;
						rotate_right(node);
					}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_left(node->parent->parent);
					}
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


// supression element sur arbre binaire normal
// 0 enfant -> suppression directe
// 1 enfant -> on le remplace par l'enfant
// 2 enfants ->	a. inordeur predecessor : on le remplace par le plus grand element de l'arbre left
//				b. inorder succecessor : on le remplace par le plus petit element de l'arbre right (methode utilisee ici)
// La suppression des noeuds se fait toujours sur les derniers noeuds s(leaf)

// Suppression sur rbt (prise en compte des couleurs)
// Si le noeud a supprimer est rouge - > supprimer le noeud
// Si le noeud a supprimer est noir:
//		Si le noeud avec qui il est remplacé est rouge -> faire le remplacement sans echanger les couleurs
		void replace_node(node_pointer old_node, node_pointer new_node)
		{
			// remplace u par v (u hors de l'arbre apres)
			if (old_node->parent == NULL)
			{
				this->tree_head = new_node;
			}
			else if (old_node == old_node->parent->left)
			{
				old_node->parent->left = new_node;
			}
			else
			{
				old_node->parent->right = new_node;
			}
			if (new_node)
				new_node->parent = old_node->parent;
		}

		node_pointer minimum_subtree(node_pointer start_node)
		{
			while (start_node->left != NULL)
			{
				start_node = start_node->left;
			}
			return (start_node);
		}

		node_pointer maximum_subtree(node_pointer start_node)
		{
			while (start_node->right != NULL)
			{
				start_node = start_node->right;
			}
			return start_node;
		}

		size_type erase( const key_type& key )
		{
			std::cout << "erase asked:" << key << std::endl;
			// recherche du noeud a supprimer
			node_pointer z = this->find(key).base();
			if (z == this->tree_end)
				return (0);
			this->tree_end->parent->right = NULL;
			node_pointer x, y;

			y = z;
			int y_original_color = y->color;
			// si un cote sans enfant remonter noeud a la place du noeud a sup
			if (z->left == NULL)
			{
				x = z->right;
				replace_node(z, z->right);
			}
			else if (z->right == NULL)
			{
				x = z->left;
				replace_node(z, z->left);
			}
			// sinon on va cherche le mini du sous arbre de droite (<=> noeud suivant dans rbt)
			else
			{
				y = minimum_subtree(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z && x)
				{
					x->parent = y;
				}
				else
				{
					replace_node(y, y->right);
					y->right = z->right;
					if (y->right)
						y->right->parent = y;
				}

				replace_node(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			// suppression du noeud
			this->myAllocator.destroy(z);
			this->myAllocator.deallocate(z, 1);
			// fix suppression
			if (y_original_color == BLACK && x)
			{
				fix_deletion(x);
			}
			// update tree_head, begin, end, noeud fantome
			update_end_erase();
			return (1);
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
		iterator lower_bound (const key_type& k) const
		{
			node_pointer search_node = this->tree_head;
			node_pointer return_ptr = NULL;
			while (search_node && search_node != this->tree_end)
			{
				if (!mycompare(search_node->value.first, k)) //elm de recherce >= key -> on le note et on descend
				{
					return_ptr = search_node;
					search_node = search_node->left;
				}
				else //elm de recherce < key -> on monte
					search_node = search_node->right;
			}
			if (return_ptr == NULL)
				return (this->tree_end);
			return (iterator(return_ptr));
		}
		// TBD a voir si besoin d'ajouter pour les const (dans ce cas enlever le const sur les autres)
		//const_iterator lower_bound (const key_type& k) const
		//{
		//	node_pointer search_node = this->tree_head;
		//	node_pointer return_ptr = NULL;
		//	while (search_node && search_node != this->tree_end)
		//	{
		//		if (!mycompare(search_node->value.first, k)) //elm de recherce >= key -> on le note et on descend
		//		{
		//			return_ptr = search_node;
		//			search_node = search_node->left;
		//		}
		//		else //elm de recherce < key -> on monte
		//			search_node = search_node->right;
		//	}
		//	if (return_ptr == NULL)
		//		return (this->tree_end);
		//	return (const_iterator(return_ptr));
		//}
		iterator upper_bound (const key_type& k) const
		{
			node_pointer search_node = this->tree_head;
			node_pointer return_ptr = NULL;
			while (search_node && search_node != this->tree_end)
			{
				if (mycompare(k, search_node->value.first)) //elm de recherce <= key -> on le note et on descend
				{
					return_ptr = search_node;
					search_node = search_node->left;
				}
				else // elm de recherce > key -> on monte
					search_node = search_node->right;
			}
			if (return_ptr == NULL)
				return (this->tree_end);
			return (iterator(return_ptr));
		}
		// TBD a voir si besoin d'ajouter pour les const (dans ce cas enlever le const sur les autres)
		//const_iterator upper_bound (const key_type& k) const
		//{
		//	node_pointer search_node = this->tree_head;
		//	node_pointer return_ptr = NULL;
		//	while (search_node && search_node != this->tree_end)
		//	{
		//		if (mycompare(k, search_node->value.first)) //elm de recherce <= key -> on le note et on descend
		//		{
		//			return_ptr = search_node;
		//			search_node = search_node->left;
		//		}
		//		else // elm de recherce > key -> on monte
		//			search_node = search_node->right;
		//	}
		//	if (return_ptr == NULL)
		//		return (this->tree_end);
		//	return (const_iterator(return_ptr));
		//}
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
