#pragma once

template<typename T>
class container
{
	T* cont;
	size_t size;
	size_t capacity;

	void copy(const container& other);
	void move_copy(container&& other);
	void free();
	void resize();
	void resize(size_t cap);
	void rearange();
public:
	container();
	container(const size_t capacity, const size_t size);
	container(const container& other);
	container<T>& operator=(const container& other);
	container(container&& other);
	container<T>& operator=(container&& other);
	~container();

	void remove_item(const T& item);
	T& operator[](size_t pos);
	T operator[](size_t pos) const;
	void add_item(const T& item);
	int find_item(const T& item) const;
	size_t get_capacity() const;
	size_t get_size() const;
	bool is_empty() const;
	void print_list() const;
	void load_from_file_list(string file_name);
	
	friend std::ostream& operator<<(std::ostream& stream,const container<T>& cont)// inline because https://stackoverflow.com/questions/27207043/overloading-the-operator-in-a-templated-class-gives-me-linker-errors-c
	{
		stream.write((char*)&cont.capacity, sizeof(size_t));
		stream.write((char*)&cont.size, sizeof(size_t));
		for (size_t i = 0; i < cont.capacity; i++)
		{
			stream << cont.cont[i];
		}
		return stream;
	}

	friend std::istream& operator>>(std::istream& stream, container<T>& cont)
	{
		stream.read((char*)&cont.capacity, sizeof(size_t));
		stream.read((char*)&cont.size, sizeof(size_t));
		cont.resize(cont.capacity);
		for (size_t i = 0; i < cont.capacity; i++)
		{
			stream >> cont.cont[i];
		}
		return stream;
	}
	void initial();
};

template <typename T>
container<T>::container()
{
	size = 0;
	capacity = 8;
	cont = new T[capacity]; 
	initial();
}

template <typename T>
container<T>::container(const container<T>& other)
{
	copy(other);
}

template <typename T>
container<T>::container(const size_t capacity, const size_t size)
{
	this->capacity = capacity;
	this->size = size;
	cont = new T[capacity]();
	initial();
}

template <typename T>
container<T>& container<T>::operator=(const container<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <typename T>
container<T>::container(container<T>&& other)
{
	move_copy(other);
}

template <typename T>
container<T>& container<T>::operator=(container<T>&& other)
{
	free();
	move_copy(other);
	return *this;
}

template <typename T>
container<T>::~container()
{
	free();
}

template <typename T>
void container<T>::copy(const container<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	cont = new T[capacity]();
	for (size_t i = 0; i < capacity; i++)
	{
		cont[i] = other.cont[i];
	}
}

template <typename T>
void container<T>::move_copy(container<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	cont = other.cont;
	other.cont = nullptr;
}

template <typename T>
void container<T>::free()
{
	delete[] cont;
}

template <typename T>
void container<T>::rearange()
{
	size_t mid_pt = capacity / 2;
	T empty = T();
	for (size_t i = capacity; i >= mid_pt && i; i--)	// going backwards if we find item we move it in
	{													// the first free position
		if (!(cont[i] == empty))							
		{												
			cont[find_item(empty)] = cont[i];			
		}
	}
}

template <typename T>
void container<T>::resize()
{
	if (size == capacity)
	{
		
		container<T> temp = *this;					    // if size == capacity then we double the space
		free();										    
		capacity *= 2;									
		cont = new T[capacity];
		initial();
		for (size_t i = 0; i < size; i++)
		{
			cont[i] = temp.cont[i];
		}
	}
	else if (capacity > 8 && size < capacity / 2)		 // if size == half of the capacity then 
	{													 // we need to rearange all items then chop
		container<T> temp = *this;						 // the empty half of the container
		temp.rearange();
		free();
		capacity /= 2;
		cont = new T[capacity];
		initial();
		for (size_t i = 0; i < size; i++)
		{
			cont[i] = temp.cont[i];
		}
	}
}

template <typename T>
void container<T>::resize(size_t cap)
{
	free();
	cont = new T[cap];
	initial();
}

template <typename T>
void container<T>::add_item(const T& item)
{
	resize();
	++size;
	T empty = T();
	int item_pos = find_item(empty);
	if (item_pos == -1)
		throw std::invalid_argument("Item doesn't exist in container");
	
	cont[item_pos] = item;
}

template <typename T>
void container<T>::remove_item(const T& item)
{
	int item_pos = find_item(item);
	if (item_pos == -1)
		throw std::invalid_argument("Item doesn't exist in container");
	T empty = T();
	cont[item_pos] = empty;
	size--;
	resize();
}

template <typename T>
size_t container<T>::get_capacity() const
{
	return capacity;
}

template <typename T>
size_t container<T>::get_size() const
{
	return size;
}

template <typename T>
T& container<T>::operator[](size_t pos)
{
	if (pos < 0 || pos > capacity)
		throw std::invalid_argument("Invalid position");

	T empty = T();
	if (cont[pos] == empty)
		throw std::invalid_argument("Empty spot");

	return cont[pos];
}

template <typename T>
T container<T>::operator[](size_t pos) const
{
	if (pos < 0 || pos > capacity)
		throw std::invalid_argument("Invalid position");

	T empty = T();
	if (cont[pos] == empty)
		throw std::invalid_argument("Empty spot");

	return cont[pos];
}

template <typename T>
int container<T>::find_item(const T& item) const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (cont[i] == item) return i;
	}
	return -1;
}

template <typename T>
bool container<T>::is_empty() const
{
	T empty = T();
	for (size_t i = 0; i < capacity; i++)
	{
		if (cont[i] != empty) return false;
	}
	return true;
}

template <typename T>
void container<T>::print_list() const
{
	T empty = T();
	for (size_t i = 0; i < capacity; i++)
	{
		if (cont[i] != empty)
			std::cout << i + 1 << ". " << cont[i].get_name() << std::endl;
	}
}

template <typename T>
void container<T>::load_from_file_list(string file_name)
{
	std::ifstream stream(file_name.get_str(), std::ios::binary);

	if (!stream)
		throw std::invalid_argument("No such file exists or file could not be loaded");

	T loading_item;
	while (stream.peek() != EOF)
	{
		stream >> loading_item;
		add_item(loading_item);
	}
}

template <typename T>
void container<T>::initial()
{
	T empty = T();
	for (size_t i = 0; i < capacity; i++)
	{
		cont[i] = empty;
	}
}