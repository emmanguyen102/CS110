#include <iostream>

using namespace std;

unsigned int subfactorial(unsigned int m, unsigned int n)
{
    double test = 1;
    unsigned int count = n - m;

    for (unsigned int i = m + 1; i <= n; ++i)
    {
        test = double((test * i)) / double(count);
        if (count > 0) {
            count -= 1;
        }
    }
    return test;
}

double prob(unsigned int a, unsigned int b)
{
    if ((a - b) > b) {
        return subfactorial(a - b, a);
    }
    else {
        return subfactorial(b, a);
    }
}

int main()
{
    int a, b;
    cout << "Enter the total number of lottery balls: ";
    cin >> a;
    cout << "Enter the number of drawn balls: ";
    cin >> b;

    if (a <= 0) {
        cout << "The number of balls must be a positive number.";
    }
    else if (b > a) {
        cout << "The maximum number of drawn balls is the total amount of balls.";
    }
    else {
        cout << "The probability of guessing all " << b << " balls correctly is 1/" << prob(a, b) << endl;
    }
    return 0;
}