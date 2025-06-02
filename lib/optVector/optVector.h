#pragma once

template<typename T>
class optVector {
private:
    char capacity = 1;
    bool isEmpty = true;
    T* data;
    void resize();
public:
    optVector();
    optVector(const optVector<T>& obj);
    optVector(const T obj[], char n);
    optVector(T obj[], char n);

    T& operator[](char index);
    T operator[](char index) const;
    optVector<T>& operator=(optVector<T>& obj);
    optVector<T>& operator=(T* obj);

    optVector<T> operator+(optVector<T>& obj);
    ~optVector();

    T getByIndex(char i);
    void del(char index);
    void push(const T& obj);
    char len() const;
    bool empty();
};

template<typename T>
optVector<T>::optVector()
{
    capacity = 1;
    data = new T[capacity];
}

template<typename T>
optVector<T>& optVector<T>::operator=(T* obj) {
    capacity = 1;
    resize();

    data[0] = *obj;
    isEmpty = false;
    return *this;
}

template<typename T>
T optVector<T>::getByIndex(char i) {
    T resp = data[i];
    return resp;
}

template<typename T>
optVector<T>::optVector(const T obj[], char n) {
    capacity = getLenFromArray(obj);

    resize();
    for (char i = 0; i < capacity; i++)
        data[i] = obj[i];
    isEmpty = false;
}

template<typename T>
optVector<T>::optVector(T obj[], char n) {
    capacity = n;

    resize();
    for (char i = 0; i < capacity; i++)
        data[i] = obj[i];
    isEmpty = false;
}

template<typename T>
void optVector<T>::resize() {
    if (!empty())
        delete[] data;

    if (capacity <= 0)
        capacity = 1;
    data = new T[capacity];
}

template<typename T>
optVector<T>::optVector(const optVector<T>& obj) {
    capacity = obj.len();

    resize();
    for (char i = 0; i < capacity; i++)
        data[i] = obj[i];
    isEmpty = false;
}

template<typename T>
T& optVector<T>::operator[](char index) {
    if (index >= capacity || index < 0) {
        static T dummy;
        return dummy;
    }
    return data[index];
}

template<typename T>
T optVector<T>::operator[](char index) const {
    if (index >= capacity || index < 0) {
        static T dummy;
        return dummy;
    }
    return data[index];
}

template<typename T>
optVector<T>::~optVector()
{
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

template<typename T>
optVector<T>& optVector<T>::operator=(optVector<T>& obj) {
    if (this != &obj)
    {
        capacity = obj.capacity;
        resize();
        for (char i = 0; i < capacity; i++)
            data[i] = obj[i];
        isEmpty = false;
        return *this;
    }
    return *this;
}

template<typename T>
void optVector<T>::del(char index) {
    if (index >= capacity || capacity <= 0)
        return;

    T* newData = new T[capacity - 1];

    for (char i = 0, j = 0; i < capacity; i++) {
        if (i != index)
            newData[j++] = data[i];
    }

    delete[] data;
    data = newData;
    capacity--;
}

template<typename T>
optVector<T> optVector<T>::operator+(optVector<T>& str) {
    const char newLen = capacity + str.capacity;
    char index = 0;
    T* newStr = new T[newLen];
    while (index < capacity)
    {
        newStr[index] = data[index];
        index++;
    }

    char index2 = 0;
    while (index < str.capacity)
    {
        newStr[index] = str[index2];
        index++;
        index2++;
    }
    return optVector<T>(newStr);
}

template<typename T>
void optVector<T>::push(const T& obj) {
    if (empty() && capacity == 1)
    {
        data[0] = obj;
        isEmpty = false;
        return;
    }
    T* oldData = data;
    char oldCapacity = capacity;

    capacity++;
    data = new T[capacity];

    for (char i = 0; i < oldCapacity; i++) {
        data[i] = oldData[i];
    }

    data[capacity - 1] = obj;

    if (oldData != nullptr)
        delete[] oldData;

    isEmpty = false;
}

template<typename T>
char optVector<T>::len() const {
    return capacity;
}

template<typename T>
bool optVector<T>::empty() {
    return isEmpty;
}