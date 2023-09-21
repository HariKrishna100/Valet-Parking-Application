/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
using namespace std;
namespace sdds {
   // constructor set Menu to empty
   MenuItem::MenuItem() {
      setEmpty();
   }

   // one argument constructor set contents
   MenuItem::MenuItem(const char* textContent) {
      if (textContent) {
         strcpy(m_content, textContent);
      }
      else {
         setEmpty();
      }
   }

   // virtual destructor
   MenuItem::~MenuItem() {

   }

   // set MenuItem to empty state
   void MenuItem::setEmpty() {
      m_content[0] = '\0';
   }

   // display contents of Menu
   std::ostream& MenuItem::display(std::ostream& ostr)const {
      ostr << m_content << endl;
      return ostr;
   }

   // set Menu to empty state
   Menu::Menu() {
      clear();
   }

   // two argument constructor to set title and indentation
   Menu::Menu(const char* name, int indentVal) {
      if (name) {
         setTitle(name);
         if (indentVal > 0) {
            m_indentation = indentVal;
         }
      }
      else {
         clear();
      }
   }

   // destructor to free up memory 
   // set Menu to empty 
   Menu::~Menu() {
      clear();
   }

   // return true if Menu is in valid state
   Menu::operator bool() const {
      return (m_title[0] != '\0');
   }

   // return true if Menu is invalid state
   bool Menu::isEmpty()const {
      return (m_title[0] == '\0');
   }

   // set Menu's title
   void Menu::setTitle(const char* name) {
      if (strlen(name) >= 50) {
         strcpy(m_title, name);
      }
      else {
         for (int i = 0; i < 50; i++) {
            m_title[i] = name[i];
         }
      }
   }

   // display
   std::ostream& Menu::display(std::ostream& ostr)const {
      if (isEmpty()) {
         cout << "Invalid Menu!" << endl;
      }
      else {
         indent();
         cout << m_title << endl;
         if (m_noOfItems > 0) {
            for (int i = 0; i < m_noOfItems; i++) {
               indent();
               ostr << i + 1 << "- ";
               m_menuItems[i]->display();
            }
            indent();
            cout << "> ";
         }
         else {
            cout << "No Items to display!" << endl;
         }
      }
      return ostr;
   }

   // print indentations
   void Menu::indent()const {
      int len = m_indentation * 4;
      for (int i = 0; i < len; i++) {
         cout << " ";
      }
   }

   // add items to menuItems array list
   void Menu::add(const char* item) {
      if (item) {
         if (!isEmpty() && (m_noOfItems < MAX_NO_OF_ITEMS)) {
            MenuItem* list = new MenuItem(item);
            m_menuItems[m_noOfItems] = list;
            m_noOfItems++;
         }
      }
      else {
         clear();
      }
   }

   // set menu to empty Menu
   void Menu::clear() {
      m_title[0] = '\0';
      m_indentation = 0;
      for (int i = 0; i < m_noOfItems; i++) {
         delete m_menuItems[i];
         m_menuItems[i] = nullptr;
      }
      m_noOfItems = 0;
   }

   // insertion operator to help add items
   Menu& Menu::operator<<(const char* item) {
      add(item);
      return *this;
   }

   // copy and assign Menu items title
   Menu& Menu::operator=(const char* title) {
      clear();
      if (title) setTitle(title);
      return *this;
   }

   // set Menu to empty state
   /*void Menu::setEmpty() {
      m_title[0] = '\0';
      m_indentation = 0;
      for (int i = 0; i < m_noOfItems; i++) {
         delete m_menuItems[i];
         m_menuItems[i] = nullptr;
      }
      m_noOfItems = 0;
   }*/

   // display menu and get user input
   int Menu::run()const {
      int selection = 0;
      bool success = true;

      display();
      
      if (m_noOfItems <= 0) {
         return 0;
      }
      else {
         while (success) {
            cin >> selection;
            if (cin.fail()) {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Invalid Integer, try again: ";
            }
            else if (selection < 1 || selection > m_noOfItems) {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Invalid selection, try again: ";
            }
            else {
               cin.ignore(1000, '\n');
               success = false;
            }
         }
      } 
      return selection;
   }
   
   // integer cast operator
   Menu::operator int()const {
      return run();
   }
}