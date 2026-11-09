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
    int menuChoice = 0;
    double monthlyIncome = 0.0;
    double projectedIncome = 0.0;
    string reportPeriod;
    string salesStatus;
    string goalStatus;

    cout << "--------------------------------------------" << endl;
    cout << "Welcome to the Graphic Design Survey!" << endl;
    cout << "--------------------------------------------" << endl;

    // Read full answers so the user can enter phrases with spaces.
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

    // Check that the flyer count is a nonnegative whole number.
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

    monthlyIncome = flyersPerMonth * pricePerFlyer;

    // Paid work requires at least one flyer and a price above zero.
    if (flyersPerMonth > 0 && pricePerFlyer > 0.0)
    {
        salesStatus = "Paid flyer work";
    }
    else
    {
        salesStatus = "No paid flyer work";
    }

    // Check the example goal of earning $250 with 20 flyers or fewer.
    if (monthlyIncome >= 250.0 && flyersPerMonth <= 20)
    {
        goalStatus = "Goal met";
    }
    else
    {
        goalStatus = "Goal not met";
    }

    // Show the menu at least once and repeat until the user quits.
    do
    {
        cout << endl;
        cout << "Choose a report period:" << endl;
        cout << "1. Monthly" << endl;
        cout << "2. Quarterly" << endl;
        cout << "3. Yearly" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> menuChoice;

        // Clear invalid input and ask for another menu choice.
        while (!cin || menuChoice < 1 || menuChoice > 4 ||
            (!cin.eof() && cin.peek() != '\n'))
        {
            if (cin.eof())
            {
                return 0;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a whole number from 1 to 4: ";
            cin >> menuChoice;
        }

        switch (menuChoice)
        {
        case 1:
            reportPeriod = "Monthly";
            projectedIncome = monthlyIncome;
            break;

        case 2:
            reportPeriod = "Quarterly";
            projectedIncome = 0.0;

            // A quarter has three months, so add monthly income three times.
            for (int month = 1; month <= 3; month++)
            {
                projectedIncome = projectedIncome + monthlyIncome;
            }
            break;

        case 3:
            cout << "Thanks for using the survey!" << endl;
            continue;
            reportPeriod = "Yearly";
            projectedIncome = monthlyIncome * 12;
            break;

        case 4:
        }

        // Display the summary with aligned labels and two decimal places.
        cout << fixed << setprecision(2);
        cout << endl;
        cout << "Graphic Design Summary" << endl;
        cout << "--------------------------------------------" << endl;
        cout << left << setw(30) << "Flyer type:" << flyerType << endl;
        cout << setw(30) << "Favorite color:" << favoriteColor << endl;
        cout << setw(30) << "Flyers per month:" << flyersPerMonth << endl;
        cout << setw(30) << "Price per flyer ($):" << pricePerFlyer << endl;
        cout << setw(30) << "Monthly income ($):" << monthlyIncome << endl;
        cout << setw(30) << "Report period:" << reportPeriod << endl;
        cout << setw(30) << "Projected income ($):" << projectedIncome << endl;
        cout << setw(30) << "Sales status:" << salesStatus << endl;
        cout << setw(30) << "Monthly goal:" << goalStatus << endl;
        cout << "--------------------------------------------" << endl;

        // Save the latest summary to report.txt.
        ofstream outFile;
        outFile.open("report.txt");

        if (!outFile)
        {
            cout << "Could not open report.txt." << endl;
            return 1;
        }

        outFile << fixed << setprecision(2);
        outFile << "Graphic Design Summary" << endl;
        outFile << "--------------------------------------------" << endl;
        outFile << left << setw(30) << "Flyer type:" << flyerType << endl;
        outFile << setw(30) << "Favorite color:" << favoriteColor << endl;
        outFile << setw(30) << "Flyers per month:" << flyersPerMonth << endl;
        outFile << setw(30) << "Price per flyer ($):" << pricePerFlyer << endl;
        outFile << setw(30) << "Monthly income ($):" << monthlyIncome << endl;
        outFile << setw(30) << "Report period:" << reportPeriod << endl;
        outFile << setw(30) << "Projected income ($):" << projectedIncome << endl;
        outFile << setw(30) << "Sales status:" << salesStatus << endl;
        outFile << setw(30) << "Monthly goal:" << goalStatus << endl;
        outFile << "--------------------------------------------" << endl;

        cout << "Saved this summary to report.txt." << endl;
    } while (menuChoice != 4);

    return 0;
}