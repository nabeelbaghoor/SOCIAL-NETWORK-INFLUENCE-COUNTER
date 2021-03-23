#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#pragma warning(disable : 4996)
template<class T>
class Node {
public:
	T data;
	Node<T>* next;
public:
	Node()
	{
		next = nullptr;
	}
	Node(T d, Node<T>* n = nullptr)
		:data(d), next(n)
	{
	}
	T& getData()
	{
		return data;
	}
	~Node()
	{
		if (next != nullptr)
			delete next;
	}
};
template<class T>
class LinkList {
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	class iteratr{
		Node<T>* curr;
	public:
		iteratr(Node<T>* ptr)
		{
			curr = ptr;
		}
		iteratr()
		{
			curr = nullptr;
		}
		bool operator!=(iteratr obj)
		{
			return curr != obj.curr;
		}
		bool operator==(iteratr obj)
		{
			return curr == obj.curr;
		}
		Node<T>* operator++()//itteratr&
		{

			curr = curr->next;
			return curr;
		}
		Node<T>* operator++(int)//itteratr&
		{
			Node<T>* temp = curr;
			curr = curr->next;
			return temp;
		}
		T&operator*()
		{
			return curr->data;
		}
		Node<T>* getNodePtr()
		{
			return curr;
		}
	};
	iteratr begin()
	{
		return iteratr(head);
	}
	iteratr end()
	{
		return iteratr(nullptr);
	}
	LinkList()
	{
		head = tail = nullptr;
		size = 0;
	}
	void InsertAtStart(T d)
	{
		Node<T>* temp = new Node<T>(d, head);
		if (head == nullptr)
			tail = temp;
		head = temp;
		size++;
	}
	void InsertAtEnd(T d)
	{
		Node<T>* temp = new Node<T>(d, nullptr);
		if (head == nullptr)
			head = tail = temp;
		else
		{
			tail->next = temp;
			tail = temp;
		}
		size++;
	}
	void RemoveFromStart()
	{
		if (head != nullptr)
		{
			if (head == tail)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				Node<T>* temp = head->next;
				delete head;
				head = temp;
			}
			size--;
		}
	}
	void RemoveFromEnd()
	{
		if (head != nullptr)
		{
			if (head == tail)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				Node<T>* curr = head;
				while (curr->next != tail)
					curr = curr->next;
				curr->next = nullptr;
				delete tail;
				tail = curr;
			}
			size--;
		}
	}
	bool Search(T d)
	{
		Node<T>* curr = head;
		while (curr != nullptr)
		{
			if (curr->data == d)
				return true;
			curr = curr->next;
		}
		return false;
	}
	void print()
	{
		if (head != nullptr)
		{
			Node<T>* curr = head;
			while (curr != nullptr)
			{
				cout << curr->data << "\t";
				curr = curr->next;
			}
		}
		else
			cout << "The LinkedList Is Empty!!\n";
	}
	int Size()
	{
		return size;
	}
	T& GetTailData()
	{
		return tail->data;
	}
	T& GetHeadData()
	{
		return head->data;
	}
	~LinkList()
	{
	}
};
template<class T>
class Stack {
	LinkList<T> list;
	int size;
	int maxsize;
public:
	Stack(int max = 100)
		:maxsize(max),size(0)
	{
	}
	void Print()
	{
		for (LinkList<int>::iteratr i = list.begin(); i !=list.end(); i++)
			cout << *i << "\t";
	}
	int CurrentSize()
	{
		return size;
	}
	bool IsEmpty()
	{
		return size==0;
	}
	bool IsFull()
	{
		return maxsize == size;
	}
	bool push(const T& d)
	{
		if (!IsFull())
		{
			list.InsertAtEnd(d);
			size++;
			return true;
		}
		return false;
	}
	bool pop(T& d)
	{
		if (!IsEmpty())
		{
			d = list.GetTailData();
			list.RemoveFromEnd();
			size--;
			return true;
		}
		return false;
	}
	void Top(T& d)
	{
		if (!IsEmpty())
		{
			d = list.GetTailData();
		}
	}
	~Stack()
	{
		T d;
		while (!IsEmpty())
			pop(d);
	}
};
template <class T>
class InfluenceNetwork
{
	vector<LinkList<int>>Network;
	int size;
	/*void rCalculateInfluence(Stack<T>& stack, vector<LinkList<int>>net, int Currid, const int Originalid, int* flags, LinkList<int>::iteratr itr)
	{
		if (itr != net[Currid - 1].end())
		{
			flags[Currid - 1] = 1;
			int data = *itr;
			if (!flags[data - 1])
			{
				stack.push(data);
				flags[data - 1] = 1;
				if (net[data - 1].Size() > 1)
					rCalculateInfluence(stack, net, data, Originalid, flags, ++(net[data - 1].begin()));
				rCalculateInfluence(stack, net, Currid, Originalid, flags, ++itr);
			}
			else
				rCalculateInfluence(stack, net, Currid, Originalid, flags, ++itr);
		}
	}*/
	void CalculateInfluence(Stack<T>&stack,int id, int* flags)
	{
		Stack<int>stack2;
		int data;
		if (size != 0)
		{
			stack2.push(Network[id-1].GetHeadData());
			flags[Network[id - 1].GetHeadData() - 1] = 1;
			while (!stack2.IsEmpty())
			{
				stack2.pop(data);
				for (LinkList<int>::iteratr itr=++Network[data - 1].begin(); itr != Network[data - 1].end(); ++itr)
					if (!flags[*itr - 1])
					{
						stack.push(*itr);
						stack2.push(*itr);
						flags[*itr - 1] = 1;
					}
			}

		}
	}
public:
	/*InfluenceNetwork(int s)
		:size(s)
	{
		Network.resize(s);
	}*/
	InfluenceNetwork()
	{
		size = 0;
		Network.empty();
	}
	void Input(string filename) {
		fstream fin;
		fin.open(filename);
		if (fin.is_open() && !fin.eof())
		{
			int i = 0;
			int temp;
			char junk = '1';
			fin >> size;
			Network.resize(size);
			while (!fin.eof() && i<size)
			{
				do {
					fin >> temp;
					if (temp < 1 || temp>size)
					{
						cout << "File Format Not Supported!!\n";
						//Beep(5000);
						Network.~vector();
						size = 0;
						return;
					}
					Network[i].InsertAtEnd(temp);
					junk = fin.get();
				} while (junk != '\n' && junk != EOF);
				i++;
			}
			if (Network.size()!=size || !Network.size() || Network[Network.size() - 1].begin().getNodePtr()==nullptr)
			{
				cout << "File Format Not Supported!!\n";
				//Beep(5000);
				Network.~vector();
				size = 0;
				return;
			}
		}
		else
			cout << "File is Corrupted!!\n";
	}
	void print()
	{
		if (Network.size() && size)
		{
			cout << size << endl;
			for (int i = 0; i < Network.size(); i++)
			{
				Network[i].print();
				cout << endl;
			}
		}
		else
			cout << "Can't Print,No Data Found!!\n";
	}
	void calculate_Influence()
	{
		if (!Network.size() || Network[size - 1].begin().getNodePtr()==nullptr)
		{
			cout << "Can't Calculate Influence,File Format Not Supported!!\n";
		}
		else
		{
			int MaxInfluence = -1;
			int d=0;
			Stack<int>PersonWithMaxInfluence;
			PersonWithMaxInfluence.push(-1);
			int index = 0;
			int* flags = new int[size];
			int id;
			for (int i = 0; i < size; i++)
			{
				Stack<int>stack(size - 1);
				id = Network[i].GetHeadData();
				for (int i = 0; i < size; i++)
					flags[i] = 0;
				//rCalculateInfluence(stack, Network, id, id, flags, ++(Network[id - 1].begin()));
				CalculateInfluence(stack,id,flags);
				if (stack.CurrentSize() > MaxInfluence)
				{
					MaxInfluence = stack.CurrentSize();
					PersonWithMaxInfluence.~Stack();
					PersonWithMaxInfluence.push(Network[i].GetHeadData());
				}
				else if (MaxInfluence && stack.CurrentSize() == MaxInfluence)
					PersonWithMaxInfluence.push(Network[i].GetHeadData());
				cout << Network[i].GetHeadData() << " Influence " << stack.CurrentSize() << " Persons:" << endl;
				stack.Print();
				cout << endl;
			}
			if (MaxInfluence && PersonWithMaxInfluence.CurrentSize() > 1)
				cout << "There are " << PersonWithMaxInfluence.CurrentSize() << " Persons with Maximum Influence!!" << endl << endl;
			if (MaxInfluence && PersonWithMaxInfluence.CurrentSize() != 0 && MaxInfluence!=-1)//PersonWithMaxInfluence[0] != -1
			{
				while (!PersonWithMaxInfluence.IsEmpty())
				{
					PersonWithMaxInfluence.pop(d);
					cout << "Person With Maximum Influence: " << d << endl;
					cout << "(Influence of Person:" << d<< " is " << MaxInfluence << " )" << endl << endl;
				}
			}
			else
				cout << "Can't Calculate Influence!!\n(No Person has Influence)" << endl << endl;
		}

	}
};
int main()
{
	InfluenceNetwork<int> n;
	n.Input("a.txt");
	n.print();
	n.calculate_Influence();
	system("pause");
}