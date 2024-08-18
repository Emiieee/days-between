//Inefficient but I made this program to demonstrate to a very beginner programmer
//a way they could solve the issue they were having. This is a much better way to do this
//It does not account for leap years, so that would need to be added.
//It is a simple program for finding days between two given dates
//Because the user is not doing any input, input validation can be ignored
//First date should be in the past compared to the second date
#include <iostream>

//using namespace
using std::cout;
using std::cin;
using std::array;
using std::string;
using std::tolower;

//Function prototypes
int inputValidation_Day(int day);
int inputValidation_Year(int year, int minimumYear, int maximumYear);
string inputValidation_Month(string month, string monthName[], int numberOfMonths);
string lowerCase(string stringEntered);
int checkFail(int integerEntered);
int getMonth(int month, string monthNameEntered, string monthName[], int numberOfMonths);
int compare_SameYear(int firstDate[], int secondDate[], int daysMonth[]);
int compare_DifferentYear(int firstDate[], int secondDate[], int daysMonth[], int numberOfMonths);

int main()
{
	//------------------------------------- Variables Initialization
	const int numberOfMonths = 12;	//This constant is not recommend, but I used it to avoid pointers for beginners reading
	int day = 0,
		month = 0,
		year = 0;
	int totalDays = 0;
	int firstDate[] = { day, month, year },
		secondDate[] = { day, month, year },
		daysMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	//Days in a month
	int minimumYear = 1900;	//To be changed by the programmer
	int maximumYear = 2100; //To be changed by the programmer
	string monthName[] = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };
	string monthNameEntered;

	//-------------------------------------	prompt: first date
	//The prompts could be in their own functions, but I'm leaving them in main to make it easier to understand
	//get the input - this should be converted in your program to a different function.
	//the user should not have any access to the input.
	//prompt for day
	cout << "Enter the first day: ";
	cin >> day;		//Store the variable in day
	day = inputValidation_Day(day);	//Input validation, reassign day to returned value
	//prompt for month
	cout << "Enter the first month: ";
	cin >> monthNameEntered;	//Store the variable in monthNameEntered
	monthNameEntered = inputValidation_Month(monthNameEntered, monthName, numberOfMonths);	//Input validation, reassign to returned value
	//prompt for year
	cout << "Enter the first year: ";
	cin >> year;	//store the variable in year
	year = inputValidation_Year(year, minimumYear, maximumYear);	//input validation, reassign year to returned value

	//------------------------------------- get the month name's index
	month = getMonth(month, monthNameEntered, monthName, numberOfMonths);

	//-------------------------------------	reassign the values in firstDate array to those given
	//There is an easier way to do this, but this is for better understanding for nonprogrammers
	//This could be done in its own function but it is left here for said understanding
	firstDate[0] = day;
	firstDate[1] = month;	//remember that his is -1 due to indices starting at 0
	firstDate[2] = year;

	//-------------------------------------	prompt: second date
	//Basically a repeat of the first date prompt
	//prompt for day
	cout << "Enter the second day: ";
	cin >> day;		//Store the variable in day
	day = inputValidation_Day(day);	//Input validation, reassign day to returned value
	//prompt for month
	cout << "Enter the second month: ";
	cin >> monthNameEntered;	//Store the variable in monthNameEntered
	monthNameEntered = inputValidation_Month(monthNameEntered, monthName, numberOfMonths);	//Input validation, reassign to returned value
	//prompt for year
	cout << "Enter the second year: ";
	cin >> year;	//store the variable in year
	year = inputValidation_Year(year, minimumYear, maximumYear);	//input validation, reassign year to returned value

	//------------------------------------- get the month name's index.. again.
	month = getMonth(month, monthNameEntered, monthName, numberOfMonths);

	//-------------------------------------	reassign the values in firstDate array to those given
	//There is an easier way to do this, but this is for better understanding for nonprogrammers
	//This could be done in its own function but it is left here for said understanding
	secondDate[0] = day;
	secondDate[1] = month;	//This will show as -1 due to indices starting at 0
	secondDate[2] = year;

	//COMPARISON OF BOTH ARRAYS
	if (secondDate[2] == firstDate[2])
	{
		//in the case where both years are the same, then only the month and day are needed to compare
		totalDays = compare_SameYear(firstDate, secondDate, daysMonth);
	}
	else
	{
		totalDays = compare_DifferentYear(firstDate, secondDate, daysMonth, numberOfMonths);
	};


	cout << "DAYS: " << totalDays << std::endl;
	/*
	//cout test
	std::copy(std::begin(firstDate), std::end(firstDate), std::ostream_iterator<int>(std::cout, " "));
	std::copy(std::begin(secondDate), std::end(secondDate), std::ostream_iterator<int>(std::cout, " "));
	*/
};


//Function for input validation - day
int inputValidation_Day(int day)
{
	while (!cin || (day < 0 || day > 31))
	{
		if (cin.fail())
		{
			//Check for cin failure and get new input
			day = checkFail(day);
		}
		else
		{
			//number entered was out of range, get new input
			cout << "Day entered is out of range. Enter a new day between 0 and 31: ";
			cin >> day;
		};
	};
	return day;
};

