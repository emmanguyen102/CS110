#include <iostream>

using namespace std;

void print_vertical(unsigned int num)
{
    if (num <10) {
        cout << num << endl;
    } else {
        print_vertical(num/10);
        cout << num % 10 << endl;
    }

}

int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
