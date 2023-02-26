#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include <memory>

# include "pair.hpp"
# include "red_black_tree_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"


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
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;


		public: // public pour debug, repasser en private
			node_pointer	tree_head;
			node_pointer	tree_end;
			//node_pointer	tree_begin;
			size_type		tree_size;
			node_allocator	myAllocator;
			Compare			mycompare;
		
// ###########################################################################################################
// #########################################   Constructeur / destructeur  #######################################################
// ###########################################################################################################
	public:
		Red_black_tree(const Compare& comp = Compare(), const allocator_type &alloc = allocator_type()):
		tree_head(NULL),tree_size(0), myAllocator(alloc), mycompare(comp)
		{
			this->tree_head = myAllocator.allocate(1);
			this->myAllocator.construct(this->tree_head, Node<Val>()); // 666 et 777 valeurs random pour debug du noeud fantome
			//this->myAllocator.construct(this->tree_head, node(make_pair(666,777))); // 666 et 777 valeurs random pour debug du noeud fantome
			this->tree_end = tree_head;
			//this->tree_begin = NULL;
			this->tree_head->parent = tree_head; // ref sur lui-meme au depart;
		}

		template< class InputIterator >
		Red_black_tree(InputIterator first, InputIterator last, const Compare& comp, const node_allocator& alloc):
		tree_size(0), myAllocator(alloc), mycompare(comp)
		{
			this->tree_head = myAllocator.allocate(1);
			this->myAllocator.construct(this->tree_head, Node<Val>()); // 666 et 777 valeurs random pour debug du noeud fantome
			//this->myAllocator.construct(this->tree_head, node(make_pair(666,777))); // 666 et 777 valeurs random pour debug du noeud fantome
			this->tree_end = tree_head;
			//this->tree_begin = NULL;
			this->tree_head->parent = tree_head; // ref sur lui-meme au depart;
			this->insert(first, last);
		}

		~Red_black_tree()
		{
			clear();
			myAllocator.destroy(this->tree_end);
			myAllocator.deallocate(this->tree_end, 1);
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

		void update_end_node()
		{
			node_pointer last_elemement;
			last_elemement = maximum_subtree(this->tree_head);
			this->tree_end->parent = last_elemement;
			last_elemement->right = this->tree_end;
		}

		// TBD check si utilise (non testee encore)
		//void update_begin()
		//{
		//	// pour retrouver begin depuis racine (moins opti)
		//	tree_begin  = tree_head;
		//	while (tree_begin->left)
		//	{
		//		tree_begin = tree_begin->left;
		//	}
		//}
	
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
				//std::cout << "ERROR: cle identique lors de l'insertion" << std::endl; // message pour debug
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
					//if (insert_position == this->tree_begin)
					//	this->tree_begin = new_node;
					this->tree_size++;
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
					this->tree_size++;
					fix_insertion(new_node);
					return (ft::make_pair(iterator(new_node), true));
				}
			}
			std::cout << "DEBUG ERROR : cas inconnnu : cette ligne ne devrait pas etre executee " << std::endl;
			return(ft::make_pair(iterator(), false)); // inutile, juste pour eviter warning compilation
		}

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

		void clear_node_recursive(node_pointer node)
		{
			if (node && node != this->tree_end)
			{
				clear_node_recursive(node->left);
				clear_node_recursive(node->right);
				myAllocator.destroy(node);
				myAllocator.deallocate(node, 1);

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
		void fix_deletion(node_pointer x)
		{
			node_pointer s;
			while (x != 0 and x != tree_head and x->parent != 0 and x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						rotate_left(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == BLACK and s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							rotate_right(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						rotate_left(x->parent);
						x = tree_head;
						//x = _root->parent;
					}
				}
				else if (x == x->parent->right)
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						rotate_right(x->parent);
						s = x->parent->left;
						break;
					}
					if (s->left->color == BLACK and s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
						break;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							rotate_left(s);
							s = x->parent->left;
							break;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						rotate_right(x->parent);
						x = tree_head;
						//x = _root->parent;
					}
				}
				if (x)
					x->color = BLACK;
				//if (_size == 0)
				//	clear();
			}
		}

