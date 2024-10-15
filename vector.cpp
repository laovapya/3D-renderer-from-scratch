#include <iostream>

template<class T>
class vector {

private:
	int count = 0;
	int arrSize = 2;
	const int arrInitSize = 8;
	T* arr;

	void reinitialize() {

		int newSize = arrSize * 2;
		T* newArr = new T[newSize];
		for (int i = 0; i < count; ++i)
			newArr[i] = arr[i];

		delete[] arr;
		arr = newArr;
		arrSize = newSize;
	}
public:
	vector() {
		arrSize = arrInitSize;
		arr = new T[arrSize];
	}

	~vector() {
		delete[] arr;
	}

	int size() {
		return count;
	}

	int capacity() {
		return arrSize;
	}

	bool empty() {
		return count == 0;
	}

	T& front() {
		if (empty())
			std::cout << "vector is empty\n";
		return arr[0];
	}

	T& back() {
		if (empty())
			std::cout << "vector is empty\n";
		return arr[count - 1];
	}

	void push_back(const T& value) {
		if (count >= arrSize) 
			reinitialize();
		arr[count++] = value;
	}

	void pop_back() {
		if (count > 0) 
			--count;
	}

	void clear() {
		count = 0;
	}

	void erase(int index) {
		if (index >= count || index < 0) {
			std::cout << "index out of bounds\n";
			return;
		}
		
		--count;
		T* newArr = new T[arrSize];
		for (int i = 0; i < index; ++i)
			newArr[i] = arr[i];
		for (int i = index; i < count; ++i)
			newArr[i] = arr[i + 1];

		delete[] arr;
		arr = newArr;
	}

	void erase(int first, int last) {
		if (last < first || first >= count || first < 0 || last >= count || last < 0) {
			std::cout << "index out of bounds\n";
			return;
		}
		int totalRemoved = last - first + 1;
		count -= totalRemoved;
		T* newArr = new T[arrSize];
		for (int i = 0; i < first; ++i)
			newArr[i] = arr[i];
		for (int i = first; i < count; ++i)
			newArr[i] = arr[i + totalRemoved];

		delete[] arr;
		arr = newArr;
	}

	void insert(int index, const T& value) {
		if (index >= count - 1 || index < 0) {
			std::cout << "index out of bounds\n";
			return;
		}

		++count;
		T* newArr = new T[arrSize];
		for (int i = 0; i < index; ++i)
			newArr[i] = arr[i];
		newArr[index] = value;
		for (int i = index + 1; i < count; ++i)
			newArr[i] = arr[i - 1];

		delete[] arr;
		arr = newArr;
	}

	T& operator[](int index) {
		if (index >= count || index < 0) 
			std::cout << "index out of bounds\n";
		
		return arr[index];
	}
};
