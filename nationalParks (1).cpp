#include <stdlib.h>
#include <iostream>
#include <string>
/*
 Include directly the different
 headers from cppconn/ and mysql_driver.h + mysql_util.h
 (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

// This program retrieves all of the nationalParks

// Compile:
// g++ -I/usr/include nationalParks.cpp -o nationalParks -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./nationalParks
// 
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 sql::PreparedStatement  *prep_stmt;

void findallParks();
void findallActivities();
void findcertainActivities();
void findallVisitors();
void findallIncidents();
void findbyparkID();
void findactivitybyParks();
void oldestPark();
void insertPark();
void deletePark();
void deleteVisitors();
void insertVisitors();
void updateVisitors();
void getTotalParks();


int main(void)
{

try {

   
 /* Create a connection */
 driver = get_driver_instance();

  
con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL music database */
    
 con->setSchema("nationalParks");
 //stmt = con->createStatement();
    
 int option = 14;
 
 while (option != 15) {
     
     cout << endl;
     cout << "1. Show all Parks" << endl;
     cout << "2. Show all Visitors" << endl;
     cout << "3. Show all Incidents" << endl;
     cout << "4. Show all Activities" << endl;
     cout << "5. Show certain Activity" << endl;
     cout << "6. Find by Park ID" << endl;
     cout << "7. Find Activities and Parks" << endl;
     cout << "8. Find the oldest park" << endl;
     cout << "9. Add a park" << endl;
     cout << "10. Delete a park" << endl;
     cout << "11. Delete a visitor" << endl;
     cout << "12. Add a visitor" << endl;
     cout << "13. Update a visitor" << endl;
     cout << "14. Total number of parks" << endl;
     cout << "15. Exit" << endl << endl;
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
        
		case 1: findallParks();
		        		break;
    case 2: findallVisitors();
                 break;
		case 3: findallIncidents();
				         break;
    case 4: findallActivities();
                 break;
    case 5: findcertainActivities();
                break;
    case 6: findbyparkID();
                break;
    case 7: findactivitybyParks();
                 break;
    case 8: oldestPark();
                 break;
    case 9: insertPark();
                break;
    case 10: deletePark();
                 break;
    case 11: deleteVisitors();
                 break;
    case 12: insertVisitors();
                 break;
    case 13: updateVisitors();
                 break;
    case 14: getTotalParks();
                 break;
    case 15:     break;  
             
     }
 }
 

 delete res;
 delete stmt;
 delete con;
} catch (sql::SQLException &e) {
 cout << "# ERR: SQLException in " << __FILE__;
 cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
 cout << "# ERR: " << e.what();
 cout << " (MySQL error code: " << e.getErrorCode();
 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
cout << endl;
return EXIT_SUCCESS;

}

 void findallParks() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from parks");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("parkID") << " ";
     cout << res->getString("parkName") << " ";
     cout << res->getString("yearCreated") << " ";
     cout << res->getString("state") << " ";
     cout << res->getString("city") << " ";
     cout << res->getString("numParkVisitors") << " ";
     cout << res->getString("entryPrice") << endl;
 }
     
 }

void findallActivities() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from activities");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("activityID") << " ";
     cout << res->getString("activityName") << " ";
     cout << res->getString("activityTime") << " ";
     cout << res->getString("activityHost") << " ";
     cout << res->getString("activityDays") << " ";
     cout << res->getString("activityAge") << " ";
     cout << res->getString("parkID") << endl;
 }
     
 }

 void findcertainActivities() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from activities WHERE (activityID = 1) && (activityAge > 11)");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("activityID") << " ";
     cout << res->getString("activityName") << " ";
     cout << res->getString("activityTime") << " ";
     cout << res->getString("activityHost") << " ";
     cout << res->getString("activityDays") << " ";
     cout << res->getString("activityAge") << " ";
     cout << res->getString("parkID") << endl;
 }
     
 }

void findallVisitors() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from visitor");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("visitorName") << " ";
     cout << res->getString("timesVisited") << " ";
     cout << res->getString("email") << " ";
     cout << res->getString("phoneNumber") << " ";
     cout << res->getString("numVisitors") << " ";
     cout << res->getString("parkID") << endl;

 }
     
 }
void findallIncidents() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from incidents");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("incidentID") << " ";
     cout << res->getString("incidentName") << " ";
     cout << res->getString("incidentTime") << " ";
     cout << res->getString("incidentLocation") << " ";
     cout << res->getString("injuryType") << " ";
     cout << res->getString("parkID") << endl;
 }
     
 }
 void findbyparkID() {
     
 int parkID;
    
 cout << "Enter the park ID: ";
 cin >> parkID;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM parks WHERE parkID = ?");
prep_stmt->setInt(1, parkID);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("parkID") << " ";
     cout << res->getString("parkName") << " ";
     cout << res->getString("yearCreated") << " ";
     cout << res->getString("state") << " ";
     cout << res->getString("city") << " ";
     cout << res->getString("numParkVisitors") << " ";
     cout << res->getString("entryPrice") << endl;
 
 }
     
 }
void findactivitybyParks() {
//int activityID;
//cout << "Enter the activity ID: ";
//cin >> activityID;
    
prep_stmt = con->prepareStatement("SELECT activities.activityID, activities.activityName, activities.activityHost, activities.activityTime, activities.activityDays, activities.activityAge, parks.parkName, parks.parkID FROM activities JOIN parks ON (parks.parkID = activities.parkID)");
//prep_stmt->setInt(1, activityID);
res = prep_stmt->executeQuery();

 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("activityID") << " ";
     cout << res->getString("activityName") << " ";
     cout << res->getString("activityTime") << " ";
     cout << res->getString("activityHost") << " ";
     cout << res->getString("activityDays") << " ";
     cout << res->getInt("parkID") << " ";
     cout << res->getString("parkName") << " ";
     cout << res->getInt("activityAge") << " " << endl;

 } }

