
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
    Line line(a, b);
    lines[actualSizeLines] = (line);
    actualSizeLines++;
    lines[actualSizeLines - 1].id = actualSizeLines - 1;

    std::cout << endl << "Your line " << "y = " << a << "x ";

    if (b >= 0)
        std::cout << "+ ";
    
    std:: cout << b << " has been created successfully!" << endl << "ID of line: " << actualSizeLines - 1 << endl;
}

void inputPoint(double x, double y) {
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

bool isPointOnLineWithId(long long idOfPoint, long long idOfLine) {
    if (!isValidIdPoint(idOfPoint) || !isValidIdLine(idOfLine))
        return false;

    return ((lines[idOfLine].a * points[idOfPoint].x) + lines[idOfLine].b) == points[idOfPoint].y;
}

bool isPointOnLine(double x, double y, double coefLine, double bLine) {
    return ((coefLine * x) + bLine) == y;
}

void askToSaveLine(double a, double b) {
    bool save;
    std::cout << endl << "Do you wish to save this line? (1 for yes/0 for no): ";
    std::cin >> save;

    if (save)
        inputLine(a, b);
}

void askToSavePoint(double x, double y) {
    bool save;
    std::cout << endl << "Do you wish to save this point? (1 for yes/0 for no): ";
    std::cin >> save;

    if (save)
        inputPoint(x, y);
}

bool createLineWithId(long long idOfLinePar, long long idOfPointThrough, ofstream& fileToWriteLinesIn) {
    if (!isValidIdPoint(idOfPointThrough) || !isValidIdLine(idOfLinePar))
        return false;

    double coefOfLine = lines[idOfLinePar].a;
    double bOfLine = ((-1) * coefOfLine) * (points[idOfPointThrough].x) + points[idOfPointThrough].y;

    
    std::cout << endl << "The line parallel to the line y = " << coefOfLine << "x + " << lines[idOfLinePar].b <<
        " with id : " << idOfLinePar << " and going through point (" << points[idOfPointThrough].x << ", " <<
        points[idOfPointThrough].y << ") with id : " << idOfPointThrough << " is : y = " << coefOfLine <<
        "x + " << bOfLine;

    askToSaveLine(coefOfLine, bOfLine);

    return true;
}

bool createLine(double coefOfLine, double bOfLine, double x, double y, ofstream& fileToWriteLinesIn) {
    double bOfNewLine = y - (coefOfLine * x);

    std::cout << endl << "The line parallel to the line y = " << coefOfLine << "x + " << bOfLine <<
        " and going through point (" << x << ", " << y << ") is : y = " << coefOfLine << 
        "x + " << bOfNewLine;
    
    askToSaveLine(coefOfLine, bOfNewLine);

    return true;
}

bool createPerpLineWithId(long long idOfLine, long long idOfPoint, ostream& fileToWriteLinesIn) {
    if (!isValidIdPoint(idOfPoint) || !isValidIdLine(idOfLine))
        return false;

    while (!isPointOnLineWithId(idOfPoint, idOfLine)) {
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
        while (answer != "po" && answer != "li" && answer != "b") {
            std::cout << "Not a valid answer, please enter a valid answer (po/li/b): ";
            std::cin >> answer;
        }
    }

    double coefLine = lines[idOfLine].a;
    double newCoef = (-1) / coefLine;
    double bOfNewLine = ((-1) * newCoef * points[idOfPoint].x) + points[idOfPoint].y;

    std::cout << endl << "The perpendicular line to the line y = " << coefLine
        << "x + " << lines[idOfLine].b << " with ID: " << idOfLine <<
        " and going through the point (" << points[idOfPoint].x << ", "
        << points[idOfPoint].y << ") with ID: " << idOfPoint << " is y = "
        << newCoef << "x + " << bOfNewLine;
   
    askToSaveLine(newCoef, bOfNewLine);

    return true;
}

bool createPerpLine(double coefLine, double bLine, double x, double y, ostream& fileToWriteLinesIn) {
    while (!isPointOnLine(x, y, coefLine, bLine)) {
        string answer;
        std::cout << endl << "The point (" << x << ", " << y << ") is NOT on the line y = " << coefLine << "x + " << bLine
          << ", please choose different point or line (po for new point, li for new line, b for both, e for exit)";
        std::cin >> answer;

        if (answer == "po") {
            std::cout << endl << "Please enter the coordinates of the new point: ";
            std::cin >> x >> y;
        }
        else if (answer == "li") {
            std::cout << endl << "Please enter the coefficients of the new line: ";
            std::cin >> coefLine >> bLine;
        }
        else if (answer == "b") {
            std::cout << endl << "Please enter the coordinates of the new point and the coefficients of the new line: ";
            std::cin >> x >> y >> coefLine >> bLine;
        }
        else if (answer == "e") {
            return false;
        }
        while(answer != "po" && answer != "li" && answer != "b" && answer != "e") {
            std::cout << "Not a valid answer, please enter a valid answer (po/li/b/e): ";
            std::cin >> answer;
        }
    }

    double newCoef = (-1) / coefLine;
    double bOfNewLine = ((-1) * newCoef * x) + y;

    std::cout << endl << "The perpendicular line to the line y = " << coefLine
        << "x + " << bLine  << " and going through the point (" << x << ", "
        << y << " is y = " << newCoef << "x + " << bOfNewLine;
   
    askToSaveLine(newCoef, bOfNewLine);

    return true;
}

bool checkInterceptionWithId(long long idLineOne, long long idLineTwo) {
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

        xCoord = (bLineTwo - bLineOne) / (coefLineOne - coefLineTwo);
        yCoord = (coefLineOne * xCoord) + bLineOne;

        std::cout << endl << "This lines intersect, the intersection point is: (" << xCoord << ", " << yCoord << ").";
        
        askToSavePoint(xCoord, yCoord);

        return true;
    }
}

