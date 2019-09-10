#include <iostream>
#include <string>

using namespace std;
//O(n+k^2), needs k times string concatenation.
string strCompression(const string& str)
{
    if(str.size() == 0) return str;
    char c = str[0];
    int count=1;
    string res="";
    for(auto it = next(str.begin()); it != str.end(); ++it) {
       if(c == *it) count++;
       else {
           res.append(1, c);
           res.append(to_string(count));
           c = *it;
           count = 1;
       }
    }
    res.append(1, c);
    res.append(to_string(count));
    return res.size() < str.size() ? res : str;
}

int main()
{
    string str;
    cout << "input str:";
    getline(cin, str);
    cout << "use compression:" << strCompression(str) << endl;
}

