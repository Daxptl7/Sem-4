#include <iostream>
#include <ctime>

using namespace std;

long long power10(int n) {
    long long result = 1;
    for (int i = 0; i < n; i++)
        result *= 10;
    return result;
}


int numDigits(long long x) {
    int count = 0;
    if (x == 0) return 1;
    while (x != 0) {
        count++;
        x /= 10;
    }
    return count;
}


long long normalMultiply(long long x, long long y) {
    return x * y;
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10)
        return x * y;

    int n1 = numDigits(x);
    int n2 = numDigits(y);
    int n = (n1 > n2) ? n1 : n2;
    int half = n / 2;

    long long high1 = x / power10(half);
    long long low1  = x % power10(half);
    long long high2 = y / power10(half);
    long long low2  = y % power10(half);

    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);

    return z2 * power10(2 * half) + (z1 - z2 - z0) * power10(half) + z0;
}

int main() {
    long long x, y;

    cout<<"Enter first number:"<<endl;
    cin>>x;

    cout<<"Enter second number:"<<endl;
    cin>>y;

  
    clock_t start1 = clock();
    long long result1 = normalMultiply(x, y);
    clock_t end1 = clock();


    clock_t start2 = clock();
    long long result2 = karatsuba(x, y);
    clock_t end2 = clock();

    double time_normal = ((double)(end1 - start1)) / CLOCKS_PER_SEC * 1000;
    double time_karatsuba = ((double)(end2 - start2)) / CLOCKS_PER_SEC * 1000;

    cout<<"Result using Normal Multiplication:"<<result1<<endl;
    cout<<"Result using Karatsuba Multiplication:"<<result2<<endl;

    cout<<"Execution Time (Normal):" <<time_normal<<" ms"<<endl;
    cout<<"Execution Time (Karatsuba):"<< time_karatsuba<<" ms";

    return 0;
}