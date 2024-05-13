#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Music
{
	T data;
	Music* prev;
	Music* next;
};

template <typename T>
class PlayList
{
public:
	using node = Music<T>;
	using node_ptr = node*;

private:
	node_ptr head;

public:
	// iterator
	struct PlayList_Iterator
	{
	private:
		node_ptr ptr;

	public:
		PlayList_Iterator(node_ptr p) : ptr(p) {}
		
		string& operator*() { return ptr->data; }
		
		node_ptr get() { return ptr; }
		
		PlayList_Iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		PlayList_Iterator operator++(int)
		{
			PlayList_Iterator result = *this;
			++(*this);
			return result;
		}

		PlayList_Iterator& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}

		PlayList_Iterator operator--(int)
		{
			PlayList_Iterator result = *this;
			--(*this);
			return result;
		}

		friend bool operator==(const PlayList_Iterator& left, const PlayList_Iterator& right)
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const PlayList_Iterator& left, const PlayList_Iterator& right)
		{
			return left.ptr != right.ptr;
		}
	};

	PlayList_Iterator begin() { return PlayList_Iterator(head); }
	PlayList_Iterator end() { return PlayList_Iterator(head->prev); }
	PlayList_Iterator begin() const { return PlayList_Iterator(head); }
	PlayList_Iterator end() const { return PlayList_Iterator(head->prev); }


	// insert
	void insert(T name)
	{
		auto new_node = new node{ name, nullptr, nullptr };
		if (head != nullptr)
		{
			new_node->next = head;
			new_node->prev = head->prev;
			head->prev = new_node;
		}
		head = new_node;
		head->prev->next = head;
	}

	// delete
	void remove(T name)
	{

	}

	// print
	void printall()
	{
		auto tmp = head;
		while (tmp != nullptr)
		{
			cout << tmp->data << ", ";
			tmp = tmp->next;
		}
		cout << endl;
	}


	// constructor
	PlayList() : head(nullptr) {}
	PlayList(const PlayList<T>& other) : head(nullptr)
	{
		for (auto it = rbegin(other); it != rend(other); it++)
		{
			insert(*it);
		}
	}
	PlayList(const initializer_list<T>& ilist) : head(nullptr)
	{
		for (auto it = rbegin(ilist); it != rend(ilist); it++)
		{
			insert(*it);
		}
	}
};

int main()
{
	PlayList<string> PL;

	PL.insert("1");
	PL.insert("2");
	PL.printall();


	return 0;
}