bool checkInterception(double coefLineOne, double bLineOne, double coefLineTwo, double bLineTwo) {
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

        std::cout << endl << "This lines intersect, the intersection point is: (" << xCoord << ", " << yCoord << ").";
        
        askToSavePoint(xCoord, yCoord);

        return true;
    }
}

double findDistanceBetweenTwoPoints(double xFirst, double yFirst, double xSecond, double ySecond) {
    return sqrt((xFirst - xSecond) * (xFirst - xSecond) + (yFirst - ySecond) * (yFirst - ySecond));
}

void findLineBetweenTwoPoints(double xFirst, double yFirst, double xSecond, double ySecond, double& coef, double& b, bool& isVertical) {
    if ((xSecond - xFirst) == 0) {
        coef = 1;
        b = xFirst;
        isVertical = true;
    }
    else {
        coef = (ySecond - yFirst) / (xSecond - xFirst);
        b = yFirst - (coef * xFirst);
        isVertical = false;
    }
}

bool isValidTriangle(double xF, double yF, double xS, double yS, double xT, double yT) {
    double distFS = findDistanceBetweenTwoPoints(xF, yF, xS, yS);
    double distFT = findDistanceBetweenTwoPoints(xF, yF, xT, yT);
    double distST = findDistanceBetweenTwoPoints(xS, yS, xT, yT);

    return !((distFS + distFT <= distST) || (distFS + distST <= distFT) || (distFT + distST <= distFS));
}

void findAltitudes(double xFirst, double yFirst, double xSecond, double ySecond, double xThird, double yThird) {
    double coefFS, coefFT, coefST, bFS, bFT, bST;
    bool isVertical;

    findLineBetweenTwoPoints(xFirst, yFirst, xSecond, ySecond, coefFS, bFS, isVertical);
    findLineBetweenTwoPoints(xFirst, yFirst, xThird, yThird, coefFT, bFT, isVertical);
    findLineBetweenTwoPoints(xSecond, ySecond, xThird, yThird, coefST, bST, isVertical);

    double coefAltF, coefAltS, coefAltT, bAltF, bAltS, bAltT;

    coefAltF = (-1) / coefST;
    bAltF = yFirst - (coefAltF * xFirst);

    coefAltS = (-1) / coefFT;
    bAltS = ySecond - (coefAltS * xSecond);

    coefAltT = (-1) / coefFS;
    bAltT = yThird - (coefAltT * xThird);

    std::cout << endl << "The altitude from point (" << xFirst << ", " << yFirst << ") is y = " << coefAltF <<
        "x + " << bAltF << "." << endl << "The altitude from point (" << xSecond << ", " << ySecond << ") is y = "
        << coefAltS << "x + " << bAltS << "." << endl << "The altitude from point (" << xThird << ", " << yThird << ") is y = " << coefAltT <<
        "x + " << bAltT << ". Do you wish to save those lines? (1 0 0 for 'save only first', ..., 1 1 1 for 'save all'): ";

    bool saveF, saveS, saveT;
    std::cin >> saveF >> saveS >> saveT;

    if (saveF)
        inputLine(coefAltF, bAltF);
    if (saveS)
        inputLine(coefAltS, bAltS);
    if (saveT)
        inputLine(coefAltT, bAltT);
}

