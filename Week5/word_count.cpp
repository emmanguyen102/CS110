#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Word {
  public:
    Word(const string& word, int line);

    string getName() {
      return word_;
    }

    int getTimes() {
      return times_;
    }

    void setTimes(int line) {
    if ( find(lines_.begin(), lines_.end(), line) == lines_.end() )
      times_ += 1;
    }

    void setLines(int line) {
      if ( find(lines_.begin(), lines_.end(), line) == lines_.end() )
        lines_.push_back(line);
    }

    void print() {
      cout << word_ << " " << times_ << ":";

      string separator = "";
      for (auto i: lines_) {
        cout << separator << " " << i;
        separator = ",";
      }
      cout << endl;
    }

  private:
    string word_;
    int times_ = 0;
    vector<int> lines_;
};

Word::Word(const string& word, int line) {
  word_ = word;
  setTimes(line);
  setLines(line);
}

vector<Word> words;


bool checkWord(string wrd, int line) {
  for (Word& x: words) {
    if(x.getName() == wrd){
      x.setTimes(line);
      x.setLines(line);
      return false;
    }
  }
  return true;
}

vector<Word>::iterator insertPosition(string wrd) {
  int position = 0;
  for (Word& x: words) {
    if(x.getName() > wrd){
      break;
    }
    position++;
  }
  return words.begin() + position;
}

int main() {

  string input_name = "";
  string text;

  cout << "Input file: ";
  getline(cin, input_name);

  ifstream input(input_name);
  if(!input) {
    cout << "Error! The file " << input_name << " cannot be opened." << endl;
    return EXIT_FAILURE;
  } else {
    int line = 1;

    while (getline (input, text)) {
      string wrd = "";

      for(char& c : text) {
        if (isspace(c)) {
          if(checkWord(wrd, line)) {
              auto position = insertPosition(wrd);
              words.insert(position, Word(wrd, line));
          }
          wrd = "";
        } else {
          wrd += c;
        }
      }

      if(checkWord(wrd, line)) {
          auto position = insertPosition(wrd);
          words.insert(position, Word(wrd, line));
      }

      line++;
    }

    for (Word x: words)
      x.print();
    return EXIT_SUCCESS;
  }
  return 0;
}
