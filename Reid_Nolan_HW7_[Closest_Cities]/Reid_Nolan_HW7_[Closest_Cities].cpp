//Reid_Nolan_HW7_[Closest_Cities]
//Reid_Nolan_HW7_[Closest_Cities].cpp : Defines the entry point for the console application.
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/21/2017																				//
//Closest Cities Source File																	//
//C++ program for determining closest cities to user selection from a list.						//
//**********************************************************************************************//

#include "stdafx.h"
#include "City.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//display messages to user
void displayProgramHeader();
void displayProgramSubHeader(string mDATA_FILE);
void displayMainMenu(const string mDATA_FILE);
void displayNearbyCitySearchMenu();
void displayNoRecordsFound();
void displayMatchCount(const int matchCount);

//record removal
void deleteConfirm(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS, const string mDATA_FILE);
void vecDelete(vector<vector<string>> &vecToDelete);
void vecDelete(vector<string> &vecToDelete);

//input prompts
string makeASelection();
string cityNamePrompt();
string cityNumPrompt();
string areYouReallySurePrompt();

//get data from system or user
string getConsoleInputString(const string prompt);

//display cites from search criteria
void getCities(vector<vector<string>> &mainList, const int mCITIES_TO_DISPLAY, const int mNUM_COLS, string choice);
void getClosestCities(const int mCITIES_TO_DISPLAY, vector<int> &map, vector<int> &cityNumberColumn, vector<string> &cityNameColumn, vector<string> &countryColumn, vector<double> &latitudeColumn, vector<double> &longitudeColumn, vector<double> &distanceColumn);
void getFarthestCities(const int cityIndex, const int mCITIES_TO_DISPLAY, vector<int> &map, vector<int> &cityNumberColumn, vector<string> &cityNameColumn, vector<string> &countryColumn, vector<double> &latitudeColumn, vector<double> &longitudeColumn, vector<double> &distanceColumn);

