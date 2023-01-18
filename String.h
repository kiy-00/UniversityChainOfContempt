#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

const int STRDEFAULTSIZE = 5;

class String
{
    friend istream& operator>>(istream&, String& Str);
    friend ostream& operator <<(ostream&, const String& Str);
private:
    int currentLength;
    int maxLength;
    char* ch;
public:
    String(int size = STRDEFAULTSIZE);

    String(const char* init);

    String(const String& ob);

    ~String()
    {
        delete[]ch;
    }

    int length()const
    {
        return currentLength;
    }

    String operator()(int pos, int length);

    bool operator==(const String& ob)
    {
        return strcmp(ch, ob.ch) == 0;
    }

    bool operator!=(const String& ob)
    {
        return strcmp(ch, ob.ch) != 0;
    }

    String& operator=(const String& ob);

    String& operator+=(const String& ob);

    String& operator+=(const char c);

    char& operator[](int num)const;

    int fastFind(String& pat, int pos);

    bool operator > (String& s)
    {
        return strcmp(this->ch, s.ch) > 0;
    }
    bool operator <  (String& s)
    {
        return strcmp(this->ch, s.ch) < 0;
    }
    bool operator == (String& s)
    {
        return strcmp(this->ch, s.ch) == 0;
    }
    void strlwr( )
    {
        if (ch != NULL)
        {
            char* p = ch;
            while (*p != '\0')
            {
                if (*p >= 'A' && *p <= 'Z')
                {
                    *p += 'a' - 'A';
                }
                p++;
            }
        }
    }
};