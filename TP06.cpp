#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct student {
	string name;
	string usfid;
	string email;
	int presentation_grade;
	int essay_grade;
	int project_grade;
};

int getUser(string search_term, vector<student> students) {
	int index = 0;
	for (vector<student>::iterator it = students.begin(); it != students.end(); ++it) {
		if ((*it).name == search_term || (*it).usfid == search_term || (*it).email == search_term) {
			return index;
		}
		++index;
	}
	return -1;
}

bool idExists(string search_term, vector<student> students) {
	for (vector<student>::iterator it = students.begin(); it != students.end(); ++it) {
		if ((*it).usfid == search_term) {
			return true;
		}
	}
	return false;
}

bool emailExists(string search_term, vector<student> students) {
	for (vector<student>::iterator it = students.begin(); it != students.end(); ++it) {
		if ((*it).email == search_term) {
			return true;
		}
	}
	return false;
}


void displayStudents(vector<student> students)
{
	cout << "Student Name\t\tUSF ID\t\tEmail\t\t\t\tPresentation Grade\t\tEssay Grade\t\tProject Grade\n";
	for (vector<student>::iterator it = students.begin(); it != students.end(); ++it) {
		cout << (*it).name << "\t\t" << (*it).usfid << "\t" << (*it).email << "\t\t";

		if ((*it).presentation_grade == -1) {
			cout << "N/a\t\t\t\t";
		}
		else {
			cout << (*it).presentation_grade << "\t\t\t\t";
		}

		if ((*it).essay_grade == -1) {
			cout << "N/a\t\t\t";
		}
		else {
			cout << (*it).essay_grade << "\t\t\t";
		}

		if ((*it).project_grade == -1) {
			cout << "N/a\t\t";
		}
		else {
			cout << (*it).project_grade << "\t\t";
		}
		cout << "\n";
	}
	cout << endl;

}

int DisplayStudentsFromFile(string filename) {
	ifstream inFile(filename.c_str());
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		return 1;
	}
	string text;
	cout << "Current List of Students:\n" << endl;
	while (!inFile.eof())
	{
		getline(inFile, text);
		cout << text << endl;
	}
	inFile.close();
	return 0;
}

int loadStudentsFromFile(string filename, vector<student>& students) {
	ifstream inFile(filename.c_str());
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		return 1;
	}
	string firstname, lastname, usfid, email;
	int pres_grade, essay_grade, proj_grade;
	student n;
	while (inFile >> firstname >> lastname >> usfid >> email >> pres_grade >> essay_grade >> proj_grade) {
		n.name = firstname;
		n.usfid = usfid;
		n.email = email;
		n.presentation_grade = pres_grade;
		n.essay_grade = essay_grade;
		n.project_grade = proj_grade;
		students.push_back(n);
	}
	inFile.close();
	return 0;
}

int saveStudentsToFile(string filename, vector<student> &students) {
	ofstream outFile(filename.c_str());
	if (outFile.fail())
	{
		cerr << "Error opening file" << endl;
		return 1;
	}

	for (vector<student>::iterator it = students.begin(); it != students.end(); ++it) {
		outFile << (*it).name << " ";
		outFile << (*it).usfid << " ";
		outFile << (*it).email << " ";
		outFile << (*it).presentation_grade << " ";
		outFile << (*it).essay_grade << " ";
		outFile << (*it).project_grade << "\n";
	}
	outFile.close();
	cout << endl << endl;

	DisplayStudentsFromFile(filename);
	cout << "File updated succesfully\n\n";

}

void addStudent(vector<student> students) {
	string name, usfid, email;
	cin.ignore();
	cout << "Enter Student First Name:\n";
	getline(cin, name);

	while (name.size() > 40) {
		cout << "Name cannot exceed 40 characters, Enter a different Student Name:\n";
		getline(cin, name);
	}

	cout << "Enter Student USF ID:\n";
	getline(cin, usfid);
	while (usfid.size() != 10) {
		cout << "ID must be 10 characters long, Enter a different Student USF ID:\n";
		getline(cin, usfid);
	}
	while (idExists(usfid, students)) {
		cout << "ID already exists, Enter a different Student USF ID:\n";
		getline(cin, usfid);
	}

	cout << "Enter Student Email:\n";
	getline(cin, email);
	while (email.size() > 40) {
		cout << "E-mail cannot exceed 40 characters, Enter a different Student Name:\n";
		getline(cin, email);
	}
	while (emailExists(email, students)) {
		cout << "E-mail already exists, Enter a different Student Email:\n";
		getline(cin, email);
	}

	int presentation_grade_;
	int essay_grade_;
	int project_grade_;

	cout << "Enter Presentation Grade (0-4):\n";
	cin >> presentation_grade_;
	while (presentation_grade_ < 0 || presentation_grade_ > 4) {
		cout << "Grade must be between 0 and 4, Enter Presentation Grade (0-4):\n";
		cin >> presentation_grade_;
	}

	cout << "Enter Essay Grade (0-4):\n";
	cin >> essay_grade_;
	while (essay_grade_ < 0 || essay_grade_ > 4) {
		cout << "Grade must be between 0 and 4, Enter Essay Grade (0-4):\n";
		cin >> essay_grade_;
	}

	cout << "Enter Project Grade (0-4):\n";
	cin >> project_grade_;
	while (project_grade_ < 0 || project_grade_ > 4) {
		cout << "Grade must be between 0 and 4, Enter Project Grade (0-4):\n";
		cin >> project_grade_;
	}
	cout << "Successfuly added student \"" << name << "\"\n\n";

	student n;
	n.name = name;
	n.usfid = usfid;
	n.email = email;
	n.presentation_grade = presentation_grade_;
	n.essay_grade = essay_grade_;
	n.project_grade = project_grade_;

	students.push_back(n);

	cout << "\nIMPORATNT: Save to see changes\n\n";
}

