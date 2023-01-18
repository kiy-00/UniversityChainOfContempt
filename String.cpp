#include"String.h"
using namespace std;


String::String(int size)
{
    maxLength = size;
    ch = new char[size + 1];
    if (ch == NULL)
    {
        cerr << "Allocation Error!\n";
    }
    currentLength = 0; ch[0] = '\0';
}
String::String(const char* init)
{
    int length = (int)strlen(init);
    maxLength = length > STRDEFAULTSIZE ? length : STRDEFAULTSIZE;
    ch = new char[maxLength + 1];
    if (ch == NULL)
    {
        cerr << "Allocation Error!\n";
    }
    currentLength = length;
    strcpy(ch, init);
}
String::String(const String& ob)
{
    int length = ob.currentLength;
    maxLength = length > STRDEFAULTSIZE ? length : STRDEFAULTSIZE;
    ch = new char[maxLength + 1];
    if (ch == NULL)
    {
        cerr << "Allocation Error!\n";
    }
    currentLength = length;
    strcpy(ch, ob.ch);
}

String String::operator()(int pos, int length)
{
    String s;
    if (pos >= 0 && pos < currentLength && length>0 && pos + length - 1 < currentLength)
    {
        for (int i = 0; i < length; i++)
        {
            s.ch[i] = ch[pos + i];
        }
        s.ch[length] = '\0';
    }
    s.currentLength = (int)strlen(s.ch);
    return s;
}

String& String:: operator=(const String& ob)
{
    if (this != &ob)
    {
        delete[]ch;
        ch = new char[ob.maxLength + 1];
        maxLength = ob.maxLength;
        currentLength = ob.currentLength;
        strcpy(ch, ob.ch);
    }
    return *this;
}
String& String::operator+=(const String& ob)
{
    char* temp = ch;
    int length = currentLength + ob.currentLength;
    maxLength = maxLength > length ? maxLength : length;
    ch = new char[maxLength + 1];
    if (ch == NULL)
    {
        cerr << "Allocation Error!\n";
        exit(1);
    }
    strcpy(ch, temp);
    strcat(ch, ob.ch);
    currentLength = length;
    delete[]temp;
    return *this;
}

String& String::operator+=(const char c)
{
    char* temp = ch;
    int length = currentLength + 1;
    maxLength = maxLength > length ? maxLength : length;
    ch = new char[maxLength + 1];
    if (ch == NULL)
    {
        cerr << "Allocation Error!\n";
        exit(1);
    }
    ch[currentLength] = c;
    currentLength = length;
    delete[]temp;
    return *this;
}
char& String::operator[](int num)const
{
    if (num < 0 || num >= currentLength)
    {
        cerr << "Out of Range!\n";
        exit(1);
    }
    return ch[num];
}
int String::fastFind(String& pat, int pos)
{
    int pLength = pat.length();
    int* next = new int[pLength];
    next[0] = -1;
    int j = 0, k = -1;
    while (j < pLength - 1)
    {
        if (k == -1 || ch[j] == ch[k])
        {
            j++; k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    int tPos = 0;
    int pPos = 0;
    while (tPos < currentLength && pPos < pLength)
    {
        if (pPos == -1 || ch[tPos] == ch[pPos])
        {
            tPos++;
            pPos++;
        }
        else
        {
            pPos = next[pPos];
        }
    }
    delete[]next;
    if (pPos < pLength)
    {
        return -1;
    }
    else
    {
        return tPos - pLength;
    }
}
istream& operator>>(istream& cin, String& Str)
{
    char* init = new char[STRDEFAULTSIZE * 10];
    cin.getline(init, STRDEFAULTSIZE * 10, '\n');
    int length = (int)strlen(init);
    delete[]Str.ch;
    Str.ch = new char[length + 1];
    Str.currentLength = length;
    strcpy(Str.ch, init);
    
    return cin;
}

ostream& operator<<(ostream& cout, const String& Str)
{
    cout << Str.ch;

    return cout;
}