int main()
{
	//create 2-d vector for rows and columns
	vector<vector<string>> mainList;

	//declare and initialize local variables
	const string mDATA_FILE = "worldcities.csv";
	int programRunCount = 0;

	//display program header
	displayProgramHeader();
	//display current sub-header
	displayProgramSubHeader(mDATA_FILE);

	//loop until user opts to quit
	while (true)
	{		
		//initialize new class object
		City city;

		//declare and initialize local variables
		const int mNUM_COLS = 5;
		const int mLAST_COL = 4;
		const int mFIRST_ROW = 0;
		const int mCITIES_TO_DISPLAY = 5;
		int cityCount = 0;
		int matchCount = 0;
		fstream inFile;

		//display main menu
		displayMainMenu(mDATA_FILE);

		//loop until valid input is entered
		bool mainMenuChoiceGood = false;
		while (!mainMenuChoiceGood)		//loop for main menu options
		{
			//create vector for valid input values
			vector<string> validMainInput{ "0", "1", "2", "3", "4" };

			//declare and initialize local variables
			string toMatch = "";

			//set console input to local variable
			string menuChoice = getConsoleInputString(makeASelection());

			//validate input
			if (find(begin(validMainInput), end(validMainInput), menuChoice) != end(validMainInput))
			{
				//set boolean to true to exit loop
				mainMenuChoiceGood = true;
			}
			else
			{
				//do nothing
			}

			//Load contacts from...
			if (menuChoice == "1")
			{
				//if records already exist in memory
				if (mainList.size() > 0)
				{
					cout << endl << "Records have already been loaded into memory." << endl << endl;
				}
				//if no records already exist in memory
				else if (mainList.size() == 0)
				{
					//load records from file
					City::loadRecords(city, mainList, mDATA_FILE, inFile, cityCount);
				}
				else
				{
					//do nothing
				}
			}

			//Select a city by name
			else if (menuChoice == "2" && mainList.size() > 0)
			{
				//declare and initialize local variables
				const int mCITY_COLUMN = 1;
				string matchNumber = "";
				string nearbyMenuChoice = "";

				//display records
				City::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);
				City::outputAllRecords(mainList, mNUM_COLS);
				City::displayColumnFooter();

				//loop until valid input is entered
				bool numberGood = false;
				while (!numberGood)
				{
					//set console input to local variable
					toMatch = getConsoleInputString(cityNamePrompt());
					//display selected city match data
					City::displayMatches(mainList, toMatch, mCITY_COLUMN, mNUM_COLS, matchCount, mFIRST_ROW);

					//continue if match found
					if (matchCount > 0)
					{
						numberGood = true;
					}
					else
					{
						//display number of matches
						displayMatchCount(matchCount);
					}
				}

				//display number of matches
				displayMatchCount(matchCount);

				//display sub-menu options options
				displayNearbyCitySearchMenu();

				//loop until valid input is entered
				bool nearbyMenuGood = false;
				while (!nearbyMenuGood)
				{
					//set console input to local variable
					nearbyMenuChoice = getConsoleInputString(makeASelection());

					//validate input is in range
					if (nearbyMenuChoice == "1" || nearbyMenuChoice == "2")
					{
						//set boolean to true to exit loop
						nearbyMenuGood = true;
					}
					else
					{
						//do nothing
					}
				}

				//search for mCITIES_TO_SEARCH closest
				if (nearbyMenuChoice == "1")
				{
					//declare and initialize local variables
					const string choice = "closest";
					//get list of cities
					getCities(mainList, mCITIES_TO_DISPLAY, mNUM_COLS, choice);
				}
				//search for mCITIES_TO_SEARCH farthest
				else if (nearbyMenuChoice == "2")
				{
					//declare and initialize local variables
					const string choice = "farthest";
					//get list of cities
					getCities(mainList, mCITIES_TO_DISPLAY, mNUM_COLS, choice);
				}
				else
				{
					//do nothing
				}
			}

			//Select a city by number
			else if (menuChoice == "3" && mainList.size() > 0)
			{
				//declare and initialize local variables
				const int mNUMBER_COLUMN = 0;
				string nearbyMenuChoice = "";

				//display records
				City::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);
				City::outputAllRecords(mainList, mNUM_COLS);
				City::displayColumnFooter();

				//loop until valid input is entered
				bool numberGood = false;
				while (!numberGood)
				{
					//set console input to local variable
					toMatch = getConsoleInputString(cityNumPrompt());
					City::displayMatches(mainList, toMatch, mNUMBER_COLUMN, mNUM_COLS, matchCount, mFIRST_ROW);

					//continue if match found
					if (matchCount > 0)
					{
						//set boolean to true to exit loop
						numberGood = true;
					}
					else
					{
						//display number of matches
						displayMatchCount(matchCount);
					}
				}

				//display number of matches
				displayMatchCount(matchCount);

				//display sub-menu options options
				displayNearbyCitySearchMenu();				

				//loop until valid input is entered
				bool nearbyMenuGood = false;
				while (!nearbyMenuGood)
				{
					//set console input to local variable
					nearbyMenuChoice = getConsoleInputString(makeASelection());

					//validate input is in range
					if (nearbyMenuChoice == "1" || nearbyMenuChoice == "2")
					{
						//set boolean to true to exit loop
						nearbyMenuGood = true;
					}
					else
					{
						//do nothing
					}
				}

				//search for mCITIES_TO_SEARCH closest
				if (nearbyMenuChoice == "1")
				{
					//declare and initialize local variables
					const string choice = "closest";
					//get list of cities
					getCities(mainList, mCITIES_TO_DISPLAY, mNUM_COLS, choice);
				}
				//search for mCITIES_TO_SEARCH farthest
				else if (nearbyMenuChoice == "2")
				{
					//declare and initialize local variables
					const string choice = "farthest";
					//get list of cities
					getCities(mainList, mCITIES_TO_DISPLAY, mNUM_COLS, choice);
				}
				else
				{
					//do nothing
				}
			}

			//Display all cities
			else if (menuChoice == "4" && mainList.size() > 0)
			{
				//display records
				City::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);
				City::outputAllRecords(mainList, mNUM_COLS);
				City::displayColumnFooter();
				//display number of records output
				cout << endl << "Records displayed: " << (mainList.size() - 1) << endl << endl;
			}

			//DELETE ALL CONTACTS
			else if (menuChoice == "5" && mainList.size() > 0)
			{
				//declare and initialize local variables
				const int mDELETE_ALL = 999;

				//display DELETE_ALL warning message
				cout << endl << "!!!WARNING!!!" << endl;
				cout << "All records will be deleted from memory." << endl << endl;

				//delete matching records after confirmation
				deleteConfirm(mainList, toMatch, mDELETE_ALL, mNUM_COLS, mDATA_FILE);
			}

			//Exit ContactsList
			else if (menuChoice == "0")
			{
				//erase all vector elements from vector
				vecDelete(mainList);
				vecDelete(validMainInput);

				//display exit status message
				City::displayExit();
			}

			//display no records found message if no records are currently in memory(mainList vector)
			else if (mainList.size() == 0)
			{
				//display message for no matching record(s)
				displayNoRecordsFound();
				break;
			}

			else
			{
				//do nothing
			}
			//erase all vector elements from vector
			vecDelete(validMainInput);
		}
		//increment program run count
		programRunCount++;
	}
	return 0;
}

