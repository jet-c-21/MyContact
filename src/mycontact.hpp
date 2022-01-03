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

 private:
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

  // Static Method
  static std::vector<Contact> read_mcsv(const std::string &mcsv_file_path);

  int get_contact_count();
  void print_contacts();

 private:
  static std::string get_divider(int width);
  static std::string get_aligned_fld_header(const std::string &fld_s, int &fld_pw);
  void print_contact(const Contact &ct);

  int get_no_pw();
  int get_name_pw();
  int get_phone_pw();
  int get_address_pw();
  int get_email_pw();
  int get_notes_pw();

  bool find_data_dir();
  bool find_contact_file();
};

#endif //MYCONTACT_SRC_MYCONTACT_HPP_
