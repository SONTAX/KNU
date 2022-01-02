#ifndef DATEOPERATIONS_H_
#define DATEOPERATIONS_H_

#include "Date.h"
#include <string>

using namespace std;
/**
* Class to store two dates and do arithmetic operations on it
*/
class DateOperations
{
public:
	/**
	* \brief DateOperations constructor
	*
	* Creates class example. All parametrs must be specified
	*/
	DateOperations(Date first, Date second);
	/**
	* Calculates difference between two stored dates
	* \return return date difference in string format (ex. Difference is: <days_difference> days and <seconds_difference> seconds)
	*/
	string DateDifference();
	/**
	* Add (subtract) date difference to (from) first (second) date
	* \param sign 1 - add, 0 - subtract
	* \param order 1 - first date, 0 - second date
	*/
	void Arithmetic(bool sign, bool order);
	/**
	* Input new number
	* \param number 1 - first date, 0 - second date
	*/
	void ChangeDate(bool number);
	/**
	* Function that returns date and time as string for selected date
	* \param number 1 - first date, 0 - second date
	*/
	string Print(bool number) const;
	/**
	* Function to find out day of the week for selected date
	* \return return string of the day of the week
	* \param number 1 - first date, 0 - second date
	*/
	string DayOfTheWeek(bool number) const;
private:
	Date date1;	/**< Stores information about first date */
	Date date2;	/**< Stores information about second date */
	int days_difference;	/**< Stores number of days difference between first and second dates */
	int seconds_difference;	/**< Stores number of seconds difference between first and second dates */
};

#endif DATEOPERATIONS_H_