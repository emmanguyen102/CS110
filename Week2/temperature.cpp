#include <iostream>

using namespace std;

int main()
{
    int temperature;
    float fahr, cel;
    cout << "Enter a temperature: ";
    cin >> temperature;

    fahr = (1.8 * temperature) + 32.0;
    cout << temperature << " degrees Celsius is " << fahr << " degrees Fahrenheit" << endl;

    cel = (temperature - 32) / 1.8;
    cout << temperature << " degrees Fahrenheit is " << cel << " degrees Celsius" << endl;
    return 0;
}