void findMedians(double xFirst, double yFirst, double xSecond, double ySecond, double xThird, double yThird) {
    double xHalfFS = (xFirst + xSecond) / 2;
    double yHalfFS = (yFirst + ySecond) / 2;

    double xHalfFT = (xFirst + xThird) / 2;
    double yHalfFT = (yFirst + yThird) / 2;

    double xHalfST = (xSecond + xThird) / 2;
    double yHalfST = (ySecond + yThird) / 2;

    double coefF, coefS, coefT, bF, bS, bT;
    bool isVerticalF, isVerticalS, isVerticalT;

    findLineBetweenTwoPoints(xFirst, yFirst, xHalfST, yHalfST, coefF, bF, isVerticalF);
    findLineBetweenTwoPoints(xSecond, ySecond, xHalfFT, yHalfFT, coefS, bS, isVerticalS);
    findLineBetweenTwoPoints(xThird, yThird, xHalfFS, yHalfFS, coefT, bT, isVerticalT);

    std::cout << endl << "The median from (" << xFirst << ", " << yFirst << ") is: ";
    
    if (isVerticalF)
        std::cout << "x = " << bF << "." << endl;
    else {
        std::cout << "y = " << coefF << "x ";

        if (bF >= 0)
            std::cout << "+ ";

        std::cout << bF << "." << endl;
    }
        
    std::cout << "The median from (" << xSecond << ", " << ySecond << ") is: ";

    if (isVerticalS)
        std::cout << "x = " << bS << "." << endl;
    else {
        std::cout << "y = " << coefS << "x ";
        
        if (bS >= 0)
            std::cout << "+ ";
        
        std::cout << bS << "." << endl;
    }
    std::cout << "The median from (" << xThird << ", " << yThird << ") is:";
    
    if (isVerticalT) {
        std::cout << "x = " << bT << "." << endl;
    }
    else {
        std::cout << "y = " << coefT << "x ";
        
        if (bT >= 0)
            std::cout << "+ ";

        std::cout << bT << "." << endl;
    }

    std::cout << endl << ". Do you want to save those lines? (1 0 0 for saving only the first, ..., 1 1 1 for saving all): ";

    bool saveF, saveS, saveT;
    std::cin >> saveF >> saveS >> saveT;

    if (saveF)
        inputLine(coefF, bF);
    if (saveS)
        inputLine(coefS, bS);
    if (saveT)
        inputLine(coefT, bT);
}

void findSimetrals(double xFirst, double yFirst, double xSecond, double ySecond, double xThird, double yThird) {
    double xHalfFS = (xFirst + xSecond) / 2;
    double yHalfFS = (yFirst + ySecond) / 2;

    double xHalfFT = (xFirst + xThird) / 2;
    double yHalfFT = (yFirst + yThird) / 2;

    double xHalfST = (xSecond + xThird) / 2;
    double yHalfST = (ySecond + yThird) / 2;

    double coefLineFS, coefLineST, coefLineFT, bLineFS, bLineST, bLineFT;
    bool isVertical;

    findLineBetweenTwoPoints(xFirst, yFirst, xSecond, ySecond, coefLineFS, bLineFS, isVertical);
    findLineBetweenTwoPoints(xFirst, yFirst, xThird, yThird, coefLineFT, bLineFT, isVertical);
    findLineBetweenTwoPoints(xSecond, ySecond, xThird, yThird, coefLineST, bLineST, isVertical);

    double newCoefFS = (-1) / coefLineFS;
    double bOfNewFS = ((-1) * newCoefFS * xHalfFS) + yHalfFS;

    double newCoefFT = (-1) / coefLineFT;
    double bOfNewFT = ((-1) * newCoefFT * xHalfFT) + yHalfFT;

    double newCoefST = (-1) / coefLineST;
    double bOfNewST = ((-1) * newCoefST * xHalfST) + yHalfST;

    std::cout << endl << "The simetral through the line between points (" << xFirst << ", " << yFirst << ") and (" << xSecond << ", " <<
        ySecond << ") is y = " << newCoefFS << "x ";

    if (bOfNewFS >= 0)
        std::cout << "+ ";

    std::cout << bOfNewFS << "." << endl << "The simetral through the line between points(" << xFirst << ", " << yFirst << ") and (" << xThird << ", " <<
        yThird << ") is y = " << newCoefFT << "x ";

    if (bOfNewFT >= 0)
        std::cout << "+ ";

    std::cout << bOfNewFT << "." << endl << "The simetral through the line between points(" << xSecond << ", " << ySecond << ") and (" << xThird << ", " <<
        yThird << ") is y = " << newCoefST << "x ";

    if (bOfNewST >= 0)
        std::cout << "+ ";

    std::cout << bOfNewST << ".";
}