//Function for input validation - year
int inputValidation_Year(int year, int minimumYear, int maximumYear)
{
	while (!cin || (year < minimumYear || year > maximumYear))
	{
		if (cin.fail())
		{
			//Check for cin failure and get new input
			year = checkFail(year);
		}
		else
		{
			//number entered was out of range, get new input
			cout << "Year out of range. Reenter a year between " << minimumYear << " and " << maximumYear << ": ";
			cin >> year;
		};
	};
	return year;
};

//Function for input validation - month
string inputValidation_Month(string month, string monthName[], int numberOfMonths)
{
	//Temp variables
	bool monthExists = false;
	//Validation
	do
	{
		//Lower case it
		month = lowerCase(month);

		//Compare the month entered to the months available
		for (int i = 0; i < numberOfMonths; i++)
		{
			if (month == monthName[i])
			{
				//set flag to true and exit loop
				monthExists = true;
				break;
			};
		};
		//if the boolean flag is still false, get new input 
		if (!monthExists)
		{
			//string entered does not exist in the array, get new input
			cout << month << " does not exist. Check your spelling and reenter the month: ";
			cin >> month;
		};
	} while (!monthExists);
	return month;
};

//Function to lowercase each month
string lowerCase(string stringEntered)
{
	//force lower case by accessing each index of the string
	for (int i = 0; i < stringEntered.length(); i++)
	{
		stringEntered[i] = tolower(stringEntered[i]);
	};
	return stringEntered;
};

//Function to check for cin failure
int checkFail(int integerEntered)
{
	//Purge
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//Prompt for new input
	cout << "ERROR: Ensure the variable entered is a whole number: ";
	cin >> integerEntered;
	//return new value
	return integerEntered;
};

//Function for finding the index number of the month entered
int getMonth(int month, string monthNameEntered, string monthName[], int numberOfMonths)
{
	//This couldve been found by using and editing a reference variable during the input valiation
	//but I am choosing to do it here separately in case the learner does not know what a reference is or
	//how it can effect a program

	//temp variable
	int monthIndex = month;

	//Compare month name entered to the name in the array
	//use numberOfMonths as a comparison for the counter
	for (int i = 0; i < numberOfMonths; i++)
	{
		if (monthNameEntered == monthName[i])
		{
			//assign the index to month and break out of the loop
			monthIndex = i;
			break;
		};
	};
	//Return the index found as month to caller
	return monthIndex;
};



//These are the functions for comparing the dates. They could be combined, and that is probably preferable, but I chose to keep them separate
//so that they may be easier to follow
int compare_SameYear(int firstDate[], int secondDate[], int daysMonth[])
{
	//Temp variables
	int days = 0;
	int firstMonth = firstDate[1];		//the initial month
	int secondMonth = secondDate[1];	//the final month
	int tempStartDays = 0;
	int tempEndDays = 0;

	//Test to see if the months are the same
	if (secondDate[1] != firstDate[1])
	{
		//This for loop adds the days from the months between, but not from the same months entered
		//so, if u entered 20 march to 17 august, the total will be 122 for the months inbetween, not 150
		//step through loop adding the total of days between each month to days, excluding the first and last days
		//Add +1 to first month because the first month's days are not calculated here
		for (int i = firstMonth + 1; i < secondMonth; i++)
		{
			days = days + daysMonth[i];	//grab the number of days from the daysMonth array
		};
		//This next section can be done on one line, but I chose to separate it to make it easier to understand
		//Get the amount of days from the starting month
		//operation is like number of days in the month subtracted by the number of days used
		tempStartDays = firstDate[0];	//store the number of days used from the first month
		tempEndDays = daysMonth[firstDate[1]];	//using the month stored in the firstDate array to indicate the index needed in the daysMonth array
		days = days + (tempEndDays - tempStartDays);	//calculate the difference between the total month's amount of days and the days used

		//Get the amount of days from the ending month, this is similar to the steps before
		tempStartDays = secondDate[0];
		days = days + tempStartDays;	//just add the days since we're starting the operation is 0 + n now
	}
	else
	{
		//just subtract the days from each other
		days = secondDate[0] - firstDate[0];
	};

	//Return the total days
	return days;
};

int compare_DifferentYear(int firstDate[], int secondDate[], int daysMonth[], int numberofMonths)
{
	//Temp variables
	int days = 0;
	int firstDate_Month = firstDate[1];		//month in the first date
	int secondDate_Month = secondDate[1];	//month in the second date
	int tempDays = 0;
	int yearDifference = secondDate[2] - firstDate[2];	//difference between the first and second year.

	//find the difference between the first date and the end of the year
	//for loop to find days outside of starting month until the end of the year
	for (int i = firstDate_Month + 1; i < numberofMonths; i++)
	{
		days = days + daysMonth[i];
	};

	tempDays = (daysMonth[firstDate[1]] - firstDate[0]);
	days = days + tempDays;	//+1 if you want to include the end date

	//find the days between start of year and second date
	for (int i = 0; i < secondDate_Month; i++)
	{
		days = days + daysMonth[i];
	};

	//Add the days used in the month for ending month
	days = days + secondDate[0];

	cout << "year difference: " << yearDifference << std::endl;

	//Check to see if the difference between the years is greater than one.
	if (yearDifference > 1)
	{
		//if so, multiply it by 365 and add it to the days
		//subtract 1 from year difference so than an extra 365 is not added
		days = days + ((yearDifference - 1) * 365);
	};

	//Return the total days
	return days;
};