/* Citation and Sources...
Final Project Milestone 5
Module: Parking
Filename: Parking.h
Version 1.0
Author	Harikrishna Paresh Patel
Revision History
-----------------------------------------------------------
Date      Reason
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Parking.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
   // no argument constructor set parking to empty
   Parking::Parking() {
      setEmpty();
      for (int i = 0; i < MAX_NO_OF_SPOTS; i++) {
         m_parkingSpots[i] = nullptr;
      }
      m_noOfSpots = 0;
      m_noOfVehicles = 0;
   }

   // two argument constructor to set parking spot and get file name to be read
   Parking::Parking(const char* datafile, int spots) {
      for (int i = 0; i < MAX_NO_OF_SPOTS; i++) {
         m_parkingSpots[i] = nullptr;
      }
      m_noOfVehicles = 0;

      if (datafile && datafile[0] && !(spots < 10 && spots > MAX_NO_OF_SPOTS)) {
         m_noOfSpots = spots;
         m_filename = ut.alcpy(datafile);

         if (loadData()) {
            // add to parking menu
            m_parkingMenu = new Menu("Parking Menu, select an action:");
            m_parkingMenu->add("Park Vehicle");
            m_parkingMenu->add("Return Vehicle");
            m_parkingMenu->add("List Parked Vehicles");
            m_parkingMenu->add("Find Vehicle");
            m_parkingMenu->add("Close Parking (End of day)");
            m_parkingMenu->add("Exit Program");

            // add to veicle menu
            m_vehicleMenu = new Menu("Select type of the vehicle:", 1);
            m_vehicleMenu->add("Car");
            m_vehicleMenu->add("Motorcycle");
            m_vehicleMenu->add("Cancel");
         }
         else {
            m_parkingMenu = nullptr;
            m_vehicleMenu = nullptr;
         }
      }
      else {
         cout << "Error in data file" << endl;
         setEmpty();
         m_noOfSpots = 0;
      }
   }

   // destructor
   Parking::~Parking() {
      saveData();
      delete[] m_filename;
      delete m_parkingMenu;
      delete m_vehicleMenu;
      for (int i = 0; i < m_noOfSpots; i++) {
         delete m_parkingSpots[i];
      }
      setEmpty();
   }

   // menuitem selection
   int Parking::run() {
      int selection;
      int exit = 0;

      while (!exit) {
         parkingStatus();
         selection = m_parkingMenu->run();
         switch (selection)
         {
         case 1:
            parkVehicle();
            break;
         case 2:
            returnVehicle();
            break;
         case 3:
            parkedVehicles();
            break;
         case 4:
            findVehicle();
            break;
         case 5:
            exit = closeParking();
            break;
         case 6:
            exit = exitParking();
            break;
         }
      }
      return exit;
   }

   // return true if file is empty
   bool Parking::isEmpty() const {
      return (m_filename == nullptr);
   }

   // display parking status
   void Parking::parkingStatus() {
      cout << "****** Valet Parking ******" << endl;
      cout << "*****  Available spots: ";
      cout.width(4);
      cout.setf(ios::left);
      cout << (m_noOfSpots - m_noOfVehicles);
      cout.unsetf(ios::left);
      cout << " *****" << endl;
   }

   // displays vehicle selection menu items
   // sets comma separated bool to read data from file
   void Parking::parkVehicle() {
      Vehicle* vehicle{};
      bool success = false;
      if (m_noOfVehicles == m_noOfSpots) {
         cout << "Parking is full" << endl;
      }
      else {
         int selection = m_vehicleMenu->run();
         switch (selection)
         {
         case 1:
            vehicle = new Car();
            break;
         case 2:
            vehicle = new Motorcycle();
            break;
         case 3:
            cout << "Cancelled parking" << endl;
            return;
         }
         vehicle->setCsv(false);
         cin >> *vehicle;
         for (int i = 0; i < m_noOfSpots && !success; i++) {
            if (m_parkingSpots[i] == nullptr) {
               vehicle->setParkingSpot(i + 1);
               m_parkingSpots[i] = vehicle;
               m_noOfVehicles++;
               cout << endl;
               cout << "Parking Ticket" << endl;
               cout << *vehicle;
               success = true;
            }
         }
      }
      cin.ignore();
      cout << "Press <ENTER> to continue....";
      cin.ignore(1000, '\n');
   }

   // gets license plate from user and searchs for parked vehicle and removes vehicle from parking
   void Parking::returnVehicle() {
      bool success = false;
      char plateCstr[100]{};

      cout << "Return Vehicle" << endl;
      cout << "Enter License Plate Number: ";
      while (!success) {
         cin.clear();
         cin >> plateCstr;
         
         if (strlen(plateCstr) > 8) {
            cout << "Invalid License Plate, try again: ";
         }
         else {
            success = true;
         }
      }

      bool spots = false;

      ut.toUpper(plateCstr);

      for (int i = 0; i < m_noOfSpots && !spots; i++) {
         if (m_parkingSpots[i] && (*m_parkingSpots[i] == plateCstr)) {
            spots = true;
            cout << endl;
            cout << "Returning:" << endl;
            m_parkingSpots[i]->setCsv(false);
            cout << *m_parkingSpots[i];
            delete m_parkingSpots[i];
            m_parkingSpots[i] = nullptr;
            m_noOfVehicles--;
         }
      }
      if (!spots) {
         cout << endl;
         cout << "License plate " << plateCstr << " Not found" << endl;
      }
      cin.ignore();
      cout << endl;
      cout << "Press <ENTER> to continue....";
      cin.ignore(1000, '\n');
   }

   // prints all vehicles from parking lot
   void Parking::parkedVehicles() {
      cout << "*** List of parked vehicles ***" << endl;
      for (int i = 0; i < m_noOfSpots; i++) {
         if (m_parkingSpots[i] != nullptr) {
            m_parkingSpots[i]->setCsv(false);
            cout << *m_parkingSpots[i];
            cout << "-------------------------------" << endl;
         }
      }
      cout << "Press <ENTER> to continue....";
      cin.ignore(1000, '\n');
   }

   // gets vehicle plate number and searches for it in parking lot
   void Parking::findVehicle() {
      char plateCstr[100]{};
      bool success = false;

      cout << "Vehicle Search" << endl;
      cout << "Enter License Plate Number: ";
      while (!success) {
         cin.clear();
         cin >> plateCstr;
         if (strlen(plateCstr) > 8) {
            cout << "Invalid License Plate, try again: ";
         }
         else {
            success = true;
         }
      }

      ut.toUpper(plateCstr);

      bool spots = false;
      for (int i = 0; i < m_noOfSpots && !spots; i++) {
         if (m_parkingSpots[i] && (*m_parkingSpots[i] == plateCstr)) {
            spots = true;
            m_parkingSpots[i]->setCsv(false);
            cout << endl;
            cout << "Vehicle found:" << endl;
            cout << *m_parkingSpots[i];
         }
      }
      if (!spots) {
         cout << endl;
         cout << "License plate " << plateCstr << " Not found" << endl;
      }
      cin.ignore();
      cout << endl;
      cout << "Press <ENTER> to continue....";
      cin.ignore(1000, '\n');
   }

   // if parking has no vehicles parking is closed
   // if there are vehicles and user doesn't remove vehicle from parking lot 
   // vehicle is towed and ticket is issued
   bool Parking::closeParking() {
      bool close = false;
      if (isEmpty()) {
         cout << "Closing Parking" << endl;
         return true;
      }
      else {
         cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
         cout << "Are you sure? (Y)es/(N)o: ";
         if (ut.yes()) {
            cout << "Closing Parking" << endl;
            for (int i = 0; i < m_noOfSpots; i++) {
               if (m_parkingSpots[i] != nullptr) {
                  cout << endl;
                  cout << "Towing request" << endl;
                  cout << "*********************" << endl;
                  m_parkingSpots[i]->setCsv(false);
                  cout << *m_parkingSpots[i];
                  delete m_parkingSpots[i];
                  m_parkingSpots[i] = nullptr;
               }
            }
            close = true;
         }
      }
      return close;
   }

   // exit option
   bool Parking::exitParking() {
      bool exit = false;
      cout << "This will terminate the program!" << endl;
      cout << "Are you sure? (Y)es/(N)o: ";
      if (ut.yes()) {
         cout << "Exiting program!" << endl;
         exit = true;
      }
      return exit;
   }

   // if not empty gets data from file and returns true
   bool Parking::loadData() {
      bool success = true;
      bool read = true;
      if (isEmpty()) {
         success = false;
      }
      else {
         ifstream file;
         file.open(m_filename);
         Vehicle* v{};
         m_noOfVehicles = 0;

         while (read) {
            char type= '\0';
            file.get(type);
            file.ignore();

            if (type == 'C') {
               v = new Car();
            }
            else if (type == 'M') {
               v = new Motorcycle();
            }
            else {
               break;
            }

            v->setCsv(true);
            file >> *v;
            m_parkingSpots[v->getParkingSpot() - 1] = v;
            m_noOfVehicles++;
            if (m_noOfVehicles >= m_noOfSpots) {
               success = false;
            }
         } 
         file.close();
      }
      return success;
   }

   // saves vehicle in data file
   void Parking::saveData() {
      if (!isEmpty()) {
         ofstream file;
         file.open(m_filename);
         if (file.is_open()) {
            for (int i = 0; i < m_noOfSpots; i++) {
               if (m_parkingSpots[i]) {
                  m_parkingSpots[i]->setCsv(true);
                  file << *m_parkingSpots[i];
                  file.flush();
               }
            }
            file.close();
         }
      }
   }

   // sets parking to empty state
   void Parking::setEmpty() {
      m_filename = nullptr;
      m_parkingMenu = nullptr;
      m_vehicleMenu = nullptr;
   }
}