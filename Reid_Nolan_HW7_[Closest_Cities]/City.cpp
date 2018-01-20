//Reid_Nolan_HW7_[Closest_Cities]
//City.cpp
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/21/2017																				//
//City Class Source File																		//
//Class for returning specific values from input file for Reid_Nolan_HW7_[Closest_Cities].cpp	//
//**********************************************************************************************//

#include "stdafx.h"
#include "City.h"
#include <cmath> 
#include <string>
#define earthRadiusKm 6371.0
#define pi 3.14159265358979323846

//create new class instance
City cityA;

//constructors
City::City()
{
	//initialize class variables
	CityNumber = "";
	CityName = "";
	Country = "";
	Latitude = "";
	Longitude = "";
	matchNumber = "";
}

//destructors
City::~City()
{
}

//setters
void City::setCityNumber(string cityCount)
{
	CityNumber = cityCount;
}

void City::setCityName(string nextValue)
{
	CityName = nextValue;
}

void City::setCountry(string nextValue)
{
	Country = nextValue;
}

void City::setLatitude(string nextValue)
{
	Latitude = nextValue;
}

void City::setLongitude(string nextValue)
{
	Longitude = nextValue;
}

void City::setMatchNumber(string match)
{
	matchNumber = match;
}

//getters
string City::getCityNumber()
{
	return CityNumber;
}
string City::getCityName()
{
	return CityName;
}

string City::getCountry()
{
	return Country;
}

string City::getLatitude()
{
	return Latitude;
}

string City::getLongitude()
{
	return Longitude;
}

string City::getMatchNumber()
{
	return cityA.matchNumber;
}

//load records into vectors
void City::loadRecords(City city, vector<vector<string>> &mainList, const string mDATA_FILE, fstream &inFile, int &cityCount)
{
	//open input file
	inFile.open(mDATA_FILE);

	//notify and terminate if input file cannot be opened
	while (!inFile)
	{
		//display error and exit message
		displayNoInputFile(mDATA_FILE);
		displayExit();
		//wait for user to continue before terminating
		system("pause");
		//terminate program
		exit(1);
	}

	//loop while input file is open
	while (inFile)
	{
		string Row = "";

		//display loading contacts message
		displayLoadingRecords(mDATA_FILE);

		//create sub-vector for each row of values
		vector<string>newRow;

		//loop for reading from file and appending rows to vector
		while (getline(inFile, Row))
		{
			//declare and initialize local variables			
			stringstream ss(Row);
			string cell = "";

			string newCityCount = to_string(cityCount);
			if (newCityCount == "0")
			{
				newRow.push_back("Num");
			}
			else
			{
				city.setCityNumber(newCityCount);
				newRow.push_back(city.getCityNumber());
			}

			//get comma seperated values for each row and add to sub-vector			
			for (int i = 0; (getline(ss, cell, ',')); i++) //use City Class to set and get cell values
			{				

				if (i == 0)			//set and get value in first columm (CityName)
				{
					city.setCityName(cell);
					newRow.push_back(city.getCityName());
				}
				else if (i == 1)	//set and get value in second columm (Country)
				{
					city.setCountry(cell);
					newRow.push_back(city.getCountry());
				}
				else if (i == 2)	//set and get value in third columm (Latitude)
				{
					city.setLatitude(cell);
					newRow.push_back(city.getLatitude());
				}
				else if (i == 3)	//set and get value in fourth columm (Longitude)
				{
					city.setLongitude(cell);
					newRow.push_back(city.getLongitude());
				}
				else
				{
					//do nothing
				}
			}
			//add sub-vector to main vector(append row)
			mainList.push_back(newRow);

			//erase all vector elements from vector
			newRow.erase(newRow.begin(), newRow.end());
			vector<string>().swap(newRow);

			//increment contacts counter
			cityCount++;
		}
	}

	//close input file after reading into memory
	inFile.close();

	//compare by lastname, firstname, middlename, and number, in that order (+1 excludes first row, assuming column headers)		
	sort(mainList.begin() + 1, mainList.end(), defineSortOrder);

	//display number of records processed
	displaycityCount(cityCount);
}

//status messages
void City::displayLoadingRecords(const string mDATA_FILE)
{
	//display input file opened confirmation message
	cout << endl << "Please wait. Loading records from " << mDATA_FILE << " into memory..." << endl;
}

void City::displayNoInputFile(const string mDATA_FILE)
{
	//display no input file message
	cout << "Error! Input file could not be opened." << endl;
	cout << "Ensure that " << mDATA_FILE << " has been placed in the current working directory" << endl;
	cout << "     and/or is not open in another program." << endl;
}

void City::displaycityCount(const int cityCount)
{
	//display number of records processed (excludes first row of input file, assumes column headers)
	cout << "Records successfully loaded into memory: " << cityCount - 1 << endl << endl;
}

