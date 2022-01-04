//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//

#ifndef MYCONTACT_SRC_CONTACT_MANAGER_HPP_
#define MYCONTACT_SRC_CONTACT_MANAGER_HPP_

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "contact.hpp"

class ContactManager {
 public:
  static const int kFldCount = 6;
  static const std::string kFields[];
  static const int kSortFldCount = 5;
  static const std::string kSortFields[];
  static const std::string kFldDelimiter;
  static const std::string kFldNO;
  static const std::string kFldName;
  static const std::string kFldPhone;
  static const std::string kFldAddress;
  static const std::string kFldEmail;
  static const std::string kFldNotes;

  enum class SortField {
    kName = 0, kPhone, kAddress, kEmail, kNotes
  };

  static const int kSortTypeCount = 2;
  enum class SortType {
    kAscending = 0, kDescending
  };
  SortType eSortType = SortType::kAscending;

 private:
  SortField eSortField = SortField::kName;

  static const std::string kDataDir;
  static const std::string kContactFilePath;

  std::vector<Contact> contact_ls;


 public:
  // Constructor
  ContactManager();
  explicit ContactManager(const std::string &contact_file_path);

  // Destructor
  ~ContactManager();

  // Public Static Method
  static std::vector<Contact> read_mcsv(const std::string &mcsv_file_path);
  static void print_contacts(std::vector<Contact> &ct_ls, SortField &sort_field, SortType &sort_type);
  static std::string get_sort_mode_name(SortField &sort_field);
  static std::string get_sort_type_symbol(SortType &sort_type);
  static bool find_contact_file(const std::string &mcsv_file_path);

  void to_mcsv(const std::string &file_save_pth);

  int get_contact_count();
  void print_contacts();
  int get_sort_mode() const;
  void set_sort_mode(int mode_code);
  std::string get_sort_mode_name() const;
  void set_sort_type(int type_code);
  std::string get_sort_type_symbol() const;
  void sort();
  void sort_by_name();
  void sort_by_phone();
  void sort_by_address();
  void sort_by_email();
  void sort_by_notes();


  Contact &get_contact(int contact_idx);
  void delete_contact(int contact_idx);
  void replace_contact_ls(std::vector<Contact> &new_ct_ls);

  std::vector<Contact> select_contacts(const std::string &query);
  void search(const std::string &query);

  void add_contact(const std::string &name,
                   const std::string &phone,
                   const std::string &address,
                   const std::string &email,
                   const std::string &notes);

  void extend_contact_ls(std::vector<Contact> &new_ct_ls);

 private:
  // Private Static Method
  static std::string get_divider(int width);
  static std::string get_aligned_fld_header(const std::string &fld_s, int &fld_pw);
  static int get_field_pw(std::vector<Contact> &ct_ls, const std::string &field);
  static int get_no_pw(std::vector<Contact> &ct_ls);
  static int get_name_pw(std::vector<Contact> &ct_ls);
  static int get_phone_pw(std::vector<Contact> &ct_ls);
  static int get_address_pw(std::vector<Contact> &ct_ls);
  static int get_email_pw(std::vector<Contact> &ct_ls);
  static int get_notes_pw(std::vector<Contact> &ct_ls);

  //  void print_contact(const Contact &ct);

  bool find_data_dir();
  bool find_contact_file();
};

#endif //MYCONTACT_SRC_CONTACT_MANAGER_HPP_
