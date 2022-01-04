//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/3/22
//

#ifndef MYCONTACT_SRC_MYCONTACT_HPP_
#define MYCONTACT_SRC_MYCONTACT_HPP_
#include <tuple>
#include "contact_manager.hpp"

class MyContact {
 public:
  ContactManager contact_manager;
  std::string os_name = get_os_name();

  struct ContactData {
    std::string name;
    std::string phone;
    std::string address;
    std::string email;
    std::string notes;
  };

 private:
  enum class MainMenuFunc {
    kExit = 0,
    kViewContactList = 1,
    kSortContactList = 2,
    kSearchContact = 3,
    kAddNewContact = 4,
    kAddMultipleContacts = 5,
    kAddContactsFromFile = 6,
    kEditContact = 7,
    kDeleteContact = 8,
    kImportContactsFromFile = 9,
    kExportContactList = 10,
    kFunctionCount = 10,
  };

 public:
  // Constructor
  explicit MyContact(ContactManager &ct_mgr);

  // Destructor
  ~MyContact();

  void launch();

 private:
  static std::string get_os_name();
  static void print_main_menu();

  void main_menu_dlg();
  static int ask_main_menu_choice();
  static void invalid_menu_choice_prompt();
  static void invalid_adding_ct_count_prompt();
  static void flush_cin();

  void view_contact_ls_dlg();

  void sort_contact_ls_dlg();
  static int ask_sort_mode();
  static int ask_sort_type();

  void search_contact_dlg();

  void add_contact_dlg();

  void add_multi_contacts_dlg();
  int ask_add_contact_count();

  void add_contacts_from_file();

  void edit_contact_dlg();
  int ask_user_select_ct_number();
  std::tuple<bool, std::string> ask_new_field_val(const std::string &field_name);

  void delete_contact_dlg();

  void import_contacts_from_File_dlg();

  void export_contact_list_dlg();

  void exit_dlg();

  void ask_to_go_back_to_main_menu();

  void clear_console();

  static ContactData gen_contact_data();

};

#endif //MYCONTACT_SRC_MYCONTACT_HPP_
