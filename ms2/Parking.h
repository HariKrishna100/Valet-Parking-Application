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
#ifndef SDDS_PARKING_H_
#include "Menu.h"
namespace sdds {
   class Parking {
      char* m_filename;
      Menu* m_parkingMenu;
      Menu* m_vehicleMenu;
   private:
      bool isEmpty() const;
      void parkingStatus();
      void parkVehicle();
      void returnVehicle();
      void parkedVehicles();
      void findVehicle();
      bool closeParking();
      bool exitParking();
      bool loadData();
      void saveData();
      void setEmpty();
   public:
      Parking();
      Parking(const char* datafile);
      ~Parking();
      Parking(const Parking& notToCopy) = delete;
      Parking& operator=(const Parking& notToCopy) = delete;
      int run();
   };
}
#endif // !SDDS_PARKING_H_