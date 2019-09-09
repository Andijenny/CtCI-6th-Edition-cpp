#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// rotating a square matrix by 90 degree is equaivalent 
// to reversing it along one dim after by transposing
void rotateMatClockWise(vector<int>& vec, size_t N)
{
    const size_t n1 = N/2;
    const size_t n2 = N%2==0 ? n1 : n1+1;
    for(size_t i = 0; i < n2; ++i) {
        for(size_t j = 0; j < n1; ++j) {
            int t1 = vec[i*N + j];
            int t2 = vec[j*N + N-i-1];
            int t3 = vec[(N-j-1)*N + N-i-1];
            vec[i*N + j] = vec[(N-j-1)*N + i];
            vec[j*N + N-i-1] = t1;
            vec[(N-j-1)*N + N-i-1] = t2;
            vec[(N-j-1)*N + i] = t3;
        }
    }
}

void rotateMatAntiClockWise(vector<int>& vec, size_t N)
{
    const size_t n1 = N/2;
    const size_t n2 = N%2==0 ? n1 : n1+1;
    for(size_t i = 0; i < n2; ++i) {
        for(size_t j = 0; j < n1; ++j) {
            int t1 = vec[i*N + j];
            int t2 = vec[(N-j-1)*N + i];
            int t3 = vec[(N-j-1)*N + N-i-1];
            vec[i*N + j] = vec[j*N + N-i-1];
            vec[j*N + N-i-1] = t3;
            vec[(N-j-1)*N + N-i-1] = t2;
            vec[(N-j-1)*N + i] = t1;
        }
    }
}

int main()
{
    size_t N;
    cout << "input N: ";
    cin >> N;
    getchar();
    vector<int> vec(N*N);
    cout << "input vector: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    for(size_t i = 0; i < N*N; ++i) {
        itr >> vec[i];
    }
    cout << "original matrix:" << endl;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0;j < N; ++j) {
            cout << vec[i*N + j] << " ";
        }
        cout << endl;
    }
    rotateMatAntiClockWise(vec, N);
    cout << "rotated matrix:" << endl;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0;j < N; ++j) {
            cout << vec[i*N + j] << " ";
        }
        cout << endl;
    }
}
