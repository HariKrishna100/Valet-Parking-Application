/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.cpp
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
#include <iostream>
#include <cstring>
#include "Vehicle.h"
#include "Utils.h"
using namespace std;
using namespace sdds;
namespace sdds {
   // no arguemnt constructor sets Vehicle empty
   Vehicle::Vehicle() : ReadWritable() {
      setEmpty();
   }

   // two argument constructor set license plate and vehicle model
   Vehicle::Vehicle(const char* plateCstr, const char* model) : ReadWritable() {
      if ((plateCstr != nullptr) && (plateCstr[0] != '\0') && (strlen(plateCstr) <= 8) && (model != nullptr) && (model[0] != '\0') && (strlen(model) >= 2)) {
         ut.strcpy(m_licensePlate, plateCstr);
         m_makeModel = ut.alcpy(model);
         m_parkingSpot = 0;
      }
      else {
         setEmpty();
      }
   }

   // copy constructor
   Vehicle::Vehicle(const Vehicle& toCopy) : ReadWritable() {
      operator=(toCopy);
   }

   // assignment operator
   Vehicle& Vehicle::operator=(const Vehicle& toCopy) {
      delete[] m_makeModel;
      setEmpty();
      if ((toCopy.m_licensePlate != nullptr) && (toCopy.m_licensePlate[0] != '\0') && (strlen(toCopy.m_licensePlate) <= 8) && (toCopy.m_licensePlate != nullptr) && (toCopy.m_licensePlate[0] != '\0') && (strlen(toCopy.m_licensePlate) >= 2)) {
         ut.strcpy(m_licensePlate, toCopy.m_licensePlate);
         m_makeModel = new char[strlen(toCopy.m_makeModel) + 1];
         ut.strcpy(m_makeModel, toCopy.m_makeModel);
         
         (toCopy.m_parkingSpot != 0) ? m_parkingSpot = toCopy.m_parkingSpot : m_parkingSpot = 0;
         (toCopy.isCsv()) ? setCsv(true) : setCsv(false);
      }
      else {
         m_licensePlate[0] = '\0';
         m_makeModel = nullptr;
         m_parkingSpot = 0;
      }
      return *this;
   }

   // destructor
   Vehicle::~Vehicle() {
      delete[] m_makeModel;
   }

   // sets Vehicle to empty
   void Vehicle::setEmpty() {
      m_licensePlate[0] = '\0';
      m_makeModel = nullptr;
      m_parkingSpot = 0;
   }

   // returns true if make and model is empty
   bool Vehicle::isEmpty()const {
      return (m_makeModel == nullptr);
   }

   // reads address of license plate string
   const char* Vehicle::getLicensePlate() {
      return m_licensePlate;
   }

   // reads address of make and model 
   const char* Vehicle::getMakeModel() {
      return m_makeModel;
   }

   // returns vehicles parking spot number
   int Vehicle::getParkingSpot() const {
      return m_parkingSpot;
   }

   // resets parking spot to a new value
   void Vehicle::setParkingSpot(int spotNo) {
      if (spotNo >= 0) {
         m_parkingSpot = spotNo;
      }
      else {
         setEmpty();
      }
   }

   // resets make and model to a new value
   void Vehicle::setMakeModel(const char* modelCstr) {
      if (modelCstr) {
         delete[] m_makeModel;
         m_makeModel = ut.alcpy(modelCstr);
      }
      else {
         setEmpty();
      }
   }

   // compares license plate of vehicle and with license plate value
   bool Vehicle::operator==(const char* plateCstr) {
      bool success = false;

      if (!isEmpty() && (plateCstr != nullptr && plateCstr[0] != '\0')) {
         if (ut.strcmp(m_licensePlate, plateCstr)) {
            success = true;
         }
      }
      return success;
   }

   // returns true if license plate match
   bool Vehicle::operator==(const Vehicle& V) {
      return operator==(V.m_licensePlate);
   }

   // reads data from file
   istream& Vehicle::read(istream& istr) {
      char modelCstr[100]{}, plateCstr[100]{};
      int spotNo = 0;
      bool success = false;

      if (isCsv()) {
         istr >> spotNo;
         setParkingSpot(spotNo);
         istr.ignore(1, ',');

         istr.getline(plateCstr, 8, ',');
         ut.toUpper(plateCstr);
         ut.strcpy(m_licensePlate, plateCstr);

         istr.getline(modelCstr, 60, ',');

         delete[] m_makeModel;
         m_makeModel = ut.alcpy(modelCstr);
      }
      else {
         cout << "Enter License Plate Number: ";
         do {
            istr >> plateCstr;
            istr.clear();

            if (strlen(plateCstr) == 0 || strlen(plateCstr) > 8) {
               cout << "Invalid License Plate, try again: ";
               success = false;
            }
            else {
               success = true;
            }
         } while (!success);

         ut.toUpper(plateCstr);
         ut.strcpy(m_licensePlate, plateCstr);

         success = false;

         cout << "Enter Make and Model: ";
         do {
            istr.ignore(1000, '\n');
            istr.getline(modelCstr, 60, '\n');
            if (strlen(modelCstr) < 2 ) {
               cout << strlen(modelCstr);
               cout << "Invalid Make and model, try again: ";
            }
            else {
               success = true;
            }
         } while (!success);

         delete[] m_makeModel;
         m_makeModel = ut.alcpy(modelCstr);
      }
      return istr;
   }

   // displays vehicle details
   ostream& Vehicle::write(ostream& ostr) const {
      if (isEmpty()) {
         ostr << "Invalid Vehicle Object" << endl;
      }
      else {
         writeType(ostr);
         if (isCsv()) {
            ostr << m_parkingSpot << "," << m_licensePlate << "," << m_makeModel << ",";
         }
         else {
            if (m_parkingSpot == 0) {
               ostr << "Parking Spot Number: N/A" << endl;
            }
            else {
               ostr << "Parking Spot Number: " << m_parkingSpot << endl;
            }
            ostr << "License Plate: " << m_licensePlate << endl;
            ostr << "Make and Model: " << m_makeModel << endl;
         }
      }
      return ostr;
   }
}