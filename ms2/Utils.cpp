/* Citation and Sources...
Final Project Milestone 2
Module: Utils
Filename: Utils.cpp
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
#include "Utils.h"
using namespace std;
namespace sdds {
   bool confirmation(std::istream& istr) {
      char input;
      char line;
      do {
         input = istr.get();
         line = istr.get();
         if (line != '\n') {
            istr.ignore(1000, '\n');
            input = 'x';
         }
      } while (input != 'y' && input != 'Y' && input != 'n' && input != 'N'
         && cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ");
      return input == 'y' || input == 'Y';
   }
}