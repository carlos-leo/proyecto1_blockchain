#include <iostream>

template <class T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node() {
		next = nullptr;
		prev = nullptr;
	}

	Node(T value) {
		data = value;
		next = nullptr;
		prev = nullptr;
	}

};

template <typename T>
class CircularDoubleListIterator {
private:
	Node<T>* current;

public:
	CircularDoubleListIterator(Node<T>* node) {
		current = node;
	}

	bool operator!=(const CircularDoubleListIterator& other) {
		return current != other.current;
	}


	CircularDoubleListIterator operator++() {
		current = current->next;
		return *this;
	}

	CircularDoubleListIterator operator--() {
		current = current->prev;
		return *this;
	}

	T operator*() {
		return current->data;
	}

	Node<T>* GetCurrent() {
		return current;
	}
};


template <typename T>
class CircularDoubleList {
private:
	Node<T>* head;
	int nodes;
	Node<T>* current;

public:
	typedef CircularDoubleListIterator<T> iterator;

	CircularDoubleList() {
		head = new Node<T>(T());
		head->next = head;
		head->prev = head;
		nodes = 0;
		current = nullptr;
	}

	~CircularDoubleList() {
		while (nodes > 0) {
			pop_front();
		}
		delete head;
	}

	iterator begin() {
		return iterator(head->next);
	}

	iterator end() {
		return iterator(head);
	}

	void push_front(T data) {
		Node<T>* nuevo = new Node<T>(data);
		nuevo->next = head->next;
		nuevo->prev = head;
		head->next->prev = nuevo;
		head->next = nuevo;
		nodes++;
	}

	void push_back(T data) {
		Node<T>* nuevo = new Node<T>(data);
		nuevo->next = head;
		nuevo->prev = head->prev;
		head->prev->next = nuevo;
		head->prev = nuevo;
		nodes++;
	}

	T pop_front() {
		if (head->next == head) {
			throw std::out_of_range("List is empty");
		}
		Node<T>* temp = head->next;
		T data = temp->data;
		head->next = temp->next;
		temp->next->prev = head;
		delete temp;
		nodes--;
		return data;
	}

	T pop_back() {
		if (head->prev == head) {
			throw std::out_of_range("List is empty");
		}
		Node<T>* temp = head->prev;
		T data = temp->data;
		head->prev = temp->prev;
		temp->prev->next = head;
		delete temp;
		nodes--;
		return data;
	}

	void pop(Node<T>* pos) {
		if (pos == nullptr || pos == head) {
			throw std::out_of_range("Invalid position");
		}

		if (pos == current) {
			current = pos->next;
		}

		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete pos;
		nodes--;
	}


	bool is_empty() {
		return nodes == 0;
	}

	void display() {
		if (is_empty()) {
			std::cout << "List is empty" << std::endl;
			return;
		}
		Node<T>* current = head->next;
		while (current != head) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	int size() const {
		return nodes;
	}

	T back() {
		if (head->prev == head) {
			throw std::out_of_range("List is empty");
		}
		return head->prev->data;
	}

	void SetCurrent(Node<T>* node) {
		current = node;
	}

	Node<T>* GetCurrent() {
		return current;
	}
};