#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;
/**
* Class to store number of the day (is used only to direct Date constructor)
*/
class Day {
public:
	int value;	/**< Number of the day */
	/**
	* Constructor of Day class. new_value must be specified
	*/
	explicit Day(int new_value);
};
/**
* Class to store number of the month (is used only to direct Date constructor)
*/
class Month {
public:
	int value;	/**< Number of the month */
	/**
	* Constructor of Month class. new_value must be specified
	*/
	explicit Month(int new_value);
};
/**
* Class to store number of the year (is used only to direct Date constructor)
*/
class Year {
public:
	int value;	/**< Number of the year */
	/**
	* Constructor of Year class. new_value must be specified
	*/
	explicit Year(int new_value);
};
/**
* Class to store number of the hour (is used only to direct Date constructor)
*/
class Hour {
public:
	int value;	/**< Number of the hour */
	/**
	* Constructor of Hour class. new_value must be specified
	*/
	explicit Hour(int new_value);
};
/**
* Class to store number of the minute (is used only to direct Date constructor)
*/
class Minute {
public:
	int value;	/**< Number of the minute */
	/**
	* Constructor of Minute class. new_value must be specified
	*/
	explicit Minute(int new_value);
};
/**
* Class to store number of the second (is used only to direct Date constructor)
*/
class Second {
public:
	int value;	/**< Number of the second */
	/**
	* Constructor of Second class. new_value must be specified
	*/
	explicit Second(int new_value);
};
/**
* Class to store full information about date
*/
class Date
{
public:
	/**
	* \brief Date constructor
	*
	* Creates class example. All parametrs must be specified
	*/
	Date(Year new_year, Month new_month, Day new_day, Hour new_hour, Minute new_minute, Second new_second);
	/**
	* \brief Default constructor
	* 
	* Constructor which creates empty class example
	*/
	Date();
	/**
	* User inputes new date
	*/
	void Fill();
	/**
	* Function to find out day of the week for inputed date
	* \return return string of the day of the week
	*/
	string DayOfTheWeek() const;
	/**
	* Function that returns date and time as string
	*/
	string Print() const;
	/**
	* Converting gregorian calendar date to julian day number
	* \return julian day number
	*/
	int GetJDN() const;
	/**
	* Converting time to seconds
	* \return number of seconds in the date
	*/
	int GetTimeInSeconds() const;
	/**
	* Converting julian day number to gregorian calendar date 
	* \param JDN julian day number to be converted
	*/
	void ReverseJDN(int JDN);
	/**
	* Converting seconds to time
	* \param seconds number of seconds to be converted
	*/
	void ReverseSeconds(int seconds);
private:
	int year;	/**< Number of the year */
	int month;	/**< Number of the month */
	int day;	/**< Number of the day */
	int hour;	/**< Number of the hour */
	int minute;	/**< Number of the minute */
	int second;	/**< Number of the second */
	vector<int> days_in_month = { 31,28,31,30,31,30,31,31,30,31,30,31 }; 
	bool is_year_leap = false;
	/**
	* Checks is inputed year leap or not. If true add to February one day
	*/
	void IsYearLeap();
	/**
	* Cheks is inputed date correct or not
	*/
	bool IsInputedDataCorrect();
	/**
	* Converting date from string format
	* \param input date in string format
	*/
	bool TransformStringIntoDate(string input);
	/**
	* Converting time from string format
	* \param input time in string format
	*/
	bool TransformStringIntoTime(string input);
};

#endif