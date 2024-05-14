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

	void display() const {
		cout << "Title: " << title << endl;
		cout << "Content: " << content << endl;
		cout << "-------------------" << endl;
	}

	string getTitle() const {
		return title;
	}

	void saveToFile(ofstream &file) const {
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

	void deleteNote() {
		string title;
		cout << "Enter the title of the note you want to delete: ";
		getline(cin, title);

		auto it = notes.begin();
		while (it != notes.end()) {
			if (it->getTitle() == title) {
				it = notes.erase(it);
				cout << "Note deleted successfully!" << endl;
			} else {
				++it;
			}
		}

		ofstream outFile("notes.txt");
		if (outFile.is_open()) {
			for (const Note &note : notes) {
				note.saveToFile(outFile);
			}
			outFile.close();
		} else {
			cout << "Unable to open file!" << endl;
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
		cout << "3. Delete Note" << endl;
		cout << "4. Exit" << endl;
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
			noteManager.deleteNote();
			break;
		case '4':
			cout << "Exiting program..." << endl;
			break;
		default:
			cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != '4');

	return 0;
}
