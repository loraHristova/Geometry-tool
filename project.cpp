
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int MAX = 1000000;
const double DOUBLE_MAX = 1.7976931348623157E+308;
const double DOUBLE_MIN = -1.7976931348623157E+308;

struct Line {
    double a;
    double b;
    long long id;
    string name;

    Line() : Line(0, 0) {}
    Line(double _a, double _b, string name = "-") : a(_a), b(_b), name(name) {}
};

struct Point {
    double x;
    double y;
    string name;
    long long id;

    Point() : Point(0, 0) {}
    Point(double _x, double _y, string _name = "-") : x(_x), y(_y), name(_name) {}
};

vector<Line> lines(MAX);
long long actualSizeLines = 0;
vector<Point> points(MAX);
long long actualSizePoints = 0;

void inputLine(double a, double b) {
    //fileToWriteLinesIn << actualSizeLines << " " << a << " " << b << "\n";
    //fileToWriteLinesIn.flush();
    Line line(a, b);
    lines[actualSizeLines] = (line);
    actualSizeLines++;
    lines[actualSizeLines - 1].id = actualSizeLines - 1;

    std::cout << endl << "Your line " << "y = " << a << "x + " << b << " has been created successfully!" << endl << "ID of line: " << actualSizeLines - 1 << endl;
}

