#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    string flyerType;
    string favoriteColor;
    int flyersPerMonth = 0;
    double pricePerFlyer = 0.0;
    double monthlyIncome = 0.0;

    cout << "--------------------------------------------" << endl;
    cout << "Welcome to the Graphic Design Survey!" << endl;
    cout << "--------------------------------------------" << endl;

    // Read the full answers so they can include spaces.
    cout << "What type of flyers do you create? ";
    getline(cin, flyerType);

    if (!cin || flyerType.empty())
    {
        cout << "Please enter a flyer type." << endl;
        return 1;
    }

    cout << "What is your favorite design color? ";
    getline(cin, favoriteColor);

    if (!cin || favoriteColor.empty())
    {
        cout << "Please enter a color." << endl;
        return 1;
    }

    // Check the number and make sure the answer ends there.
    cout << "How many flyers do you create each month? ";
    cin >> flyersPerMonth;

    if (!cin || flyersPerMonth < 0 || cin.peek() != '\n')
    {
        cout << "Enter a whole number of 0 or more, then press Enter." << endl;
        return 1;
    }

    cout << "How much do you charge per flyer? Enter the price without a $: ";
    cin >> pricePerFlyer;

    if (!cin || pricePerFlyer < 0 || (!cin.eof() && cin.peek() != '\n'))
    {
        cout << "Enter a price of 0 or more, then press Enter." << endl;
        return 1;
    }

    // Calculate monthly income before expenses.
    monthlyIncome = flyersPerMonth * pricePerFlyer;

    // Print the summary with lined-up labels and two decimal places.
    cout << fixed << setprecision(2);
    cout << endl;
    cout << "Graphic Design Summary" << endl;
    cout << "--------------------------------------------" << endl;
    cout << left << setw(30) << "Flyer type:" << flyerType << endl;
    cout << setw(30) << "Favorite color:" << favoriteColor << endl;
    cout << setw(30) << "Flyers per month:" << flyersPerMonth << endl;
    cout << setw(30) << "Price per flyer ($):" << pricePerFlyer << endl;
    cout << setw(30) << "Monthly income ($):" << monthlyIncome << endl;
    cout << "--------------------------------------------" << endl;

    // Save the same formatted summary to report.txt.
    ofstream outFile;
    outFile.open("report.txt");

    outFile << fixed << setprecision(2);
    outFile << "Graphic Design Summary" << endl;
    outFile << "--------------------------------------------" << endl;
    outFile << left << setw(30) << "Flyer type:" << flyerType << endl;
    outFile << setw(30) << "Favorite color:" << favoriteColor << endl;
    outFile << setw(30) << "Flyers per month:" << flyersPerMonth << endl;
    outFile << setw(30) << "Price per flyer ($):" << pricePerFlyer << endl;
    outFile << setw(30) << "Monthly income ($):" << monthlyIncome << endl;
    outFile << "--------------------------------------------" << endl;

    return 0;
}