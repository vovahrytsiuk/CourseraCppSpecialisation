#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;


class Day{
  int value;
public:
  Day(int d = 1):value(d){}
  friend istream& operator>>(istream&in, Day& day);
  friend ostream& operator<<(ostream&out, const Day& day);
};

class Month
{
  int value;
public:
  Month(int m = 1):value(m){}
  friend ostream& operator<<(ostream&out, const Month& month);
  friend istream& operator>>(istream&in , Month& month);
};

class Year
{
  int value;
public:
  Year(int y = 0):value(y){}
  friend ostream& operator<<(ostream& out, const Year& year)
  {
    out << year.value;
    return out;
  }
  friend istream& operator>>(istream& in, Year& year)
  {
    in >> year.value;
    return in;
  }
};


class Date
{
  Year year;
  Month month;
  Day day;
  void readDateFromString(const string& stringDate);
  bool is_day_valid(int new_day);
  bool is_month_valid(int new_month);
  void verifySeparator(istream& in, const string& date, char sep = '-');

public:
  Date(int y = 0, int m = 0, int d = 0):year(y), month(m), day(d){}
  friend ostream& operator<<(ostream& out, const Date& date);
  friend istream& operator>>(istream& in, Date& newdate);
  
  
};


int main()
{
  //1
  {
    stringstream ss("1-1-1");
    try
    {
      Date d;
      ss >> d;
    }
    catch(const std::exception& e)
    {
      cout << "case 1" << endl;
      std::cerr << e.what() << '\n';
    }
  }
  //2
  {
    stringstream ss("-1-1-1");
    try
    {
      Date d;
      ss >> d;
    }
    catch(const std::exception& e)
    {
      cout << "case 2" << endl;
      std::cerr << e.what() << '\n';
    }
  }
  //3
  {
    stringstream ss("1--1-1");
    try
    {
      Date d;
      ss >> d;
    }
    catch(const std::exception& e)
    {
      cout << "case 3" << endl;
      std::cerr << e.what() << '\n';
    }
  }
  //4
  {
    stringstream ss("1---1-1");
    try
    {
      Date d;
      ss >> d;
    }
    catch(const std::exception& e)
    {
      cout << "case 4" << endl;
      std::cerr << e.what() << '\n';
    }
  }
  //5
  {
    stringstream ss("1-+1-+1");
    try
    {
      Date d;
      ss >> d;
    }
    catch(const std::exception& e)
    {
      cout << "case 5" << endl;
      std::cerr << e.what() << '\n';
    }
  }
  return 0;
}



ostream& operator<<(ostream& out, const Date& date)
{
  out << date.year << "-" << date.month << "-" << date.day;
  return out;
}

istream& operator>>(istream& in, Date& newdate)
{
  string string_date;
  in >> string_date;
  newdate.readDateFromString(string_date);


  return in;
}


bool Date::is_day_valid(int new_day)
{
  return new_day >= 1 && new_day <= 31;
}

bool Date::is_month_valid(int new_month)
{
  return new_month <= 12 && new_month >= 1;
}

void Date::verifySeparator(istream& in, const string& date, char sep)
{
  if(in.peek() != sep)
  {
    throw runtime_error("Wrong date format: " + date);
  }
  else
  {
    in.ignore(1);
    if(in.peek() == '-')
    {
      int currentpos = in.tellg();
      in.ignore(1);
      if(in.peek() == '-')
      {
        throw runtime_error("Wrong date format: " + date);
      }
      else
      {
        in.seekg(currentpos);
      }
    }
  }

}



void Date::readDateFromString(const string& stringDate)
{
  stringstream ss;
  ss << stringDate;
  ss >> year;
  verifySeparator(ss, stringDate);
  ss >> month;
  verifySeparator(ss, stringDate);
  ss >> day;
  if(!ss)
  {
    throw runtime_error("Wrong date format: " + stringDate);
  }
  
}



istream& operator>>(istream&in, Day& day)
{
  in >> day.value;
  if(day.value > 31 || day.value < 1)
  {
    throw runtime_error("Day value is invalid: " + to_string(day.value));
  }
  return in;
}



ostream& operator<<(ostream&out, const Day& day)
{
  out << day.value;
  return out;
}


ostream& operator<<(ostream&out, const Month& month)
{
  out << month.value;
  return out;
}

istream& operator>>(istream&in , Month& month)
{
  in >> month.value;
  if(month.value > 12 || month.value < 1)
  {
    throw runtime_error("Month value is invalid: " + to_string(month.value));
  }
  return in;
}



