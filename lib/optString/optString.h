#define nullptr 0
#include <string.h>

class optString
{
private:
    char size = 2;
    bool isEmpty = true;
    char* data = new char[size];
    void resize();
public:
    optString();
    optString(const optString& str);
    optString(const char str[]);
    optString(char sizeOut);

    char& operator[](char index);
    char operator[](char index) const;
    optString& operator+=(const char str);
    optString& operator=(optString& str);
    optString& operator=(const char* str);
    optString operator+(optString& str);
    ~optString();

    char getLenFromArray(const char array[]);
    char getLenFromArray(char array[]);
    char len() const;
    void del(char index);
    char* convertChar() const;
    void push(const char& obj);
    bool empty() const;
    optString copy();
};