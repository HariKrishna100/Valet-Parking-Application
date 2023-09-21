/* Citation and Sources...
Final Project Milestone 4
Module: Vehicle
Filename: Vehicle.h
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
#ifndef SDDS_VEHICLE_H_
#define SDDS_VEHICLE_H_
#include <iostream>
#include "ReadWritable.h"
namespace sdds {
   class Vehicle : public ReadWritable {
      char m_licensePlate[9]{};
      char* m_makeModel{};
      int m_parkingSpot;
   protected:
      void setEmpty();
      bool isEmpty()const;
      const char* getLicensePlate();
      const char* getMakeModel();
      void setMakeModel(const char* modelCstr);
   public:
      Vehicle();
      Vehicle(const char* plateCstr, const char* model);
      Vehicle(const Vehicle& toCopy);
      Vehicle& operator=(const Vehicle& toCopy);
      ~Vehicle();
      int getParkingSpot()const;
      void setParkingSpot(int spotNo);
      bool operator==(const char* plateCstr);
      bool operator==(const Vehicle& V);
      std::istream& read(std::istream& istr);
      virtual std::ostream& writeType(std::ostream& ostr)const = 0;
      std::ostream& write(std::ostream& ostr)const;
   };
}
#endif // !SDDS_VEHICLE_H_