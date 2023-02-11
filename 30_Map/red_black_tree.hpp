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
		public:
			typedef Key								key_type;
			typedef Val								mapped_type;
			typedef Allocator						allocator_type;

		public: // public pour debug, repasser en private
			template <typename K, typename V>
			struct Node
			{
				K			key;
				V			value;
				Node		*left;
				Node		*right;
				Node		*parent;
				int			color;

				Node(): value(mapped_type()), left(NULL), right(NULL), parent(NULL), color(RED){}
				Node(mapped_type val): value(val), left(NULL), right(NULL), parent(NULL), color(RED){}
			};

		public:// public pour debug, repasser en private
			typedef Node<Key, Val>						node;
			typedef Node<Key, Val>*						node_pointer;



		// TBD check si ca corrige pb
		//-- Create a new type of allocator that is bound to the 'Node' type and uses the same 
		//   memory ressource as the original 'allocator_type'.
		typedef typename Allocator::template rebind<Node<Key, Val> >::other   node_allocator;

		public: // public pour debug, repasser en private
			node_pointer	tree_head;
			node_allocator	myAllocator;
			Compare			mycompare;
		

	Red_black_tree(const Compare& comp = Compare(), const allocator_type &alloc = allocator_type()):
	tree_head(NULL), myAllocator(alloc), mycompare(comp)
	{
		//node_pointer tree_head = myAllocator.allocate(1);

	}

	void insert_node(node_pointer insert_position, pair<key_type, mapped_type> added_pair)
	{	
		if (this->tree_head == NULL)
		{
			//this->myAllocator.construct(tree_head, node());

			node_pointer new_node = this->myAllocator.allocate(1);
			this->myAllocator.construct(new_node, added_pair.second);
			this->tree_head = new_node;
		}
		else
		{
			//if(true == true)
			if (mycompare(added_pair.first, this->tree_head->value) == mycompare(this->tree_head->value, added_pair.first))
			{
				std::cout << "ERROR: cle identique lors de l'insertion" << std::endl;
			}
			else if (mycompare(added_pair.first, this->tree_head->value))
			{
				if (insert_position->left)
					insert_node(insert_position->left, added_pair);
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, added_pair.second);
					insert_position->left = new_node;
				}
			}
			else if (mycompare(this->tree_head->value, added_pair.first))
			{
				if (insert_position->right)
					insert_node(insert_position->right, added_pair);
				else
				{
					node_pointer new_node = this->myAllocator.allocate(1);
					this->myAllocator.construct(new_node, added_pair.second);
					insert_position->right = new_node;
				}

			}
			std::cout << "DEBUG ERROR : cas inconnnu : cette ligne ne devrait pas etre executee " << std::endl;


		}
	}

	void print()
	{
		std::cout << "pouet" << std::endl;
		print_recursive(this->tree_head, "", false);
	}
	void print_recursive(node_pointer root, std::string indent, bool last)
	{
		std::cout << "pouet" << std::endl;
		if (root != 0 and root != tree_head)
		{
			std::cout << indent;
			if (last)
			{
				std::cout << "R----";
				indent += "   ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}
			std::string sColor = root->color ? "RED" : "BLACK";
			std::cout << root->value << "(" << sColor << ")" << std::endl;
			this->print_recursive(root->left, indent, false);
			this->print_recursive(root->right, indent, true);
		}
	}


//if (root->color == RED)
//                        std::cout << root->value.second << REDCOLOR << "(RED)" << CLEAR << std::endl;
//                    else
//                        std::cout << root->value.second << "(BLACK)" << std::endl;	


	};
}


#endif
