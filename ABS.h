#pragma once
#include <iostream>
#include <string>
using namespace std;
template <typename T>

class ABS {

private:
	T* data;
	int size;
	int capacity;
	T scaleFactor = 2.0f;

public:
	ABS();
	ABS(int capacity);
	ABS(const ABS& d);
	ABS& operator=(const ABS& d);
	~ABS();
	void push(T _data);
	T pop();
	T peek();
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();

};


template<typename T>
ABS<T>::ABS() {
	//Default constructor
	//Max capacity should be set to 1 and current size set to 0.

	data = nullptr;
	capacity = 1;
	size = 0;
}

template<typename T>
ABS<T>::ABS(int _capacity) {
	//Constructor for an ABS with the specified starting maximum capacity.

	capacity = _capacity;
	size = 0;
	data = new T[capacity];
}

template<typename T>
ABS<T>::ABS(const ABS& d) {
	//Copy Construtor

	capacity = d.capacity;
	size = d.size;
	data = nullptr;

	data = new T[d.capacity]; 
	for (int i = 0; i < size; i++) {
		data[i] = d.data[i];
	}
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& d) {
	// Assignment operator

	delete[] data;

	capacity = d.capacity;
	size = d.size;

	T* newData = new T[capacity];

	for (int i = 0; i < size; i++) {
		newData[i] = d.data[i];
	}

	return *this;
}

template<typename T>
ABS<T>::~ABS() {
	// Destructor
	delete[] data;
}

template<typename T>
void ABS<T>::push(T _data) {
	// Add a new item to the top of the stack and resize if necessary.

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
T ABS<T>::pop() {
	//Remove the item at the top of the stack, resizes if necessary, and return the value removed.
	//Throws a runtime_error if the stack is empty.
	
		if (size == 0) {
			throw runtime_error("Item not popped properly!");
		}
		else {
			T topValue = data[size - 1];
			data[size - 1] = 0;
			size--;

			T* newArray = new T[capacity - 1];
			for (int i = 0; i < size; i++) {
				newArray[i] = data[i];
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
T ABS<T>::peek() {
	//Return the value of the item at the top of the stack without removing it.
	//Throws a runtime_error if the stack is empty.

	if (size == 0) {
		throw runtime_error("Item not peeked at properly!");
	}
	else {
		return data[size - 1];
	}

}

template<typename T>
unsigned int ABS<T>::getSize() {
	// Returns the current number of items in the ABS.

	return size;
}

template<typename T>
unsigned int ABS<T>::getMaxCapacity() {
	//Retruns the current max capacity of the ABS

	return capacity;
}

template<typename T>
T* ABS<T>::getData() {
	//Returns the array representing the stack.

	return data;
}

