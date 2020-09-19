#include <iostream>
using namespace std;

int main()
{
    int N, i;
    float num[1000], sum = 0.0, average;

    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> N;

    for (i = 0; i < N; ++i)
    {
        cout << "Input " << i + 1 << ". number: ";
        cin >> num[i];
        sum += num[i];
    }

    if (N > 0)
    {
        average = sum / N;
        cout << "Mean value of the given numbers is " << average << endl;
    }

    if (N <= 0)
    {
        cout << "Cannot count mean value from 0 numbers" << endl;
    }

    return 0;

}
