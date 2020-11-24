#include<bits/stdc++.h>
using namespace std;


class MyDate{
private:
	int day;
	int month;
	int year;
public:
	MyDate(int year,int month,int day){
		this->day = day;
		this->month = month;
		this->year = year;
	}
	static const string MONTHS[];
	static const string DAYS[];
	static const int DAYS_IN_MONTHS[];
	static bool isLeapYear(int year);
	static int getDayofYear(int year,int month,int day);
	bool isValidDate(int year,int month,int day);
	int getDayofWeek(int year,int month,int day);
	void setDate(int year,int month,int day);
	int getYear();
	int getMonth();
	int getDay();
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	string toString();
	MyDate nextDay();
	MyDate nextMonth();
	MyDate nextYear();
	MyDate previousDay();
	MyDate previousMonth();
	MyDate previousYear();
	MyDate addDays(int days);
	MyDate subDays(int days);
	MyDate addMonths(int months);
	MyDate subMonths(int months);
	MyDate addYears(int years);
	MyDate subYears(int years);
};

const string MyDate::MONTHS[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
const string MyDate::DAYS[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
const int MyDate::DAYS_IN_MONTHS[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int MyDate::getDayofYear(int year,int month,int day){
	int ans = 0;
	for(int i = 1 ; i < month ; i++){
		if(i == 2){
			if(isLeapYear(year))
				ans += DAYS_IN_MONTHS[i - 1] + 1;
			else
				ans += DAYS_IN_MONTHS[i - 1];
		} else {
			ans += DAYS_IN_MONTHS[i - 1];
		}
	}
	ans += day;
	return ans;
}

int MyDate::getDay(){
	return day;
}

int MyDate::getMonth(){
	return month;
}

int MyDate::getYear(){
	return year;
}

int MyDate::getDayofWeek(int year,int month,int day){
	int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  	year -= month < 3;
  	return (year + year/4 - year/100 + year/400 + t[month - 1] + day) % 7;
}

bool MyDate::isLeapYear(int year){
	if(year % 100 == 0){
		if(year % 400 == 0) return true;
		return false;
	}
	if(year % 4 == 0)
		return true;
	return false;
}

bool MyDate::isValidDate(int year,int month,int day){
	if(month > 12 or month < 1) return false;
	if(year > 9999 or year < 1) return false;
	if(day < 1 or day > 31) return false;
	switch(month){
		case 2:{
			if(isLeapYear(year)){
				if(day > 29) return false;
			} else {
				if(day > 28) return false;
			}
		}
		case 4:
		case 6:
		case 9:
		case 11:{
			if(day > 30) return false;
		}
	}
	return true;
}

void MyDate::setDate(int year,int month,int day){
	setDay(day);
	setMonth(month);
	setYear(year);
}

void MyDate::setYear(int new_year){
	year = new_year;
}

void MyDate::setMonth(int new_month){
	month = new_month;
}

void MyDate::setDay(int new_day){
	day = new_day;
}

string MyDate::toString(){
	string date = "";
	int day_of_week = getDayofWeek(year,month,day);
	date = DAYS[day_of_week] + " " + to_string(day) + " " + MONTHS[month - 1] + " " + to_string(year);
	return date;
}

MyDate MyDate::addDays(int days){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= days ; i++){
		ans = ans.nextDay();
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::nextDay(){
	int day_of_year = getDayofYear(year,month,day) + 1;
	if(isLeapYear(year)){
		if(day_of_year == 367){
			month = 1;
			day = 1;
			year++;
			setDate(year,month,day);
			MyDate ans(year,month,day);
			return ans;
		}
		if(month == 2 and day == 29){
			month++;
			day = 1;
			setDate(year,month,day);
			MyDate ans(year,month,day);
			return ans;
		}
	}
	if(!isLeapYear(year) and day_of_year == 366){
		month = 1;
		day = 1;
		year++;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	if(!isLeapYear(year) and month == 2 and day == 28){
		month++;
		day = 1;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	if(day == DAYS_IN_MONTHS[month - 1] and month != 2){
		day = 1;
		month++;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	day++;
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}

MyDate MyDate::subDays(int days){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= days ; i++){
		ans.previousDay();
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::previousDay(){
	int day_of_year = getDayofYear(year,month,day) - 1;
	if(isLeapYear(year)){
		if(month == 3 and day == 1){
			month--;
			day = 29;
			setDate(year,month,day);
			MyDate ans(year,month,day);
			return ans;
		}
	}
	if(day_of_year == 0){
		year--;
		month = 12;
		day = 31;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	if(day == 1){
		month--;
		day = DAYS_IN_MONTHS[month - 1];
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	day--;
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}

MyDate MyDate::addMonths(int months){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= months ; i++){
		ans.nextMonth();
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::nextMonth(){
	if(month == 12){
		year++;
		month = 1;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	if(isLeapYear(year) and day == 29)
		day = DAYS_IN_MONTHS[month];
	else{
		if(day == DAYS_IN_MONTHS[month - 1] and month != 2){
			day = DAYS_IN_MONTHS[month];
			if(isLeapYear(year) and month == 1)
				day = 29;
		}
	}
	month++;
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}

MyDate MyDate::subMonths(int months){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= months ; i++){
		ans.previousMonth();
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::previousMonth(){
	if(month == 1){
		year--;
		month = 12;
		setDate(year,month,day);
		MyDate ans(year,month,day);
		return ans;
	}
	if(month == 2 and day == DAYS_IN_MONTHS[month - 1] and isLeapYear(year)){
		month--;
	} else {
		if(isLeapYear(year) and day == 29)
			day = DAYS_IN_MONTHS[month - 2];
		else{
			if(day == DAYS_IN_MONTHS[month - 1]){
				day = DAYS_IN_MONTHS[month - 2];
				if(isLeapYear(year) and month == 3)
					day = 29;
			}
		}
		month--;
	}
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}

MyDate MyDate::addYears(int years){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= years ; i++){
		ans.nextYear();
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::nextYear(){
	if(isLeapYear(year) and month == 2 and day == 29)
		day = DAYS_IN_MONTHS[month - 1];
	else if(isLeapYear(year + 1) and month == 2 and day == 28)
		day = DAYS_IN_MONTHS[month - 1] + 1;
	year++;
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}

MyDate MyDate::subYears(int years){
	MyDate ans(year,month,day);
	for(int i = 1 ; i <= years ; i++){
		ans.previousYear();
		cout << ans.toString() << endl;
	}
	setDate(ans.getYear(),ans.getMonth(),ans.getDay());
	return ans;
}

MyDate MyDate::previousYear(){
	if(isLeapYear(year - 1) and month == 2 and day == 28)
		day = 29;
	else if(isLeapYear(year) and month == 2 and day == 29)
		day = DAYS_IN_MONTHS[month - 1];
	year--;
	setDate(year,month,day);
	MyDate ans(year,month,day);
	return ans;
}


int main(){
	MyDate d1(2012, 2, 29);
	// cout << d1.addMonths(12).toString() << endl;
	// cout << d1.subMonths(12).toString() << endl;
	cout << d1.addYears(12).toString() << endl;
	cout << d1.subYears(12).toString() << endl;
	// cout << d1.toString() << endl; // Tuesday 28 Feb 2012
	// cout << d1.addDays(33).toString() << endl;
	// cout << d1.getDayofYear(d1.getYear(),d1.getMonth(),d1.getDay()) << endl;
	// cout << d1.subDays(657).toString() << endl; // Wednesday 29 Feb 2012
	// cout << d1.getDayofYear(d1.getYear(),d1.getMonth(),d1.getDay()) << endl;
	// cout << d1.nextDay().toString() << endl; // Thursday 1 Mar 2012
	// cout << d1.nextMonth().toString() << endl;; // Sunday 1 Apr 2012
	// cout << d1.nextYear().toString() << endl;; // Monday 1 Apr 2013
	// MyDate d2(2012, 1, 2);
	// cout << d2.toString() << endl; // Monday 2 Jan 2012
	// cout << d2.previousDay().toString() << endl;; // Sunday 1 Jan 2012
	// cout << d2.previousDay().toString() << endl;; // Saturday 31 Dec 2011
	// cout << d2.previousMonth().toString() << endl;; // Wednesday 30 Nov 2011
	// cout << d2.previousYear().toString() << endl;; // Tuesday 30 Nov 2010 
}