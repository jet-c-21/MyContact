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
#include <algorithm>
#include "ult.hpp"
#include "mycontact.hpp"
#define print(x) std::cout << x << std::endl

std::string const MyContact::kDataDir = "data";
std::string const MyContact::kContactFilePath = MyContact::kDataDir + "/contacts.mcsv";
std::string const MyContact::kFldDelimiter = "|";
std::string const MyContact::kFldNO = "No.";
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

std::string const MyContact::kSortFields[] = {MyContact::kFldName,
                                              MyContact::kFldPhone,
                                              MyContact::kFldAddress,
                                              MyContact::kFldEmail,
                                              MyContact::kFldNotes};

MyContact::MyContact() {
  if (find_contact_file()) {
    contact_ls = read_mcsv(kContactFilePath);
    sort();
  }
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

int MyContact::get_no_pw(std::vector<Contact> &ct_ls) {
  int fld_len = MyContact::kFldNO.length();
  std::string ct_count_str = std::to_string(ct_ls.size());
  int no_len = ct_count_str.length();

  if (fld_len > no_len)
    return fld_len;

  return no_len;
}

int MyContact::get_field_pw(std::vector<Contact> &ct_ls, const std::string &field) {
  int print_width = field.length();

  for (Contact &c: ct_ls) {
    int curr_len;
    if (field == MyContact::kFldName)
      curr_len = c.get_name().length();
    else if (field == MyContact::kFldPhone)
      curr_len = c.get_phone().length();
    else if (field == MyContact::kFldAddress)
      curr_len = c.get_address().length();
    else if (field == MyContact::kFldEmail)
      curr_len = c.get_email().length();
    else
      curr_len = c.get_notes().length();

    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int MyContact::get_name_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, MyContact::kFldName);
}

int MyContact::get_phone_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, MyContact::kFldPhone);
}

int MyContact::get_address_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, MyContact::kFldAddress);
}

int MyContact::get_email_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, MyContact::kFldEmail);
}

int MyContact::get_notes_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, MyContact::kFldNotes);
}

std::string MyContact::get_divider(int width) {
  std::string div;
  for (int i = 1; i <= width; i++)
    div += "_";

  return div;
}

std::string MyContact::get_aligned_fld_header(const std::string &fld_s, int &fld_pw) {
  std::cout << "fld_s: " << fld_s << " fld_pw: " << fld_pw << std::endl;

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

void MyContact::print_contacts() {
  print_contacts(contact_ls, eSortField, eSortType);
}

void MyContact::print_contacts(std::vector<Contact> &ct_ls, SortField &sort_field, SortType &sort_type) {
  int no_pw = get_no_pw(ct_ls);
  std::string no_header = get_aligned_fld_header(MyContact::kFldNO, no_pw);

  int name_pw = get_name_pw(ct_ls);
  std::string name_header = get_aligned_fld_header(MyContact::kFldName, name_pw);

  int phone_pw = get_phone_pw(ct_ls);
  std::string phone_header = get_aligned_fld_header(MyContact::kFldPhone, phone_pw);

  int address_pw = get_address_pw(ct_ls);
  std::string address_header = get_aligned_fld_header(MyContact::kFldAddress, address_pw);

  int email_pw = get_email_pw(ct_ls);
  std::string email_header = get_aligned_fld_header(MyContact::kFldEmail, email_pw);

  int notes_pw = get_notes_pw(ct_ls);
  std::string notes_header = get_aligned_fld_header(MyContact::kFldNotes, notes_pw);

  int divider_pw =
      no_pw + name_pw + phone_pw + address_pw + email_pw + notes_pw +
          (int) MyContact::kFldDelimiter.length() * (MyContact::kFldCount + 1);
//  std::string divider = get_divider(divider_pw);


  std::string ct_count_str = " *TOTAL: " + std::to_string(ct_ls.size());
  std::string
      sort_info_str = "*SORT FIELD: " + get_sort_mode_name(sort_field) + " (" + get_sort_type_symbol(sort_type) + ") ";

  std::cout << UNDERLINE
            << std::left << ct_count_str
            << std::right << std::setw(divider_pw - (int) ct_count_str.length() + 2) << sort_info_str
            << CLOSE_UNDERLINE << std::endl;

  std::cout << UNDERLINE << MyContact::kFldDelimiter
            << no_header << MyContact::kFldDelimiter
            << name_header << MyContact::kFldDelimiter
            << phone_header << MyContact::kFldDelimiter
            << address_header << MyContact::kFldDelimiter
            << email_header << MyContact::kFldDelimiter
            << notes_header << MyContact::kFldDelimiter
            << CLOSE_UNDERLINE << std::endl;

  for (int i = 0; i < ct_ls.size(); i++) {
    Contact ct = ct_ls[i];
    int ct_number = i + 1;
    std::cout << UNDERLINE << MyContact::kFldDelimiter
              << std::right << std::setw(no_pw) << ct_number << MyContact::kFldDelimiter
              << std::right << std::setw(name_pw) << ct.get_name() << MyContact::kFldDelimiter
              << std::right << std::setw(phone_pw) << ct.get_phone() << MyContact::kFldDelimiter
              << std::right << std::setw(address_pw) << ct.get_address() << MyContact::kFldDelimiter
              << std::right << std::setw(email_pw) << ct.get_email() << MyContact::kFldDelimiter
              << std::right << std::setw(notes_pw) << ct.get_notes() << MyContact::kFldDelimiter
              << CLOSE_UNDERLINE << std::endl;

  }
}

void MyContact::set_sort_mode(int mode_code) {
  switch (mode_code) {
    case 0:eSortField = SortField::kName;
      break;

    case 1:eSortField = SortField::kPhone;
      break;

    case 2:eSortField = SortField::kAddress;
      break;

    case 3:eSortField = SortField::kEmail;
      break;

    case 4:eSortField = SortField::kNotes;
      break;
  }
}

int MyContact::get_sort_mode() const {
  return static_cast<int> (eSortField);
}

std::string MyContact::get_sort_mode_name() const {
  return kSortFields[get_sort_mode()];
}

std::string MyContact::get_sort_mode_name(SortField &sort_field) {
  return MyContact::kSortFields[static_cast<int> (sort_field)];
}

std::string MyContact::get_sort_type_symbol() const {
  if (eSortType == SortType::kAscending)
    return "↑";
  else
    return "↓";
}

std::string MyContact::get_sort_type_symbol(SortType &sort_type) {
  if (sort_type == SortType::kAscending)
    return "↑";
  else
    return "↓";
}

void MyContact::set_sort_type(int type_code) {
  if (type_code == 0)
    eSortType = SortType::kAscending;
  else
    eSortType = SortType::kDescending;
}

void MyContact::sort() {
  switch (eSortField) {
    case SortField::kName:sort_by_name();
      break;

    case SortField::kPhone:sort_by_phone();
      break;

    case SortField::kAddress: sort_by_address();
      break;

    case SortField::kEmail: sort_by_email();
      break;

    case SortField::kNotes: sort_by_notes();
      break;
  }
}

void MyContact::sort_by_name() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_name() < c2.get_name();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_name() > c2.get_name();
    });
}

void MyContact::sort_by_phone() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_phone() < c2.get_phone();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_phone() > c2.get_phone();
    });
}

void MyContact::sort_by_address() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_address() < c2.get_address();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_address() > c2.get_address();
    });
}

void MyContact::sort_by_email() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_email() < c2.get_email();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_email() > c2.get_email();
    });
}

void MyContact::sort_by_notes() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_notes() < c2.get_notes();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_notes() > c2.get_notes();
    });
}








