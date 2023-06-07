#include <iostream>
#include <sstream>
using namespace std;

template<class T>
class CircularArrayIterator {
    int current;
    int capacity;
    T* array;

public:
    CircularArrayIterator()
    {
        current = -1;
    }
    CircularArrayIterator(int index, int capacidad, T* array = nullptr)
    {
        current = index;
        capacity = capacidad;
        this->array = array;
    }

    bool operator!=(const CircularArrayIterator& other) {
        return this->current != other.current;
    }

    CircularArrayIterator operator++() {
        current = (current + 1) % capacity;
        return *this;
    }

    CircularArrayIterator operator--() {
        current = (current - 1 + capacity) % capacity;
        return *this;
    }

    T operator*() {
        return array[current];
    }
};

template <class T>
class CircularArray
{
private:
    T* array;
    int capacity;
    int back, front;

public:
    CircularArray(int _capacity = 100);
    //virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    // void clear();
    T& operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep = " ");
    bool operator==(int value);
    typedef CircularArrayIterator<T> iterator;
    void erase(int pos);

    iterator begin()
    {
        return iterator(front, capacity, this->array);
    }

    iterator end()
    {
        return iterator(next(back), capacity, this->array);
    }



private:
    int next(int);
    int prev(int);
};




template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1; // empty
}

template <class T>
bool CircularArray<T>::is_empty()
{
    return (front == -1 && back == -1);
}

//template <class T>
//CircularArray<T>::~CircularArray()
//{
//    delete[] array;
//}

template <class T>
bool CircularArray<T>::is_full()
{
    return ((front == 0 && back == capacity - 1) || (back == front - 1));
}

template <class T>
void CircularArray<T>::push_back(T data)
{
    if (is_full())
    {
        try
        {
            throw overflow_error("arreglo está lleno");
        }
        catch (const exception& ex)
        {
            cout << "Excepción Capturada: " << ex.what() << endl;
        }
    }
    if (is_empty())
    {

        front = back = 0;
    }
    else
    {

        back = next(back);
    }
    array[back] = data;
}

template <class T>
void CircularArray<T>::push_front(T data)
{
    if (is_full())
    {
        try
        {
            throw overflow_error("arreglo está lleno");
        }
        catch (const exception& ex)
        {
            cout << "Excepción Capturada: " << ex.what() << endl;
        }
    }
    if (is_empty())
    {
        front = back = 0;
    }
    else if (front == 0)
    {
        front = capacity - 1;
    }
    else
    {
        front = prev(front);
    }
    array[front] = data;
}

template <class T>
T& CircularArray<T>::operator[](int index)
{
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index out of range.");
    }
    int pos = (front + index) % capacity;

    return array[pos];
}

template <class T>
bool CircularArray<T>::operator==(int value)
{
    if (is_empty())
    {
        return false;
    }
    int i = front;
    /*do
    {
        if (array[i] == value)
        {
            return true;
        }
        i = next(i);

    } while (i != next(back));*/

    return true;

    //return false;
}

template <class T>
bool CircularArray<T>::is_sorted()
{
    if (is_empty())
    {
        return true;
    }

    int i = front;
    T prev = array[i];
    while (i != back)
    {
        int j = next(i);
        if (array[j] < prev)
        {
            return false;
        }
        prev = array[j];
        i = j;
    }

    return true;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    if (is_empty())
    {
        return "";
    }
    std::ostringstream oss;
    int i = front;
    do
    {
        oss << array[i] << sep;
        i = next(i);
    } while (i != next(back));
    return oss.str();
}

template <class T>
T CircularArray<T>::pop_front()
{
    if (is_empty())
    {
        try
        {
            throw overflow_error("el arreglo está vacío");
        }
        catch (const exception& ex)
        {
            cout << "Excepción Capturada: " << ex.what() << endl;
        }
    }

    T data = array[front];
    if (front == back)
    {
        front = back = -1; // empty
    }
    else
    {
        front = next(front);
    }

    return data;
}

template <class T>
int CircularArray<T>::size()
{
    if (back == -1 && front == -1)
    {
        return 0;
    }
    else if (back >= front)
    {
        return back - front + 1;
    }
    else
    {
        return capacity - front + back + 1;
    }
}

template <class T>
void CircularArray<T>::sort()
{
    int i, j;
    int n = size();
    bool ordenado;

    for (i = 0; i < n - 1; i++)
    {
        ordenado = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (array[next(j)] > array[next(j + 1)])
            {
                T temp = array[next(j)];
                array[next(j)] = array[next(j + 1)];
                array[next(j + 1)] = temp;
                ordenado = true;
            }
        }
        if (!ordenado)
            break;
    }
}

template <class T>
void CircularArray<T>::reverse()
{
    int i = front, j = back;
    while (i != j && next(i) != j)
    {
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i = next(i);
        j = prev(j);
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos)
{
    if (is_full())
    {
        T* new_array = new T[capacity * 2];
        int j = 0;
        for (int i = front; i != back; i = next(i))
        {
            new_array[j] = array[i];
            j = next(j);
        }
        new_array[j] = array[back];
        front = 0;
        back = j;
        capacity *= 2;
        delete[] array;
        array = new_array;
    }
    int i = back;
    while (i != pos)
    {
        array[i] = array[prev(i)];
        i = prev(i);
    }
    array[i] = data;
    back = next(back);
}

template <class T>
T CircularArray<T>::pop_back()
{
    if (is_empty())
    {
        try
        {
            throw out_of_range("el arreglo está lleno");
        }
        catch (const exception& ex)
        {
            cout << "Excepción Capturada: " << ex.what() << endl;
        }
    }
    T data = array[back];
    if (front == back)
    {
        front = back = -1;
    }
    else
    {
        back = prev(back);
    }
    return data;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index - 1 + capacity) % capacity;
}

template <class T>
void CircularArray<T>::erase(int pos)
{
    if (is_empty())
    {
        try
        {
            throw out_of_range("el arreglo está vacío");
        }
        catch (const exception& ex)
        {
            cout << "Excepción Capturada: " << ex.what() << endl;
        }
    }
    int index = (front + pos) % capacity;
    for (int i = index; i != back; i = next(i))
    {
        array[i] = array[next(i)];
    }
    back = prev(back);
}
