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
#include <map>
#include <algorithm>
#include "ult.hpp"
#include "contact_manager.hpp"
#define print(x) std::cout << x << std::endl

std::string const ContactManager::kDataDir = "data";
std::string const ContactManager::kContactFilePath = ContactManager::kDataDir + "/contacts.mcsv";
std::string const ContactManager::kFldDelimiter = "|";
std::string const ContactManager::kFldNO = "No.";
std::string const ContactManager::kFldName = "Name";
std::string const ContactManager::kFldPhone = "Phone";
std::string const ContactManager::kFldAddress = "Address";
std::string const ContactManager::kFldEmail = "Email";
std::string const ContactManager::kFldNotes = "Notes";
std::string const ContactManager::kFields[] = {ContactManager::kFldNO,
                                               ContactManager::kFldName,
                                               ContactManager::kFldPhone,
                                               ContactManager::kFldAddress,
                                               ContactManager::kFldEmail,
                                               ContactManager::kFldNotes};

std::string const ContactManager::kSortFields[] = {ContactManager::kFldName,
                                                   ContactManager::kFldPhone,
                                                   ContactManager::kFldAddress,
                                                   ContactManager::kFldEmail,
                                                   ContactManager::kFldNotes};

ContactManager::ContactManager() {
  if (find_contact_file()) {
    contact_ls = read_mcsv(kContactFilePath);
    sort();
  }
}

ContactManager::ContactManager(const std::string &contact_file_path) {
  contact_ls = read_mcsv(kContactFilePath);
}

ContactManager::~ContactManager() {

}

bool ContactManager::find_data_dir() {
  struct stat info;
  return stat(kDataDir.c_str(), &info) == 0 && info.st_mode & S_IFDIR;
}

bool ContactManager::find_contact_file() {
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

std::vector<Contact> ContactManager::read_mcsv(const std::string &mcsv_file_path) {
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

int ContactManager::get_contact_count() {
  return contact_ls.size();
}

int ContactManager::get_no_pw(std::vector<Contact> &ct_ls) {
  int fld_len = ContactManager::kFldNO.length();
  std::string ct_count_str = std::to_string(ct_ls.size());
  int no_len = ct_count_str.length();

  if (fld_len > no_len)
    return fld_len;

  return no_len;
}

int ContactManager::get_field_pw(std::vector<Contact> &ct_ls, const std::string &field) {
  int print_width = field.length();

  for (Contact &c: ct_ls) {
    int curr_len;
    if (field == ContactManager::kFldName)
      curr_len = c.get_name().length();
    else if (field == ContactManager::kFldPhone)
      curr_len = c.get_phone().length();
    else if (field == ContactManager::kFldAddress)
      curr_len = c.get_address().length();
    else if (field == ContactManager::kFldEmail)
      curr_len = c.get_email().length();
    else
      curr_len = c.get_notes().length();

    if (curr_len > print_width)
      print_width = curr_len;
  }

  return print_width;
}

int ContactManager::get_name_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, ContactManager::kFldName);
}

int ContactManager::get_phone_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, ContactManager::kFldPhone);
}

int ContactManager::get_address_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, ContactManager::kFldAddress);
}

int ContactManager::get_email_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, ContactManager::kFldEmail);
}

int ContactManager::get_notes_pw(std::vector<Contact> &ct_ls) {
  return get_field_pw(ct_ls, ContactManager::kFldNotes);
}

std::string ContactManager::get_divider(int width) {
  std::string div;
  for (int i = 1; i <= width; i++)
    div += "_";

  return div;
}

