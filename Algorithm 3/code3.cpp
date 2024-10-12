//ALGORITHM 3: GROUP 9 CPSC 335-11
//Xareni Merino 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//------------------------------------------------------------------------------------
// Convert time to military time (minutes) to int
int convertToMilitaryTime(const string &time) {
  int hours = (time[0] - '0') * 10 + (time[1] - '0');
  int minutes = (time[3] - '0') * 10 + (time[4] - '0');
  return hours * 60 + minutes;
}
//------------------------------------------------------------------------------------

// Convert military time to string
string convertTimeToString(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;

    string hour;
    string min;

    // This is for Hours
    if (hours < 10) {
        hour = "0" + to_string(hours);
    } 
    else
    {
        hour = to_string(hours);
    }

    // This is for minutes
    if (mins < 10)
    {
        min = "0" + to_string(mins);
    } 
    else 
    {
        min = to_string(mins);
    }

    return hour + ":" + min;
}
//------------------------------------------------------------------------------------
// This function will combine the busy schedules from two people
vector<pair<int, int>>
combineBusySchedules(const vector<pair<int, int>> &firstSchedule,
                   const vector<pair<int, int>> &secondSchedule)
{
  vector<pair<int, int>> combined_Schedules = firstSchedule;

  // the program will add the second schedule to the combined_Schedules vector
  combined_Schedules.insert(combined_Schedules.end(), secondSchedule.begin(),
                         secondSchedule.end());

  // Sort by start times
  sort(combined_Schedules.begin(), combined_Schedules.end());

  // The following will get rid of any overlapping times
  vector<pair<int, int>> finalMerge;
    
  for (int i = 0; i < combined_Schedules.size(); i++)
      {
        pair<int, int> current = combined_Schedules[i];
      
        if (finalMerge.empty() || finalMerge.back().second < current.first) {
          finalMerge.push_back(current);
        }
        else 
        {
          finalMerge.back().second = max(finalMerge.back().second, current.second);
        }
  }

  return finalMerge;
}

//--------------------------------------------------------------------------------------------

