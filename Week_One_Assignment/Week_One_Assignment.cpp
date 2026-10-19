#include <iostream>
#include <string>

using namespace std;

int main()
{
	//Store the user's favorite design information: 
	string flyerType; 
	string favoriteColor;
	//Store the number of flyers created each month:
	int flyersPerMonth;
	//Calculate yearly flyer production : 
	int flyersPerYear;

	//Program Starts:

	cout<<"Welcome to the Graphic Design Survey!"<<endl;

	//Get info from the user:
	cout << "What type of flyers do you create the most often? ";
	cin >> flyerType;

	cout << "What is your favorite design color? ";
	cin >> favoriteColor;

	cout << "How many flyers do you create each month? ";
	cin >> flyersPerMonth;

	//Preforming the calculation for yearly flyer production:
	flyersPerYear = flyersPerMonth * 12;

	cout << endl;
	cout << "Summary" << endl;
	cout << "-------" << endl;
	cout << "You like creating " << flyerType << " flyers." << endl;
	cout << "Your favorite color is " << favoriteColor << "." << endl;
	cout << "You create about " << flyersPerMonth << " flyers each month." << endl;
	cout << "That means you could create " << flyersPerYear << " flyers in a year." << endl;

}