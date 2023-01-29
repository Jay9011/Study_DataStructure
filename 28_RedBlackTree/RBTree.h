#pragma once

template<typename T>
class RBTree
{

public:
	struct Node;
	enum class Color { Red, Black };

public:
	struct Node
	{
		Node* Parent;
		Node* Left;
		Node* Right;
		Color Color;

		T Data;
	};

public:
	void RotateRight(Node** root, Node* parent)
	{
		Node* leftChild = parent->Left;
		
		/*
		* �ڽ� ���� parent�� parent�� ��ġ�ؾ� �� child(Right Child)�� ��ġ�� �ٲٱ� �����մϴ�.
		*/
		// parent�� �ڽ� ��ġ�� child(Right Child)�� �ٲ��ݴϴ�.
		parent->Left = leftChild->Right;

		// child(Right Child)�� parent�� �ٲ� parent�� �ٲ��ݴϴ�.
		if (leftChild->Right != nil)
			leftChild->Right->Parent = parent;
		// (Right Child ���� ��, Left Child�� parent�� ������ ����...)

		/*
		* �ڽ��� ��ġ�� parent�� Parent ��ġ�� �ٲٱ� �����մϴ�.
		*/ 
		leftChild->Parent = parent->Parent;
		if (parent->Parent != nullptr)
		{
			// �ٲ� parent�� ��ġ�� parent�� �θ��� �����̸� �ٲٷ��� �ڽ��� ������,
			// �θ��� �����̸� �ٲٷ��� �ڽ��� ������ �������ݴϴ�.
			// (parent�� �θ� �ڽ��� �����մϴ�.)
			if (parent == parent->Parent->Left)
				parent->Parent->Left = leftChild;
			else
				parent->Parent->Right = leftChild;
		}
		else
		{
			// parent�� Root ���ٸ� root�� �ڽ����� ����ϴ�.
			(*root) = leftChild;
		}

		/*
		* ���� �ٲٴ� �� ����� ���� �ٲ㼭 �������ݴϴ�.
		* (�ڽİ� �θ� �ٲߴϴ�.)
		*/
		leftChild->Right = parent;
		parent->Parent = leftChild;
	}

	void RotateLeft(Node** root, Node* parent)
	{
		Node* rightChild = parent->Right;
		parent->Right = rightChild->Left;

		if (rightChild->Left != nil)
			rightChild->Left->Parent = parent;

		rightChild->Parent = parent->Parent;
		if (parent->Parent != nullptr)
		{
			if (parent == parent->Parent->Left)
				parent->Parent->Left = rightChild;
			else
				parent->Parent->Right = rightChild;
		}
		else
		{
			(*root) = rightChild;
		}

		rightChild->Left = parent;
		parent->Parent = rightChild;
	}

	void InsertNode(Node** node, Node* newNode)
	{
		InsertNodeInternal(node, newNode);

		newNode->Color = Color::Red;
		newNode->Left = nil;
		newNode->Right = nil;

		RebuildInsert(node, newNode);
	}

	void RebuildInsert(Node** root, Node* node)
	{
		// Red�� �����ϴµ�, parent�� Red���� ��
		while (node != (*root) && node->Parent->Color == Color::Red)
		{
			// parent�� parent�� �θ��� ������ ���
			if (node->Parent == node->Parent->Parent->Left)
			{
				Node* uncle = node->Parent->Parent->Right;

				// U�� Red�� ��� [Recoloring] ����
				if (uncle->Color == Color::Red)
				{
					// ������ �� ���(parent�� uncle)�� ���������� �����
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					// �� ���� ���(parent�� �θ�)�� ���������� ����ϴ�.
					node->Parent->Parent->Color = Color::Red;

					// ���� parent�� 4�� ��Ģ(Red-Black)�� ������ �ö󰡼� �ٽ� Ȯ���մϴ�.
					node = node->Parent->Parent;
				}
				// U�� Black�� ��� [Restructuring] ����
				else
				{
					// �����ʿ� ���� ��� ȸ���� ���� ���� ��ȸ���� �մϴ�.
					if (node == node->Parent->Right)
					{
						node = node->Parent;
						RotateLeft(root, node);
					}

					// parent�� parent�� �θ� ����� ���� �ٲ��� ��
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					// ��ȸ���� ���� Red-Black ��Ģ�� �����մϴ�.
					RotateRight(root, node->Parent->Parent);
				}
			}
			// parent�� parent�� �θ��� �������� ���
			else
			{
				Node* uncle = node->Parent->Parent->Left;

				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else
				{
					if (node == node->Parent->Left)
					{
						node = node->Parent;
						RotateRight(root, node);
					}

					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					RotateLeft(root, node->Parent->Parent);
				}
			}//if(node->parent)
		}//while(node)

		// ������ Root�� ���������� �������ݴϴ�.
		(*root)->Color = Color::Black;
	}