// This vector function gets available slots based on merged schedules and daily availability
vector<pair<int, int>>
getAvailableSlots(const vector<pair<int, int>> &mergedSchedule,
                   pair<int, int> dailyAvailability, int duration) {
  vector<pair<int, int>> availableSlots;

  // Check for gaps between busy periods
  int startOfDay = dailyAvailability.first;
  int endOfDay = dailyAvailability.second;

  // Check for a gap between the start of the day and the first meeting
  if (!mergedSchedule.empty() &&
      mergedSchedule[0].first - startOfDay >= duration) {
    availableSlots.push_back({startOfDay, mergedSchedule[0].first});
  }

  // Check for gaps between meetings
  for (int i = 1; i < mergedSchedule.size(); i++) {
    int previousEndTime = mergedSchedule[i - 1].second;
    int currentStartTime = mergedSchedule[i].first;
    if (currentStartTime - previousEndTime >= duration) {
      availableSlots.push_back({previousEndTime, currentStartTime});
    }
  }

  // Check for a gap after the last meeting
  if (!mergedSchedule.empty() &&
      endOfDay - mergedSchedule.back().second >= duration) {
    availableSlots.push_back({mergedSchedule.back().second, endOfDay});
  }

    //This iteration of the available slots ensures they are within the daily availability of both people. 
    vector<pair<int, int>> Final_Slots;
    for (int i = 0; i < availableSlots.size(); i++)
        {
            int startTime = availableSlots[i].first;
            int endTime = availableSlots[i].second;
    
            // Ensure the available slot falls within the daily availability
            if (startTime >= startOfDay && endTime <= endOfDay)
            {
                Final_Slots.push_back({startTime, endTime});
            }
        }

    return Final_Slots;

}
//------------------------------------------------------------------------------------
// Main function to find available meeting times for two people
vector<pair<string, string>>
findAvailableMeetingTimes(const vector<pair<string, string>> &firstSchedule,
                          const vector<pair<string, string>> &secondSchedule,
                          const pair<string, string> &dailyAvailability1,
                          const pair<string, string> &dailyAvailability2,
                          int duration) 
{
  // Rewriting schedule inputs to military time (int)
  vector<pair<int, int>> MilitaryTime_firstSchedule;
  vector<pair<int, int>> MilitaryTime_secondSchedule;

  // rewrite first schedule to military time
  for (int i = 0; i < firstSchedule.size(); i++) 
  {
    int start = convertToMilitaryTime(firstSchedule[i].first);
    int end = convertToMilitaryTime(firstSchedule[i].second);
    MilitaryTime_firstSchedule.push_back(make_pair(start, end));
  }

  // rewrite second schedule to military time
  for (int i = 0; i < secondSchedule.size(); i++)
{
    int start = convertToMilitaryTime(secondSchedule[i].first);
    int end = convertToMilitaryTime(secondSchedule[i].second);
    MilitaryTime_secondSchedule.push_back(make_pair(start, end));
}

  // Calling combineBusySchedules to combine the two schedules
  vector<pair<int, int>> combined_Schedule =
      combineBusySchedules(MilitaryTime_firstSchedule, MilitaryTime_secondSchedule);

    //-----------------------------------------------------
  // The following code will find the intersection of daily availabilities from person1 and
  // person2

  // Convert the start times of the two people's daily availability to military
  // time
  int start1 = convertToMilitaryTime(dailyAvailability1.first);
  int start2 = convertToMilitaryTime(dailyAvailability2.first);

  // Determine the later start time
  int startAvailability;
  if (start1 > start2)
  {
    startAvailability = start1;
  } 
  else
  {
    startAvailability = start2;
  }

  // Convert the end times of both daily availabilities to minutes
  int end1 = convertToMilitaryTime(dailyAvailability1.second);
  int end2 = convertToMilitaryTime(dailyAvailability2.second);

  // Determine the earlier end time
    int endAvailability;
      if (end1 < end2)
      {
        endAvailability = end1;
      }
      else
      {
        endAvailability = end2;
      }

  // --------------------------------------------------------
    //the function will call getAvailabeSlots to find the available slots for both people
  vector<pair<int, int>> availableSlots = getAvailableSlots(
      combined_Schedule, make_pair(startAvailability, endAvailability), duration);

  // Convert available slots back to strings to print at the end of the main function. 
  vector<pair<string, string>> string_result;
  for (int i = 0; i < availableSlots.size(); i++)
      {
        string start = convertTimeToString(availableSlots[i].first);
        string end = convertTimeToString(availableSlots[i].second);
        string_result.push_back(make_pair(start, end));
      }

  return string_result;
    
}

//------------------------------------------------------------------------------------
 /*In the main function, two people's schedule and availability 
 are used to find available meeting times based on the meeting_duration criteria */
//------------------------------------------------------------------------------------
int main() {
  // Person 1's schedule and availability
  vector<pair<string, string>> person1_Schedule = {{"07:00", "08:30"}, {"12:00", "13:00"}, {"16:00", "18:00"}};
  pair<string, string> person1_DailyAct = {"09:00", "19:00"};

  // Person 2's schedule and availability
  vector<pair<string, string>> person2_Schedule = {{"09:00", "10:30"}, {"12:20", "13:30"},{"14:00", "15:00"},{"16:00", "17:00"}};
  pair<string, string> person2_DailyAct = {"09:00", "18:30"};

  // Meeting duration in minutes
  int meeting_duration = 30;

  // FindAvailabeMeetingTimes function is called!
  vector<pair<string, string>> availableTimes = findAvailableMeetingTimes(
      person1_Schedule, person2_Schedule, person1_DailyAct, person2_DailyAct,
      meeting_duration);

    // Output available times
    for (const pair<string, string> &time : availableTimes)
    {  
    cout << "[" << time.first << ", " << time.second << "]" << endl;
    }


  return 0;
}
