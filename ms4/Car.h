/* Citation and Sources...
Final Project Milestone 4
Module: Car
Filename: Car.h
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
#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_
#include <iostream>
#include "Vehicle.h"
namespace sdds {
   class Car : public Vehicle {
      bool m_carWashFlag;
   public:
      Car();
      Car(const char* plateCstr, const char* model);
      Car(const Car& toCopy);
      Car& operator=(const Car& toCopy);
      virtual ~Car();
      std::ostream& writeType(std::ostream& ostr)const;
      std::istream& read(std::istream& istr);
      std::ostream& write(std::ostream& ostr)const;
   };
}
#endif // !SDDS_CAR_H_