void displayProgramHeader()
{
	//display program header
	cout << "// Reid_Nolan_HW7_[Closest_Cities].cpp" << endl;
}

void displayProgramSubHeader(string mDATA_FILE)
{
	cout << "*** No contact records currently loaded into memory. ***" << endl;
	cout << "*** Please select option 1 to load from " << mDATA_FILE << " before beginning. ***" << endl << endl;
}

void displayMainMenu(const string mDATA_FILE)
{
	//display main menu
	cout << "---------------Main Menu---------------" << endl;
	cout << "1. Load records from " << mDATA_FILE << " into memory." << endl;
	cout << "2. Select a city by name." << endl;
	cout << "3. Select a city by number." << endl;
	cout << "4. Display all cities." << endl;
	cout << "5. !!!DELETE ALL Cities!!!" << endl;
	cout << "0. Exit Closest Cities." << endl;
}

void displayNearbyCitySearchMenu()
{
	//display nearby city search menu
	cout << "-----Nearby City Search-----" << endl;
	cout << "1. Display the five closest cities." << endl;
	cout << "2. *BONUS* Display the five farthest cities." << endl;
}

void displayNoRecordsFound()
{
	//display no records found message
	cout << endl << "No records could be found." << endl << endl;
}

void displayMatchCount(const int matchCount)
{
	//display count of matching values
	cout << endl << "Matching record(s) found: " << matchCount << endl << endl;
}

void deleteConfirm(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS, const string mDATA_FILE)
{
	//declare and initialize local variables
	string deleteConfirm = "";
	int deletionCounter = 0;

	//loop until input is good
	bool deleteConfirmGood = false;
	while (!deleteConfirmGood)
	{
		if (columnTosearch == 999) //for DELETE_ALL
		{
			//set console input to local variable
			deleteConfirm = getConsoleInputString(areYouReallySurePrompt());
		}
		else
		{
			//do nothing
		}

		if (deleteConfirm == "y" || deleteConfirm == "Y")
		{
			if (columnTosearch == 999) //for DELETE_ALL
			{
				//remove vector
				vecDelete(mainList);

				//display deletion confirmation message
				cout << endl << "All records have been deleted." << endl << endl;
				displayMainMenu(mDATA_FILE);
			}
			else
			{
				//do nothing					
			}

			//set boolean to true to exit loop
			deleteConfirmGood = true;
		}
		else if (deleteConfirm == "n" || deleteConfirm == "N")
		{
			//display no deletion perfomed confirmation message
			cout << endl << "No records have been deleted." << endl << endl;
			//set boolean to true to exit loop
			deleteConfirmGood = true;
		}
		else
		{
			//do nothing
		}
	}
}

void vecDelete(vector<vector<string>> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<vector<string>>().swap(vecToDelete);
}

void vecDelete(vector<string> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<string>().swap(vecToDelete);
}

void vecDelete(vector<int> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<int>().swap(vecToDelete);
}

void vecDelete(vector<double> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<double>().swap(vecToDelete);
}