void inputPoint(double x, double y) {
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

bool verifyInputData(double a, double b) {
    return (a <= DOUBLE_MIN || a >= DOUBLE_MAX) ||  (b >= DOUBLE_MAX || b <= DOUBLE_MIN);
} 

bool isAnArabicNumber(char ch) {
    return ch >= '1' && ch <= '9';
}

bool isLatinLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isValidIdLine(long long idLine) {
    if (idLine >= actualSizeLines) {
        std::cout << endl << "No such ID of line!" << endl;
        return false;
    }

    return true;
}

bool isValidIdPoint(long long idPoint) {
    if (idPoint >= actualSizePoints) {
        std::cout << endl << "No such ID of point!" << endl;
        return false;
    }

    return true;
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

bool isPointOnLine(long long idOfPoint, long long idOfLine) {
    if (!isValidIdPoint(idOfPoint) || !isValidIdLine(idOfLine))
        return false;
    
    return ((lines[idOfLine].a * points[idOfPoint].x) + lines[idOfLine].b) == points[idOfPoint].y;
}

bool createLine(long long idOfLinePar, long long idOfPointThrough, ofstream& fileToWriteLinesIn) {
    if (!isValidIdPoint(idOfPointThrough) || !isValidIdLine(idOfLinePar))
        return false;

    double coefOfLine = lines[idOfLinePar].a;
    double bOfLine = ((-1) * coefOfLine) * (points[idOfPointThrough].x) + points[idOfPointThrough].y;

    bool toSaveIt;
    std::cout << endl << "The line parallel to the line y = " << coefOfLine << "x + " << lines[idOfLinePar].b << 
        " with id : " << idOfLinePar << " and going through point (" << points[idOfPointThrough].x << ", " <<
        points[idOfPointThrough].y << ") with id : " << idOfPointThrough << " is : y = " << coefOfLine << 
        "x + " << bOfLine << endl << "Do you wish to save this line ? (1 for 'yes / 0 for 'no')";
    
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

bool createPerpLine(long long idOfLine, long long idOfPoint, ostream& fileToWriteLinesIn) {
    if (!isValidIdPoint(idOfPoint) || !isValidIdLine(idOfLine))
        return false;

    while (!isPointOnLine(idOfPoint, idOfLine)) {
        string answer;
        std::cout << endl << "The point (" << points[idOfPoint].x << ", " << points[idOfPoint].y << ") with id: "
            << idOfPoint << " is NOT on the line y= " << lines[idOfLine].a << "x + " << lines[idOfLine].b
            << "with id: " << idOfLine << ", please choose different point or line (po for new point, li for new line, b for both,e for exit)";
        std::cin >> answer;

        if (answer == "po") {
            std::cout << endl << "Please enter the id of the new point: ";
            std::cin >> idOfPoint;
            if (!isValidIdPoint(idOfPoint))
                return false;
        }
        else if (answer == "li") {
            std::cout << endl << "Please enter the id of the new line: ";
            std::cin >> idOfLine;
            if (!isValidIdLine(idOfLine))
                return false;
        }
        else if (answer == "b") {
            std::cout << endl << "Please enter the id of the new point and the id of the new line: ";
            std::cin >> idOfPoint >> idOfLine;
            if (!isValidIdPoint(idOfPoint) || !isValidIdLine(idOfLine))
                return false;
        }
        else if (answer == "e") {
            return false;
        }
        while(answer != "po" && answer != "li" && answer != "b") {
            std::cout << "Not a valid answer, please enter a valid answer (po/li/b): ";
            std::cin >> answer;
        }
    }

    double coefLine = lines[idOfLine].a;
    double newCoef = (-1) / coefLine;
    double bOfNewLine = ((-1) * newCoef * points[idOfPoint].x) + points[idOfPoint].y;

    bool saveIt;
    std::cout << endl << "The perpendicular line to the line y = " << coefLine
        << "x + " << lines[idOfLine].b << " with ID: " << idOfLine <<
        " and going through the point (" << points[idOfPoint].x << ", "
        << points[idOfPoint].y << ") with ID: " << idOfPoint << " is y = "
        << newCoef << "x + " << bOfNewLine << ". Do you want to save this line?(1 for yes/0 for no): ";
    std::cin >> saveIt;

    if (saveIt) {
        inputLine(newCoef, bOfNewLine);
    }

    return true;
}

bool checkInterception(long long idLineOne, long long idLineTwo) {
    if (!isValidIdPoint(idLineOne) || !isValidIdLine(idLineTwo))
        return false;

    double coefLineOne = lines[idLineOne].a;
    double coefLineTwo = lines[idLineTwo].a;

    double bLineOne = lines[idLineOne].b;
    double bLineTwo = lines[idLineTwo].b;

    if (coefLineOne == coefLineTwo) {

        if (bLineOne == bLineTwo) {
            std::cout << endl << "These are the same line!" << endl;
            return true;
        }
        else {
            std::cout << endl << "The lines are parralel, they don't intersect!" << endl;
            return false;
        }
    }
    else {
        double xCoord, yCoord;
        bool saveIt;

        xCoord = (bLineTwo - bLineOne) / (coefLineOne - coefLineTwo);
        yCoord = (coefLineOne * xCoord) + bLineOne;

        std::cout << endl << "This lines intersect, the intersection point is: (" << xCoord << ", " << yCoord << "). Do you want to save this point? (1 for yes, 0 for no): ";
        std::cin >> saveIt;

        if (saveIt)
            inputPoint(xCoord, yCoord);

        return true;
    }
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
            "Find perpendicular line to another line that passes through given point. (perp)" << endl <<
            "Check if two lines intercept.(inte)" << endl <<
            "Enter 0 to terminate program," << endl <<
            "Enter your choice: ";
        std::cin >> answer;

        if (answer == "l") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            std::cout << endl << "Please enter coefficients a and b: ";
            double a, b;
            std::cin >> a >> b;

            while (verifyInputData(a, b)) {
                std::cout << endl << "Too big/small of a number, please enter different coefficients: ";
                std::cin >> a >> b;
            }

            inputLine(a, b);
            
        }
        else if (answer == "p") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            std::cout << endl << "Please enter coordinates x and y: ";
            double x, y;

            std::cin >> x >> y;

            while (verifyInputData(x, y)) {
                std::cout << endl << "Too big/small of a number, please enter different coefficients: ";
                std::cin >> x >> y;
            }

            inputPoint(x, y);
            
        }

        else if (answer == "nl") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

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
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

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
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

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
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            std::cout << endl <<  "enter the ids of the line to be parallel to and the point to go through: ";

            long long idP, idL;
            std::cin >> idL >> idP;

            createLine(idL, idP, fileToWriteLinesIn);
        }

        else if (answer == "perp") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            std::cout << endl << "Please enter the id of the line to be perpendicular to and the id of the point that is on the given line: ";
            
            long long idL, idP;
            std::cin >> idL >> idP;

            createPerpLine(idL, idP, fileToWriteLinesIn);
        }

        else if (answer == "inte") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            std::cout << endl << "Please enter the ids of the lines: (2 ids):";

            long long idLOne, idLTwo;
            std::cin >> idLOne >> idLTwo;

            checkInterception(idLOne, idLTwo);
        }

        else if (answer == "0") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

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

