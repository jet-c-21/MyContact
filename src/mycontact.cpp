//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
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
    case MainMenuFunc::kExit:exit_dlg();
      break;

    case MainMenuFunc::kViewContactList:view_contact_ls_dlg();
      break;

    case MainMenuFunc::kSortContactList:sort_contact_ls_dlg();
      break;

    case MainMenuFunc::kSearchContact:search_contact_dlg();
      break;

    case MainMenuFunc::kAddNewContact:add_contact_dlg();
      break;

    case MainMenuFunc::kAddMultipleContacts:add_multi_contacts_dlg();
      break;

    case MainMenuFunc::kAddContactsFromFile:add_contacts_from_file();
      break;

    case MainMenuFunc::kEditContact: edit_contact_dlg();
      break;

    case MainMenuFunc::kDeleteContact: delete_contact_dlg();
      break;

    case MainMenuFunc::kDeleteAllContact: delete_all_contact_dlg();
      break;

    case MainMenuFunc::kImportContactsFromFile:import_contacts_from_File_dlg();
      break;

    case MainMenuFunc::kExportContactList:export_contact_list_dlg();
      break;
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
                          " [9] Delete ALL Contact\n"
                          "[10] Import Contacts List from file\n"
                          "[11] Export Contacts List\n"
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
  clear_console();
  std::string mode_info = "• Search Contact •\n\n";;
  std::cout << mode_info;

  std::string query;
  std::string msg = "Please Enter an KeyWord: ";
  std::cout << msg;

  flush_cin();
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
}

void MyContact::add_contact_dlg() {
  clear_console();
  std::string mode_info = "• Add a new Contact •\n\n";;
  std::cout << mode_info;

  ContactData ct_data = gen_contact_data();

  contact_manager.add_contact(ct_data.name, ct_data.phone, ct_data.address, ct_data.email, ct_data.notes);

  std::string msg = "Contact List has updated!";
  std::cout << msg << std::endl;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

MyContact::ContactData MyContact::gen_contact_data() {
  flush_cin();

  std::string user_input_name;
  std::cout << "Enter <Name> for the new Contact: ";
  std::getline(std::cin, user_input_name, '\n');
//  print(user_input_name);

  std::string user_input_phone;
  std::cout << "Enter <Phone> for the new Contact: ";
  std::getline(std::cin, user_input_phone, '\n');
//  print(user_input_phone);

  std::string user_input_address;
  std::cout << "Enter <Address> for the new Contact: ";
  std::getline(std::cin, user_input_address, '\n');
//  print(user_input_address);

  std::string user_input_email;
  std::cout << "Enter <Email> for the new Contact: ";
  std::getline(std::cin, user_input_email, '\n');
//  print(user_input_email);

  std::string user_input_notes;
  std::cout << "Enter <Notes> for the new Contact: ";
  std::getline(std::cin, user_input_notes, '\n');
//  print(user_input_notes);

  ContactData result = {user_input_name,
                        user_input_phone,
                        user_input_address,
                        user_input_email,
                        user_input_notes};

  return result;
}

void MyContact::add_multi_contacts_dlg() {
  clear_console();
  std::string mode_info = "• Add multiple Contacts •\n\n";;
  std::cout << mode_info;

  int add_contact_count = ask_add_contact_count();

  for (int i = 1; i <= add_contact_count; i++) {
    flush_cin();
    clear_console();
    std::cout << mode_info;

    std::string user_input_name;
    std::cout << "Enter <Name> for #" + std::to_string(i) + " Contact: ";
    std::getline(std::cin, user_input_name, '\n');
//    print(user_input_name);

    std::string user_input_phone;
    std::cout << "Enter <Phone> for #" + std::to_string(i) + " Contact: ";
    std::getline(std::cin, user_input_phone, '\n');
//    print(user_input_phone);

    std::string user_input_address;
    std::cout << "Enter <Address> for #" + std::to_string(i) + " Contact: ";
    std::getline(std::cin, user_input_address, '\n');
//    print(user_input_address);

    std::string user_input_email;
    std::cout << "Enter <Email> for #" + std::to_string(i) + " Contact: ";
    std::getline(std::cin, user_input_email, '\n');
//    print(user_input_email);

    std::string user_input_notes;
    std::cout << "Enter <Notes> for #" + std::to_string(i) + " Contact: ";
    std::getline(std::cin, user_input_notes, '\n');
//    print(user_input_notes);

    contact_manager.add_contact(user_input_name,
                                user_input_phone,
                                user_input_address,
                                user_input_email,
                                user_input_notes);

    std::cout << "Finish adding #" + std::to_string(i) + " Contact. \n\n";
    std::cout << "Press Enter to Continue . . . \n";
    std::cout << std::endl;

  }

  clear_console();
  std::cout << mode_info;
  std::string msg = "Finish adding " + std::to_string(add_contact_count) + " of Contact.\n";
  std::cout << msg << std::endl;

  ask_to_go_back_to_main_menu();
}

int MyContact::ask_add_contact_count() {
  std::string msg = "How many Contacts do you want to add?\n";
  std::cout << msg;
  std::cout << std::endl;

  int user_choice;
  msg = "Enter the amount: ";
  while (true) {
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice < 1) {
      invalid_adding_ct_count_prompt();
      flush_cin();
      continue;
    }

    return user_choice;
  }
}

