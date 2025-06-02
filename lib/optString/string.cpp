#include "optString.h"
#include <Arduino.h>
optString::optString()
{
    data = new char[size];
    data[1] = '\0';
}

optString::optString(const char obj[]) {
    size = getLenFromArray(obj);

    resize();
    for (char i = 0; i < size; i++)
        data[i] = obj[i];
    isEmpty = false;
}

char optString::getLenFromArray(char array[]) {
    char n = 0;
    for (char i = 0; array[i] != '\0'; i++)
        n++;
    return n;
}

char optString::getLenFromArray(const char array[]) {
    char n = 0;
    for (char i = 0; array[i] != '\0'; i++)
        n++;
    return n;
}

void optString::resize() {
    if (!isEmpty)
        delete[] data;
    if (size <= 1)
        size = 2;
    data = new char[size + 1];
    data[size - 1] = '\0';
}

optString::optString(const optString& obj) {
    size = obj.len();

    resize();
    for (char i = 0; i < size; i++)
        data[i] = obj[i];
    isEmpty = false;
}

char& optString::operator[](char index) {
    if (index > size) {
        char returnValue = '\0';
        return returnValue;
    }
    return data[index];
}

char optString::operator[](char index) const {
    if (index > size) {
        char returnValue = '\0';
        return returnValue;
    }
    return data[index];
}

optString::~optString()
{
    if (!isEmpty)
        delete[] data;
}

optString& optString::operator=(optString& obj) {
    if (this != &obj)
    {
        size = obj.size;
        resize();
        for (char i = 0; i < size; i++)
            data[i] = obj[i];
        isEmpty = false;
    }
    return *this;
}

optString::optString(char sizeOut) {
    size = sizeOut;
    resize();
}

optString& optString::operator=(const char* str) {
    size = strlen(str);
    resize();

    for (char i = 0; i < size; i++)
        data[i] = str[i];
    return *this;
}

optString& optString::operator+=(const char str)
{
    optString tempData = *this;
    Serial.println("IN:");
    for (size_t i = 0; i < size; i++)
    {
        Serial.print(data[i]);
    }
        Serial.println("OUT");

    if (size <= 2 && empty())
    {
        data[0] = str;
        isEmpty = false;
        return *this;
    }
    size++;
    resize();
    for (char i = 0; i < size - 1; i++) {
        data[i] = tempData[i];
    }

    data[size - 1] = str;
    isEmpty = false;
    return *this;
}

optString optString::copy() {
    optString newStr;
    newStr = data;
    return newStr;
}

optString optString::operator+(optString& str) {
    const char newLen = size + str.size;
    char index = 0;
    char* newStr = new char[newLen];
    while (index < size)
    {
        newStr[index] = data[index];
        index++;
    }

    char index2 = 0;
    while (index < str.size)
    {
        newStr[index] = str[index2];
        index++;
        index2++;
    }
    return optString(newStr);
}

char* optString::convertChar() const {
    return data;
}

void optString::push(const char& obj) {
    optString tempData;
    tempData = data;

    size++;

    resize();
    for (char i = 0; i < size; i++)
    {
        if (i == size - 2)
            data[i] = obj;
        data[i] = tempData[i];
    }
}

char optString::len() const {
    return size;
}

bool optString::empty() const {
    return isEmpty;
}

void optString::del(char index) {
    if (index > size) {
        return;
    }

    optString tempData = *this;
    size--;
    resize();
    for (char i = 0; i < size; i++)
    {
        if (i == index)
        {
            i++;
            continue;
        }
        data[i] = tempData[index];
    }
}