string makeASelection()
{
	//display promt to enter selection
	return "Make a selection> ";
}

string cityNamePrompt()
{
	//display prompt for city to search 
	return "Enter city name> ";
}

string cityNumPrompt()
{
	//display prompt for city to search 
	return "Enter city number> ";
}

string areYouReallySurePrompt()
{
	//display prompt to confirm deletion af all records
	return "This action cannot be undone. Continue(y/n)> ";
}

string getConsoleInputString(const string prompt)
{
	//declare and initialize local variables
	string s1 = "";

	//loop until input is good
	bool inputGood = false;
	while (!inputGood)
	{
		//prompt for input
		cout << prompt;
		//read input from console
		getline(cin, s1);

		if (s1.length() == 0)
		{
			//do nothing
		}
		else
		{
			//set boolean to true to leave while loop
			inputGood = true;
		}
	}
	//return validated input
	return s1;
}

void getCities(vector<vector<string>> &mainList, const int mCITIES_TO_DISPLAY, const int mNUM_COLS, string choice)
{
	//create seperate vectores for each column
	vector<string> distances;
	vector<int> cityNumberColumn;
	vector<string> cityNameColumn;
	vector<string> countryColumn;
	vector<double> latitudeColumn;
	vector<double> longitudeColumn;
	vector<double> distanceColumn;

	//declare and initialize local variables
	const int latitudeColumnPosition = 3;
	const int longitudeColumnPosition = 4;

	//get index of selected city
	int cityIndex = stoi(City::getMatchNumber());

	//get latitude and longitude of selected city
	double lat1 = stod(mainList[cityIndex][latitudeColumnPosition]);
	double long1 = stod(mainList[cityIndex][longitudeColumnPosition]);

	//fill first element in vector
	distances.push_back(" ");

	//calculate all distances from selected city
	for (size_t i = 1; i < mainList.size(); i++)
	{
		//type copnversions
		double lat2 = stod(mainList[i][latitudeColumnPosition]);
		double long2 = stod(mainList[i][longitudeColumnPosition]);

		//get distance and store in string
		string distance = to_string(City::distanceEarth(lat1, long1, lat2, long2));
		//add distance to vector
		distances.push_back(distance);
	}

	//fill first element in vector
	distanceColumn.push_back(0);

	//add values to vectors (type conversions where necessary)
	for (size_t i = 1; i < mainList.size(); i++)
	{
		for (int j = 0; j < mNUM_COLS; j++)
		{
			if (j == 0)			//CityNumber
			{
				int cityNum_temp = stoi(mainList[i][j]);
				cityNumberColumn.push_back(cityNum_temp);
			}
			else if (j == 1)	//CityName
			{
				cityNameColumn.push_back(mainList[i][j]);
			}
			else if (j == 2)	//Country
			{
				countryColumn.push_back(mainList[i][j]);
			}
			else if (j == 3)	//Latitude
			{
				double lat_temp = stod(mainList[i][j]);
				latitudeColumn.push_back(lat_temp);
			}
			else if (j == 4)	//Longitude
			{
				double lon_temp = stod(mainList[i][j]);
				longitudeColumn.push_back(lon_temp);
			}
			else
			{
				//do nothing
			}
		}
		//Distance
		double dist_temp = stod(distances[i]);
		distanceColumn.push_back(dist_temp);
	}

	//create vector to store indexes of sorted values
	vector<int> indexList(distanceColumn.size());
	for (size_t i = 0; i < distanceColumn.size(); i++)
	{
		indexList[i] = i;
	}

	//sort indicies by element value
	sort(indexList.begin(), indexList.end(), [&](int elem1, int elem2)
	{
		return distanceColumn[elem1] < distanceColumn[elem2];
	});
	cout << endl;

	//display tabs header
	City::displayColumnTabs_wDistance();
	City::displayColumnHeaderFooter_wDistance();

	//sort distanceColumn by ascending numerical value
	sort(distanceColumn.begin() + 1, distanceColumn.end());

	if (choice == "closest")
	{
		//display closest cities
		getClosestCities(mCITIES_TO_DISPLAY, indexList, cityNumberColumn, cityNameColumn, countryColumn, latitudeColumn, longitudeColumn, distanceColumn);
	}
	else if (choice == "farthest")
	{
		getFarthestCities(cityIndex, mCITIES_TO_DISPLAY, indexList, cityNumberColumn, cityNameColumn, countryColumn, latitudeColumn, longitudeColumn, distanceColumn);
	}
	else
	{
		//do nothing
	}

	//display tabs end
	City::displayColumnHeaderFooter_wDistance();
	cout << endl;

	//remove vector elements before going out of scope
	vecDelete(distances);
	vecDelete(cityNumberColumn);
	vecDelete(cityNameColumn);
	vecDelete(countryColumn);
	vecDelete(latitudeColumn);
	vecDelete(longitudeColumn);
	vecDelete(distanceColumn);
	vecDelete(indexList);
}

