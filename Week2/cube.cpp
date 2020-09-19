#include <iostream>
using namespace std;

int main()
{
    int N;
    cout << "Enter a number: ";
    cin >> N;
    int cube = N * N * N;
    if (N < 88000)
    {
        cout << "The cube of " << N << " is " << cube << "." << endl;
    }

    if (N >= 88000)
    {
        cout << "The cube of " << N << " is not " << cube << "." << endl;
    }
    return 0;
}