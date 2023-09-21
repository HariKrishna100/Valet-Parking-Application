/* Citation and Sources...
Final Project Milestone 2
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
#include"Parking.h"
#include "Utils.h"
using namespace std;
namespace sdds {
   Parking::Parking() {
      setEmpty();
   }

   Parking::Parking(const char* datafile) {
      if (datafile && datafile[0]) {
         m_filename = new char[strlen(datafile) + 1];
         strcpy(m_filename, datafile);

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
      }
   }

   Parking::~Parking() {
      saveData();
      delete[] m_filename;
      delete m_parkingMenu;
      delete m_vehicleMenu;
   }

   int Parking::run() {
      int success = true, selection;
      if (!isEmpty()) {
         while (success) {
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
               if (closeParking()) return success;
               break;
            case 6:
               if (exitParking()) return success;
               break;
            }
         }
      }
      return 0;
   }

   bool Parking::isEmpty() const {
      return (m_filename == nullptr);
   }

   void Parking::parkingStatus() {
      cout << "****** Valet Parking ******" << endl;
   }

   void Parking::parkVehicle() {
      int selection = m_vehicleMenu->run();
      switch (selection)
      {
      case 1:
         cout << "---------------------------------" << endl;
         cout << "Parking Car" << endl;
         cout << "---------------------------------" << endl << endl;
         break;
      case 2:
         cout << "---------------------------------" << endl;
         cout << "Parking Motorcycle" << endl;
         cout << "---------------------------------" << endl << endl;
         break;
      case 3:
         cout << "---------------------------------" << endl;
         cout << "Cancelled parking" << endl;
         cout << "---------------------------------" << endl << endl;
         break;
      }
   }

   void Parking::returnVehicle() {
      cout << "---------------------------------" << endl;
      cout << "Returning Vehicle" << endl;
      cout << "---------------------------------" << endl << endl;
   }

   void Parking::parkedVehicles() {
      cout << "---------------------------------" << endl;
      cout << "Listing Parked Vehicles" << endl;
      cout << "---------------------------------" << endl << endl;
   }

   void Parking::findVehicle() {
      cout << "---------------------------------" << endl;
      cout << "Finding a Vehicle" << endl;
      cout << "---------------------------------" << endl << endl;
   }

   bool Parking::closeParking() {
      bool close = false;
      cout << "This will close the parking; All the vehicles will be removed!" << endl;
      cout << "Are you sure? (Y)es/(N)o: ";
      if (confirmation()) {
         cout << "Ending application!" << endl;
         close = true;
      }
      return close;
   }

   bool Parking::exitParking() {
      bool exit = false;
      cout << "This will terminate the application and save the data!" << endl;
      cout << "Are you sure? (Y)es/(N)o: ";
      if (confirmation()) {
         cout << "Exiting application!" << endl;
         exit = true;
      }
      return exit;
   }

   bool Parking::loadData() {
      bool success = true;
      if (!isEmpty()) {
         cout << "---------------------------------" << endl;
         cout << "loading data from " << m_filename << endl;
         cout << "---------------------------------" << endl << endl;
      }
      else {
         success = false;
      }
      return success;
   }

   void Parking::saveData() {
      if (!isEmpty()) {
         cout << "---------------------------------" << endl;
         cout << "Saving data into " << m_filename << endl;
         cout << "---------------------------------" << endl << endl;
      }
   }

   void Parking::setEmpty() {
      m_filename = nullptr;
      m_parkingMenu = nullptr;
      m_vehicleMenu = nullptr;
   }
}