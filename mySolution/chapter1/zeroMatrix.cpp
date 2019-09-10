#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;
void zeroMatrix(vector<int>& vec, size_t N)
{
    const size_t M = vec.size()/N;
    unordered_map<size_t, int> m1, m2;
    for(size_t i = 0; i < M; ++i) {
        for(size_t j = 0; j < N; ++j) {
            if(vec[i*N+j] == 0) {
                if(m1.find(i) == m1.end())
                    m1.emplace(i, 0);
                if(m2.find(j) == m2.end())
                    m2.emplace(j, 0);
            }
        }
    }
    for(auto it = m1.begin(); it != m1.end(); ++it) {
        for(size_t j = 0; j < N; ++j) {
            vec[it->first*N + j] = 0;
        }
    }
    for(auto it = m2.begin(); it != m2.end(); ++it) {
        for(size_t i = 0; i < M; ++i) {
            vec[i*N + it->first] = 0;
        }
    }
}

int main()
{
    size_t M, N;
    cout << "input M, N: ";
    cin >> M >> N;
    getchar();
    vector<int> vec(M*N);
    cout << "input matrix: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    for(size_t i = 0; i < M*N; ++i) {
        itr >> vec[i];
    }
    cout << "original matrix:" << endl;
    for(size_t i = 0; i < M; ++i) {
        for(size_t j = 0; j < N; ++j) {
            cout << vec[i*N+j] << " ";
        }
        cout << endl;
    }

    zeroMatrix(vec, N);
    cout << "zero matrix:" << endl;
    for(size_t i = 0; i < M; ++i) {
        for(size_t j = 0; j < N; ++j) {
            cout << vec[i*N+j] << " ";
        }
        cout << endl;
    }
}
