/*
* 
* Name: Kevin Caballero
* Date: 08/13/2024
* Version: 1.0.0
* Description: Course Application Software
* 
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

// Defines a structure to hold course information
struct Course {
	string courseId = "0";
	string courseName = "Non-Existent Course";
	vector<string> preReq;
};

// Credit: https://www.tutorialspoint.com/sorting-a-vector-of-custom-objects-using-cplusplus-stl
// Sorts a vector of courses alphanumerically and prints the sorted list of courses
void sortCourses(vector<Course> courses) {

	// Sorts each course within the vector of courses alphanumerically
	sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
		return a.courseId < b.courseId;
		});

	// Formats and prints a schedule of courses that have been sorted
	cout << "Here is a sample schedule: " << endl << endl;
	for (auto course = courses.begin(); course != courses.end(); course++) {
		cout << course->courseId << ", " << course->courseName << endl;
	}

	cout << endl;
}

// Searches for a particular course given by the user
Course searchCourse(vector<Course> courseVector, string course) {
	
	Course Course; // Defines a course

	// Iterates through course vector and compares element within the vector according to the courseID with user input
	for (int i = 0; i < courseVector.size(); i++) {
		if (courseVector.at(i).courseId.compare(course) == 0) {
			Course = courseVector.at(i); // Sets course equivalent to the course being searched for if found
		}
	}

	return Course; // Returns the course found (if found)
}

// Displays a course's info
void displayCourse(vector<Course> courseVector) {

	string input; // Stores string user input
	Course course; // Initializes a course struct

	// Prompts user and retrieves input
	cout << "What course do you want to know about? ";
	cin >> input;


	transform(input.begin(), input.end(), input.begin(), ::toupper); // Converts input to all uppercase

	course = searchCourse(courseVector, input); // Searches for the desired course based on input

	// Formats and displays all course information
	try {
		cout << course.courseId << ", " << course.courseName << endl;
		if (course.preReq.at(0) != "") {
			cout << "Prerequisites: ";
			for (int i = 0; i < course.preReq.size(); i++) {
				if (i == course.preReq.size() - 1) {
					cout << course.preReq.at(i);
				}
				else {
					cout << course.preReq.at(i) << ", ";
				}
			}
		}
		cout << endl << endl;
	}
	catch (exception) {
		cout << "Invalid Input, try again" << endl << endl;
	}
}

// Credit: https://www.geeksforgeeks.org/program-to-parse-a-comma-separated-string-in-c/
// Parses a string based on a delimeter such as ','
vector<string> parse(string input) {

		vector<string> courseParam; // Defines a vector to store parsed string

		stringstream fs(input);

		// Stores each word separated by a comma while the stringstream contains a string
		while (fs.good()) {
			string subinput;
			getline(fs, subinput, ',');
			courseParam.push_back(subinput);
		}

		return courseParam; // Returns parsed string stored in vector
}

// Loads the file into the program
vector<Course> loadCourses(string csvPath) {

	string fileInput; // Stores file input
	vector<string> parsedCourse; // Stores parsed string from parser function
	vector<Course> courseList; // Stores final course vector to store all courses and their info
	
	ifstream courseFile(csvPath); // Loads and opens file using ifstream

	// Verifies if file opens, otherwise, prompts error
	if (!courseFile.is_open()) {
		cout << "Failed to open the course file." << endl << endl;
	}

	// Reads every line within the file, parsing each line, and loading every course in the courseList vector
	while (!courseFile.eof()) {
		Course newCourse; // Initializes a new course

		getline(courseFile, fileInput);
		parsedCourse = parse(fileInput);

		// Checks to see if the parsed string vector contains less than two parameters, otherwise skips a line
		if (parsedCourse.size() < 2) {
			cout << "A line has been skipped due to improper formatting." << endl << endl;
		}
		// Else assigns the new course with corresponding values based on the parsed string and adds it to the courseList vector
		else {
			newCourse.courseId = parsedCourse.at(0);
			newCourse.courseName = parsedCourse.at(1);

			for (int i = 2; i < parsedCourse.size(); i++) {
				newCourse.preReq.push_back(parsedCourse.at(i));
			}
			courseList.push_back(newCourse);
		}
	}
	courseFile.close(); // Closes the file
	return courseList; // Returns the vector with the courses loaded from the file
}


int main(int argc, char* argv[]) {

	string csvPath, aCourseKey;

	// Processes command line arguments
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	case 3:
		csvPath = argv[1];
		aCourseKey = argv[2];
		break;
	default:
		csvPath = "ABCU_Advising_Program_Input.csv";
	}

	// Defines a vector containing all the course information
	vector<Course> courseInfo;

	int choice = 0; // Stores user int choice

	cout << "Welcome to the course planner." << endl << endl;
	// While-loop runs the program until user decides to exit with choice '9'
	while (choice != 9) {
		cout << "  1. Load Data Structure." << endl;
		cout << "  2. Print Course List." << endl;
		cout << "  3. Print Course." << endl;
		cout << "  9. Exit" << endl << endl;
		cout << "What would you like to do? ";
		cin >> choice;

		switch (choice) {
		case 1:
			// Loads file into the vector
			courseInfo = loadCourses(csvPath);
			break;
		case 2:
			// Prints an alphanumeric list of all the course in the Computer Science Department
			sortCourses(courseInfo);
			break;
		case 3:
			// Prints the course title and the prerequisites for any individual course
			displayCourse(courseInfo);
			break;
		default:
			// User will be prompted with an error if any other option is picked
			cout << choice << " is not a valid option." << endl << endl;
			continue;
		}
	}
}