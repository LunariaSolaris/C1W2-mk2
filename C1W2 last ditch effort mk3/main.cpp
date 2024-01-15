#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <string>
using namespace std;



int main() {
    cout << "test";
    string unprocessedUserInput;
    //user inputs
    cout << "please enter the student ID in the format of action (querydb), database to be viewed (computing.txt), student ID (-sid), modifiers (-n, -g, -p), seperate each with one space:";
    istream& getline(istream & is, string & unprocessedUserInput, char delim);
    cout << "\n";



    //user input processing plant, warning authorised personel only
    bool processed = false;
    string compiler;
    int n = 0;
    string word;
    vector<string> words;
    int lineLength = int(unprocessedUserInput.length());
    while (n <= lineLength) {
        compiler = unprocessedUserInput[n];
        n++;
        if (!compiler.compare(" ")) {//word serperator
            words.push_back(word);
            word = "";
        }
        else {
            word = word + compiler;
        }
    }
    //so now i have the vector "words" this is all the different "words" the user input, i can sift through them and get my "instructions" from it, hence, welcome to the sifter!
    n = 1;
    string openThisFile;
    int sifterRepeats = int(words.size());
    bool nextWordIsDB = false;
    bool nextWordIsSid = false;
    string sid;
    bool negativeN = false;
    bool negativeG = false;
    bool negativeP = false;
    bool showAll = false;
    while (n <= sifterRepeats) {
        word = words[n];
        n++;
        if (nextWordIsDB = true) {
            openThisFile = word;
            nextWordIsDB = false;
        }
        if (!word.compare("-db")) {
            nextWordIsDB = true;
        }
        if (nextWordIsSid = true) {
            sid = word;
            nextWordIsSid = false;
        }
        if (!word.compare("-sid")) {
            nextWordIsSid = true;
        }
        if (!word.compare("-n")) {
            negativeN = true;
        }
        if (!word.compare("-g")) {
            negativeG = true;
        }
        if (!word.compare("-p")) {
            negativeP = true;
        }
        if (!word.compare("-showAll")) {
            showAll = true;
        }
    }
    //time to finally make the "scan for the correct record" bit. (thats whats bellow) it searches for the line that the enrollements with the correct student id contained is on, no matter where it is contained within.
    fstream file;
    string line;
    int startLineRecord = 0;
    n = 0;
    bool recordFound = false;
    file.open(openThisFile, ios::out);
    if (file.is_open()) {
        while (getline(file, line)) {
            n++;
            if (!line.compare(" #ENROLLMENTS")) {
                startLineRecord = n;
            }
            if (!line.compare(sid)) {
                recordFound = true;
                file.close();//closing it to open again at line 1.
                break;
            }
        }
    }
    file.open(openThisFile, ios::out); //the file was closed and re-opened to set it back to line 1, but now i know the line number that the record starts on, so i can repeate the "new line" command a set number of times.
    n = 0;
    if (file.is_open()) {
        while (getline(file, line) && n != startLineRecord) {
            n++;
        }
    }
    //this next bit sorts EVERYTHING within a record, this allows me to put it in whatever config i want, so the n, g and p things are super easy!
    string name = "not found";
    int readNextLineName = 1;
    bool nameFound = false;
    string grades = "not found";
    int readNextLineGrades = 1;
    bool gradesFound = false;
    string enrolement = "not found";
    int readNextLineEnrolement = 1;
    bool enrolementFound = false;
    string phone = "not found";
    int readNextLinePhone = 1;
    bool phoneFound = false;
    int readNextLineSid = 1;
    bool sidFound = false;
    string SIDTwo = "not found";
    bool recordEndReached = false;
    if (file.is_open()) {
        while (getline(file, line)) {
            int lineLength = int(line.length());
            int tempNum = 2;
            string append;
            string letterScan;
            while (tempNum <= 5) {
                letterScan = line[tempNum];
                tempNum++;
                append = append, letterScan;
            }
            tempNum = 2; //this next bit is messy, but it will look at whats written on the line, then if it matches any catagory it will tell the code to shove whatevers in the line bellow into the corresponding variable (if a person has two names listed it will only take one)
            if (readNextLineSid == 2) {
                sid = line;
                readNextLineSid++;
            }
            if (!append.compare(" #SID")) {
                readNextLineSid++;
            }
            if (readNextLineName == 2) {
                name = line;
                readNextLineName++;
            }
            if (!append.compare(" #NAME")) {
                readNextLineName++;
            }
            if (readNextLineEnrolement == 2) {
                enrolement = line;
                readNextLineEnrolement++;
            }
            if (!append.compare(" #ENROLLMENTS")) {
                readNextLineEnrolement++;
            }
            if (readNextLinePhone == 2) {
                phone = line;
                readNextLinePhone++;
            }
            if (!append.compare(" #PHONE")) {
                readNextLinePhone++;
            }
            if (readNextLineGrades == 2) {
                grades = line;
                readNextLineGrades++;
            }
            if (!append.compare(" #GRADES")) {
                readNextLineGrades++;
            }
            if (!append.compare("#RECORD")) {
                if (readNextLineGrades != 1) {
                    gradesFound = true;
                }
                readNextLineGrades = 3;
                if (readNextLinePhone != 1) {
                    phoneFound = true;
                }
                readNextLinePhone = 3;
                if (readNextLineEnrolement != 1) {
                    enrolementFound = true;
                }
                readNextLineEnrolement = 3;
                if (readNextLineName != 1) {
                    nameFound = true;
                }
                readNextLineName = 3;
                if (readNextLineSid != 1) {
                    sidFound = true;
                }
                readNextLineSid = 3;
                recordEndReached = true;
            }
        }
    }
    file.close();
    //ok! everything should be sorted now, the next bit is configurations! (ive done so much setup for this lol)
    string output = "";
    //some of this is redundant from earlier versions, however it makes troubleshooting easier so i left it, makes no difference to the user (this is why some have else statements with alt text)
    if (negativeN = true, nameFound = true) {
        output = output + "name: " + name + "\n";
    }
    else if (negativeN = true, nameFound = false) {
        output = output + "name: not found \n";
    }
    if (negativeG = true, enrolementFound = true, gradesFound = true) {
        output = output + "enrolements: " + enrolement + "\n" + "grades: " + grades + "\n";
    }
    if (negativeP = true, phoneFound = true) {
        output = output + "phone: " + phone + "\n";
    }
    else if (negativeP = true, phoneFound = false) {
        output = output + "phone: not found \n";
    }
    if (negativeN = false, negativeG = false, negativeP = false) {
        output = "student ID: " + SIDTwo + "\n" + "name: " + name + "\n" + "enrolements: " + enrolement + "\n" + "phone: " + phone + "\n" + "grades: " + grades + "\n";
    }
    if (showAll = true) {
        file.open(openThisFile, ios::out);
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line;
            }
        }
    }
    else {
        cout << output;
    }
}