// Graphic Design Survey
// Weeks 1-4 by London Haynes.
// Week 06 changes by Youssef Safeh:
//   1. Fixed the 3 menu bugs from Issue #1.
//   2. Moved the code into functions.
//   3. Invalid input now asks again instead of ending the program.
//   4. Added console colors, a DesignerLevel enum, and a weekly flyer array.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>   // needed for SetConsoleTextAttribute (console colors)

using namespace std;

// Designer skill level, picked from the number of flyers and the price
enum DesignerLevel { BEGINNER, INTERMEDIATE, PRO };

// Named constants
const int WEEKS_IN_MONTH = 4;          // size of the weekly flyer array
const int MAX_FLYERS_PER_WEEK = 100;
const double MAX_PRICE = 1000.00;

const double MONTHLY_INCOME_GOAL = 250.00;   // goal is $250 a month
const int MAX_FLYERS_FOR_GOAL = 20;          // using 20 flyers or fewer

const int PRO_MIN_FLYERS = 20;
const double PRO_MIN_PRICE = 25.00;
const int INTERMEDIATE_MIN_FLYERS = 8;
const double INTERMEDIATE_MIN_PRICE = 15.00;

const int MENU_QUIT = 4;
const int LABEL_WIDTH = 30;

// Windows console color codes
const int NORMAL_COLOR = 7;     // light gray
const int TITLE_COLOR = 11;     // light aqua
const int MENU_COLOR = 14;      // yellow
const int GOOD_COLOR = 10;      // light green
const int ERROR_TEXT_COLOR = 12;  // light red

// Function prototypes
void setConsoleColor(int colorCode);
void displayBanner();
string getTextInput(string prompt);
double getPriceInput(string prompt);
void getWeeklyFlyerCounts(int weeklyFlyers[], int numWeeks);
int getMenuChoice();
bool isValidText(string text);
bool isValidWholeNumber(int number, int minValue, int maxValue);
bool isValidPrice(double price);
void showError(string message);
int calculateTotalFlyers(const int weeklyFlyers[], int numWeeks);
double calculateIncome(int flyers, double pricePerFlyer);
string getSalesStatus(int totalFlyers, double pricePerFlyer);
string getGoalStatus(double monthlyIncome, int totalFlyers);
DesignerLevel recommendLevel(int totalFlyers, double pricePerFlyer);
string levelToString(DesignerLevel level);
void displayRecommendation(DesignerLevel level);
void displayMenu();
void displayReport(string flyerType, string favoriteColor, double pricePerFlyer,
    const int weeklyFlyers[], int numWeeks);
void saveReport(string flyerType, string favoriteColor, double pricePerFlyer,
    const int weeklyFlyers[], int numWeeks);

int main()
{
    string flyerType;
    string favoriteColor;
    double pricePerFlyer = 0.0;
    int weeklyFlyers[WEEKS_IN_MONTH] = { 0 };   // flyers made each week, starts at 0
    int menuChoice = 0;

    cout << fixed << setprecision(2);

    displayBanner();

    // Collect input (each function keeps asking until the input is valid)
    flyerType = getTextInput("What type of flyers do you create? ");
    favoriteColor = getTextInput("What is your favorite design color? ");
    pricePerFlyer = getPriceInput("How much do you charge per flyer? Enter the price without a $: ");
    getWeeklyFlyerCounts(weeklyFlyers, WEEKS_IN_MONTH);

    // Show the menu at least once and repeat until the user quits
    do
    {
        displayMenu();
        menuChoice = getMenuChoice();

        switch (menuChoice)
        {
        case 1:
            displayReport(flyerType, favoriteColor, pricePerFlyer, weeklyFlyers, WEEKS_IN_MONTH);
            break;

        case 2:
            displayRecommendation(recommendLevel(
                calculateTotalFlyers(weeklyFlyers, WEEKS_IN_MONTH), pricePerFlyer));
            break;

        case 3:
            saveReport(flyerType, favoriteColor, pricePerFlyer, weeklyFlyers, WEEKS_IN_MONTH);
            break;

        case 4:
            cout << "Thanks for using the survey!" << endl;
            break;
        }
    } while (menuChoice != MENU_QUIT);

    setConsoleColor(NORMAL_COLOR);
    return 0;
}

