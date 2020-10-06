#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string text;
  string input_name;
  string output_name;

  cout << "Input file: ";
  getline(cin,input_name);

  cout << "Output file: ";
  getline(cin,output_name);

  ifstream input(input_name);


  if(input) {
    ofstream output(output_name);
    int numb = 1;

    while (getline (input, text)) {
        output << numb << " " <<  text << endl;
        numb++;
    }
    output.close();
  } else {
    cout << "Error! The file " << input_name << " cannot be opened." << endl;
    return EXIT_FAILURE;
  }

  input.close();
  return 0;
}

