
			node_pointer deleteNode(node_pointer node)
			{
				node_pointer nextNode = replace(node);
				node_pointer parent = node->parent;
				node_pointer sibling = GetSibling(node);
				node_pointer ret = successor(node);
				
				if (nextNode == NULL)
				{
					if (node == _root)
						_root = NULL;
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
					_size--;
					updateEnd();
					return ret;
				}
				if (node->left == NULL || node->right == NULL)
				{
					if (node == _root)
					{
						change_value(node, nextNode);
						freeNode(nextNode);
						//node->data = nextNode->data;
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
					_size--;
					updateEnd();
					return ret;
				}
				swap_value(nextNode, node);
				deleteNode(nextNode);
				return node;
			}

				node_pointer	replace(node_pointer node)
			{
				if (node->left != NULL && node->right != NULL && node->right != _end)
					return successor(node);
				if (!node->left && !node->right)
					return NULL;
				if (node->left != NULL)
					return node->left;
				return node->right;
			}

			void swap_value(node_pointer a,node_pointer b)
			{
				key_type tmp;
				key_type *keya = const_cast<key_type *>(&a->data.first);
				key_type *keyb = const_cast<key_type *>(&b->data.first);
				value_type	temp;

				tmp = *keya;
				*keya = *keyb;
				*keyb = tmp;

				temp.second= a->data.second;
				a->data.second = b->data.second;
				b->data.second = temp.second;

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
				_alloc.destroy(node);
				_alloc.deallocate(node, RED);
			}


			void updateEnd()
			{
				node_pointer max = maximum();
				max->right = _end;
				_end->parent = max;
				_end->left = NULL;
				_end->right = NULL;
				_end->color = BLACK;
			}


			void 	change_value(node_pointer a, node_pointer b)
			{
				key_type* kRED;
				key_type* k2;

				kRED = const_cast<key_type*>(&a->data.first);
				k2 = const_cast<key_type*>(&b->data.first);
				
				*kRED = *k2;
				a->data.second = b->data.second;
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
				while (parent != NULL && parent != _end && node == parent->right) 
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
