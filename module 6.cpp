#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_FRIENDS = 50;

struct Student {
    string name;
    string friends[MAX_FRIENDS];
    int numFriends = 0;
};

void readStudents(Student students[], int &numStudents, const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    numStudents = 0;

    while (getline(infile, students[numStudents].name)) {
        students[numStudents].numFriends = 0;
        string friendName;

        while (infile >> friendName) {
            students[numStudents].friends[students[numStudents].numFriends] = friendName;
            students[numStudents].numFriends++;
            if (infile.peek() == '\n') break;
        }

        infile.ignore();
        numStudents++;
    }

    infile.close();
}

void findPotentialFriendships(const Student students[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        for (int j = i + 1; j < numStudents; ++j) {
            bool areDirectFriends = false;
            for (int k = 0; k < students[i].numFriends; ++k) {
                if (students[i].friends[k] == students[j].name) {
                    areDirectFriends = true;
                    break;
                }
            }

            if (!areDirectFriends) {
                int commonFriends = 0;
                for (int m = 0; m < students[i].numFriends; ++m) {
                    for (int n = 0; n < students[j].numFriends; ++n) {
                        if (students[i].friends[m] == students[j].friends[n]) {
                            commonFriends++;
                        }
                    }
                }

                if (commonFriends > 0) {
                    cout << "Potential friendship between " << students[i].name << " and " << students[j].name
                         << " with " << commonFriends << " common friends." << endl;
                }
            }
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;

    readStudents(students, numStudents, "C:\\Users\\Abdul Wahab\\Downloads\\Friends Dataset (1).csv");

    findPotentialFriendships(students, numStudents);

    return 0;
}
