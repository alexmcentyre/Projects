#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

/**
  This method stores one month within a string variable and returns that string
  @param timeInfo a tm struct
  @param timeMeat a time_t
  @param calendarMonth a string representing one calendar month
  @param wday an integer value representing a weekday
  @param julian a boolean value that determines whether or not the date is a julian date
  @param realMonth an integer value representing a month
  @param realYear an integer value representing a year
  @param realDay an integer value representing a day
**/
string oneMonth(struct tm * timeInfo, time_t timeMeat, string calendarMonth, int wday, bool julian, int realMonth, int realYear, int realDay){
  
  int day = 1, firstWeekDay, today, yearI, month, count = 0;
  string year = "";
  char yearCArray[5];
  today = timeInfo->tm_mday;
  month = timeInfo->tm_mon;
  timeInfo->tm_mday = day;
  yearI = timeInfo->tm_year;
  mktime(timeInfo);
  
  while(month == timeInfo->tm_mon){ //stores the number of days in the current month within count
    count++;
    day++;
    timeInfo->tm_mday = day;
    mktime(timeInfo);
  }

  timeInfo->tm_mday = today;
  timeInfo->tm_mon = month;
  timeInfo->tm_year = yearI;
  mktime(timeInfo);
  
  timeInfo->tm_mday = count;
  mktime(timeInfo);
  
  timeInfo->tm_mday = 1;
  mktime(timeInfo);
  
  if(julian){
    firstWeekDay = wday;
  }else{
    firstWeekDay = timeInfo->tm_wday;  
  }

  
  switch(timeInfo->tm_mon){
    case 0:
      calendarMonth += "    January ";
      break;
    case 1:
      calendarMonth += "    February ";
      break;
    case 2:
      calendarMonth += "    March ";
      break;
    case 3:
      calendarMonth += "    April ";
      break;
    case 4:
      calendarMonth += "    May ";
      break;
    case 5:
      calendarMonth += "    June ";
      break;
    case 6:
      calendarMonth += "    July ";
      break;
    case 7:
      calendarMonth += "    August ";
      break;
    case 8:
      calendarMonth += "    September ";
      break;
    case 9:
      calendarMonth += "    October ";
      break;
    case 10:
      calendarMonth += "    November ";
      break;
    case 11:
      calendarMonth += "    December ";
      break;
    default:
      calendarMonth += "\tUnknown ";
      break;
  }
  strftime(yearCArray, 5, "%Y", timeInfo);
  year = yearCArray;
  
  calendarMonth += year;
  calendarMonth += "\n";
  calendarMonth +="Su Mo Tu We Th Fr Sa\n";
  int counter = 1;
  
  while(counter <= firstWeekDay){
    calendarMonth += "   ";
    counter++;
  }
  
  int count2 = 1;
  int row = 0, col = firstWeekDay;
  int dayGrid[6][7];
  
  while(count2 <= count){
    dayGrid[row][col] = count2;
    if(count2 < 10){
      calendarMonth+= " ";
    }
    if((count2 == realDay)&&(timeInfo->tm_mon == realMonth)&&(timeInfo->tm_year == realYear)){
      calendarMonth += "\033[30;47m" + to_string(dayGrid[row][col]) + "\033[0m";
    }else{
      calendarMonth += to_string(dayGrid[row][col]);
    }
    if(count2 < 10){
      calendarMonth += " ";
    }else{
      calendarMonth += " ";
    }
    if(col == 6){
      row++;
      col = 0;
      calendarMonth += "\n";
    }else{
      col++;
    }
    count2++;
  }
  calendarMonth += "\n";
  return calendarMonth;
}
/**
  This global mehtod takes two integer values, year and month represpectively, and calculates the day of the week
  @param year an integer value representing a year
  @param month an integer value that represents a month
  @param timeInfo a struct tm
**/
int convertJulian(int year,int month, struct tm *timeInfo){
  int temp = year / 100;
  int centuryCode = ((temp - 18) * -1)% 7;
  temp = year/100;
  temp = year - (temp * 100);
  int yearCode =  (temp + (temp/4))%7;
  int monthCode = 0;
  int dayNum = 1;
  int leapYearCode = 0;
  int dayOfWeek;
  string calendarMonth = "";
    
  switch(month){
    case 0:
      monthCode = 0;
      break;
    case 1:
      monthCode = 3;
      break;
    case 2:
      monthCode = 3;
      break;
    case 3:
      monthCode = 6;
      break;
    case 4:
      monthCode = 1;
      break;
    case 5:
      monthCode = 4;
      break;
    case 6:
      monthCode = 6;
      break;
    case 7:
      monthCode = 2;
      break;
    case 8:
      monthCode = 5;
      break;
    case 9:
      monthCode = 0;
      break;
    case 10:
      monthCode = 3;
      break;
    case 11:
      monthCode = 5;
      break;
    default:
      break;
  }
  
  if((year %4 ==0) && ((month == 0) ||(month == 1))){
    leapYearCode = 1;
  }
  
  timeInfo->tm_year = year - 1900;
  timeInfo->tm_mon = month;
  mktime(timeInfo);
  
  return dayOfWeek = (yearCode + monthCode + centuryCode + dayNum - leapYearCode)%7;
}
/**
  This global method stores a single month in a specific year within a string
  @param timeInfo a tm struct
  @param timeMeat a time_t
  @param calendarMonth a string representing one calendar month
  @param yearS a string storing a year in decimal
  @param month a string storing a month in decimal
  @param wday an integer value representing a weekday
  @param julian a boolean value that determines whether or not the date is a julian date
  @param realMonth an integer value representing a month
  @param realYear an integer value representing a year
  @param realDay an integer value representing a day
**/
string monthAndYear(struct tm *timeInfo, time_t timeMeat, string calendarMonth, string yearS, string month, int wday, bool julian, int realMonth, int realYear, int realDay){
  int yearI, monthI;
  stringstream(yearS) >> yearI;
  stringstream(month) >> monthI;
  monthI--;
  string september1752 = "   September 1752\nSu Mo Tu We Th Fr Sa/n       1  2 14 15 16\n17 18 19 20 21 22 23\n24 25 26 27 28 29 30";
  
  
  if(yearI < 1752){
    wday = convertJulian(yearI, monthI, timeInfo);
    julian = true;
    return oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
  }else if(yearI == 1752){
    if(monthI < 8){
      wday = convertJulian(yearI, monthI, timeInfo);
      julian = true;
      return oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
    }
    if(monthI == 8){
      return september1752;
    }
    if(monthI > 8){
      timeInfo->tm_year = yearI - 1900;
      timeInfo->tm_mon = monthI;
      mktime(timeInfo);
      return oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
    }
  }else{
    timeInfo->tm_year = yearI - 1900;
    timeInfo->tm_mon = monthI;
    mktime(timeInfo);
    return oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
  }
  string emptyString = "";
  return emptyString;
}
/**
  This method stores an entire year within a string and returns it.
  @param timeInfo a tm struct
  @param timeMeat a time_t
  @param calendarMonth a string representing one calendar month
  @param calendarYear a string representing a decimal year
  @param yearS a string storing a year in decimal year
  @param wday an integer value representing a weekday
  @param julian a boolean value that determines whether or not the date is a julian date
  @param realMonth an integer value representing a month
  @param realYear an integer value representing a year
  @param realDay an integer value representing a day
**/
string oneYear(struct tm *timeInfo, time_t timeMeat, string calendarMonth, string calendarYear, string yearS, int wday, bool julian, int realMonth, int realYear, int realDay){
  int yearI;
  stringstream(yearS) >> yearI;
  timeInfo->tm_year = yearI - 1900;
  mktime(timeInfo);
  int countJ = 0;
  calendarYear += "\t" + yearS + "\n";
  
  string september1752 = "   September 1752\nSu Mo Tu We Th Fr Sa\n       1  2 14 15 16\n17 18 19 20 21 22 23\n24 25 26 27 28 29 30\n";
  
  if(yearI < 1752){
    julian = true;
    while(countJ < 12){
      wday = convertJulian(yearI, countJ, timeInfo);
      calendarYear += oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
      calendarYear += "\n";
      countJ++;
    }
  }else if(yearI == 1752){
    julian = true;
    while(countJ < 12){
      if(countJ <= 8){
        wday = convertJulian(yearI, countJ, timeInfo);
        julian = true;
      }else{
        julian = false; 
        timeInfo->tm_year = yearI - 1900;
        timeInfo->tm_mon = countJ;
        mktime(timeInfo);
      }
      if(countJ == 8){
        calendarYear += september1752;
      }else{
        calendarYear += oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);      
      }
      calendarYear += "\n";
      countJ++;
    }
  }else{
    int count = 0;
    while(count < 12){
      timeInfo->tm_mon = count;
      calendarYear += oneMonth(timeInfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay);
      calendarYear += "\n";
      count++;
    }
  }
  return calendarYear;
  
}
/**
  The main method takes arguments from the console and outputs a certain date
  @param argc an integer value that represents a number of arguments
  @param argv an array of pointers to chars 
**/
int main(int argc, char * argv[]){
  cout.setf(ios::unitbuf);
  struct tm * timeinfo;
  time_t timeMeat;
  string calendarMonth = "", calendarYear = "";
  string month, argument = "";
  string yearS;
  bool julian = false;
  time(&timeMeat);
  timeinfo = localtime(&timeMeat);
  int wday = 0, realYear = timeinfo->tm_year, realMonth = timeinfo->tm_mon, realDay = timeinfo->tm_mday;
  if(argc > 1){
    argument = argv[1];
  }

  switch(argc){
    case 1:
      //works
      cout << oneMonth(timeinfo, timeMeat, calendarMonth, wday, julian, realMonth, realYear, realDay); 
      break;
    case 2:
      yearS = argv[1];
      cout << oneYear(timeinfo, timeMeat, calendarMonth, calendarYear, yearS, wday, julian, realMonth, realYear, realDay);
      break;
    case 3:
      month = argv[1];
      yearS = argv[2];
      
      cout << monthAndYear(timeinfo, timeMeat, calendarMonth, yearS, month, wday, julian, realMonth, realYear, realDay);
    default:
//      oneMonth(timeinfo, timeMeat, calendarMonth);
      break;
  
  }
}
