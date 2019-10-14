#pragma once
#include "ABS.h"
template<typename T>

class ABQ {

private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;
	T scaleFactor = 2.0f;

public:
	ABQ();
	ABQ(int capacity);
	ABQ(const ABS<T>& d);
	ABQ& operator=(const ABQ&);
	~ABQ();
	void enqueue(T data);
	T dequeue();
	T peek();
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();
};

template<typename T>
ABQ<T>::ABQ() {
	// Default Constructor
	// Maximum capacity should be set to 1 and current size set to 0

	data = nullptr;
	capacity = 1;
	size = 0;
}

template<typename T>
ABQ<T>::ABQ(int _capacity) {
	//Constructor for an ABQ with the specified starting maximim capacity

	capacity = _capacity;
	size = 0;
	data = new T[capacity];
}

template<typename T>
ABQ<T>::ABQ(const ABS<T>& d) {
	// Copy Constructor

	capacity = d.capacity;
	size = d.size;
	data = nullptr;

	data = new T[d.capacity]; //Allocating space
	for (int i = 0; i < size; i++) {  //Copy existing data into new space
		data = d.data[i];
	}
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d) {
	//Assignment Operator

	//1. Delete old data
	delete[] data;

	//2. Copy non-dynamic variables
	capacity = d.capacity;
	size = d.size;
	data = nullptr;

	//3. Allocate space for some data
	T* newData = new T[capacity];

	//4. Copy existing data into new space
	for (int i = 0; i < size; i++) {
		newData = d.data[i];
	}

	return *this;

}

template<typename T>
ABQ<T>::~ABQ() {
	// Destructor
	delete[] data;
}

template<typename T>
void ABQ<T>::enqueue(T _data) {
	// Add a new item to the end of the queue and recize if necessary

	if (data == nullptr) {
		data = new T[1];
		data[0] = _data;
		capacity = 1;
		size = 1;
	}
	else if (size == capacity) {
		T* newArray = new T[(int)(capacity * (scaleFactor))];
		for (int i = 0; i < size; i++) {
			newArray[i] = data[i];
		}
		newArray[size] = _data;
		size++;
		capacity = (int)(capacity * (scaleFactor));
		delete[] data;
		data = newArray;
	}
	else if (size < capacity) {
		data[size] = _data;
		size++;
	}
}

template<typename T>
T ABQ<T>::dequeue() {
	//Remove the item at the top of the stack, resizes if necessary, and return the value removed.
	//Throws a runtime_error if the stack is empty.

	if (size == 0) {
		throw runtime_error("Item not peeked at properly!");
	}
	else {
		T topValue = data[0];
		data[size] = 0;
		size--;

		T* newArray = new T[capacity];
		for (int i = 0; i < size; i++) {
			newArray[i] = data[i+1];
		}

		if (((float)(size) / (float)(capacity)) < (1.0 / (scaleFactor))) {
			capacity = (int)(capacity / (int)(scaleFactor));
		}

		delete[] data;
		data = newArray;

		return topValue;
	}
}

template<typename T>
T ABQ<T>::peek() {
	// Return the value of the item at the front of the queue without removing it.
	// Throw a runtime_error if the queue is empty.

	if (size == 0) {
		throw runtime_error("Item not peeked at properly!");
	}
	else {
		return data[0];
	}
}

template<typename T>
unsigned int ABQ<T>::getSize() {
	// Returns the current number of items in the ABQ
	return size;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity() {
	//Returns the current max capacity of the ABQ
	return capacity;
}

template<typename T>
T* ABQ<T>::getData() {
	// Returns the array representing the queue
	return data;
}