// Changes the color of the text printed after this call
void setConsoleColor(int colorCode)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}

// Prints the welcome banner
void displayBanner()
{
    setConsoleColor(TITLE_COLOR);
    cout << "--------------------------------------------" << endl;
    cout << "Welcome to the Graphic Design Survey!" << endl;
    cout << "--------------------------------------------" << endl;
    setConsoleColor(NORMAL_COLOR);
}

// Reads a full line of text (spaces allowed) until it is not empty
string getTextInput(string prompt)
{
    string text;

    cout << prompt;
    getline(cin, text);

    while (!isValidText(text))
    {
        showError("Please enter at least one character.");
        cout << prompt;
        getline(cin, text);
    }

    return text;
}

// Reads a price until it is a number from 0 to MAX_PRICE
double getPriceInput(string prompt)
{
    double price = 0.0;

    cout << prompt;
    cin >> price;

    while (!isValidPrice(price))
    {
        cin.clear();               // clear the fail state
        cin.ignore(10000, '\n');   // remove the bad input
        showError("Enter a price from 0 to 1000 without the $.");
        cout << prompt;
        cin >> price;
    }

    cin.ignore(10000, '\n');   // remove the newline left after the number
    return price;
}

// Fills the array with the number of flyers made each week
void getWeeklyFlyerCounts(int weeklyFlyers[], int numWeeks)
{
    int count = 0;

    cout << "Enter how many flyers you created each week this month." << endl;

    for (int week = 0; week < numWeeks; week++)
    {
        cout << "Week " << (week + 1) << ": ";
        cin >> count;

        // Keep asking until the count is a whole number from 0 to 100
        while (!isValidWholeNumber(count, 0, MAX_FLYERS_PER_WEEK))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            showError("Enter a whole number from 0 to 100.");
            cout << "Week " << (week + 1) << ": ";
            cin >> count;
        }
        cin.ignore(10000, '\n');

        weeklyFlyers[week] = count;   // store the valid count in the array
    }
}

// Reads a menu choice until it is a whole number from 1 to 4
int getMenuChoice()
{
    int choice = 0;

    cout << "Enter your choice: ";
    cin >> choice;

    while (!isValidWholeNumber(choice, 1, MENU_QUIT))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        showError("Enter a whole number from 1 to 4.");
        cout << "Enter your choice: ";
        cin >> choice;
    }

    cin.ignore(10000, '\n');
    return choice;
}

// Text is valid if it is not empty
bool isValidText(string text)
{
    return text.length() > 0;
}

// A whole number is valid if cin read it, it is in range, and nothing else was typed
bool isValidWholeNumber(int number, int minValue, int maxValue)
{
    if (!cin)
    {
        return false;
    }

    return number >= minValue && number <= maxValue && cin.peek() == '\n';
}

// A price is valid if cin read it, it is from 0 to MAX_PRICE, and nothing else was typed
bool isValidPrice(double price)
{
    if (!cin)
    {
        return false;
    }

    return price >= 0.0 && price <= MAX_PRICE && cin.peek() == '\n';
}

// Prints an error message in red
void showError(string message)
{
    setConsoleColor(ERROR_TEXT_COLOR);
    cout << "Invalid input. " << message << endl;
    setConsoleColor(NORMAL_COLOR);
}

// Adds up all the weekly counts in the array
int calculateTotalFlyers(const int weeklyFlyers[], int numWeeks)
{
    int total = 0;

    for (int week = 0; week < numWeeks; week++)
    {
        total = total + weeklyFlyers[week];
    }

    return total;
}

