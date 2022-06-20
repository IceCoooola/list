#pragma once
#include<assert.h>

namespace IceCola
{
	//list node
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T()):_next(nullptr), _val(val), _prev(nullptr){}
		
		T _val;
		ListNode<T>* _next;
		ListNode<T>* _prev;
	};

	//iterator
	template<class T, class reference, class pointer>
	class ListIterator 
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, reference, pointer> self;
	public:
		ListIterator(Node* node = nullptr):_node(node){}

		ListIterator(const self& x)
		{
			_node = x._node;
		}

		bool operator!=(const self& n) const
		{
			return _node != n._node;
		}

		bool operator==(const self& n) const
		{
			return _node == n._node;
		}

		pointer operator->()
		{
			return &(_node->_val);
		}

		reference operator*()
		{
			return _node->_val;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		Node* _node;
	};

	//list
	template<class T>
	class list
	{
		typedef ListNode<T> Node;

	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		//constructor
		list() 
		{ 
			_pHead = new Node;
			_pHead->_next = _pHead; 
			_pHead->_prev = _pHead;
		}

		list(int n, const T& value = T())
		{
			_pHead = new Node;
			_pHead->_next = _pHead;
			_pHead->_prev = _pHead;
			for (int i = 0; i < n; ++i)
			{
				push_back(value);
			}
		}

		template<class inputIterator>
		list(inputIterator first, inputIterator last)
		{
			_pHead = new Node;
			_pHead->_next = _pHead;
			_pHead->_prev = _pHead;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& lt)
		{
			_pHead = new Node;
			_pHead->_next = _pHead;
			_pHead->_prev = _pHead;
			list tmp(lt.begin(), lt.end());
			swap(tmp);
			//iterator it = lt.begin();
			//while (it != lt.end())
			//{
			//	push_back(*it);
			//	it++;
			//}
		}

		list<T>& operator=(const list<T>& lt)
		{
			list tmp(lt.begin(), lt.end());
			swap(tmp);
			return *this;
		}

		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		// List Iterator
		iterator begin()
		{
			return iterator(_pHead->_next);
		}
		 
		iterator end()
		{
			return iterator(_pHead);
		}

		const_iterator begin() const
		{
			return const_iterator(_pHead->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_pHead);
		}

		//capacity
		size_t size() const
		{
			size_t sz = 0;
			iterator cur = begin();
			while (cur != end())
			{
				++sz;
				++cur;
			}
			return sz;
		}
		
		//判空
		bool empty() const
		{
			return (begin() == end());
		}

		//access
		T& front()
		{
			return _pHead->_next->_val;
		}

		const T& front() const
		{
			return _pHead->_next->_val;
		}

		T& back()
		{
			return _pHead->_prev->_val;
		}
		
		const T& back() const
		{
			return _pHead->_prev->_val;
		}

		//modify
		void push_back(const T& val)
		{
			insert(end(), val);
			//Node* newNode = new Node;
			//newNode->_val = val;
			//Node* prev = _pHead->_prev;
			//prev->_next = newNode;
			//newNode->_prev = prev;
			//newNode->_next = _pHead;
			//_pHead->_next = newNode;
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos._node);
			Node* newNode = new Node(val);
			Node* prev = pos._node->_prev;
			Node* next = pos._node;
			prev->_next = newNode;
			newNode->_prev = prev;
			newNode->_next = next;
			next->_prev = newNode;
			return iterator(newNode);
		}

		iterator erase(iterator pos)
		{
			assert(pos._node);
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			delete pos._node;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(list, *this);
		}
	private:
		Node* _pHead;
	};
}