std::string ContactManager::get_aligned_fld_header(const std::string &fld_s, int &fld_pw) {
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

void ContactManager::print_contacts() {
  print_contacts(contact_ls, eSortField, eSortType);
}

void ContactManager::print_contacts(std::vector<Contact> &ct_ls, SortField &sort_field, SortType &sort_type) {
  int no_pw = get_no_pw(ct_ls);
  std::string no_header = get_aligned_fld_header(ContactManager::kFldNO, no_pw);

  int name_pw = get_name_pw(ct_ls);
  std::string name_header = get_aligned_fld_header(ContactManager::kFldName, name_pw);

  int phone_pw = get_phone_pw(ct_ls);
  std::string phone_header = get_aligned_fld_header(ContactManager::kFldPhone, phone_pw);

  int address_pw = get_address_pw(ct_ls);
  std::string address_header = get_aligned_fld_header(ContactManager::kFldAddress, address_pw);

  int email_pw = get_email_pw(ct_ls);
  std::string email_header = get_aligned_fld_header(ContactManager::kFldEmail, email_pw);

  int notes_pw = get_notes_pw(ct_ls);
  std::string notes_header = get_aligned_fld_header(ContactManager::kFldNotes, notes_pw);

  int divider_pw =
      no_pw + name_pw + phone_pw + address_pw + email_pw + notes_pw +
          (int) ContactManager::kFldDelimiter.length() * (ContactManager::kFldCount + 1);

  std::string ct_count_str = " *TOTAL: " + std::to_string(ct_ls.size());
  std::string
      sort_info_str = "*SORT FIELD: " + get_sort_mode_name(sort_field) + " (" + get_sort_type_symbol(sort_type) + ") ";
  std::cout << UNDERLINE
            << std::left << ct_count_str
            << std::right << std::setw(divider_pw - (int) ct_count_str.length() + 2) << sort_info_str
            << CLOSE_UNDERLINE << std::endl;

  std::cout << UNDERLINE << ContactManager::kFldDelimiter
            << no_header << ContactManager::kFldDelimiter
            << name_header << ContactManager::kFldDelimiter
            << phone_header << ContactManager::kFldDelimiter
            << address_header << ContactManager::kFldDelimiter
            << email_header << ContactManager::kFldDelimiter
            << notes_header << ContactManager::kFldDelimiter
            << CLOSE_UNDERLINE << std::endl;

  for (int i = 0; i < ct_ls.size(); i++) {
    Contact ct = ct_ls[i];
    int ct_number = i + 1;
    std::cout << UNDERLINE << ContactManager::kFldDelimiter
              << std::right << std::setw(no_pw) << ct_number << ContactManager::kFldDelimiter
              << std::right << std::setw(name_pw) << ct.get_name() << ContactManager::kFldDelimiter
              << std::right << std::setw(phone_pw) << ct.get_phone() << ContactManager::kFldDelimiter
              << std::right << std::setw(address_pw) << ct.get_address() << ContactManager::kFldDelimiter
              << std::right << std::setw(email_pw) << ct.get_email() << ContactManager::kFldDelimiter
              << std::right << std::setw(notes_pw) << ct.get_notes() << ContactManager::kFldDelimiter
              << CLOSE_UNDERLINE << std::endl;

  }
}

void ContactManager::set_sort_mode(int mode_code) {
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

int ContactManager::get_sort_mode() const {
  return static_cast<int> (eSortField);
}

std::string ContactManager::get_sort_mode_name() const {
  return kSortFields[get_sort_mode()];
}

std::string ContactManager::get_sort_mode_name(SortField &sort_field) {
  return ContactManager::kSortFields[static_cast<int> (sort_field)];
}

std::string ContactManager::get_sort_type_symbol() const {
  if (eSortType == SortType::kAscending)
    return "↑";
  else
    return "↓";
}

std::string ContactManager::get_sort_type_symbol(SortType &sort_type) {
  if (sort_type == SortType::kAscending)
    return "↑";
  else
    return "↓";
}

void ContactManager::set_sort_type(int type_code) {
  if (type_code == 0)
    eSortType = SortType::kAscending;
  else
    eSortType = SortType::kDescending;
}

void ContactManager::sort() {
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

void ContactManager::sort_by_name() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_name() < c2.get_name();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_name() > c2.get_name();
    });
}