void printIsPointOnLineWithId(long long idPoint, long long idLine) {
    if (isPointOnLineWithId(idPoint, idLine)) {
        std::cout << "The point (" << points[idPoint].x << ", " << points[idPoint].y << ") is on the line y = " << lines[idLine].a << "x ";

        if (lines[idLine].b >= 0)
            std::cout << "+ ";

        std::cout << lines[idLine].b;
    }
    else {
        std::cout << "The point (" << points[idPoint].x << ", " << points[idPoint].y << ") is NOT on the line y = " << lines[idLine].a << "x ";

        if (lines[idLine].b >= 0)
            std::cout << "+ ";

        std::cout << lines[idLine].b;
    }
}

void printIsPointOnLine(double x, double y, double a, double b) {
    if (isPointOnLine(x, y, a, b)) {
        std::cout << "The point (" << x << ", " << y << ") is on the line y = " << a << "x ";

        if (b >= 0)
            std::cout << "+ ";

        std::cout << b;
    }
    else {
        std::cout << "The point (" << x << ", " << y << ") is NOT on the line y = " << a << "x ";

        if (b >= 0)
            std::cout << "+ ";

        std::cout << b;
    }
}

void askReuse(bool& createdLine, bool& createdPoint) {
    if (actualSizeLines > 0) {
        std::cout << endl << "Do you want to use a line that is already created? (1 for yes/0 for no): ";
        std::cin >> createdLine;
    }
    else
        createdLine = 0;

    if (actualSizePoints > 0) {
        std::cout << endl << "Do you want to use a point that is already created? (1 for yes/0 for no): ";
        std::cin >> createdPoint;
    }
    else
        createdPoint = 0;
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
            "Build a triangle by three points and get altitudes, medians and semitrals. (tr)" << endl << 
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

            bool createdLine, createdPoint;

            askReuse(createdLine, createdPoint);

            if (createdLine && createdPoint) {
                long long idPoint;
                std::cout << endl << "Please enter the ID of the point: ";
                std::cin >> idPoint;

                long long idLine;
                std::cout << endl << "Please enter the ID of the line: ";
                std::cin >> idLine;

                printIsPointOnLineWithId(idPoint, idLine);
            }

            else if (!createdLine && !createdPoint) {
                double a, b;
                std::cout << endl << "Please enter the coefficients of the line:";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                double x, y;
                std::cout << endl << "Please enter the coordinates of the point: ";
                std::cin >> x >> y;

                askToSavePoint(x, y);

                printIsPointOnLine(x, y, a, b);
            }

            else if (!createdLine && createdPoint) {
                double a, b;
                std::cout << endl << "Please enter the coefficients of the line: ";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                long long idPoint;
                std::cout << endl << "Please enter the ID of the point you wish to use: ";
                std::cin >> idPoint;

                while (!isValidIdPoint(idPoint)) {
                    std::cout << endl << "Please enter valid ID of point: ";
                    std::cin >> idPoint;
                }

                double x = points[idPoint].x;
                double y = points[idPoint].y;

                printIsPointOnLine(x, y, a, b);
            }

            else if (createdLine && !createdPoint) {
                long long idLine;
                std::cout << endl << "Please enter the ID of the line you wish to use: ";
                std::cin >> idLine;

                while (!isValidIdLine(idLine)) {
                    std::cout << endl << "Please enter valid ID for line: ";
                    std::cin >> idLine;
                }

                double a = lines[idLine].a;
                double b = lines[idLine].b;
                double x, y;
                std::cout << endl << "Please enter the coordinates of the point you wish to use: ";
                std::cin >> x >> y;

                askToSavePoint(x, y);

                printIsPointOnLine(x, y, a, b);
            }
        }

        else if (answer == "par") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            bool createdLine, createdPoint;

            askReuse(createdLine, createdPoint);

            if (createdLine && createdPoint) {
                long long idLine, idPoint;
                std::cout << endl << "Please enter the ID of the line you wish to use: ";
                std::cin >> idLine;

                std::cout << endl << "Please enter the ID of the point you wish to use: ";
                std::cin >> idPoint;

                createLineWithId(idLine, idPoint, fileToWriteLinesIn);
            }
            else if (!createdLine && !createdPoint) {

                double a, b, x, y;
                std::cout << endl << "Please enter the coefficients of the line to be parallel to: ";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                std::cout << endl << "Please enter the coordinates of the point to go through: ";
                std::cin >> x >> y;

                askToSavePoint(x, y);

                createLine(a, b, x, y, fileToWriteLinesIn);
            }
            else if (createdLine && !createdPoint) {
                double idLine, x, y;

                std::cout << endl << "Please enter the ID of the line you wish to use: ";
                std::cin >> idLine;

                while (!isValidIdLine(idLine)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idLine;
                }

                double coefLine = lines[idLine].a;
                double bLine = lines[idLine].b;

                std::cout << endl << "Please enter the coordinates of the point to go through: ";
                std::cin >> x >> y;
                
                askToSavePoint(x, y);

                createLine(coefLine, bLine, x, y, fileToWriteLinesIn);
            }
            else if (!createdLine && createdPoint) {
                double a, b, idPoint;

                std::cout << endl << "Please enter the coefficients of the line you wish to use: ";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                std::cout << endl << "Please enter the ID of the point to go through: ";
                std::cin >> idPoint;

                while (!isValidIdPoint(idPoint)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idPoint;
                }

                double x = points[idPoint].x;
                double y = points[idPoint].y;
               
                createLine(a, b, x, y, fileToWriteLinesIn);
            }
        }

        else if (answer == "perp") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            bool createdLine, createdPoint;

            askReuse(createdLine, createdPoint);

            if (createdLine && createdPoint) {
                long long idLine, idPoint;

                std::cout << endl << "Please enter the ID of the line: ";
                std::cin >> idLine;

                std::cout << endl << "Please enter the ID of the point: ";
                std::cin >> idPoint;

                createPerpLineWithId(idLine, idPoint, fileToWriteLinesIn);
            }

            else if (!createdLine && !createdPoint) {
                double a, b;
                std::cout << endl << "Please enter the coefficients of the line: ";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                double x, y;
                std::cout << endl << "Please enter the coordinates of the point: ";
                std::cin >> x >> y;

                askToSavePoint(x, y);

                createPerpLine(a, b, x, y, fileToWriteLinesIn);
            }

            else if (!createdLine && createdPoint) {
                double a, b;
                std::cout << endl << "Please enter the coefficients of the line: ";
                std::cin >> a >> b;

                askToSaveLine(a, b);

                long long idPoint;
                std::cout << endl << "Please enter the ID of the point: ";
                std::cin >> idPoint;

                while (!isValidIdPoint(idPoint)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idPoint;
                }

                double x = points[idPoint].x;
                double y = points[idPoint].y;

                createPerpLine(a, b, x, y, fileToWriteLinesIn);
            }

            else if (createdLine && !createdPoint) {
                long long idLine;
                std::cout << endl << "Please enter the ID of the line: ";
                std::cin >> idLine;

                while (!isValidIdLine(idLine)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idLine;
                }

                double a = lines[idLine].a;
                double b = lines[idLine].b;

                double x, y;
                std::cout << endl << "Please enter the coordinates of the point: ";
                std::cin >> x >> y;

                askToSavePoint(x, y);

                createPerpLine(a, b, x, y, fileToWriteLinesIn);
            }
        }

        else if (answer == "inte") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            bool firstCreatedLine, secondCreatedLine;

            if (actualSizeLines > 0) {
                std::cout << endl << "Do you want to use lines you have already created? (0 0 for use two new lines, 1 0 for use first already created line and second new line, ..., 1 1 for use two already created lines): ";
                std::cin >> firstCreatedLine >> secondCreatedLine;
            }
            else
            {
                firstCreatedLine = 0;
                secondCreatedLine = 0;
            }

            if (firstCreatedLine && secondCreatedLine) {
                long long idFirst, idSecond;
                std::cout << endl << "Please enter the ID of the first line and the ID of the second line: ";
                std::cin >> idFirst >> idSecond;

                checkInterceptionWithId(idFirst, idSecond);
            }
            else if (!firstCreatedLine && !secondCreatedLine) {
                double a1, b1;
                std::cout << endl << "Please enter the coefficients of the first line: ";
                std::cin >> a1 >> b1;

                askToSaveLine(a1, b1);

                double a2, b2;
                std::cout << endl << "Please enter the coefficients of the second line: ";
                std::cin >> a2 >> b2;

                askToSaveLine(a2, b2);

                checkInterception(a1, b1, a2, b2);
            }
            else if (!firstCreatedLine && secondCreatedLine) {
                double a1, b1;
                std::cout << endl << "Please enter the coefficients of the first line: ";
                std::cin >> a1 >> b1;

                askToSaveLine(a1, b1);

                long long idSecond;
                std::cout << endl << "Please enter tne ID of the second line: ";
                std::cin >> idSecond;

                while (!isValidIdLine(idSecond)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idSecond;
                }

                double a2, b2;
                a2 = lines[idSecond].a;
                b2 = lines[idSecond].b;

                checkInterception(a1, b1, a2, b2);
            }

            else if (firstCreatedLine && !secondCreatedLine) { 
                long long idFirst;
                std::cout << endl << "Please enter tne ID of the first line: ";
                std::cin >> idFirst;

                while (!isValidIdLine(idFirst)) {
                    std::cout << endl << "Please enter a valid ID: ";
                    std::cin >> idFirst;
                }

                double a1, b1;
                a1 = lines[idFirst].a;
                b1 = lines[idFirst].b;

                double a2, b2;
                std::cout << endl << "Please enter the coefficients of the second line: ";
                std::cin >> a2 >> b2;

                askToSaveLine(a2, b2);

                checkInterception(a1, b1, a2, b2);
            }
        }

        else if (answer == "tr") {
            bool exit;
            std::cout << endl << "Do you want to go back to the main menu? (1 for yes/0 for no): ";
            std::cin >> exit;

            if (exit)
                continue;

            bool firstCreatedPoint, secondCreatedPoint, thirdCreatedPoint;

            if (actualSizePoints > 0) {
                std::cout << endl << "Do you want to use already existant points? (0 0 0 for 'not at all', 1 0 0 for 'use only first point of the created, for the rest no', ..., 1 1 1 for 'use all existant points')";
                std::cin >> firstCreatedPoint >> secondCreatedPoint >> thirdCreatedPoint;
            }
            else
                firstCreatedPoint = secondCreatedPoint = thirdCreatedPoint = 0;

            if (firstCreatedPoint && secondCreatedPoint && thirdCreatedPoint) {
                long long idF, idS, idT;
                std::cout << endl << "Please enter the IDs of all three points: ";
                std::cin >> idF >> idS >> idT;

                while (!isValidIdPoint(idF) || !isValidIdPoint(idS) || !isValidIdPoint(idT)) {
                    std::cout << "Please enter valid IDs: (enter all IDs)";
                    std::cin >> idF >> idS >> idT;
                }

                double x1 = points[idF].x;
                double y1 = points[idF].y;

                double x2 = points[idS].x;
                double y2 = points[idS].y;

                double x3 = points[idT].x;
                double y3 = points[idT].y;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3)) 
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
                
                
            }
            else if (!firstCreatedPoint && !secondCreatedPoint && !thirdCreatedPoint) {

                double x1, y1;
                std::cout << endl << "Please enter the coordinates of the first point: ";
                std::cin >> x1 >> y1;

                double x2, y2;
                std::cout << endl << "Please enter the coordinates of the second point: ";
                std::cin >> x2 >> y2;

                double x3, y3;
                std::cout << endl << "Please enter the coordinates of the third point: ";
                std::cin >> x3 >> y3;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }

            else if (!firstCreatedPoint && secondCreatedPoint && thirdCreatedPoint) {

                double x1, y1;
                std::cout << endl << "Please enter the coordinates of the first point: ";
                std::cin >> x1 >> y1;

                long long idS, idT;
                std::cout << endl << "Please enter the IDs of the second and the third point: ";
                std::cin >> idS >> idT;

                while (!isValidIdPoint(idS) || !isValidIdPoint(idT)) {
                    std::cout << endl << "Please enter correct IDs (re-enter all): ";
                    std::cin >> idS >> idT;
                }

                double x2 = points[idS].x;
                double y2 = points[idS].y;

                double x3 = points[idT].x;
                double y3 = points[idT].y;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }

            else if (firstCreatedPoint && !secondCreatedPoint && thirdCreatedPoint) {

                long long idF;
                std::cout << endl << "Please enter the ID of the first point you want to use: ";
                std::cin >> idF;

                while (!isValidIdPoint(idF)) {
                    std::cout << endl << "Please enter a valid ID for the first point: ";
                    std::cin >> idF;
                }

                double x1 = points[idF].x;
                double y1 = points[idF].y;


                double x2, y2;
                std::cout << endl << "Please enter the coordinates of the second point: ";
                std::cin >> x2 >> y2;

                long long idT;
                std::cout << endl << "Please enter the ID of the third point: ";
                std::cin >> idT;

                while (!isValidIdPoint(idT)) {
                    std::cout << endl << "Please a valid ID for the third point: ";
                    std::cin >> idT;
                }

                double x3 = points[idT].x;
                double y3 = points[idT].y;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }

            else if (firstCreatedPoint && secondCreatedPoint && !thirdCreatedPoint) {
                long long idF, idS;
                std::cout << endl << "Please enter the IDs of the first and the second point: ";
                std::cin >> idF >> idS;

                while (!isValidIdPoint(idF) || !isValidIdPoint(idS)) {
                    std::cout << endl << "Please enter correct IDs (re-enter all): ";
                    std::cin >> idF >> idS;
                }

                double x1 = points[idF].x;
                double y1 = points[idF].y;

                double x2 = points[idS].x;
                double y2 = points[idS].y;
                
                double x3, y3;
                std::cout << endl << "Please enter the coordinates of the third point: ";
                std::cin >> x3 >> y3;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }

            else if (!firstCreatedPoint && !secondCreatedPoint && thirdCreatedPoint) {
                double x1, y1;
                std::cout << endl << "Please enter the coordinates of the first point: ";
                std::cin >> x1 >> y1;


                double x2, y2;
                std::cout << endl << "Please enter the coordinates of the second point: ";
                std::cin >> x2 >> y2;

                long long idT;
                std::cout << endl << "Please enter the ID of the third point: ";
                std::cin >> idT;

                while (!isValidIdPoint(idT)) {
                    std::cout << endl << "Please a valid ID for the third point: ";
                    std::cin >> idT;
                }

                double x3 = points[idT].x;
                double y3 = points[idT].y;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }

            else if (!firstCreatedPoint && secondCreatedPoint && !thirdCreatedPoint) {
                double x1, y1;
                std::cout << endl << "Please enter the coordinates of the first point: ";
                std::cin >> x1 >> y1;

                long long idS;
                std::cout << endl << "Please enter the ID of the second point: ";
                std::cin >> idS;

                while (!isValidIdPoint(idS)) {
                    std::cout << endl << "Please enter correct ID for the second point: ";
                    std::cin >> idS;
                }

                double x2 = points[idS].x;
                double y2 = points[idS].y;

                double x3, y3;
                std::cout << endl << "Please enter the coordinates of the third point: ";
                std::cin >> x3 >> y3;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
                }

            else if (firstCreatedPoint && !secondCreatedPoint && !thirdCreatedPoint) {
                long long idF;
                std::cout << endl << "Please enter the IDs of the first point: ";
                std::cin >> idF;

                while (!isValidIdPoint(idF)) {
                    std::cout << endl << "Please enter a correct ID for the firstPoint: ";
                    std::cin >> idF;
                }

                double x1 = points[idF].x;
                double y1 = points[idF].y;

                double x2, y2;
                std::cout << endl << "Please enter the coordinates of the second point: ";
                std::cin >> x2 >> y2;

                double x3, y3;
                std::cout << endl << "Please enter the coordinates of the third point: ";
                std::cin >> x3 >> y3;

                if (!isValidTriangle(x1, y1, x2, y2, x3, y3))
                    std::cout << endl << "These points does not form a triangle!";
                else {
                    findAltitudes(x1, y1, x2, y2, x3, y3);
                    findMedians(x1, y1, x2, y2, x3, y3);
                    findSimetrals(x1, y1, x2, y2, x3, y3);
                }
            }  
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

