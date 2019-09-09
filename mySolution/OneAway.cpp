#include <iostream>
#include <string>
#include <cmath>

using namespace std;
bool one_Away(const string& str1, const string& str2)
{
    size_t n1 = str1.size(), n2 = str2.size();
    if(fabs((double)n1 - n2) > 1) return false;
    uint32_t b1 = 0, b2 = 0;
    bool foundDiff = false;
    while(b1 < n1 && b2 < n2) {
        if(str1[b1] == str2[b2]) {
            b1++;
            b2++;
        }
        else if(str1[b1] != str2[b2]) {
            if(foundDiff) return false;

            foundDiff = true;
            if(b1+1 < n1 && str1[++b1] == str2[b2]) {
                b1++;
                b2++;
            }
            else if(b2+1 < n2 && str2[++b2] == str1[b1]) {
                b1++;
                b2++;
            }
            else if(b1+1 < n1 && b2+1 < n2 && str1[++b1] == str2[++b2]) {
                b1++;
                b2++;
            }
            else {
                return true; // b1 = n-1 or b2 = n-1
            }
        }
    }
    return true;
}

int main()
{
    string str1, str2;
    cout <<"input str1:";
    getline(cin, str1);
    cout <<"input str2:";
    getline(cin, str2);
    cout << "is one-away? " << boolalpha << one_Away(str1, str2) << endl;
}
