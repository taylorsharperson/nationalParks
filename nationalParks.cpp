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
// g++ -I/usr/include nationalParks.cpp -o nationalParks-I /usr/local/lib -lmysqlcppconn
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
void findallVisitors();
void findallIncidents();
void findbyparkID();
void findbyActivity();
void oldestPark();
void insertPark();
void deletePark();
void deleteVisitors();
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
 
 while (option != 13) {
     
     cout << endl;
     cout << "1. Show all Parks" << endl;
     cout << "2. Show all Visitors" << endl;
     cout << "3. Show all Incidents" << endl;
     cout << "4. Show all Activities" << endl;
     cout << "5. Find by Park ID" << endl;
     cout << "6. Find by Activity ID" << endl;
     cout << "7. Find the oldest park" << endl;
     cout << "8. Add a park" << endl;
     cout << "9. Delete a park" << endl;
     cout << "10. Delete a visitor" << endl;
     cout << "11. Add a visitor" << endl;
     cout << "12. Total number of parks" << endl;
     cout << "13. Exit" << endl << endl;
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
        
	case 1: findallParks();
		break;
        case 2: findallActivities();
                 break;
	case 3: findallVisitors();
		break;
        case 4: findallIncidents();
                 break;
        case 5: findbyparkID();
                 break;
        case 6: findbyActivity();
                 break;
        case 7: oldestPark();
                 break;
        case 8: insertPark();
                 break;
        case 9: deletePark();
                 break;
        case 10: deleteVisitors();
                 break;
        case 11: updateVisitors();
                 break;
        case 12: getTotalParks();
                 break;
        case 13: break;  
             
     }
 }
 
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
        
				 case 1: insertPark();
				         break;

         case 2: findbyparkID();
                 break;

				case 3: findbyActivity();
				         break;
             
         case 4: findallParks();
                 break;

         case 5: deletePark();
                 break;

          case 6: break;  
             
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

 void insertPark() {

int parkID, yearCreated, numParkVisitors;
string entryPrice, parkName, state, city;
    
 cout << "Enter park ID: ";
 cin >> parkID;
 
 cout << "Enter park name: ";
 cin >> parkName;
 
 cout << "Enter year created: ";
 cin >> yearCreated;

 cout << " Enter the state: ";
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

void findbyActivity() {

int activityID;
    
 cout << "Enter the activity ID: ";
 cin >> activityID;
    
prep_stmt = con->prepareStatement("SELECT activities.activityID, activities.activityName, activities.activityTime, activities.activityDays, activities.activityAge, parks.parkID" 
                                          "FROM activities join parks" 
                                          " USING activities.parkID = parks.parkID ");
prep_stmt->setInt(1, activityID);
res = prep_stmt->executeQuery();

 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("activityName") << " ";
     cout << res->getString("activityTime") << " ";
     cout << res->getString("activityDays") << " ";
     cout << res->getString("activityAge") << " ";
     cout << res->getInt("activityID") << " " << endl;

 } }

void deletePark(){
    int parkID;

    cout << "Enter the park ID you want to delete: ";
    cin >> parkID;

    prep_stmt = con->prepareStatement("DELETE FROM parks WHERE parkID=?");
    prep_stmt->setInt(1, parkID);

    prep_stmt->execute();
    cout << "Park ID " << parkID << " deleted." << endl;
}