	Node* RemoveNode(Node** root, T data)
	{
		Node* target = Search(*root, data);
		if (target == nullptr) return nullptr;

		Node* remove = nullptr;
		if (target->Left == nil || target->Right == nil)
		{
			remove = target;
		}
		else
		{
			remove = SearchMinNode(target->Right);
			target->Data = remove->Data;
		}

		Node* successor = nullptr;
		if (remove->Left != nil)
			successor = remove->Left;
		else
			successor = remove->Right;

		successor->Parent = remove->Parent;

		if (remove->Parent != nullptr)
		{
			if (remove == remove->Parent->Left)
				remove->Parent->Left = successor;
			else
				remove->Parent->Right = successor;
		}
		else
		{
			(*root) = successor;
		}

		// �����Ϸ��� ���� �������� ��� ���� ����Ʈ���� ������Ű�� ���� ������ ����� �Ѵ�.
		if (remove->Color == Color::Black)
		{
			RebuildRemove(root, successor);
		}

		return remove;
	}

	void RebuildRemove(Node** root, Node* node)
	{
		Node* sibling = nullptr;

		while (node->Parent != nullptr && node->Color == Color::Black)
		{
			if (node == node->Parent->Left)
			{
				sibling = node->Parent->Right;

				if (sibling->Color == Color::Red)
				{
					sibling->Color = Color::Black;
					node->Parent->Color = Color::Red;

					RotateLeft(root, node->Parent);
				}
				else
				{
					if (sibling->Left->Color == Color::Black && sibling->Right->Color == Color::Black)
					{
						sibling->Color = Color::Red;
						node = node->Parent;
					}
					else
					{
						if (sibling->Left->Color == Color::Red)
						{
							sibling->Left->Color = Color::Black;
							sibling->Color = Color::Red;

							RotateRight(root, sibling);
							sibling = node->Parent->Right;
						}

						sibling->Color = node->Parent->Color;
						node->Parent->Color = Color::Black;
						sibling->Right->Color = Color::Black;

						RotateLeft(root, node->Parent);
						node = (*root);
					}
				}
			}
			else
			{
				sibling = node->Parent->Left;

				if (sibling->Color == Color::Red)
				{
					sibling->Color = Color::Black;
					node->Parent->Color = Color::Red;

					RotateRight(root, node->Parent);
				}
				else
				{
					if (sibling->Right->Color == Color::Black && sibling->Left->Color == Color::Black)
					{
						sibling->Color = Color::Red;
						node = node->Parent;
					}
					else
					{
						if (sibling->Right->Color == Color::Red)
						{
							sibling->Right->Color = Color::Black;
							sibling->Color = Color::Red;

							RotateLeft(root, sibling);
							sibling = node->Parent->Left;
						}

						sibling->Color = node->Parent->Color;
						node->Parent->Color = Color::Black;
						sibling->Left->Color = Color::Black;

						RotateRight(root, node->Parent);
						node = (*root);
					}
				}
			}
		}

		node->Color = Color::Black;
	}

private:
	void InsertNodeInternal(Node** node, Node* newNode)
	{
		if (*node == nullptr)
			*node = newNode;

		if ((*node)->Data < newNode->Data)
		{
			if ((*node)->Right == nil)
			{
				(*node)->Right = newNode;
				newNode->Parent = *node;
			}
			else
				InsertNodeInternal(&(*node)->Right, newNode);
		}
		else if ((*node)->Data > newNode->Data)
		{
			if ((*node)->Left == nil)
			{
				(*node)->Left = newNode;
				newNode->Parent = *node;
			}
			else
				InsertNodeInternal(&(*node)->Left, newNode);
		}
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Parent = nullptr;
		node->Left = node->Right = nullptr;
		node->Color = Color::Black;
		node->Data = data;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

private:
	Node* nil;
};