#include <iostream>
#include <string>

using namespace std;

bool isSubstring(const string& s1, const string& s2)
{
    return s2.find(s1) != string::npos;
}

//O(N^2)
bool strRotation(const string& s1, const string& s2)
{
    if(s1.size() != s2.size()) return false;
    size_t pivot = 0;
    for(size_t i = 0; i < s2.size(); ++i) {
        if(!isSubstring(s2.substr(0, i+1), s1)) {
            if(isSubstring(s2.substr(i), s1)) return true;
        }
    }
    return false;
}

//O(N)
bool strRotation2(const string& s1, const string& s2)
{
    if(s1.size() != s2.size()) return false;
    return isSubstring(s2, s1+s1);
}

int main()
{
    string s1, s2;
    cout << "input s1: ";
    cin >> s1;
    cout << "input s2: ";
    cin >> s2;
    cout << "Is rotation? " << boolalpha << strRotation2(s1, s2) << endl;
}
