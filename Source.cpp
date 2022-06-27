#include "Banking.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include<conio.h>  //_getch
#include <windows.h> //sleep

using namespace std;

/**
 * Returns a string of length n, each character a c.
 * For example, nCharString(5, '*') should return "*****"
 *
 * @param n string length, >=0
 * @return string of n c's
 */
string nCharString(size_t n, char c) {

    string cstr;
    unsigned int i;

    for (i = 0; i < n; i++) {
        cstr = c + cstr; // adds additional character to string
    }
    return cstr;
}

/**
 * displays data entry screen
 */
void displayEntries(string entries[], const unsigned int NUM) {
   
    unsigned int i = 0;
    cout << nCharString(50, '*') << endl;  // adds top border and title
    cout << nCharString(18, '*') << " Data Input " << nCharString(20, '*') << endl;

    // prints data entry headings with border 
    for (i = i; i < NUM; i++) {
        cout << entries[i] << endl;
    }
    cout << "Press any key to continue ...";
}

/**
 * Display the report title and headings with a border
 *
 * @param type, report type
 */
void displayReportHeader(string type) {

    string headings[] = { "Year", "Year End Balance", "Year End Earned Interest" };
    const unsigned int NUM_HEADINGS = 3; //headings array length
    unsigned int i;

    cout << nCharString(75, '-') << endl;  // adds top border and displays report title using report type
    cout << nCharString(10, ' ') << "Balance and Interest " << type << " Additional Monthly Deposits" << endl;
    cout << nCharString(75, '=') << endl;  // adds bottom border

    // displays headings 
    for (i = 0; i < NUM_HEADINGS; i++) {
        cout << nCharString(5, ' ') << headings[i] << nCharString(5, ' ');
    }
    cout << endl << nCharString(75, '-') << endl; //adds border
}

/**
 * Display the annual report details
 *
 * @param yearIndex, specified year
 * @param balance, year end balance
 * @param interestEarnedThisYear, ""
 */
void printReport(unsigned int yearIndex, double balance, double interestEarnedThisYear) {

    cout << setprecision(2) << fixed; //formats to two decimal places

    cout << nCharString(7, ' ') << yearIndex << nCharString(15, ' ') << "$" << balance << nCharString(23, ' ')
        << "$" << interestEarnedThisYear << endl;  //prints details for the year
}

/**
 * Gets and validates double input values from user for data entries
 *
 * @return dbl, valid input
 */
double validInput(unsigned int incr) {

    double dbl;
    string line;
    COORD coord; //to move cursor position on console
    
    coord.X = 32; //sets coordinates
    coord.Y = 2 + incr;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    while (getline(cin, line)) {
        
        stringstream ss(line); //gets user entry 

        try {
            cin.clear();
            if (ss >> dbl && ss.eof() && dbl >= 0) { 
                break; //ends loop if positive double 
            }
            else {
                throw runtime_error("");
                cin.clear();
            }
        }
        catch (runtime_error& excpt) {
            MessageBox(0, L"Data is not a number greater than or equal to zero.\nEnter a valid number.", L"Error", MB_OK);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << nCharString(15, ' ');  // hides previous input
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
    }
    return dbl;
}

/**
 * Sets vailid input values from user for data entries
 * 
 * @return obj, the object with the data entries 
 */
Banking inputValues(Banking obj) {

    unsigned int y = 0; //to increment position of cursor
    
    obj.setInvestment(validInput(y++));
    obj.setDeposit(validInput(y++));
    obj.setInterest(validInput(y++));
    obj.setYears(validInput(y++));

    return obj;
}

/**
* Calculates balance With or Without monthly deposit
*
* @param data, obj with data entries
* @param report, report type "With" or "Without"
*/
double calculateBalance(Banking data, string report) {

    double deposit = (report == "Without") ? 0 : data.getDeposit(); // based on report type
    unsigned int months = 12; //months in a year
    unsigned int years = data.getYears();
    double rate = (data.getInterest() / 100) / months; //monthly rate
    double balance = data.getInvestment(); //initial year 0 balance
    double interestForThisMonth, interestForThisYear;
    unsigned int i, j;

    displayReportHeader(report);
    // calculate report values
    for (i = 1; i <= years; i++) {
        interestForThisYear = 0;
        for (j = 1; j <= months; j++) {
            interestForThisMonth = (balance + deposit) * rate; // if no interest 1st month: balance * rate
            balance = balance + deposit + interestForThisMonth;
            interestForThisYear += interestForThisMonth;
        }
        printReport(i, balance, interestForThisYear);
    }
    cout << endl;

    return balance;
}

/**
 * Checks if user presses a key
 *
 * @return the first key pressed
 * @return 0
 */
char CheckChar() {
    if (_kbhit()) {
        return _getch(); // first key pressed
    }
    return 0;
}

int main()
{
    string dataEntries[] = { "Initial Investment Amount: ", "Monthly Deposit: ", "Annual Interest: ", "Number of Years: " };
    const unsigned int NUM_ENTRIES = 4; //data entries array length
    Banking userEntries; //object to store user's data entries
    string reportType;// "with" or "without" additional monthly deposits;
    char ch = '\0'; // user's keypressed for menu
    double endingBalance;

    displayEntries(dataEntries, NUM_ENTRIES);

    userEntries = inputValues(userEntries);
    cout << "Press any key to continue ...";
     
    while (!ch) {
         ch = CheckChar(); // checks if user presses a key
         Sleep(1); // pauses program millisecond 
     }
        
    cout << "\n\n";
    reportType = "Without";
    endingBalance = calculateBalance(userEntries, reportType);
    cout << "Ending Balance: " << "$" << endingBalance << endl;

    reportType = "With";
    endingBalance = calculateBalance(userEntries, reportType);
    cout << "Ending Balance: " << "$" << endingBalance << endl;

    return 0;
}
