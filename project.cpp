
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int MAX = 1000000;

struct Line {
    long long a;
    long long b;
    long long id;
    string name;

    Line() : Line(0, 0) {}
    Line(long long _a, long long _b, string name = "-") : a(_a), b(_b), name(name) {}
};

struct Point {
    long long x;
    long long y;
    string name;
    long long id;

    Point() : Point(0, 0) {}
    Point(long long _x, long long _y, string _name = "-") : x(_x), y(_y), name(_name) {}
};

vector<Line> lines(MAX);
long long actualSizeLines = 0;
vector<Point> points(MAX);
long long actualSizePoints = 0;

void inputLine(long long a, long long b) {
    //fileToWriteLinesIn << actualSizeLines << " " << a << " " << b << "\n";
    //fileToWriteLinesIn.flush();
    Line line(a, b);
    lines[actualSizeLines] = (line);
    actualSizeLines++;
    lines[actualSizeLines - 1].id = actualSizeLines - 1;

    std::cout << endl << "Your line " << "y = " << a << "x + " << b << " has been created successfully!" << endl << "ID of line: " << actualSizeLines - 1 << endl;
}

void inputPoint(long long x, long long y) {
    //fileToWritePointsIn << actualSizePoints << x << y << "\n";
    //fileToWritePointsIn.flush();
    Point point(x, y);
    points[actualSizePoints] = point;
    actualSizePoints++;
    points[actualSizePoints - 1].id = actualSizePoints - 1;

    std::cout << endl << "Your point " << "(" << x << " , " << y << ") has been created successfully!" << endl << "ID of point: " << actualSizePoints - 1 << endl;
}

void setNameToLine(long long index, const string& _name) {
    if (index < actualSizeLines)
    {
        lines[index].name = _name;
        std::cout << endl << "The name: " << lines[index].name << " to line y = " << lines[index].a << "x + " << lines[index].b << " was set successfully!" << endl;
    }

    else
        std::cout << endl << "This is an invalid ID, no such line exists!" << std::endl;
}

void setNameToPoint(long long index, const string& _name) {
    if (index < actualSizePoints) {
        points[index].name = _name;
        std::cout << endl << "The name: " << points[index].name << " to point (" << points[index].x << " , " << points[index].y << ") was set successfully!" << endl;
    }

    else
        std::cout << endl << "This is an invalid ID, no such point exists!" << std::endl;
}

bool verifyInputData(long long a, long long b) {
    return (a <= LLONG_MIN || a >= LLONG_MAX) ||  (b >= LLONG_MAX || b <= LLONG_MIN);
} 

bool isAnArabicNumber(char ch) {
    return ch >= '1' && ch <= '9';
}

bool isLatinLetter(char ch) {
    return (ch >= 'a' & ch <= 'z') || (ch >= 'A' & ch <= 'Z');
}

bool verifyInputDataName(const string& name) {
    for (int i = 0; i < name.length(); i++) {
        if (isAnArabicNumber(name[i]) || isLatinLetter(name[i]) || name[i] == '_')
            continue;
        else
            return false;
    }

    return true;
}

void saveLinesToFile(ofstream& fileToWriteLinesIn) {
    for (int i = 0; i < actualSizeLines; i++) {
        fileToWriteLinesIn << lines[i].id << " " << lines[i].a << " " << lines[i].b << " " << lines[i].name << '\n';
        fileToWriteLinesIn.flush();
    }
}

void savePointsToFile(ofstream& fileToWritePointsIn) {
    for (int i = 0; i < actualSizePoints; i++) {
        fileToWritePointsIn << points[i].id << " " << points[i].x << " " << points[i].y << " " << points[i].name << '\n';
        fileToWritePointsIn.flush();
    }
}

bool isPointOnLine(int idOfPoint, int idOfLine) {
    if (idOfPoint >= actualSizePoints) {
        std::cout << endl << "No such ID of point!" << endl;
        return false;
    }
    if (idOfLine >= actualSizeLines) {
        std::cout << endl << "No such ID of line!" << endl;
        return false;
    }

    return ((lines[idOfLine].a * points[idOfPoint].x) + lines[idOfLine].b) == points[idOfPoint].y;
}

