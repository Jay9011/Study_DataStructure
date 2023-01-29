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
		* 자신 기준 parent와 parent가 위치해야 할 child(Right Child)의 위치를 바꾸기 시작합니다.
		*/
		// parent의 자신 위치에 child(Right Child)로 바꿔줍니다.
		parent->Left = leftChild->Right;

		// child(Right Child)의 parent도 바뀐 parent로 바꿔줍니다.
		if (leftChild->Right != nil)
			leftChild->Right->Parent = parent;
		// (Right Child 연결 끝, Left Child와 parent는 연결이 끊김...)

		/*
		* 자신의 위치와 parent의 Parent 위치를 바꾸기 시작합니다.
		*/ 
		leftChild->Parent = parent->Parent;
		if (parent->Parent != nullptr)
		{
			// 바꿀 parent의 위치가 parent의 부모의 좌측이면 바꾸려는 자신을 좌측에,
			// 부모의 우측이면 바꾸려는 자신을 우측에 연결해줍니다.
			// (parent의 부모에 자신을 연결합니다.)
			if (parent == parent->Parent->Left)
				parent->Parent->Left = leftChild;
			else
				parent->Parent->Right = leftChild;
		}
		else
		{
			// parent가 Root 였다면 root를 자신으로 만듭니다.
			(*root) = leftChild;
		}

		/*
		* 이후 바꾸는 두 대상을 서로 바꿔서 연결해줍니다.
		* (자식과 부모를 바꿉니다.)
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
		// Red로 삽입하는데, parent가 Red였을 때
		while (node != (*root) && node->Parent->Color == Color::Red)
		{
			// parent가 parent의 부모의 왼쪽인 경우
			if (node->Parent == node->Parent->Parent->Left)
			{
				Node* uncle = node->Parent->Parent->Right;

				// U가 Red인 경우 [Recoloring] 적용
				if (uncle->Color == Color::Red)
				{
					// 위쪽의 두 노드(parent와 uncle)를 검은색으로 만들고
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					// 그 위의 노드(parent의 부모)를 빨간색으로 만듭니다.
					node->Parent->Parent->Color = Color::Red;

					// 이후 parent가 4번 규칙(Red-Black)을 어겼는지 올라가서 다시 확인합니다.
					node = node->Parent->Parent;
				}
				// U가 Black인 경우 [Restructuring] 적용
				else
				{
					// 오른쪽에 붙은 경우 회전을 위해 먼저 좌회전을 합니다.
					if (node == node->Parent->Right)
					{
						node = node->Parent;
						RotateLeft(root, node);
					}

					// parent와 parent의 부모 노드의 색을 바꿔준 후
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					// 우회전을 통해 Red-Black 규칙을 적용합니다.
					RotateRight(root, node->Parent->Parent);
				}
			}
			// parent가 parent의 부모의 오른쪽인 경우
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

		// 마지막 Root는 검은색으로 변경해줍니다.
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

		// 제거하려는 색이 검은색인 경우 균형 이진트리를 유지시키기 위해 리빌딩 해줘야 한다.
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