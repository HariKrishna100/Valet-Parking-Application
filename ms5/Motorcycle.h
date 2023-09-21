/* Citation and Sources...
Final Project Milestone 5
Module: Motorcycle
Filename: Motorcycle.h
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
#ifndef SDDS_MOTORCYCLE_H_
#define SDDS_MOTORCYCLE_H_
#include <iostream>
#include "Vehicle.h"
namespace sdds {
   class Motorcycle : public Vehicle {
      bool m_hasSideCarFlag;
   public:
      Motorcycle();
      Motorcycle(const char* plateCstr, const char* model);
      Motorcycle(const Motorcycle& toCopy);
      virtual ~Motorcycle();
      Motorcycle& operator=(const Motorcycle& toCopy);
      std::ostream& writeType(std::ostream& ostr)const;
      std::istream& read(std::istream& istr);
      std::ostream& write(std::ostream& ostr)const;
   };
}
#endif // !SDDS_MOTORCYCLE_H_