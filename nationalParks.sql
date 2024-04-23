-- NATIONALPARKSDATABASE

-- drop database if exists nationalParks;
drop database nationalParks;

create database nationalParks;

use nationalParks;

-- drop table if exists parks;

CREATE TABLE parks (
  parkID int (40) not null,
  parkName varchar (40) not null,
  yearCreated int(4),
  state char(2),
  city varchar(25),
  numParkVisitors varchar(20),
  entryPrice decimal,
  PRIMARY KEY (parkID));

-- drop table if exists visitor;

CREATE TABLE visitor (
  visitorName varchar (40) not null,
  timesVisited int(4),
  email varchar(40),
  phoneNumber varchar(15),
  numVisitors int(4),
  parkID int (40) not null,
  PRIMARY KEY (visitorName),
  FOREIGN KEY (parkID) REFERENCES parks(parkID)); 

-- drop table if exists incidents;

CREATE TABLE incidents (
  incidentID int(10) not null,
  incidentName varchar (100),
  incidentTime varchar (50),
  incidentLocation varchar(55),
  injuryType varchar (30),
  parkID int (40) not null,
  PRIMARY KEY (incidentID),
  FOREIGN KEY (parkID) REFERENCES parks(parkID));

-- drop table if exists activities;

CREATE TABLE activities(
  activityID int (3) not null,
  activityName varchar (20),
  activityTime varchar (20),
  activityHost varchar (25),
  activityDays varchar (20),
  activityAge int(3),
  parkID int (40) not null,
  Primary Key (activityID),
  FOREIGN KEY (parkID) REFERENCES parks(parkID));

insert into parks values(1, 'Acadia',1919, 'ME', 'Mount Desert Island', '3,437,286', 35.0);
insert into parks values(2, 'Great Smoky Mountains', 1934, 'TN', 'Gatlinburg', '12,547,743', 5.0);
insert into parks values(3, 'Yosemite', 1934, 'CA', 'Sierra Nevada', '4,422,861', 25.0);
insert into parks values(4, 'Yellowstone', 1934, 'WY', 'Yellowstone', '4,020,288', 35.0);
insert into parks values(5, 'Everglades', 1904, 'FL', 'Orlando', '2,020,288', 65.0);

insert into visitor values('Taylor Sharperson', 4, 'taylor@gmail.com', '973-401-2233', 6, 4);
insert into visitor values('Annalise Keating', 5, 'annalaw@gmail.com', '908-505-3095', 1, 2);
insert into visitor values('Beyonce Carter', 1, 'beyhive@gmail.com', '404-223-3995', 20, 1);
insert into visitor values('Rihanna Knowles', 10, 'rih@gmail.com', '813-393-9853', 4, 3);
insert into visitor values('Ashley Carter', 40, 'ash@gmail.com', '803-393-2853', 5, 5);


insert into activities values(1, 'Hiking', '10:00', 'Park Rangers', 'Weekends', 12,3 );
insert into activities values(2, 'Camping', '9:00', 'Adventure Team', 'MWF', 8, 1);
insert into activities values(3, 'Fishing', '7:00', 'Fishing Team', 'Everyday', 5, 2);
insert into activities values(4, 'Canoeing', '14:00', 'Adventure Club', 'Saturdays', 18, 4);
insert into activities values(5, 'Rock Climbing', '2:00', 'Walking Club', 'Fridays', 20, 5);

insert into incidents values(1, 'Fall from cliff', '15:00', 'Trail C', 'Broken arm', 4);
insert into incidents values(2, 'Encounter with an animal', '13:00', 'Campground B', 'Cuts and bruises', 3);
insert into incidents values(3, 'Trip and fall', '9:00', 'Welcome Center', 'Sprained ankle', 2);
insert into incidents values(4, 'Caught in Wildfire', '18:00', 'Forest Trail', 'Smoke inhalation', 1);
insert into incidents values(4, 'Poision Ivy', '10:00', 'Forest Trail B', 'Itchy', 5);
