//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <string>
#include "ult.hpp"
#include "mycontact.hpp"
#define print(x) std::cout << x << std::endl

std::string const MyContact::kDataDir = "data";
std::string const MyContact::kContactFilePath = MyContact::kDataDir + "/contacts.mcsv";
std::string const MyContact::kFldDelimiter = "|";
std::string const MyContact::kFldNO = "NO.";
std::string const MyContact::kFldName = "Name";
std::string const MyContact::kFldPhone = "Phone";
std::string const MyContact::kFldAddress = "Address";
std::string const MyContact::kFldEmail = "Email";
std::string const MyContact::kFldNotes = "Notes";
std::string const MyContact::kFields[] = {MyContact::kFldNO,
                                          MyContact::kFldName,
                                          MyContact::kFldPhone,
                                          MyContact::kFldAddress,
                                          MyContact::kFldEmail,
                                          MyContact::kFldNotes};

MyContact::MyContact() {
  if (find_contact_file())
    contact_ls = read_mcsv(kContactFilePath);
}

MyContact::MyContact(const std::string &contact_file_path) {
  contact_ls = read_mcsv(kContactFilePath);
}

MyContact::~MyContact() {

}

bool MyContact::find_data_dir() {
  struct stat info;
  return stat(kDataDir.c_str(), &info) == 0 && info.st_mode & S_IFDIR;
}

bool MyContact::find_contact_file() {
  if (find_data_dir() == 0) {
    mkdir(kDataDir.c_str(), 0777);
    return false;
  }

  struct stat buffer;
  if (stat(kContactFilePath.c_str(), &buffer) != 0) {
    return false;
  }

  return true;
}

std::vector<Contact> MyContact::read_mcsv(const std::string &mcsv_file_path) {
  std::vector<Contact> result;

  std::ifstream file(mcsv_file_path);

  std::string line;
  getline(file, line, '\n'); // skip header
  while (file.good()) {
    getline(file, line, '\n');
//    std::cout << "Line: " << line << std::endl;
    result.emplace_back(line);
  }

//  for (Contact c: result) {
//    c.print_info();
//    std::cout << "\n";
//  }

  return result;
}

int MyContact::get_contact_count() {
  return contact_ls.size();
}

int MyContact::get_no_pw() {
  int fld_len = kFldNO.length();
  std::string ct_count_str = std::to_string(get_contact_count());
  int no_len = ct_count_str.length();

  if (fld_len > no_len)
    return fld_len;

  return no_len;
}

int MyContact::get_name_pw() {
  int print_width = kFldName.length();

  for (Contact &c: contact_ls) {
    int curr_len = c.get_name().length();
    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int MyContact::get_phone_pw() {
  int print_width = kFldPhone.length();

  for (Contact &c: contact_ls) {
    int curr_len = c.get_phone().length();
    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int MyContact::get_address_pw() {
  int print_width = kFldAddress.length();

  for (Contact &c: contact_ls) {
    int curr_len = c.get_address().length();
    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int MyContact::get_email_pw() {
  int print_width = kFldEmail.length();

  for (Contact &c: contact_ls) {
    int curr_len = c.get_email().length();
    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int MyContact::get_notes_pw() {
  int print_width = kFldNotes.length();

  for (Contact &c: contact_ls) {
    int curr_len = c.get_notes().length();
    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

std::string MyContact::get_divider(int width) {
  std::string div;
  for (int i = 1; i <= width; i++)
    div += "_";

  return div;
}

void MyContact::print_contacts() {
  int no_pw = get_no_pw();
  std::string no_header = get_aligned_fld_header(kFldNO, no_pw);

  int name_pw = get_name_pw();
  std::string name_header = get_aligned_fld_header(kFldName, name_pw);

  int phone_pw = get_phone_pw();
  std::string phone_header = get_aligned_fld_header(kFldPhone, phone_pw);

  int address_pw = get_address_pw();
  std::string address_header = get_aligned_fld_header(kFldAddress, address_pw);

  int email_pw = get_email_pw();
  std::string email_header = get_aligned_fld_header(kFldEmail, email_pw);

  int notes_pw = get_notes_pw();
  std::string notes_header = get_aligned_fld_header(kFldNotes, notes_pw);

  int divider_pw =
      no_pw + name_pw + phone_pw + address_pw + email_pw + notes_pw + (int) kFldDelimiter.length() * (kFldCount - 1);

  std::string divider = get_divider(divider_pw);


  std::cout << UNDERLINE << kFldDelimiter
            << no_header << kFldDelimiter
            << name_header << kFldDelimiter
            << phone_header << kFldDelimiter
            << address_header << kFldDelimiter
            << email_header << kFldDelimiter
            << notes_header << kFldDelimiter
            << CLOSE_UNDERLINE << std::endl;

//  std::cout << kFldDelimiter
//            << no_header << kFldDelimiter
//            << name_header << kFldDelimiter
//            << phone_header << kFldDelimiter
//            << address_header << kFldDelimiter
//            << email_header << kFldDelimiter
//            << notes_header << kFldDelimiter
//            << std::endl;

//  std::cout << divider << std::endl;

  for (int i = 0; i < contact_ls.size(); i++) {
    Contact ct = contact_ls[i];
    int ct_number = i + 1;
    std::cout << UNDERLINE << kFldDelimiter
              << std::right << std::setw(no_pw) << ct_number << kFldDelimiter
              << std::right << std::setw(name_pw) << ct.get_name() << kFldDelimiter
              << std::right << std::setw(phone_pw) << ct.get_phone() << kFldDelimiter
              << std::right << std::setw(address_pw) << ct.get_address() << kFldDelimiter
              << std::right << std::setw(email_pw) << ct.get_email() << kFldDelimiter
              << std::right << std::setw(notes_pw) << ct.get_notes() << kFldDelimiter
              << CLOSE_UNDERLINE << std::endl;

//    std::cout << kFldDelimiter
//              << std::right << std::setw(no_pw) << ct_number << kFldDelimiter
//              << std::right << std::setw(name_pw) << ct.get_name() << kFldDelimiter
//              << std::right << std::setw(phone_pw) << ct.get_phone() << kFldDelimiter
//              << std::right << std::setw(address_pw) << ct.get_address() << kFldDelimiter
//              << std::right << std::setw(email_pw) << ct.get_email() << kFldDelimiter
//              << std::right << std::setw(notes_pw) << ct.get_notes() << kFldDelimiter
//              << std::endl;

  }

}

std::string MyContact::get_aligned_fld_header(const std::string &fld_s, int &fld_pw) {
  int w_diff = fld_pw - (int) fld_s.length();
  if (w_diff == 0)
    return fld_s;

  if (w_diff % 2 != 0)
    w_diff += 1;

  w_diff /= 2;

  std::string ident;
  for (int i = 1; i <= w_diff; i++)
    ident += " ";

  std::string result = ident + fld_s + ident;
  int new_fld_pw = (int) result.length();
  if (new_fld_pw != fld_pw)
    fld_pw = new_fld_pw;

  return result;
}

void MyContact::print_contact(const Contact &ct) {

}



