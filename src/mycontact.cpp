//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/3/22
//
#include <string>
#include <iostream>
#include <limits>
#include "mycontact.hpp"
#define print(x) std::cout << x << std::endl

MyContact::MyContact(ContactManager &ct_mgr) {
  contact_manager = ct_mgr;
}

MyContact::~MyContact() {

}

std::string MyContact::get_os_name() {
#ifdef _WIN32 //|| _WIN64
  return "Windows";
#elif __APPLE__ || __MACH__
  return "MacOS";
#elif __linux__
  return "Linux";
#elif __FreeBSD__
  return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

void MyContact::clear_console() {
  if (os_name == "Windows")
    system("cls");
  else
    system("clear");
}

void MyContact::launch() {
  main_menu_dlg();
}

void MyContact::main_menu_dlg() {
  clear_console();
  print_main_menu();
  int user_choice = ask_main_menu_choice();
  switch (static_cast<MainMenuFunc>(user_choice)) {
    case MainMenuFunc::kExit:break;

    case MainMenuFunc::kViewContactList:view_contact_ls_dlg();
      break;

    case MainMenuFunc::kSortContactList:sort_contact_ls_dlg();
      break;

    case MainMenuFunc::kSearchContact:search_contact_dlg();
      break;

    case MainMenuFunc::kAddNewContact:break;
    case MainMenuFunc::kAddMultipleContacts:break;
    case MainMenuFunc::kAddContactsFromFile:break;
    case MainMenuFunc::kEditContact:break;
    case MainMenuFunc::kDeleteContact:break;
    case MainMenuFunc::kImportContactsFromFile:break;
    case MainMenuFunc::kExportContactList:break;
  }

}

void MyContact::print_main_menu() {
  std::string main_menu = "♦♦♦ Welcome to My Contact ♦♦♦\n"
                          "\n\n"
                          "• MAIN MENU •\n"
                          "=============================================\n"
                          " [1] View Contact List\n"
                          " [2] Sort Contact List\n"
                          " [3] Search Contact\n"
                          " [4] Add a new Contact\n"
                          " [5] Add multiple Contacts\n"
                          " [6] Add Contacts from file\n"
                          " [7] Edit a Contact\n"
                          " [8] Delete a Contact\n"
                          " [9] Import Contacts List from file\n"
                          "[10] Export Contacts List\n"
                          "\n"
                          " [0] Exit\n"
                          "=============================================\n"
                          "\n";
  std::cout << main_menu;
}

int MyContact::ask_main_menu_choice() {
  int user_choice;
  std::string msg = "Enter the choice: ";
  while (true) {
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice < 0 || user_choice > static_cast<int>(MainMenuFunc::kFunctionCount)) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    return user_choice;
  }
}

void MyContact::invalid_menu_choice_prompt() {
  std::string msg = "Invalid Command! Please try again.";
  std::cout << msg << std::endl;
}

void MyContact::view_contact_ls_dlg() {
  clear_console();
  std::string mode_info = "• View Contact List •\n\n";
  std::cout << mode_info;
  contact_manager.print_contacts();
  std::cout << std::endl;
  ask_to_go_back_to_main_menu();
}

void MyContact::ask_to_go_back_to_main_menu() {
  std::string msg = "Press ENTER (or double press) to go back to MAIN MENU . . . ";
  std::cout << msg;

//  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore();
//  flush_cin();
  std::cin.get();

  main_menu_dlg();
}

void MyContact::sort_contact_ls_dlg() {
  clear_console();
  std::string mode_info = "• Sort Contact List •\n\n";
  std::cout << mode_info;

  // ask sort mode
  int user_sort_mode = ask_sort_mode();
  clear_console();
  contact_manager.set_sort_mode(user_sort_mode - 1);
  std::string user_sort_mode_name = contact_manager.get_sort_mode_name();
  mode_info += "*Sort Field: " + user_sort_mode_name + "\n";
  std::cout << mode_info;
  std::cout << std::endl;

  //  ask sort type
  int user_sort_type = ask_sort_type();
  clear_console();
  contact_manager.set_sort_type(user_sort_type - 1);
  if (user_sort_type == 1)
    mode_info += "*Sort Type: Ascending\n";
  else
    mode_info += "*Sort Type: Descending\n";
  std::cout << mode_info;
  std::cout << std::endl;

  std::string msg = "The sorting setting now is set as: \"" +
      user_sort_mode_name +
      "(" + contact_manager.get_sort_type_symbol() + ")\" \n";
  std::cout << msg;
  std::cout << std::endl;

  // sort contact manager
  contact_manager.sort();

  ask_to_go_back_to_main_menu();
}

int MyContact::ask_sort_mode() {
  flush_cin();
  std::string msg = "Please choose the sort mode:\n"
                    "[1] Name\n"
                    "[2] Phone\n"
                    "[3] Address\n"
                    "[4] Email\n"
                    "[5] Notes\n"
                    "\n";
  std::cout << msg;

  int user_choice;
  msg = "Enter the choice: ";
  while (true) {
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice < 1 || user_choice > ContactManager::kSortFldCount) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    return user_choice;
  }
}

int MyContact::ask_sort_type() {
  flush_cin();
  std::string msg = "Please choose the sort type:\n"
                    "[1] Ascending\n"
                    "[2] Descending\n"
                    "\n";
  std::cout << msg;

  int user_choice;
  msg = "Enter the choice: ";
  while (true) {
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice < 1 || user_choice > 2) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    return user_choice;
  }
}

void MyContact::search_contact_dlg() {
  flush_cin();
  clear_console();
  std::string mode_info = "• Search Contact •\n\n";;
  std::cout << mode_info;

  std::string query;
  std::string msg = "Please Enter an KeyWord: ";
  std::cout << msg;

  std::cin.clear();
  std::getline(std::cin, query, '\n');
  std::cout << "Search : " + query << std::endl;

  clear_console();
  std::cout << mode_info;
  contact_manager.search(query);
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

void MyContact::flush_cin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

