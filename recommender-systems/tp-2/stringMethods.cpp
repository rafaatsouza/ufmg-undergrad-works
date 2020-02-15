#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "stringMethods.hpp"

using namespace std;

string trim(const string& text){
    size_t firstOcurrence = text.find_first_not_of(' ');
    if (string::npos == firstOcurrence)
        return text;

    size_t lastOcurrence = text.find_last_not_of(' ');
    return text.substr(firstOcurrence, (lastOcurrence - firstOcurrence + 1));
}

string GetOnlyName(const string& text){
    int parenthesesPosition = text.find("(");

    if(parenthesesPosition > 0){
        return text.substr(0, parenthesesPosition);
    } else {
        return text;
    }
}

vector<string> SplitString(string text, bool onlyName, char separator){
  stringstream streamtext(text);
  vector<string> splitted;

  while(streamtext.good()) {
      string substr;
      getline(streamtext, substr, separator);
      if(onlyName == true){
        splitted.push_back(trim(GetOnlyName(substr)));
      } else {
        splitted.push_back(trim(substr));
      }
  }

  return splitted;
}

string RemoveComma(string text){
    text.erase(std::remove(text.begin(), text.end(), ','), text.end());
    return text;
}