// Income for a number of flyers
double calculateIncome(int flyers, double pricePerFlyer)
{
    return flyers * pricePerFlyer;
}

// Paid work requires at least one flyer and a price above zero
string getSalesStatus(int totalFlyers, double pricePerFlyer)
{
    if (totalFlyers > 0 && pricePerFlyer > 0.0)
    {
        return "Paid flyer work";
    }
    else
    {
        return "No paid flyer work";
    }
}

// The goal is met when income is at least $250 and flyers are 20 or fewer
string getGoalStatus(double monthlyIncome, int totalFlyers)
{
    if (monthlyIncome >= MONTHLY_INCOME_GOAL && totalFlyers <= MAX_FLYERS_FOR_GOAL)
    {
        return "Goal met";
    }
    else
    {
        return "Goal not met";
    }
}

// Picks a designer level from the monthly flyers and the price
DesignerLevel recommendLevel(int totalFlyers, double pricePerFlyer)
{
    DesignerLevel level = BEGINNER;

    if (totalFlyers >= PRO_MIN_FLYERS && pricePerFlyer >= PRO_MIN_PRICE)
    {
        level = PRO;
    }
    else if (totalFlyers >= INTERMEDIATE_MIN_FLYERS || pricePerFlyer >= INTERMEDIATE_MIN_PRICE)
    {
        level = INTERMEDIATE;
    }
    else
    {
        level = BEGINNER;
    }

    return level;
}

// Converts the enum value to text
string levelToString(DesignerLevel level)
{
    switch (level)
    {
    case BEGINNER:
        return "Beginner";
    case INTERMEDIATE:
        return "Intermediate";
    case PRO:
        return "Pro";
    default:
        return "Unknown";
    }
}

// Prints the recommended level in a different color for each level
void displayRecommendation(DesignerLevel level)
{
    switch (level)
    {
    case BEGINNER:
        setConsoleColor(MENU_COLOR);
        cout << "Recommended level: Beginner" << endl;
        cout << "To reach Intermediate, create " << INTERMEDIATE_MIN_FLYERS
            << " flyers a month or charge $" << INTERMEDIATE_MIN_PRICE << " or more." << endl;
        break;

    case INTERMEDIATE:
        setConsoleColor(TITLE_COLOR);
        cout << "Recommended level: Intermediate" << endl;
        cout << "To reach Pro, create " << PRO_MIN_FLYERS
            << " flyers a month and charge $" << PRO_MIN_PRICE << " or more." << endl;
        break;

    case PRO:
        setConsoleColor(GOOD_COLOR);
        cout << "Recommended level: Pro" << endl;
        break;
    }

    setConsoleColor(NORMAL_COLOR);
}

// Prints the menu
void displayMenu()
{
    setConsoleColor(MENU_COLOR);
    cout << endl;
    cout << "Choose an option:" << endl;
    cout << "1. View report" << endl;
    cout << "2. Recommend designer level" << endl;
    cout << "3. Save report to report.txt" << endl;
    cout << "4. Quit" << endl;
    setConsoleColor(NORMAL_COLOR);
}

