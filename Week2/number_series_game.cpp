#include <iostream>
using namespace std;

void result(int N)
{
    // iterate from 0 to N
    for (int num = 1; num <= N; num++)
    {
        // Short-circuit operator is used
        if (num % 3 == 0 && num % 7 != 0)
            cout << "zip" << endl;
        else if (num % 7 == 0 && num % 3 != 0)
            cout << "boing" << endl;
        else if (num % 3 == 0 && num % 7 == 0)
            cout << "zip boing" << endl;
        else
            cout << num << endl;
    }
}

int main()
{
    int N;
    cout << "How many numbers would you like to have? ";
    cin >> N;
    result(N);
    return 0;
}