void City::displayExit()
{
	//display exiting program status message
	cout << endl << "exiting program..." << endl;
	system("pause");
	exit(1);
}

//displaying data
void City::displayColumnHeader(vector<vector<string>> &mainList, const int mNUM_COLS, const int mFIRST_ROW)
{
	//output rows
	cout << endl;
	outputRows(mainList, mNUM_COLS, mFIRST_ROW);

	//format second line, spacer between column headers and record values, for tabular format	
	cout << "| --- |";						//CityNumber
	cout << " ----------------- ";			//CityName
	cout << "| ----------------- ";			//Country
	cout << "| ------------ ";				//Latitude
	cout << "| ------------ |" << endl;		//Longitude
}

void City::outputRows(vector<vector<string>> &mainList, const int mNUM_COLS, const int i)
{
	//loop through columns
	for (int j = 0; j < mNUM_COLS; j++)
	{
		//format record fields for output
		if (j == 0)				//CityNumber
		{
			cout << "| " << setw(3) << mainList[i][j] << " | ";
		} 
		else if (j == 1)		//CityName
		{
			cout << setw(17) << mainList[i][j] << " | ";
		}
		else if (j == 2)		//Country
		{
			cout << setw(17) << mainList[i][j] << " | ";
		}
		else if (j == 3)		//Latitude
		{
			cout << setw(12) << mainList[i][j] << " | ";
		}
		else if (j == 4)		//Longitude
		{
			cout << setw(12) << mainList[i][j] << " |";
		}
		else
		{
			//do nothing
		}
	}
	cout << endl;
}

void City::displayColumnFooter()
{
	//format second line, spacer between column headers and record values, for tabular format	
	cout << "| --- |";						//CityNumber
	cout << " ----------------- ";			//CityName
	cout << "| ----------------- ";			//Country
	cout << "| ------------ ";				//Latitude
	cout << "| ------------ |" << endl;		//Longitude
}

void City::displayColumnTabs_wDistance()
{
	cout << "| Num ";						//CityNumber
	cout << "|              City ";			//CityName
	cout << "|           Country ";			//Country
	cout << "|     Latitude ";				//Latitude
	cout << "|     Longitude ";				//Longitude
	cout << "|   Distance |" << endl;		//Distance
}

void City::displayColumnHeaderFooter_wDistance()
{
	cout << "| --- ";						//CityNumber
	cout << "| ----------------- ";			//CityName
	cout << "| ----------------- ";			//Country
	cout << "| ------------ ";				//Latitude
	cout << "| ------------- ";				//Longitude
	cout << "| ---------- |" << endl;		//Distance
}

void City::displayMatches(vector<vector<string>> &mainList, string &toMatch, const int columnTosearch, const int mNUM_COLS, int &matchCount, const int i)
{
	//display column header
	displayColumnHeader(mainList, mNUM_COLS, i);

	//loop through rows
	for (size_t i = 0; i < mainList.size(); i++)
	{
		//copy vector contencts to string for comparison
		string s1 = mainList[i][columnTosearch];

		//add string case-insensitivity
		for (size_t i = 0; i < s1.length(); i++)
		{
			s1[i] = tolower(s1[i]);
		}
		for (size_t i = 0; i < toMatch.length(); i++)
		{
			toMatch[i] = tolower(toMatch[i]);
		}

		//compare search value to record values
		if (s1 == toMatch)
		{
			//outpuit rows
			outputRows(mainList, mNUM_COLS, i);
			//increment match counter
			matchCount++;

			//set value to new instance
			cityA.setMatchNumber(mainList[i][0]);
		}
		else
		{
			//do nothing
		}
	}
}

void City::outputAllRecords(vector<vector<string>> &mainList, const int mNUM_COLS)
{
	//loop through rows, excluding first row (assumes column headers)
	for (size_t i = 1; i < mainList.size(); i++)
	{
		//output rows
		outputRows(mainList, mNUM_COLS, i);
	}
}

//relational
bool City::defineSortOrder(const vector<string>& vector1, const vector<string>& vector2)
{
	//for sorting values
	//CityName = 0 | Country = 1 | Latitude = 2 | Longitude = 3 |

	//compare by CityName, Country, Latitude, and Longitude, in that order
	return vector1[1] + vector1[0] + vector1[2] + vector1[3] < vector2[1] + vector2[2] + vector2[2] + vector2[3];
}

////relational
//bool City::defineSortOrderForDistance(const vector<string>& vector1, const vector<string>& vector2)
//{
//	//for sorting values
//	//CityNumber = 0 | CityName = 1 | Country = 2 | Latitude = 3 | Longitude = 4 | Distance = 5 
//
//	//compare by CityName, Country, Latitude, and Longitude, in that order
//	return vector1[5] < vector2[5];
//}

//computational
double City::deg2rad(double deg)
{
	return (deg * pi / 180);
}

double City::rad2deg(double rad)
{
	return (rad * 180 / pi);
}

double City::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d)
{
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);

	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}