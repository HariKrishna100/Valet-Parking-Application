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
#ifndef SDDS_PARKING_H_
#include "Vehicle.h"
#include "Menu.h"
namespace sdds {
   const int MAX_NO_OF_SPOTS = 100;
   class Parking {
      char* m_filename;
      Menu* m_parkingMenu;
      Menu* m_vehicleMenu;
      Vehicle* m_parkingSpots[MAX_NO_OF_SPOTS]{};
      int m_noOfSpots;
      int m_noOfVehicles;
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
      Parking(const char* datafile, int spots);
      ~Parking();
      Parking(const Parking& notToCopy) = delete;
      Parking& operator=(const Parking& notToCopy) = delete;
      int run();
   };
}
#endif // !SDDS_PARKING_H_