void ContactManager::sort_by_phone() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_phone() < c2.get_phone();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_phone() > c2.get_phone();
    });
}

void ContactManager::sort_by_address() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_address() < c2.get_address();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_address() > c2.get_address();
    });
}

void ContactManager::sort_by_email() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_email() < c2.get_email();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_email() > c2.get_email();
    });
}

void ContactManager::sort_by_notes() {
  if (eSortType == SortType::kAscending)
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_notes() < c2.get_notes();
    });
  else
    std::sort(contact_ls.begin(), contact_ls.end(), [](const Contact &c1, const Contact &c2) {
      return c1.get_notes() > c2.get_notes();
    });
}
std::vector<Contact> ContactManager::select_contacts(const std::string &query) {
  std::vector<Contact> result;

  for (Contact ct: contact_ls) {
    if (ct.is_match(query))
      result.push_back(ct);
  }

  return result;
}

void ContactManager::search(const std::string &query) {
  std::vector<Contact> search_res = select_contacts(query);

  std::string msg;
  if (search_res.empty()) {
    msg = "No matched Contact.";
    std::cout << msg << std::endl;
    return;
  }

  msg = "Query: \"" + query + "\" \n" +
      "Search Result Count: " + std::to_string(search_res.size()) + "\n";
  std::cout << msg;

  int no_pw = get_no_pw(search_res);
  std::string no_header = get_aligned_fld_header(ContactManager::kFldNO, no_pw);

  int name_pw = get_name_pw(search_res);
  std::string name_header = get_aligned_fld_header(ContactManager::kFldName, name_pw);

  int phone_pw = get_phone_pw(search_res);
  std::string phone_header = get_aligned_fld_header(ContactManager::kFldPhone, phone_pw);

  int address_pw = get_address_pw(search_res);
  std::string address_header = get_aligned_fld_header(ContactManager::kFldAddress, address_pw);

  int email_pw = get_email_pw(search_res);
  std::string email_header = get_aligned_fld_header(ContactManager::kFldEmail, email_pw);

  int notes_pw = get_notes_pw(search_res);
  std::string notes_header = get_aligned_fld_header(ContactManager::kFldNotes, notes_pw);

  int divider_pw =
      no_pw + name_pw + phone_pw + address_pw + email_pw + notes_pw +
          (int) ContactManager::kFldDelimiter.length() * (ContactManager::kFldCount + 1);

  std::cout << UNDERLINE
            << std::setw(divider_pw) << " "
            << CLOSE_UNDERLINE << std::endl;

  std::cout << UNDERLINE << ContactManager::kFldDelimiter
            << no_header << ContactManager::kFldDelimiter
            << name_header << ContactManager::kFldDelimiter
            << phone_header << ContactManager::kFldDelimiter
            << address_header << ContactManager::kFldDelimiter
            << email_header << ContactManager::kFldDelimiter
            << notes_header << ContactManager::kFldDelimiter
            << CLOSE_UNDERLINE << std::endl;

  for (int i = 0; i < search_res.size(); i++) {
    Contact ct = search_res[i];
    int ct_number = i + 1;
    std::cout << UNDERLINE << ContactManager::kFldDelimiter
              << std::right << std::setw(no_pw) << ct_number << ContactManager::kFldDelimiter
              << std::right << std::setw(name_pw) << ct.get_name() << ContactManager::kFldDelimiter
              << std::right << std::setw(phone_pw) << ct.get_phone() << ContactManager::kFldDelimiter
              << std::right << std::setw(address_pw) << ct.get_address() << ContactManager::kFldDelimiter
              << std::right << std::setw(email_pw) << ct.get_email() << ContactManager::kFldDelimiter
              << std::right << std::setw(notes_pw) << ct.get_notes() << ContactManager::kFldDelimiter
              << CLOSE_UNDERLINE << std::endl;

  }

}








