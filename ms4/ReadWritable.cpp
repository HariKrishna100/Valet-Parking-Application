/* Citation and Sources...
Final Project Milestone 4
Module: ReadWritable
Filename: ReadWritable.cpp
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
#include "ReadWritable.h"
using namespace std;
using namespace sdds;
namespace sdds {
   // set comma seperated value flag
   ReadWritable::ReadWritable() {
      m_csvFlag = false;
   }

   // virtual
   ReadWritable::~ReadWritable() {

   }

   // gets comma seperated value
   bool ReadWritable::isCsv() const {
      return m_csvFlag;
   }

   // set comma seperated flag to incoming value
   void ReadWritable::setCsv(bool value) {
      m_csvFlag = value;
   }

   // insertion helper operator
   std::ostream& operator<<(std::ostream& os, const ReadWritable& R) {
      R.write(os);
      return os;
   }

   // extraction helper operator
   std::istream& operator>>(std::istream& is, ReadWritable& R) {
      R.read(is);
      return is;
   }
}