bool createLine(int idOfLinePar, int idOfPointThrough, ofstream& fileToWriteLinesIn) {
    if (idOfPointThrough >= actualSizePoints) {
        std::cout << endl << "No such ID of point!" << endl;
        return false;
    }
    if (idOfLinePar >= actualSizeLines) {
        std::cout << endl << "No such ID of line!" << endl;
        return false;
    }

    int coefOfLine = lines[idOfLinePar].a;
    int bOfLine = ((-1) * coefOfLine) * (points[idOfPointThrough].x) + points[idOfPointThrough].y;

    bool toSaveIt;
    std::cout << endl << "The line parallel to the line with id: " << idOfLinePar << " and going through point with id: " << idOfPointThrough << " is: y = " << coefOfLine << "x +" << bOfLine << endl << "Do you wish to save this line? (1 for 'yes / 0 for 'no')";
    
    std::cin >> toSaveIt;

    while (toSaveIt != 0 && toSaveIt != 1) {
        std::cout << endl << "Unvalid answer, please enter 1 if you want to save this line or 0 if you don't want to save it: ";
        std:cin >> toSaveIt;
    }

    if (toSaveIt) {
        inputLine(coefOfLine, bOfLine);
    }
    else {
        std::cout << endl << "The line has not been saved!" << endl;
    }

    return true;
}

void usersInput(ofstream& fileToWriteLinesIn, ofstream& fileToWritePointsIn) {
    bool toBeStopped = false;
    string answer;

    while (!toBeStopped) {
        std::cout << endl << "Choose one of the options below:" << endl <<
            "Enter a line with coefficients a and b: y = ax + b. (l)," << endl <<
            "Enter a point with coordinates x and y: (x, y). (p)," << endl <<
            "Name a created line. (nl)," << endl <<
            "Name a created point. (np)," << endl <<
            "Check if point is on line. (cp)" << endl <<
            "Find parallel line to another line and going through a point. (par)" << endl <<
            "Enter 0 to terminate program," << endl <<
            "Enter your choice: ";
        std::cin >> answer;

        if (answer == "l") {
            std::cout << endl << "Please enter coefficients a and b: ";
            long long a, b;
            std::cin >> a >> b;

            while (verifyInputData(a, b)) {
                std::cout << endl << "Too big/small of a number, please enter different coefficients: ";
                std::cin >> a >> b;
            }

            inputLine(a, b);
            
        }
        else if (answer == "p") {
            std::cout << endl << "Please enter coordinates x and y: ";
            long long x, y;

            std::cin >> x >> y;

            while (verifyInputData(x, y)) {
                std::cout << endl << "Too big/small of a number, please enter different coefficients: ";
                std::cin >> x >> y;
            }

            inputPoint(x, y);
            
        }

        else if (answer == "nl") {
            std::cout << endl << "Please enter the ID of the line you wish to name: ";
            long long ID;
            std::cin >> ID;

            std::cout << endl << "Please enter the name with which you wish to name your line: ";
            string nameLine;
            std::cin >> nameLine;

            while (!verifyInputDataName(nameLine)) {
                std::cout << endl << "The name can contain ONLY arabic numbers, latin letters and underscore ('_')! Please enter a different name: ";
                std::cin >> nameLine;
            }

            setNameToLine(ID, nameLine);
        }

        else if (answer == "np") {
            std::cout << endl << "Please enter the ID of the point you wish to name: ";
            long long ID;
            std::cin >> ID;

            std::cout << endl << "Please enter the name with which you wish to name your point: ";
            string namePoint;
            std::cin >> namePoint;

            while (!verifyInputDataName(namePoint)) {
                std::cout << endl << "The name can contain ONLY arabic numbers, latin letters and underscore ('_')! Please enter a different name: ";
                std::cin >> namePoint;
            }

            setNameToPoint(ID, namePoint);
        }

        else if (answer == "cp") {
            std::cout << endl << "Please enter the id of the point and id of line: ";
            
            long long idP, idL;
            std::cin >> idP >> idL;

            if (isPointOnLine(idP, idL)) {
                std::cout << endl << "The point (" << points[idP].x << ", " << points[idP].y << ") is on the line: y = " << lines[idL].a << "x + " << lines[idL].b << endl;
            }
            else
                std::cout << endl << "The point (" << points[idP].x << ", " << points[idP].y << ") is NOT on the line: y = " << lines[idL].a << "x + " << lines[idL].b << endl;
        }

        else if (answer == "par") {
            std::cout << endl <<  "enter the ids of the line to be parallel to and the point to go through: ";

            long long idP, idL;
            std::cin >> idL >> idP;

            createLine(idL, idP, fileToWriteLinesIn);
        }

        else if (answer == "0") {
            toBeStopped = true;
            saveLinesToFile(fileToWriteLinesIn);
            savePointsToFile(fileToWritePointsIn);
        }
       
        else
            std::cout << "Unvalid operation!" << endl;
    }
}

int main()
{
    ofstream MyFileLines("GeometryToolLines.txt", std::ofstream::app);
    ofstream MyFilePoints("GeometryToolPoints.txt", std::ofstream::app);

    if (!MyFileLines.is_open() || !MyFilePoints.is_open()) {
        std::cout << "Couldn't open one of the files!";
        MyFileLines.close();
        MyFilePoints.close();
        return 0;
    }

    usersInput(MyFileLines, MyFilePoints);
    
    MyFileLines.close();
    MyFilePoints.close();
}