void getClosestCities(const int mCITIES_TO_DISPLAY, vector<int> &map, vector<int> &cityNumberColumn, vector<string> &cityNameColumn, vector<string> &countryColumn, vector<double> &latitudeColumn, vector<double> &longitudeColumn, vector<double> &distanceColumn)
{
	for (int i = 1; i < mCITIES_TO_DISPLAY + 2; i++)
	{
		//new variable to account for shift
		const int shiftedIndex = map[i] - 1;
		cout << right << setfill(' ') << "| " << setw(3) << cityNumberColumn[shiftedIndex] << " | ";
		cout << setw(17) << cityNameColumn[shiftedIndex] << " | ";
		cout << setw(17) << countryColumn[shiftedIndex] << " | ";
		cout << right << setprecision(8) << setw(12) << fixed << latitudeColumn[shiftedIndex] << " | ";
		cout << right << setprecision(8) << setw(13) << fixed << longitudeColumn[shiftedIndex] << " | ";
		cout << right << setprecision(4) << setw(10) << fixed << distanceColumn[i] << " |";
		cout << endl;
	}
}

void getFarthestCities(const int cityIndex, const int mCITIES_TO_DISPLAY, vector<int> &map, vector<int> &cityNumberColumn, vector<string> &cityNameColumn, vector<string> &countryColumn, vector<double> &latitudeColumn, vector<double> &longitudeColumn, vector<double> &distanceColumn)
{
	//set counter for limiting output
	int displayCount = mCITIES_TO_DISPLAY;
	//update position to account for shift
	const int selectedCityPosition = cityIndex - 1;

	//display selected city data
	cout << right << setfill(' ') << "| " << setw(3) << cityNumberColumn[selectedCityPosition] << " | ";
	cout << setw(17) << cityNameColumn[selectedCityPosition] << " | ";
	cout << setw(17) << countryColumn[selectedCityPosition] << " | ";
	cout << right << setprecision(8) << setw(12) << fixed << latitudeColumn[selectedCityPosition] << " | ";
	cout << right << setprecision(8) << setw(13) << fixed << longitudeColumn[selectedCityPosition] << " | ";
	cout << right << setprecision(4) << setw(10) << fixed << distanceColumn[1] << " |";
	cout << endl;

	//display farthest cities data
	for (size_t i = (map.size() - mCITIES_TO_DISPLAY); i < map.size(); i++)
	{
		//new variable to account for shift
		const int shiftedIndex = map[i] - 1;

		cout << right << setfill(' ') << "| " << setw(3) << cityNumberColumn[shiftedIndex] << " | ";
		cout << setw(17) << cityNameColumn[shiftedIndex] << " | ";
		cout << setw(17) << countryColumn[shiftedIndex] << " | ";
		cout << right << setprecision(8) << setw(12) << fixed << latitudeColumn[shiftedIndex] << " | ";
		cout << right << setprecision(8) << setw(13) << fixed << longitudeColumn[shiftedIndex] << " | ";
		cout << right << setprecision(4) << setw(10) << fixed << distanceColumn[i] << " |";
		cout << endl;

		//decrement counter for limiting output
		displayCount--;
		//restrict display to farthest mCITIES_TO_DISPLAY
		while (displayCount == 0)
		{
			break;
		}
	}
}