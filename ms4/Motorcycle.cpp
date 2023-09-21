/* Citation and Sources...
Final Project Milestone 4
Module: Motorcycle
Filename: Motorcycle.cpp
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
#include "Motorcycle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
   // no argument constructor set motorcycle to empty
   Motorcycle::Motorcycle(): Vehicle() {
      m_hasSideCarFlag = false;
   }

   // two argument constructor to create motorcycle as vehicle
   Motorcycle::Motorcycle(const char* plateCstr, const char* model): Vehicle(plateCstr, model) {
      m_hasSideCarFlag = false;
   }

   // copy constructor
   Motorcycle::Motorcycle(const Motorcycle& toCopy) {
      operator=(toCopy);
   }

   // virtual destructor
   Motorcycle::~Motorcycle() {

   }

   // assign motorcycle to another car
   Motorcycle& Motorcycle::operator=(const Motorcycle& toCopy) {
      if (&toCopy) {
         (Vehicle&)(*this) = toCopy;
         (toCopy.m_hasSideCarFlag) ? m_hasSideCarFlag = true : m_hasSideCarFlag = false;
      }
      return *this;
   }

   // write depending on object formart
   std::ostream& Motorcycle::writeType(std::ostream& ostr) const {
      if (isCsv()) {
         ostr << "M,";
      }
      else {
         ostr << "Vehicle type: Motorcycle" << endl;
      }
      return ostr;
   }

   // read depending on comma separated mode
   std::istream& Motorcycle::read(std::istream& istr) {
      if (isCsv()) {
         Vehicle::read(istr);
         istr >> m_hasSideCarFlag;
         istr.ignore(1000, '\n');
      }
      else {
         cout << endl;
         cout << "Motorcycle information entry" << endl;
         Vehicle::read(istr);
         cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
         m_hasSideCarFlag = ut.yes(istr);
      }
      return istr;
   }

   // display Motorcycle details
   std::ostream& Motorcycle::write(std::ostream& ostr) const {
      if (isEmpty()) {
         ostr << "Invalid Motorcycle Object" << endl;
      }
      else {
         Vehicle::write(ostr);
         if (isCsv()) {
            ostr << m_hasSideCarFlag << endl;
         }
         else {
            if (m_hasSideCarFlag) ostr << "With Sidecar" << endl;
         }
      }
      return ostr;
   }
}