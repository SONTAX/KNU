#include "Date.h"

Day::Day(int new_value) {
	value = new_value;
}
Month::Month(int new_value) {
	value = new_value;
}
Year::Year(int new_value) {
	value = new_value;
}
Second::Second(int new_value) {
	value = new_value;
}
Minute::Minute(int new_value) {
	value = new_value;
}
Hour::Hour(int new_value) {
	value = new_value;
}

Date::Date() {
}

Date::Date(Year new_year, Month new_month, Day new_day, Hour new_hour, Minute new_minute, Second new_second) {
	day = new_day.value;
	month = new_month.value;
	year = new_year.value;
	hour = new_hour.value;
	minute = new_minute.value;
	second = new_second.value;
}

bool Date::IsInputedDataCorrect() {
	if (((year < -10000) || (year == 0) || (year > 10000)) || ((month < 1) || (month > 12)) || ((day < 1) || (day > days_in_month[month - 1])) || ((hour < 0) || (hour > 23)) || ((minute < 0) || (minute > 59)) || ((second < 0) || (second > 59))) {
		return false;
	}
	return true;
}

void Date::IsYearLeap(){
	if (!(year % 4 != 0 || year % 100 == 0 && year % 400 != 0)) {
		is_year_leap = true;
		days_in_month[1]++;
	}
}	

void Date::Fill() {
	string input;
	cout << "Input date (format: yyyy.mm.dd): ";
	cin >> input;
	bool correct_input = TransformStringIntoDate(input);
	if (!correct_input) {
		system("cls");
		cout << "Incorrect input!\nPlease, try again!\n\n";
		Fill();
		return;
	}
	cout << "Input time (format: hh:mm:ss): ";
	cin >> input;
	correct_input = TransformStringIntoTime(input);
	IsYearLeap();
	correct_input = IsInputedDataCorrect();
	if (!correct_input) {
		system("cls");
		cout << "Incorrect input!\nPlease, try again!\n\n";
		Fill();
		return;
	}
}

string Date::DayOfTheWeek() const {
	int day_in_number = GetJDN() % 7;
	switch (day_in_number) {
	case 0: {
		return "Monday\n";
	}
	case 1: {
		return "Tuesday\n";
	}
	case 2: {
		return "Wednesday\n";
	}
	case 3: {
		return "Thursday\n";
	}
	case 4: {
		return "Friday\n";
	}
	case 5: {
		return "Saturday\n";
	}
	case 6: {
		return "Sunday\n";
	}
	}
}

string Date::Print() const {
	return to_string(year) + "." + to_string(month) + "." + to_string(day) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + "\n";
}

int Date::GetJDN() const {
	int result;
	int d = (14 - month) / 12;
	int m = month + 12 * d - 3;
	int y = year + 4800 - d;
	result = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
	return result;
}

int Date::GetTimeInSeconds() const {
	int result;
	result = hour * 3600 + minute * 60 + second;
	return result;
}

void Date::ReverseJDN(int JDN) {
	int a = JDN + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;
	day = e - (153 * m + 2) / 5 + 1;
	month = m + 3 - 12 * (m / 10);
	year = 100 * b + d - 4800 + (m / 10);
}

bool Date::TransformStringIntoDate(string input) {
	string transform;
	for (size_t i = 0, counter = 0; i <= input.size(); i++) {
		if (input[i] == '.') {
			counter++;
			if (counter == 1) {
				year = stoi(transform);
			}
			else if (counter == 2) {
				month = stoi(transform);
			}
			else {
				return false;
			}
			transform.clear();
		}
		else if (i == input.size()) {
			day = stoi(transform);
		}
		else {
			transform += input[i];
		}
	}
	return true;
}

bool Date::TransformStringIntoTime(string input) {
	string transform; for (size_t i = 0, counter = 0; i <= input.size(); i++) {
		if (input[i] == ':') {
			counter++;
			if (counter == 1) {
				hour = stoi(transform);
			}
			else if (counter == 2) {
				minute = stoi(transform);
			}
			else {
				return false;
			}
			transform.clear();
		}
		else if (i == input.size()) {
			second = stoi(transform);
		}
		else {
			transform += input[i];
		}
	}
	return true;
}

void Date::ReverseSeconds(int seconds) {
	hour = seconds / 3600;
	minute = (seconds % 3600) / 60;
	second = (seconds % 3600) % 60;
}