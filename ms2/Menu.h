/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
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
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>
namespace sdds {
   const int MAX_NO_OF_ITEMS = 10;
   class Menu;
   class MenuItem {
   private:
      char m_content[51]{};
      MenuItem();
      MenuItem(const char* textContent);
      MenuItem(const MenuItem& notToCopy) = delete;
      MenuItem& operator=(const MenuItem& notToCopy) = delete;
      virtual ~MenuItem();
      void setEmpty();
      std::ostream& display(std::ostream& ostr = std::cout)const;
      friend class Menu;
   };

   class Menu {
      char m_title[51]{};
      MenuItem* m_menuItems[MAX_NO_OF_ITEMS];
      int m_noOfItems = 0;
      int m_indentation = 0;
   public:
      Menu();
      Menu(const char* name, int indentValue = 0);
      Menu(const MenuItem& notToCopy) = delete;
      MenuItem& operator=(const MenuItem& notToCopy) = delete;
      virtual ~Menu();
      operator bool()const;
      bool isEmpty()const;
      void setTitle(const char* name);
      void setEmpty();
      std::ostream& display(std::ostream& ostr = std::cout)const;
      void indent()const;
      Menu& operator=(const char* title);
      void add(const char* item);
      void clear();
      Menu& operator<<(const char* item);
      int run()const;
      operator int()const;
   };
}

#endif // !SDDS_MENU_H_
