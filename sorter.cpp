/*
Sorts text files like a26_data.txt (skeleton of code provided).
Output is majority correct except for a few exceptions (switched the order, unknown reason):
--- "and [only..." to "(Noun1..."
--- "before (not..." to "before (time..."
--- "blue" to "(is..."
--- "but [less..." to "But [at..."
--- "by (trans..." to "by (tool)"
--- "(is) cold" to "(a) cold"
Ho, Michelle
ICS 212 Assignment #26
05/03/2022
*/

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>     //to get the vector class (a vector is a type of array)
#include <algorithm>  //to use the sort() function
#include <iomanip>    //to use the setw() function

#define SIZE  130
using namespace std;

//Used to store three strings: the English, the Japanese, and the sort field
class Entry{
public:
//default constructor
  Entry() {
    english = "";
    japanese = "";
    sortfield = "";
  } //closes empty constructor

//three set functions
  void setEnglish(string tEnglish) {
    english = tEnglish;
  } //closes setEnglish function

  void setJapanese(string tJapanese) {
    japanese = tJapanese;
  } //closes setJapanese function

  void setSortfield(string tSortfield) {
    sortfield = tSortfield;
  } //closes setSortfield function

//three get functions
  string getEnglish(void) {
    return english;
  } //closes getEnglish function

  string getJapanese(void) {
    return japanese;
  } //closes getJapanese function

  string getSortfield(void) {
    return sortfield;
  } //closes getSortfield function

  //overload the operator< (less than operator)
  bool operator<(const Entry e) const {
    //used to sort Entry objects
    //compare sortfield of two Entry objects
    if (sortfield < e.sortfield) {
      return true;
    } else {
      return false;
    }
  } //closes overload < operator

  friend ostream &operator<<(ostream &output, const Entry &tEntry) {
    cout<<setiosflags(ios::left);
    output<<setw(35) << tEntry.english << tEntry.japanese << endl;
    return output;
  } //closes cout friend operator

private:
//data field for English
  string english;
//data field for Japanese
  string japanese;
//data field for the sort field
  string sortfield;
}; //closes Entry class

int main(int argc, char *argv[]){
  //Make a vector of Entry objects.
  vector<Entry> entries;
  Entry tEntry;
  //  vector<Entry>::iterator itr; //for modifying entries in the vector
  char inputFile[SIZE] = {'\0'}; //C style string
  string line = "nothing"; //C++ style string
  string tempEnglish = "";
  string tempJapanese = "";
  string tempSortfield = "";

  int tab = -1; //to break into 3 parts, search for tab char

  if (argc >= 2) { //check if commandline has the input file
    strncpy(inputFile, argv[1], SIZE);
  } else {
    cout<<"There was no input file on commandline. Please enter file name: ";
    cin>>inputFile;
  } //closes if/else - check if there's an input file

  ifstream fileStream(inputFile); //inputFile must be C style string
  if (fileStream == NULL) { //check stream object if it can be opened
    cout<<"Cannot open file " << inputFile << endl;
    return 1;
  }

  //Read the data from the file one line at a time
  while (!fileStream.eof()) {
    if (getline(fileStream, line) != NULL) { //I'm not sure why I have to check this, the while doesn't catch when the file is at EOF and throws core dumped when it gets to the getline
      //Break the line into three parts as described on the assignment webpage.
      tab = line.find('\t');
      tempEnglish = line.substr(0, tab);
      tempJapanese = line.substr(tab, line.length());
      tempSortfield = tempEnglish;

      int length = tempSortfield.length(); //won't compile if I use .length in the for loop
      //convert to lowercase
      for (int i = 0; i < length; i++) {
        tempSortfield[i] = tolower(tempSortfield[i]);
      }

      //remove any characters enclosed in brackets and parentheses in front of any words
      int brackStart = tempSortfield.find('[');
      if (brackStart >= 0) { //if there is an index in the English part of each line with [
        int brackEnd = tempSortfield.find(']');
        if (brackEnd >= 0) {
          tempSortfield.erase(brackStart, brackEnd + 1);
        } //closes checking if end brackets exists
      } //closes removing insides of []

      int parenStart = tempSortfield.find('(');
      if (parenStart >= 0) { //if there is an index in the English part of each line with (
          int parenEnd = tempSortfield.find(')');
          if (parenEnd >= 0 && parenEnd != length) {
            tempSortfield.erase(parenStart, parenEnd + 1);
          } //closes checking if end parenthese exists
      } //closes if/else - removing [] and () words

      //remove the space in front of any words
      if (tempSortfield[0] == ' ') {
        tempSortfield.erase(0, 1);
      }

      //Store the data for each line in an Entry object.
      tEntry.setEnglish(tempEnglish);
      tEntry.setJapanese(tempJapanese);
      tEntry.setSortfield(tempSortfield);

      //Store each Entry object in the vector.
      entries.push_back(tEntry);
    } //closes if
  } //closes while - reading file line by line

  int count = entries.size();
  //Sort the vector of Entry objects.
  sort(entries.begin(), entries.end());

  //Display the English and Japanese parts of the sorted Entry objects.
  for (int i = 0; i < count; i++) {
    cout<<entries[i];
  }
   return 0;
} //closes main
