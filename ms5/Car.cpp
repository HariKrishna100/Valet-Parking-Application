/* Citation and Sources...
Final Project Milestone 5
Module: Car
Filename: Car.cpp
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
#include "Vehicle.h"
#include "Car.h"
#include "Utils.h"
using namespace std;
namespace sdds {
   // no argument constructor set car to empty
   Car::Car() : Vehicle() {
      m_carWashFlag = false;
   }

   // two argument constructor to create car as vehicle
   Car::Car(const char* plateCstr, const char* model) : Vehicle(plateCstr, model) {
      m_carWashFlag = false;
   }

   // copy constructor 
   Car::Car(const Car& toCopy) {
      operator=(toCopy);
   }

   // assign car to another car
   Car& Car::operator=(const Car& toCopy) {
      if (&toCopy != this) {
         (Vehicle&)(*this) = (toCopy);
         (toCopy.m_carWashFlag) ? m_carWashFlag = true : m_carWashFlag = false;
      }
      return *this;
   }

   // virtual destructor
   Car::~Car() {

   }

   // write depending on object formart
   std::ostream& Car::writeType(std::ostream& ostr) const {
      if (isCsv()) {
         ostr << "C,";
      }
      else {
         ostr << "Vehicle type: Car" << endl;
      }
      return ostr;
   }

   // read depending on comma separated mode
   istream& Car::read(std::istream& istr) {
      if (isCsv()) {
         Vehicle::read(istr);
         istr >> m_carWashFlag;
         istr.ignore(1000, '\n');
      }
      else {
         cout << endl;
         cout << "Car information entry" << endl;
         Vehicle::read(istr);
         cout << "Carwash while parked? (Y)es/(N)o: ";
         m_carWashFlag = ut.yes(istr);
      }
      return istr;
   }

   // display Car details
   ostream& Car::write(std::ostream& ostr) const {
      if (isEmpty()) {
         ostr << "Invalid Car Object" << endl;
      }
      else {
         Vehicle::write(ostr);
         if (isCsv()) {
            ostr << m_carWashFlag << endl;
         }
         else {
            (m_carWashFlag) ? ostr << "With Carwash" << endl : ostr << "Without Carwash" << endl;
         }
      }
      return ostr;
   }
}