// Prints the summary table on the screen
void displayReport(string flyerType, string favoriteColor, double pricePerFlyer,
    const int weeklyFlyers[], int numWeeks)
{
    int totalFlyers = calculateTotalFlyers(weeklyFlyers, numWeeks);
    double monthlyIncome = calculateIncome(totalFlyers, pricePerFlyer);

    setConsoleColor(TITLE_COLOR);
    cout << endl;
    cout << "Graphic Design Summary" << endl;
    cout << "--------------------------------------------" << endl;
    setConsoleColor(NORMAL_COLOR);

    cout << left << setw(LABEL_WIDTH) << "Flyer type:" << flyerType << endl;
    cout << setw(LABEL_WIDTH) << "Favorite color:" << favoriteColor << endl;
    cout << setw(LABEL_WIDTH) << "Price per flyer ($):" << pricePerFlyer << endl;
    cout << endl;

    // One row for each week in the array
    cout << left << setw(12) << "Week" << right << setw(10) << "Flyers" << setw(14) << "Income ($)" << endl;
    for (int week = 0; week < numWeeks; week++)
    {
        cout << "Week " << left << setw(7) << (week + 1)
            << right << setw(10) << weeklyFlyers[week]
            << setw(14) << calculateIncome(weeklyFlyers[week], pricePerFlyer) << endl;
    }
    cout << endl;

    cout << left << setw(LABEL_WIDTH) << "Flyers per month:" << totalFlyers << endl;
    cout << setw(LABEL_WIDTH) << "Monthly income ($):" << monthlyIncome << endl;
    cout << setw(LABEL_WIDTH) << "Quarterly income ($):" << monthlyIncome * 3 << endl;
    cout << setw(LABEL_WIDTH) << "Yearly income ($):" << monthlyIncome * 12 << endl;
    cout << setw(LABEL_WIDTH) << "Sales status:" << getSalesStatus(totalFlyers, pricePerFlyer) << endl;
    cout << setw(LABEL_WIDTH) << "Monthly goal:" << getGoalStatus(monthlyIncome, totalFlyers) << endl;
    cout << setw(LABEL_WIDTH) << "Designer level:"
        << levelToString(recommendLevel(totalFlyers, pricePerFlyer)) << endl;
    cout << "--------------------------------------------" << endl;
}

// Saves the same summary table to report.txt
void saveReport(string flyerType, string favoriteColor, double pricePerFlyer,
    const int weeklyFlyers[], int numWeeks)
{
    int totalFlyers = calculateTotalFlyers(weeklyFlyers, numWeeks);
    double monthlyIncome = calculateIncome(totalFlyers, pricePerFlyer);
    ofstream outFile;

    outFile.open("report.txt");

    if (!outFile)
    {
        showError("Could not open report.txt.");
        return;
    }

    outFile << fixed << setprecision(2);
    outFile << "Graphic Design Summary" << endl;
    outFile << "--------------------------------------------" << endl;
    outFile << left << setw(LABEL_WIDTH) << "Flyer type:" << flyerType << endl;
    outFile << setw(LABEL_WIDTH) << "Favorite color:" << favoriteColor << endl;
    outFile << setw(LABEL_WIDTH) << "Price per flyer ($):" << pricePerFlyer << endl;
    outFile << endl;

    outFile << left << setw(12) << "Week" << right << setw(10) << "Flyers" << setw(14) << "Income ($)" << endl;
    for (int week = 0; week < numWeeks; week++)
    {
        outFile << "Week " << left << setw(7) << (week + 1)
            << right << setw(10) << weeklyFlyers[week]
            << setw(14) << calculateIncome(weeklyFlyers[week], pricePerFlyer) << endl;
    }
    outFile << endl;

    outFile << left << setw(LABEL_WIDTH) << "Flyers per month:" << totalFlyers << endl;
    outFile << setw(LABEL_WIDTH) << "Monthly income ($):" << monthlyIncome << endl;
    outFile << setw(LABEL_WIDTH) << "Quarterly income ($):" << monthlyIncome * 3 << endl;
    outFile << setw(LABEL_WIDTH) << "Yearly income ($):" << monthlyIncome * 12 << endl;
    outFile << setw(LABEL_WIDTH) << "Sales status:" << getSalesStatus(totalFlyers, pricePerFlyer) << endl;
    outFile << setw(LABEL_WIDTH) << "Monthly goal:" << getGoalStatus(monthlyIncome, totalFlyers) << endl;
    outFile << setw(LABEL_WIDTH) << "Designer level:"
        << levelToString(recommendLevel(totalFlyers, pricePerFlyer)) << endl;
    outFile << "--------------------------------------------" << endl;

    outFile.close();

    setConsoleColor(GOOD_COLOR);
    cout << "Saved this summary to report.txt." << endl;
    setConsoleColor(NORMAL_COLOR);
}