// version 3 (erreur mauvaise copie ?):
		//void fix_deletion(node_pointer node)
		//{
		//	while((node != tree_head) && (node->color != BLACK) && node->parent && node->parent->color == RED)
		//	{
		//		node_pointer uncle = NULL;
		//		if(node->parent == node->parent->parent->left)
		//		{
		//			uncle = node->parent->parent->right;
		//			if (uncle && uncle->color == RED)
		//			{
		//				node->parent->color = BLACK;
		//				uncle->color = BLACK;
		//				node->parent->parent->color = RED;
		//				node = node->parent->parent;
		//			}
		//			else
		//			{
		//				if (node == node->parent->right)
		//				{
		//					node = node->parent;
		//					rotate_left(node);
		//				}
		//				node->parent->color = BLACK;
		//				node->parent->parent->color = RED;
		//				rotate_right(node->parent->parent);
		//			}
		//		}
		//		else
		//		{
		//			uncle = node->parent->parent->left;
		//			if (uncle && uncle->color == RED)
		//			{
		//				node->parent->color = BLACK;
		//				uncle->color = BLACK;
		//				node->parent->parent->color = RED;
		//				node = node->parent->parent;
		//			}
		//			else
		//			{
		//				if (node == node->parent->left)
		//			{
		//				node = node->parent;
		//				rotate_right(node);
		//			}
		//				node->parent->color = BLACK;
		//				node->parent->parent->color = RED;
		//				rotate_left(node->parent->parent);
		//			}
		//		}
		//	}
		//	tree_head->color = BLACK;
		//}

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
		iterator begin() // TBD check si tjr ok
		{
			//return (this->tree_begin); // ancienn version
			node_pointer search_begin  = tree_head;
			while (search_begin->left)
			{
				search_begin = search_begin->left;
			}
			return (search_begin);
		}	
		const_iterator begin() const // TBD check si tjr ok
		{
			//return (this->tree_begin); // ancienn version
			node_pointer search_begin  = tree_head;
			while (search_begin->left)
			{
				search_begin = search_begin->left;
			}
			return (search_begin);
		}		
		
		iterator end()
		{
			//return (this->tree_end);
			node_pointer search_end  = tree_head;
			while (search_end->right and search_end != tree_end)
			{
				search_end = search_end->right;
			}
			return (search_end);
		}
		const_iterator end() const
		{
			//return (this->tree_end);
			node_pointer search_end  = tree_head;
			while (search_end->right and search_end != tree_end)
			{
				search_end = search_end->right;
			}
			return (search_end);

		}

		// TBD remettre en forme
 reverse_iterator rbegin()
	    { 
            return reverse_iterator(end()); 
        }

	    const_reverse_iterator rbegin() const
	    { 
            return const_reverse_iterator(end()); 
        }

	    reverse_iterator rend()
        { 
            return reverse_iterator(begin()); 
        }

	    const_reverse_iterator rend() const
        { 
            return const_reverse_iterator(begin()); 
        }
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Capacity --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		bool empty() const
		{
			return (this->tree_size == 0);
		}
		size_type size() const
		{
			return (this->tree_size);
		}
		size_type max_size() const
		{
			return (this->myAllocator.max_size());
		}


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
				//this->tree_begin = new_node;
				this->tree_size++;
				return (ft::make_pair(iterator(new_node), true));

			}
			else
				return(insert_algo(this->tree_head, added_pair));
		}
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return(this->insert(val).first);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert (*first);
				first++;
			}
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

		void erase (iterator position)
		{
			this->erase(position->first);
		}
	// erase version 1 (perso)	
		size_type erase( const key_type& key )
		{
			// recherche du noeud a supprimer
			node_pointer z = this->find(key).base();
			if (z == this->tree_end)
				return (0);
			this->tree_end->parent->right = NULL; // suppression de tree_end pendant la suppression (restauration a la fin)
			node_pointer x, y;

			y = z;
			int y_original_color = y->color;
			// Si c'est le dernier noeud a supprimer (c'est a dire le head et rien en right et left)
			if (z == this->tree_head && z->left == NULL && z->right == NULL)
			{
				this->tree_head = this->tree_end;
				this->tree_size--;
				this->myAllocator.destroy(z);
				this->myAllocator.deallocate(z, 1);
				return (1);
			}
			// si un cote sans enfant remonter noeud a la place du noeud a sup
			if (z->left == NULL)
			{
				if (z == this->tree_head) // changement du head si on supprime le 1er noeud (en cours)
					{
						//if (z->right == NULL) // cas particulier du dernier noeud
						//{
						//	this->tree_head = this->tree_end;
						//	this->tree_size--;
						//	this->myAllocator.destroy(z);
						//	this->myAllocator.deallocate(z, 1);
						//	return (1);
						//}
						//else
							this->tree_head = z->right;
					}
				//if (z == this->tree_begin) // changement du begin si on supprime le 1er noeud (en cours)
				//	this->tree_begin = z->right;
				x = z->right;
				replace_node(z, z->right);
			}
			else if (z->right == NULL || z->right == this->tree_end)
			{
				if (z == this->tree_head) // changement du head si on supprime le 1er noeud (en cours)
					this->tree_head = z->left;
				//if (z == this->tree_begin) // changement du begin si on supprime le 1er noeud (en cours)
				//	this->tree_begin = z->left;
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
				if (z == this->tree_head) // changement du begin si on supprime le 1er noeud (en cours)
					this->tree_head = y;
				//if (z == this->tree_begin) // changement du begin si on supprime le 1er noeud (en cours)
				//	this->tree_begin = y;
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
			update_end_node();
			this->tree_size--;
			return (1);
		}

			void erase (iterator first, iterator last)
			{
				if (first == begin() && last == end())
					{
						this->clear();
						return ;
					}
				while (first != last)
				{
					this->erase(first++);
					//first++; //pas incrementer apres sinon le first n'est plus valide
				}
			}

		//size_type erase( const key_type& key )
		//{
		//	iterator to_erase;
		//	to_erase = this->find(key);
		//	if (to_erase.base() != this->tree_end)
		//	{
		//		this->deleteNode(to_erase.base());
		//		return (1);
		//	}
		//	return (0); // TBD check les returns
		//}		

		//void erase (iterator first, iterator last)
		//{
		//	if (first == begin() && last == end())
		//		{
		//			this->clear();
		//			return ;
		//		}
		//	while (first != last)
		//	{
		//		this->erase(first);
		//		first++;
		//	}
		//}

		void swap (Red_black_tree& rbt_to_swap)
		{
			node_pointer tmp_tree_head		= rbt_to_swap.tree_head;
			rbt_to_swap.tree_head 			= this->tree_head;
			this->tree_head 				= tmp_tree_head;

			node_pointer tmp_tree_end		= rbt_to_swap.tree_end;
			rbt_to_swap.tree_end			= this->tree_end;
			this->tree_end					= tmp_tree_end;
			
			size_type tmp_tree_size			= rbt_to_swap.tree_size;
			rbt_to_swap.tree_size			= this->tree_size;
			this->tree_size					= tmp_tree_size;
			
			node_allocator tmp_myAllocator	= rbt_to_swap.myAllocator;
			rbt_to_swap.myAllocator			= this->myAllocator;
			this->myAllocator				= tmp_myAllocator;
			
			Compare tmp_mycompare			= rbt_to_swap.mycompare;
			rbt_to_swap.mycompare			= this->mycompare;
			this->mycompare					= tmp_mycompare;
		}

		void clear()
		{
			clear_node_recursive(this->tree_head);
			this->tree_head = tree_end; ;
			this->tree_head->parent = tree_head; // ref sur lui-meme au depart
			//this->tree_begin = tree_end;
			this->tree_size = 0;
			this->tree_head->left = NULL;
			this->tree_head->right = NULL;

		}
			
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Operations / Lookup --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		iterator find (const key_type& k) const
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
		}
		size_type count (const key_type& k) const
		{
			if (find(k) != this->tree_end)
				return (1);
			return (0);
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

		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}
// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Observers --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ Allocator --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
		allocator_type get_allocator() const
		{
			return (myAllocator);
		}





// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ a ranger (fct MI) --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------



// erase version MI

			node_pointer deleteNode(node_pointer node)
			{
				node_pointer nextNode = replace(node);
				node_pointer parent = node->parent;
				node_pointer sibling = GetSibling(node);
				node_pointer ret = successor(node);
				
				if (nextNode == NULL)
				{
					if (node == tree_head)
						tree_head = NULL;
					else
					{
						if (nextNode == NULL || nextNode->color == BLACK)
							FixViolationsErase(node);
						else if (sibling != NULL)
							sibling->color = RED;
						if (isLeftChild(node))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					freeNode(node);
					tree_size--;
					updateEnd();
					return ret;
				}
				if (node->left == NULL || node->right == NULL)
				{
					if (node == tree_head)
					{
						change_value(node, nextNode);
						freeNode(nextNode);
						node->left = NULL;
						node->right = NULL;
					}
					else
					{
						if (isLeftChild(node))
						{
							parent->left = nextNode;
						}
						else
						{
							parent->right = nextNode;
						}
						freeNode(node);
						nextNode->parent = parent;
						if (nextNode == NULL || nextNode->color == BLACK)
							FixViolationsErase(nextNode);
						else
							nextNode->color = BLACK;
					}
					tree_size--;
					updateEnd();
					return ret;
				}
				swap_value(nextNode, node);
				deleteNode(nextNode);
				return node;
			}



			void swap_value(node_pointer a,node_pointer b)
			{
				key_type tmp;
				key_type *keya = const_cast<key_type *>(&a->value.first);
				key_type *keyb = const_cast<key_type *>(&b->value.first);
				value_type	temp;

				tmp = *keya;
				*keya = *keyb;
				*keyb = tmp;

				temp.second= a->value.second;
				a->value.second = b->value.second;
				b->value.second = temp.second;

			}

			bool isLeftChild(node_pointer node)
			{
				return node == node->parent->left;
			}

			node_pointer GetSibling(node_pointer node)
			{
				if (node->parent == NULL)
					return NULL;
				if (isLeftChild(node))
					return node->parent->right;
				else
					return node->parent->left;
			}


			void freeNode(node_pointer node)
			{
				myAllocator.destroy(node);
				myAllocator.deallocate(node, RED);
			}


			void updateEnd()
			{
				node_pointer max = maximum();
				max->right = tree_end;
				tree_end->parent = max;
				tree_end->left = NULL;
				tree_end->right = NULL;
				tree_end->color = BLACK;
			}


			void 	change_value(node_pointer a, node_pointer b)
			{
				key_type* kRED;
				key_type* k2;

				kRED = const_cast<key_type*>(&a->value.first);
				k2 = const_cast<key_type*>(&b->value.first);
				
				*kRED = *k2;
				a->value.second = b->value.second;
			}

			node_pointer successor(node_pointer node) 
			{
				if (node->right != NULL) 
				{
					node = node->right;
					while(node->left != NULL)
						node = node->left;
					return node;
				}
				node_pointer parent = node->parent;
				while (parent != NULL && parent != tree_end && node == parent->right) 
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_pointer maximum() const
			{
				node_pointer max = tree_head;
				while (max && max->right != NULL && max->right != tree_end) 
					max = max->right;
				return max;
			}

			node_pointer	replace(node_pointer node)
			{
				if (node->left != NULL && node->right != NULL && node->right != tree_end)
					return successor(node);
				if (!node->left && !node->right)
					return NULL;
				if (node->left != NULL)
					return node->left;
				return node->right;
			}

			void FixViolationsErase(node_pointer node)
			{
				(void)node;
				// TBD
			}



// -----------------------------------------------------------------------------------------------------------
// ------------------------------------ a ranger (fct Julia fix rapide) --------------------------------------------------
// -----------------------------------------------------------------------------------------------------------

		// typedef Compare												key_compare;

        //key_compare key_comp() const{
        //    return mycompare;
        //}


	};
// ###########################################################################################################
// #########################################   Fonctions non membres   #######################################################
// ###########################################################################################################
    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator==(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    {
		//(void)lhs;
		//(void)rhs;
		//return (true); // tmp
    	////return lhs.size() == rhs.size() // TBD remettre
    	//	//   and ft::equal(lhs.begin(), lhs.end(), rhs.begin());

		if (lhs.size() != rhs.size())
			return (false);

		typename ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> begin_1 = lhs.begin();
		typename ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> begin_2 = rhs.begin();
	
		while (begin_1 != lhs.end())
		{
			if (begin_1 != begin_2)
				return (false);
			begin_1++;
			begin_2++;
		}
		//if (begin_2 != rhs.end())
		//	return (false);
		return (true);
	
    }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator<(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		  const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator!=(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (lhs == rhs); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator>(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		  const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return rhs < lhs; }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator>=(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (lhs < rhs); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator<=(const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::Red_black_tree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (rhs < lhs); }

}


#endif