void removeStudent(vector<student>&students) {
	string search_term;
	cin.ignore();
	cout << "Enter Student Name, USF ID, or Email:\n";
	getline(cin, search_term);

	int s = getUser(search_term, students);
	if (s == -1) {
		cout << "No student found. Type \"list\" to view all students\n";
	}
	else {
		students.erase(students.begin() + s);
		cout << "Successfuly deleted student\n";
	}
}

void editStudent(vector<student>&students) {

	string search_term;
	cin.ignore();
	cout << "Enter Student Name, USF ID, or Email:\n";
	getline(cin, search_term);
	int s = getUser(search_term, students);

	if (s == -1) {
		cout << "No student found. Type \"list\" to view all students\n";
	}
	else {
		student *c = &students[s];
		string name, firstname, lastname, usfid, email;
		int presentation_grade, essay_grade, project_grade;

		cout << "Start editing student: " << c->name << endl;

		cout << "\nEnter Student First Name (Press enter to skip):\n";
		getline(cin, firstname);
		cout << "\nEnter Student Last Name (Press enter to skip):\n";
		getline(cin, lastname);
		cout << "Enter USF ID (Press enter to skip):\n";
		getline(cin, usfid);
		cout << "Enter Email Address (Press enter to skip):\n";
		getline(cin, email);

		cout << "Enter Presentation Grade (Press enter to skip):\n";
		cin >> presentation_grade;
		while (presentation_grade < 0 || presentation_grade > 4) {
			cout << "Grade must be between 0 and 4, Enter Presentation Grade (0-4):\n";
			cin >> presentation_grade;
		}
		(*c).presentation_grade = presentation_grade;

		cout << "Enter Essay Grade (Press enter to skip):\n";
		cin >> essay_grade;
		while (essay_grade < 0 || essay_grade > 4) {
			cout << "Grade must be between 0 and 4, Enter Presentation Grade (0-4):\n";
			cin >> essay_grade;
		}
		(*c).essay_grade = essay_grade;

		cout << "Enter Project Grade (Press enter to skip):\n";
		cin >> project_grade;
		while (project_grade < 0 || project_grade > 4) {
			cout << "Grade must be between 0 and 4, Enter Presentation Grade (0-4):\n";
			cin >> project_grade;
		}
		(*c).project_grade = project_grade;

		if (name != "") {
			(*c).name = name;
		}

		if (usfid != "") {
			(*c).usfid = usfid;
		}
		if (email != "") {
			(*c).email = email;
		}
		cout << "Student Data Updated\n\n";
	}
}



int main() {
	cout << "Starting Class Roll System\n";
	cout << "Loading Class Data from File\n";
	vector<student> students;
	string filename;

	cout << "Enter the file name of the student database " << endl;
	getline(cin, filename);
	cout << endl << endl;

	DisplayStudentsFromFile(filename);
	if (loadStudentsFromFile(filename, students) == 1) {
		return 1;
	}
	cout << "Loading Class Data Complete\n";
	cout << "---------------------------\n";

	while (true) {
		cout << "Enter command prompt to select:\n";
		cout << "1. Add\n";
		cout << "2. Remove\n";
		cout << "3. Edit\n";
		cout << "5. List\n";
		cout << "6. Save\n";
		cout << "7. Exit\n";
		cout << "8. Help\n\n";

		string command;
		std::cout << "command > " << command;
		cin >> command;

		if (command == "add") {
			addStudent(students);
		}
		else if (command == "remove") {
			removeStudent(students);
		}
		else if (command == "edit") {
			editStudent(students);
		}
		else if (command == "list")
		{
			displayStudents(students);
		}
		else if (command == "save")
		{
			if (saveStudentsToFile(filename, students) == 1) {
				cout << "There was an error saving the file" << endl;
			}
		}
		else if (command == "exit")
		{
			if (saveStudentsToFile(filename, students) == 1) {
				cout << "There was an error saving the file" << endl;
			}
			break;
		}
		else cout << "Unrecognized command.\n\n";
	}
}
