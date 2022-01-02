#include "DateOperations.h"

DateOperations::DateOperations(Date first, Date second) {
	date1 = first;
	date2 = second;
}

string DateOperations::DateDifference() {
	int JDN_1 = date1.GetJDN();
	int JDN_2 = date2.GetJDN();
	int SEC_1 = date1.GetTimeInSeconds();
	int SEC_2 = date2.GetTimeInSeconds();
	days_difference = JDN_1 - JDN_2;
	seconds_difference = SEC_1 - SEC_2;
	if ((days_difference > 0) && (seconds_difference < 0)) {
		seconds_difference += 86400;
		days_difference--;
	}
	else if ((days_difference < 0) && (seconds_difference > 0)) {
		days_difference++;
		seconds_difference = 86400 - seconds_difference;
	}
	seconds_difference = abs(seconds_difference);
	days_difference = abs(days_difference);
	return "Difference is: " + to_string(days_difference) + " days and " + to_string(seconds_difference) + " seconds\n";
}

void DateOperations::Arithmetic(bool sign, bool order) { //sign: 0(-), 1(+); order: 0(with second), 1(with first)
	DateDifference();
	int JDN;
	int seconds;
	if (order) {
		JDN = date1.GetJDN();
		seconds = date1.GetTimeInSeconds();
	}
	else {
		JDN = date2.GetJDN();
		seconds = date2.GetTimeInSeconds();
	}
	if (sign) {
		JDN += days_difference;
		seconds += seconds_difference;
	}
	else {
		JDN -= days_difference;
		seconds -= seconds_difference;
	}
	if (seconds > 86399) {
		seconds = seconds - 86400;
		JDN++;
	}
	else if (seconds < 0) {
		seconds = 86400 + seconds;
		JDN--;
	}
	if (order) {
		date1.ReverseJDN(JDN);
		date1.ReverseSeconds(seconds);
	}
	else {
		date2.ReverseJDN(JDN);
		date2.ReverseSeconds(seconds);
	}
}

void DateOperations::ChangeDate(bool number) {
	if (number) {
		date1.Fill();
	}
	else {
		date2.Fill();
	}
}

string DateOperations::Print(bool number) const {
	if (number) {
		return date1.Print();
	}
	else {
		return date2.Print();
	}
}

string DateOperations::DayOfTheWeek(bool number) const {
	if (number) {
		return date1.DayOfTheWeek();
	}
	else {
		return date2.DayOfTheWeek();
	}
}