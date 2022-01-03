//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//

#ifndef MYCONTACT_SRC_MYCONTACT_HPP_
#define MYCONTACT_SRC_MYCONTACT_HPP_

#include <string>
#include <vector>
#include <fstream>
#include "contact.hpp"

class MyContact {
 public:
  static const int kFldCount = 6;
  static const std::string kFields[];
  static const int kSortFldCount = 5;
  static const std::string kSortFields[];

 private:
  enum class SortField {
    kName = 0, kPhone, kAddress, kEmail, kNotes
  };
  SortField eSortField = SortField::kName;

  enum class SortType {
    kAscending = 0, kDescending
  };
  SortType eSortType = SortType::kAscending;

  static const std::string kDataDir;
  static const std::string kContactFilePath;
  static const std::string kFldDelimiter;
  static const std::string kFldNO;
  static const std::string kFldName;
  static const std::string kFldPhone;
  static const std::string kFldAddress;
  static const std::string kFldEmail;
  static const std::string kFldNotes;

  std::vector<Contact> contact_ls;

 public:
  // Constructor
  MyContact();
  MyContact(const std::string &contact_file_path);

  // Destructor
  ~MyContact();

  // Public Static Method
  static std::vector<Contact> read_mcsv(const std::string &mcsv_file_path);
  static void print_contacts(std::vector<Contact> &ct_ls, SortField &sort_field, SortType &sort_type);
  static std::string get_sort_mode_name(SortField &sort_field);
  static std::string get_sort_type_symbol(SortType &sort_type);

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

#endif //MYCONTACT_SRC_MYCONTACT_HPP_
