//Reid_Nolan_HW7_[Closest_Cities]
//City.h
//**********************************************************************************************//
//Author: Reid S. Nolan																			//
//Date: 04/21/2017																				//
//City Class Header File																		//
//Class for returning specific values from input file for Reid_Nolan_HW7_[Closest_Cities].cpp	//
//**********************************************************************************************//

#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class City
{

private:
	//declare class variables
	string CityNumber;
	string CityName;
	string Country;
	string Latitude;
	string Longitude;
	string matchNumber;	

public:
	City();
	~City();	

	//setters
	void setCityNumber(string cityCount);
	void setCityName(string nextValue);
	void setCountry(string nextValue);
	void setLatitude(string nextValue);
	void setLongitude(string nextValue);
	void City::setMatchNumber(string match);

	//getters
	string getCityNumber();
	string getCityName();
	string getCountry();
	string getLatitude();
	string getLongitude();
	static string City::getMatchNumber();

	//load records into vectors
	static void City::loadRecords(City city, vector<vector<string>> &mainList, const string mDATA_FILE, fstream &inFile, int &cityCount);

	//status messages
	static void City::displayLoadingRecords(const string mDATA_FILE);
	static void City::displayNoInputFile(const string mDATA_FILE);
	static void City::displaycityCount(const int cityCount);
	static void City::displayExit();

	//matching & displaying data
	static void City::displayColumnHeader(vector<vector<string>> &mainList, const int mNUM_COLS, const int i);
	static void City::outputRows(vector<vector<string>> &mainList, const int mNUM_COLS, const int i);
	static void City::displayColumnFooter();
	static void City::displayColumnTabs_wDistance();
	static void City::displayColumnHeaderFooter_wDistance();
	static void City::displayMatches(vector<vector<string>> &mainList, string &toMatch, const int columnTosearch, const int mNUM_COLS, int &matchCount, const int i);
	static void City::outputAllRecords(vector<vector<string>> &mainList, const int mNUM_COLS);	

	//relational
	static bool City::defineSortOrder(const vector<string>& vector1, const vector<string>& vector2);
	//static bool City::defineSortOrderForDistance(const vector<string>& vector1, const vector<string>& vector2);

	//computational
	static double City::deg2rad(double deg);
	static double City::rad2deg(double rad);
	static double City::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
};