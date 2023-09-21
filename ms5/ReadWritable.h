/* Citation and Sources...
Final Project Milestone 5
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
#ifndef SDDS_READWRITABLE_H_
#define SDDS_READWRITABLE_H_
#include <iostream>
namespace sdds {
   class ReadWritable {
      bool m_csvFlag;
   public:
      ReadWritable();
      virtual ~ReadWritable();
      bool isCsv()const;
      void setCsv(bool value);
      virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
      virtual std::istream& read(std::istream& istr = std::cin) = 0;
   };
   std::ostream& operator<<(std::ostream& os, const ReadWritable& R);
   std::istream& operator>>(std::istream& is, ReadWritable& R);
}
#endif // !SDDS_READWRITABLE_H_