#pragma once
#include <iostream>
using namespace std;

template<class T>
class List
{
private:

	struct Node
	{
		T value;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;

	int size;

public:

	List() : head(nullptr), tail(nullptr), size(0) { }

	List(const List& other)
	{
		Node* current = other.head;
		while (current != nullptr)
		{
			AddToTail(current->value);
			current = current->next;
		}
	}

	List(List&& other)
	{
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;
	}

	List& operator=(List&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		if (this != nullptr)
		{
			while (!IsEmpty())
			{
				DeleteHead();
			}
		}

		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;

		return *this;
	}

	List& operator=(const List& other)
	{
		if (this == &other)
		{
			return *this;
		}

		if (this != nullptr)
		{
			while (!IsEmpty())
			{
				DeleteHead();
			}
		}

		Node* current = other.head;
		while (current != nullptr)
		{
			AddToTail(current->value);
			current = current->next;
		}
		return *this;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}
	int GetCount() const
	{
		return size;
	}


	void AddToHead(T value)
	{

		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = head;
		newElem->prev = nullptr;

		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			head->prev = newElem;
			head = newElem;
		}
		++size;
	}

	void AddToTail(T value)
	{
		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = nullptr;
		newElem->prev = tail;

		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			tail->next = newElem;
			tail = newElem;
		}
		++size;
	}

	void DeleteHead()
	{
		if (IsEmpty()) return;
		Node* temp = head->next;
		delete head;

		if (temp == nullptr)
		{
			head = tail = nullptr;
		}
		else
		{
			temp->prev = nullptr;
			head = temp;
		}
		--size;
	}

	void DeleteTail()
	{

		if (IsEmpty()) return;

		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node* temp = tail->prev;
			delete temp->next;
			temp->next = nullptr;
			tail = temp;
		}
		--size;
	}

	void Add(T value, int pos)
	{
		if (pos <= 0 || pos > size + 1) return;

		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}

		Node* newElem = new Node;
		newElem->value = value;

		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		newElem->prev = current->prev;
		current->prev->next = newElem;

		current->prev = newElem;
		newElem->next = current;

		++size;
	}

	void Delete(int pos)
	{
		if (pos <= 0 || pos > size) return;

		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		Node* current = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			current = current->next;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;

		--size;
	}

	void Print() const
	{
		for (Node* current = head; current != nullptr; current = current->next)
		{
			cout << current->value << ", ";
		}
	}

	int Find(T data)
	{
		Node* current = head;

		for (int i = 0; i < size; i++)
		{
			if (current->value == data)
			{
				return i;
			}
			current = current->next;
		}
		return -1;
	}

	int Replace(T oldValue, T newValue)
	{
		Node* current = head;
		int counter = 0;
		for (int i = 0; i < size; i++)
		{
			if (current->value == oldValue)
			{
				current->value = newValue;
				++counter;
			}
			current = current->next;
		}
		return counter;
	}
	List operator-()
	{
		List new_list;

		for (Node* current = tail; current != nullptr; current = current->prev)
		{
			new_list.AddToTail(current->value);
		}

		return new_list;
	}

	List operator+(const List& other)
	{
		List new_list;

		Node* current = this->head;
		for (int i = 0; i < this->size; i++)
		{
			new_list.AddToTail(current->value);
			current = current->next;
		}

		Node* current2 = other.head;
		for (int i = 0; i < other.size; i++)
		{
			new_list.AddToTail(current2->value);
			current2 = current2->next;
		}

		return new_list;
	}

	List operator*(const List& other)
	{
		List new_list;

		Node* current = this->head;
		for (int i = 0; i < this->size; i++)
		{
			Node* current2 = other.head;
			for (int i = 0; i < other.size; i++)
			{
				if (current->value == current2->value)
				{
					new_list.AddToTail(current2->value);
					break;
				}

				current2 = current2->next;
			}
			current = current->next;
		}
		return new_list;
	}

	void DeleteAll()
	{
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}

	~List()
	{
		DeleteAll();
	}

};


