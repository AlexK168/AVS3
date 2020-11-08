#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int simpleDot(const vector<int>& a, const vector<int>& b) {
    int sum = 0;
    auto start = steady_clock::now();
    for (int i =0; i < a.size(); i++) {
        sum += a[i] * b[i];
    }
    auto finish = steady_clock::now();
    auto duration = duration_cast<microseconds>(finish - start).count();
    cout << "No multithreading, duration - " << duration << endl;
    return sum;
}

int dot(const vector<int>& a, const vector<int>& b) {
    int sum = 0;
    int size = a.size();
    auto start = steady_clock::now();
#pragma omp parallel
    {
        int localSum = 0;
#pragma omp for
        for (int i = 0; i < size; ++i)
            localSum += a[i] * b[i];
#pragma omp atomic
        sum += localSum;
    }
    auto finish = steady_clock::now();
    auto duration = duration_cast<milliseconds>(finish - start).count();
    cout << "With multithreading, duration - " << duration << endl;
    return sum;
}

int main() {
    cout << "Enter vector size" << endl;
    int size;
    cin >> size;
    vector<int> a(size);
    vector<int> b(size);

    for (auto & v : a)
        v = 1;

    for (auto & v : b)
        v = 1;

    cout << dot(a, b) << endl;
    cout << simpleDot(a, b);
    return 0;
}
