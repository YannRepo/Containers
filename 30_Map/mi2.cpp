void FixViolationsErase(node_pointer node)
			{
				node_pointer sibling = GetSibling(node);
				node_pointer parent = node->parent;
				
				if (node == _root)
					return;
				if (sibling == NULL)
					FixViolationsErase(parent);
				else
				{
					if (sibling->color == RED)
					{
						parent->color = RED;
						sibling->color = BLACK;
						if (isLeftChild(sibling))
							rotateRight(parent);
						else
							rotateLeft(parent);
						FixViolationsErase(node);
					}
					else
					{
						//if at least one child is red
						if ((sibling->left && sibling->left->color == RED) || (sibling->right && sibling->right->color == RED))
						{
							if (sibling->left && sibling->left->color == RED)
							{
								if (isLeftChild(sibling))
								{
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rotateRight(parent);
								}
								else
								{
									sibling->left->color = parent->color;
									rotateRight(sibling);
									rotateLeft(parent);
								}
							}
							else
							
								if (isLeftChild(sibling))
								{
									sibling->right->color = parent->color;
									rotateLeft(sibling);
									rotateRight(parent);
								}
								else
								{
									sibling->right->color = sibling->color;
									sibling->color= parent->color;
									rotateLeft(parent);
								}
						}
						else
						{
							sibling->color = RED;
							if (parent->color == BLACK)
								FixViolationsErase(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}

				void rotateLeft(node_pointer node) 
			{
				if (node == NULL)
					return;
				node_pointer parent = node->right;
				if (parent == NULL)
					return;

				node->right = parent->left;
				if (parent->left != NULL)
					parent->left->parent = node;
				parent->parent = node->parent;
				if (node->parent == NULL)
					_root = parent;
				else if (node == node->parent->left)
					node->parent->left = parent;
				else
					node->parent->right = parent;
				parent->left = node;
				node->parent = parent;
			}

			void rotateRight(node_pointer node) 
			{
				node_pointer parent = node->left;

				if (node == _root)
					_root = parent;
				if (parent) 
				{
					if (node->parent) 
					{
						if (node == node->parent->right)
							node->parent->right = parent;
						else 
							node->parent->left = parent;
					}
					parent->parent = node->parent;
					node->parent = parent;
					node->left = parent->right;
					if (parent->right) 
						parent->right->parent = node;
					parent->right = node;
				}
			}
