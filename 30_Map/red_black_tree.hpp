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
			struct Node
			{
				mapped_type	value;
				Node		*left;
				Node		*right;
				Node		*parent;
				int			color;

				Node(): value(mapped_type()), left(NULL), right(NULL), parent(NULL), color(RED){}
				Node(mapped_type val): value(val), left(NULL), right(NULL), parent(NULL), color(RED){}
			};

		// TBD check si ca corrige pb
		//-- Create a new type of allocator that is bound to the 'Node' type and uses the same 
		//   memory ressource as the original 'allocator_type'.
		//typedef typename Allocator::template rebind<Node<Val> >::other   node_allocator;

		public: // public pour debug, repasser en private
			Node* tree_head;
			node_allocator myAllocator;
		

	Red_black_tree(const allocator_type &alloc = allocator_type()):
	tree_head(NULL), myAllocator(alloc){}

	void insert_node(Node* insert_position)//, pair<key_type, mapped_type> added_pair)
	{	
		if (this->tree_head == NULL)
		{
			Node* new_node = this->myAllocator.allocate(1);
			//this->myAllocator.construct(new_node, added_pair.second);
			//this->tree_head = new_node;
		}
		//else
		//{
		//	if (compare(added_pair.first, this->tree_head->value) == compare(this->tree_head->value, added_pair.first))
		//	{
		//		std::cout << "ERROR: cle identique lors de l'insertion" << std::endl;
		//	}
		//	else if (compare(added_pair.first, this->tree_head->value))
		//	{
		//		if (insert_position->left)
		//			insert_node(insert_position->left, added_pair);
		//		else
		//		{
		//			Node* new_node = this->myAllocator.allocate(sizeof(Node));
		//			this->myAllocator.construct(new_node, added_pair.second);
		//			insert_position->left = new_node;
		//		}
		//	}
		//	else if (compare(this->tree_head->value, added_pair.first))
		//	{
		//		if (insert_position->right)
		//			insert_node(insert_position->right, added_pair);
		//		else
		//		{
		//			Node* new_node = this->myAllocator.allocate(sizeof(Node));
		//			this->myAllocator.construct(new_node, added_pair.second);
		//			insert_position->right = new_node;
		//		}

		//	}
		//	std::cout << "DEBUG ERROR : cas inconnnu : cette ligne ne devrait pas etre executee " << std::endl;


		//}
	}

	void print(Node* root, std::string indent, bool last)
	{
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
			std::cout << root->data.second << "(" << sColor << ")" << std::endl;
			this->print(root->left, indent, false);
			this->print(root->right, indent, true);
		}
	}





	};
}


#endif
