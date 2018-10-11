/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Mariah Ashley
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * 
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
struct HelpRequest
{
	bool emergency;    //looks for !! at the beginning of a request
	string course;     //which course the student need help with
	string firstName;  //holds the first name of the student
	int minutesNeeded; //how many minutes the student needs help
};

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   	// instructions
	cout << "Every prompt is one minute.  The following input is accepted:\n";
	cout << "\t<class> <name> <#minutes>    : a normal help request\n";
	cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
	cout << "\tnone                         : no new request this minute\n";
	cout << "\tfinished                     : end simulation\n";

   	//A deque called requests to hold instances of student request submissions
   	Deque <HelpRequest> requests;
   	//create an instance of the struct
   	HelpRequest request;
  
 	int runMinutes = 0; 				//start at 0 minutes
  	string command; 					//takes in the user's help request
  	HelpRequest currentStudent;     	//currently served student

 	currentStudent.minutesNeeded = 0; 	//track time for current student

  for(;;)
  {
      cout << "<" << runMinutes << "> "; 	//initial prompt
      cin >> command;

      if (command == "!!") //emergency help request
      {
          request.emergency = true;

      	  cin >> request.course; 
          cin >> request.firstName; 
          cin >> request.minutesNeeded;

          requests.push_front(request); //emergency requests go to the front of the queue
      }
      else if(command == "none"){ /*if no request is needed the user will enter none*/}
      else if(command == "finished")
      {
          break;
      }
      else//normal command
      {
	      request.emergency = false;
          request.course = command; 

          cin >> request.firstName; 
          cin >> request.minutesNeeded;

          requests.push_back(request); //normal requests go to the back of the queue
      }

      if(currentStudent.minutesNeeded <= 0 && !requests.empty())
      {
          //take the currently helped student out of hte queue so that emergency doesn't interrupt
          currentStudent = requests.front(); 
          requests.pop_front();
      }

      if(currentStudent.minutesNeeded > 0)
      {
          if(!currentStudent.emergency)
    	  {
    	      cout << "\tCurrently serving " 
    	           << currentStudent.firstName 
    			   << " for class " 
    			   << currentStudent.course
    			   << ". Time left: " 
    			   << currentStudent.minutesNeeded << endl;
    	  }
    	  else//if emergency
     	  {
    	      cout << "\tEmergency for " 
    			   << currentStudent.firstName 
    			   << " for class " 
    			   << currentStudent.course
    			   << ". Time left: " 
    			   << currentStudent.minutesNeeded << endl;
    	  }
       }
   currentStudent.minutesNeeded--; //Each command entered is 1 minute
   runMinutes++; //running total of minutes the program has been running
   }
   cout << "End of simulation\n";
}