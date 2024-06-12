#pragma once

template <typename T>
class CListNode
{
	// CLinkedList 클래스에서는 이 클래스의 private이나 protected에 접근할 수 있게 한다.
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CListIterator;

private:
	CListNode()
	{

	}

	~CListNode()
	{

	}

private:
	T mData;
	CListNode<T>* mNext = nullptr;	// 다음 노드의 주소를 저장하기 위한 변수
	CListNode<T>* mPrev = nullptr;	// 이전 노드의 주소를 저장하기 위한 변수
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;
public:
	CListIterator()
	{

	}

	~CListIterator()
	{

	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator==(const CListIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}

	bool operator!=(const CListIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}

	// 전위 연산
	void operator++()
	{
		mNode = mNode->mNext;
	}

	// 후위 연산
	void operator++(int)
	{
		mNode = mNode->mNext;
	}

	void operator--()
	{
		mNode = mNode->mPrev;
	}

	void operator--(int)
	{
		mNode = mNode->mPrev;
	}

	// 인자가 없으면 역참조 재정의
	T& operator*()
	{
		return mNode->mData;
	}

	//// 컨버전
	//operator CListNode<T>* ()
	//{
	//	return mNode;
	//}
	// CListNode<int>* Node = iterInt;

	//void* operator new (size_t Size)
	//{
	//	return nullptr;
	//}

	//void operator delete (void* Addr)
	//{
	//}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		mBegin = new Node;
		mEnd = new Node;

		// Begin과 End를 연결
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	~CLinkedList()
	{
		Node* DeleteNode = mBegin;

		while (nullptr != DeleteNode)
		{
			// 먼저 지울 노드의 다음 노드 저장
			// 아래에서 노드 제거 시, 다음 노드의 메모리 주소를 가져올 수 없기 때문
			Node* NextNode = DeleteNode->mNext;

			delete DeleteNode;

			DeleteNode = NextNode;
		}
	}

private:
	// typedef : 타입을 재정의한다. 
	// CListNode<T> 대신에 Node라고만 작성해도 CListNode<T> 타입의 변수를 만들어냄
	// typedef CListNode<T> Node;
	using Node = CListNode<T>;

public:
	using iterator = CListIterator<T>;

private:
	Node* mBegin;	// 리스트의 처음을 나타내는 노드
	Node* mEnd;		// 리스트의 끝을 나타내는 노드
	int mSize;		// 실제 추가된 데이터의 수

public:
	void push_back(const T& data)
	{
		Node* NewNode = new Node;

		NewNode->mData = data;

		// End노드와 End의 이전 노드 사이에 새로 생성한 노드 추가
		Node* Prev = mEnd->mPrev;
		Prev->mNext = NewNode;
		NewNode->mPrev = Prev;

		NewNode->mNext = mEnd;
		mEnd->mPrev = NewNode;

		++mSize;
	}

	void push_front(const T& data)
	{
		Node* NewNode = new Node;

		NewNode->mData = data;

		// End노드와 End의 이전 노드 사이에 새로 생성한 노드 추가
		Node* Next = mBegin->mNext;
		Next->mPrev = NewNode;
		NewNode->mNext = Next;

		NewNode->mPrev = mBegin;
		mBegin->mNext = NewNode;

		++mSize;
	}

	void pop_back()
	{
		if (mSize == 0)
		{
			return;
		}

		// 지울 노드 얻어옴
		Node* DeleteNode = mEnd->mPrev;

		// 지울 노드의 이전 노드의 다음 노드로 End 지정
		// End의 이전 노드로 지울 노드의 이전 노드를 지정
		Node* Prev = DeleteNode->mPrev;

		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		delete DeleteNode;

		--mSize;
	}

	void pop_front()
	{
		if (mSize == 0)
		{
			return;
		}

		// 지울 노드 얻어옴
		Node* DeleteNode = mBegin->mNext;

		// 지울 노드의 다음 노드의 이전 노드로 Begin 지정
		// Begin의 다음 노드로 지울 노드의 다음 노드를 지정
		Node* Next = DeleteNode->mNext;

		Next->mPrev = mBegin;
		mBegin->mNext = Next;

		delete DeleteNode;

		--mSize;
	}

	bool front(T& data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		data = mBegin->mNext->mData;

		return true;
	}

	bool back(T& data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		data = mEnd->mPrev->mData;

		return true;
	}

	int size() const
	{
		return mSize;
	}

	bool empty() const
	{
		return mSize == 0;
	}

	void clear()
	{
		Node* DeleteNode = mBegin->mNext;

		while (DeleteNode != mEnd)
		{
			Node* Next = DeleteNode->mNext;

			delete DeleteNode;

			DeleteNode = Next;
		}

		// Begin과 End를 연결하고 Size를 0으로 초기화
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	// iterator를 생성하고, iterator가 begin노드의 다음 노드를 가지고 있게 하여 반환
	iterator& begin() const
	{
		static iterator iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}

	iterator& end() const
	{
		static iterator iter;
		iter.mNode = mEnd;
		return iter;
	}

	// 지운 노드의 다음 노드를 가지고 있는 iterator를 반환
	iterator erase(const T& Data)
	{
		iterator iter = begin();
		iterator iterEnd = end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == Data)
			{
				break;
			}
		}

		if (iter == iterEnd)
		{
			return iterEnd;
		}

		return erase(iter);
	}

	iterator erase(iterator& iter)
	{
		Node* Prev = iter.mNode->mPrev;
		Node* Next = iter.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		delete iter.mNode;

		iter.mNode = Next;

		return iter;
	}
};