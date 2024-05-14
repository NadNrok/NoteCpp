#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Note {
private:
 string title;
 string content;

public:
 Note(string t, string c) :
   title(t), content(c) {
 }

 void display() {
  cout << "Title: " << title << endl;
  cout << "Content: " << content << endl;
  cout << "-------------------" << endl;
 }

 string getTitle() {
  return title;
 }

 void saveToFile(ofstream &file) {
  file << title << endl;
  file << content << endl;
 }
};

class NoteManager {
private:
 vector<Note> notes;

public:

 void addNote() {
  string title, content;
  cout << "Enter title: ";
  getline(cin, title);
  cout << "Enter content: ";
  getline(cin, content);
  notes.push_back(Note(title, content));
  cout << "Note added successfully!" << endl;

  ofstream outFile("notes.txt", ios::app);
  if (outFile.is_open()) {
   notes.back().saveToFile(outFile);
   outFile.close();
  } else {
   cout << "Unable to open file!" << endl;
  }
 }

 void displayNotes() {
  cout << "---- All Notes ----" << endl;
  for (Note note : notes) {
   note.display();
  }
 }

 void loadFromFile() {
  ifstream inFile("notes.txt");
  if (inFile.is_open()) {
   string title, content;
   while (getline(inFile, title) && getline(inFile, content)) {
    notes.push_back(Note(title, content));
   }
   inFile.close();
  } else {
   cout << "No existing notes found." << endl;
  }
 }
};

int main() {
 NoteManager noteManager;
 char choice;

 noteManager.loadFromFile();

 do {
  cout << "1. Add Note" << endl;
  cout << "2. Display Notes" << endl;
  cout << "3. Exit" << endl;
  cout << "Enter your choice: ";
  cin >> choice;
  cin.ignore();

  switch (choice) {
  case '1':
   noteManager.addNote();
   break;
  case '2':
   noteManager.displayNotes();
   break;
  case '3':
   cout << "Exiting program..." << endl;
   break;
  default:
   cout << "Invalid choice! Please try again." << endl;
  }
 } while (choice != '3');

 return 0;
}