void oldestPark(){
string parkName;
int yearCreated;
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT parkName, min(yearCreated) AS minyear from parks");
 if (res->next()) {

 /* Access column data by alias or column name */
     
     //cout << res->getString("parkName") << " ";
     cout << res->getString("minyear") << " ";
 

 } 

 //cout << "The oldest park is: " << parkName << " in " << minyear;
}

void insertPark() {

int parkID, yearCreated, numParkVisitors;
string entryPrice, parkName, state, city;
    
 cout << "Enter park ID: ";
 cin >> parkID;
 
 cout << "Enter park name: ";
 cin >> parkName;
 
 cout << "Enter year created: ";
 cin >> yearCreated;

 cout << "Enter the state: ";
 cin >> state;

 cout << "Enter the city: ";
 cin >> city;

 cout << "How many park visitors: ";
 cin >> numParkVisitors;

 cout << "Enter price of admission: ";
 cin >> entryPrice;
 
prep_stmt = con->prepareStatement("INSERT INTO parks (parkID, parkName, yearCreated, state, city, numParkVisitors, entryPrice) " \
                                   "VALUES(?,?,?,?,?,?,?) ");
                                                                                                  
prep_stmt->setInt(1, parkID);
prep_stmt->setString(2, parkName);
prep_stmt->setInt(3, yearCreated);
prep_stmt->setString(4, state);
prep_stmt->setString(5, city);
prep_stmt->setInt(6, numParkVisitors);
prep_stmt->setString(7, entryPrice);


prep_stmt->execute();

}

void deletePark(){
    int parkID;

    cout << "Enter the park ID you want to delete: ";
    cin >> parkID;

    prep_stmt = con->prepareStatement("DELETE FROM parks WHERE parkID=?");
    prep_stmt->setInt(1, parkID);

    prep_stmt->execute();
    cout << "Park ID " << parkID << " deleted." << endl;
}

void deleteVisitors(){
    int visitorID;
    string visitorName;

    cout << "Enter the visitor ID you want to delete: ";
    cin >> visitorID;

    prep_stmt = con->prepareStatement("DELETE FROM visitor WHERE visitorID=?");
    prep_stmt->setInt(1, visitorID);

    prep_stmt->execute();
    cout << "Visitor: " << visitorID << " deleted." << endl;
}


void insertVisitors() {

int timesVisited, numVisitors, visitorID, parkID;
string visitorName, email, phoneNumber;

 cout << "Enter Visitor ID: ";
 cin >> visitorID;  

 cout << "Enter visitor name: ";
 cin >> visitorName;
 
 cout << "Enter times visited: ";
 cin >> timesVisited;
 
 cout << "Enter email: ";
 cin >> email;

 cout << "Enter phone number: ";
 cin >> phoneNumber;

 cout << "Enter number of visitors: ";
 cin >> numVisitors;

 cout << "Enter park ID: ";
 cin >> parkID;
 
prep_stmt = con->prepareStatement("INSERT INTO visitor (visitorID, visitorName, timesVisited, email, phoneNumber, numVisitors, parkID) " \
                                   "VALUES(?,?,?,?,?,?,?) ");

prep_stmt->setInt(1, visitorID);                                                                                                 
prep_stmt->setString(2, visitorName);
prep_stmt->setInt(3, timesVisited);
prep_stmt->setString(4, email);
prep_stmt->setString(5, phoneNumber);
prep_stmt->setInt(6, numVisitors);
prep_stmt->setInt(7, parkID);

prep_stmt->execute();

cout << "Visitor Added." << endl;

}

void updateVisitors(){
int timesVisited, numVisitors, visitorID, parkID;
string visitorName, email, phoneNumber;

 cout << "Enter visitor ID you want to update: ";
 cin >> visitorID;

 cout << "Update visitor name: ";
 cin >> visitorName;

 cout << "Update times visited: ";
 cin >> timesVisited;
 
 cout << "Update email: ";
 cin >> email;

 cout << "Update phone number: ";
 cin >> phoneNumber;

 cout << "Update number of visitors: ";
 cin >> numVisitors;

 cout << "Enter park ID: ";
 cin >> parkID;

prep_stmt = con->prepareStatement("UPDATE visitor "
                                      "SET visitorName=?, timesVisited=?, email=?, phoneNumber=?, numVisitors=?, parkID=? " \
                                      "WHERE visitorID=?");

prep_stmt->setString(1, visitorName);
prep_stmt->setInt(2, timesVisited);
prep_stmt->setString(3, email);
prep_stmt->setString(4, phoneNumber);
prep_stmt->setInt(5, numVisitors);
prep_stmt->setInt(6, parkID);
prep_stmt->setInt(7, visitorID);

prep_stmt->execute();

cout << "Visitor Updated." << endl;
}

void getTotalParks(){
    prep_stmt = con->prepareStatement("SELECT COUNT(parkID) from parks");
    res = prep_stmt->executeQuery();
    
 /* Access column data by alias or column name */
     if (res->next()) {
        cout << "Total number of parks: " << res->getInt("COUNT(parkID)") << endl;
    }
}