void MyContact::invalid_adding_ct_count_prompt() {
  std::string msg = "Only Positive Integer is Allowed! Please try again.";
  std::cout << msg << std::endl;
}

void MyContact::add_contacts_from_file() {
  clear_console();
  std::string mode_info = "• Add Contacts from file •\n\n";;
  std::cout << mode_info;

  std::string msg = "Enter the path of the (.mcsv) file: ";
  std::cout << msg;
  std::string file_path;
  flush_cin();
  getline(std::cin, file_path, '\n');

  if (!ContactManager::find_contact_file(file_path)) {
    msg = "The Input File does not exist!\n";
    std::cout << msg;
    std::cout << std::endl;
    ask_to_go_back_to_main_menu();
  }

  std::vector<Contact> new_ct_ls = ContactManager::read_mcsv(file_path);
  contact_manager.extend_contact_ls(new_ct_ls);
  msg = "Finish adding " + std::to_string(new_ct_ls.size()) + " Contacts. \n";
  std::cout << msg;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

void MyContact::edit_contact_dlg() {
  clear_console();
  std::string mode_info = "• Edit a Contact •\n\n";;
  std::cout << mode_info;

  std::string msg;

  if (!contact_manager.get_contact_count()) {
    msg = "Contact List is Empty now!\n";
    std::cout << msg;
    std::cout << std::endl;

    return ask_to_go_back_to_main_menu();
  }

  msg = "Which Contact do you want to edit?\n";
  std::cout << msg;
  std::cout << std::endl;

  contact_manager.print_contacts();
  std::cout << std::endl;

  int edit_ct_number = ask_user_select_ct_number();
  clear_console();
  std::cout << mode_info;

  Contact &ct = contact_manager.get_contact(edit_ct_number - 1);

  std::tuple<bool, std::string> new_field_val;

  clear_console();
  std::cout << mode_info;
  new_field_val = ask_new_field_val(ContactManager::kFldName);
  if (std::get<0>(new_field_val))
    ct.set_name(std::get<1>(new_field_val));

  clear_console();
  std::cout << mode_info;
  new_field_val = ask_new_field_val(ContactManager::kFldPhone);
  if (std::get<0>(new_field_val))
    ct.set_phone(std::get<1>(new_field_val));

  clear_console();
  std::cout << mode_info;
  new_field_val = ask_new_field_val(ContactManager::kFldAddress);
  if (std::get<0>(new_field_val))
    ct.set_address(std::get<1>(new_field_val));

  clear_console();
  std::cout << mode_info;
  new_field_val = ask_new_field_val(ContactManager::kFldEmail);
  if (std::get<0>(new_field_val))
    ct.set_email(std::get<1>(new_field_val));

  clear_console();
  std::cout << mode_info;
  new_field_val = ask_new_field_val(ContactManager::kFldNotes);
  if (std::get<0>(new_field_val))
    ct.set_notes(std::get<1>(new_field_val));

  clear_console();
  std::cout << mode_info;
  msg = "Finish Edition.\n";
  std::cout << msg;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

int MyContact::ask_user_select_ct_number() {
  int user_choice;
  std::string msg = "Enter the Contact No.: ";
  while (true) {
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice < 1 || user_choice > contact_manager.get_contact_count()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    return user_choice;
  }

}

std::tuple<bool, std::string> MyContact::ask_new_field_val(const std::string &field_name) {
  std::string msg = "Modify Field: <" + field_name + "> ?\n\n";
  std::cout << msg;

  std::string user_choice;
  while (true) {
    msg = "Enter your choice, Press [y] or [n]: ";
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice != "y" && user_choice != "Y" &&
        user_choice != "n" && user_choice != "N") {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice == "n" || user_choice == "N") {
      return std::make_tuple(false, "");
    }

    break;
  }

  std::cout << std::endl;
  msg = "Enter the new value for Field < " + field_name + ">: ";
  std::cout << msg;
  flush_cin();
  std::string new_val;
  std::getline(std::cin, new_val, '\n');

  return std::make_tuple(true, new_val);
}

void MyContact::delete_contact_dlg() {
  clear_console();
  std::string mode_info = "• Delete a Contact •\n\n";;
  std::cout << mode_info;

  std::string msg;

  if (!contact_manager.get_contact_count()) {
    msg = "Contact List is Empty now!\n";
    std::cout << msg;
    std::cout << std::endl;

    return ask_to_go_back_to_main_menu();
  }

  msg = "Which Contact do you want to delete?\n";
  std::cout << msg;
  std::cout << std::endl;

  contact_manager.print_contacts();
  std::cout << std::endl;

  int edit_ct_number = ask_user_select_ct_number();
  contact_manager.delete_contact(edit_ct_number - 1);
  clear_console();
  std::cout << mode_info;

  clear_console();
  std::cout << mode_info;
  msg = "Finish Deletion.\n";
  std::cout << msg;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

void MyContact::import_contacts_from_File_dlg() {
  clear_console();
  std::string mode_info = "• Import Contacts List from file •\n\n";;
  std::cout << mode_info;

  std::string msg = "(WARNING: If the import operation succeed, "
                    "the Contact Data will be overwritten as the Data of the Input File)\n";
  std::cout << msg;
  std::cout << std::endl;

  msg = "Enter the path of the (.mcsv) file: ";
  std::cout << msg;
  std::string file_path;
  flush_cin();
  getline(std::cin, file_path, '\n');

  if (!ContactManager::find_contact_file(file_path)) {
    msg = "The Input File does not exist!\n";
    std::cout << msg;
    std::cout << std::endl;
    ask_to_go_back_to_main_menu();
  }

  std::vector<Contact> new_ct_ls = ContactManager::read_mcsv(file_path);
  contact_manager.replace_contact_ls(new_ct_ls);

  clear_console();
  std::cout << mode_info;
  msg = "Finish Import File: " + file_path + ". \n";
  std::cout << msg;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

void MyContact::export_contact_list_dlg() {
  clear_console();
  std::string mode_info = "• Export Contacts List •\n\n";;
  std::cout << mode_info;

  std::string msg = "Enter the save path of the (.mcsv) file: ";
  std::cout << msg;
  std::string file_path;
  flush_cin();
  getline(std::cin, file_path, '\n');

  contact_manager.to_mcsv(file_path);

  bool export_res = ContactManager::find_contact_file(file_path);
  clear_console();
  std::cout << mode_info;

  if (export_res)
    msg = "Export Operation Succeed.\n";
  else
    msg = "Export Operation Failed.\n";

  std::cout << msg;
  std::cout << std::endl;

  ask_to_go_back_to_main_menu();
}

void MyContact::exit_dlg() {
  clear_console();
  contact_manager.close();

  std::cout << std::endl << std::endl;

  std::string mode_info = "♦♦♦ Thank You For Using My Contact! ♦♦♦\n"
                          "\n"
                          "* My Contact © Developed By: https://github.com/jet-c-21";

  std::cout << mode_info;
  std::cout << std::endl;
}

void MyContact::delete_all_contact_dlg() {
  clear_console();
  std::string msg;
  std::string mode_info = "• Delete a Contact •\n\n";;
  std::cout << mode_info;
  if(ask_for_vital_execution()){
    contact_manager.remove_all_contact();
    clear_console();
    std::cout << mode_info;

    msg = "All Contacts have been deleted.\n";
    std::cout << msg;
    std::cout << std::endl;
  }

  std::cout << std::endl;
  ask_to_go_back_to_main_menu();
}

bool MyContact::ask_for_vital_execution() {
  std::string user_choice, msg;
  while (true) {
    msg = "Are you sure for doing this? Press [y] or [n]: ";
    std::cout << msg;
    std::cin >> user_choice;

    if (std::cin.fail()) {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice != "y" && user_choice != "Y" &&
        user_choice != "n" && user_choice != "N") {
      invalid_menu_choice_prompt();
      flush_cin();
      continue;
    }

    if (user_choice == "n" || user_choice == "N")
      return false;
    else
      return true;
  }

};

