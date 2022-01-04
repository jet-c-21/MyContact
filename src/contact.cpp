//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/2/22
//
#include <iostream>
#include "contact.hpp"
#include "ult.hpp"

std::string const Contact::kMCSVDelimiter = "<|>";
std::string const Contact::kColName = "Name";
std::string const Contact::kColPhone = "Phone";
std::string const Contact::kColAddress = "Address";
std::string const Contact::kColEmail = "Email";
std::string const Contact::kColNotes = "Notes";
std::string const Contact::kColumns[] = {Contact::kColName,
                                         Contact::kColPhone,
                                         Contact::kColAddress,
                                         Contact::kColEmail,
                                         Contact::kColNotes};

Contact::Contact() {
  m_name = "";
  m_phone = "";
  m_address = "";
  m_email = "";
  m_notes = "";
}

Contact::Contact(const std::string &name,
                 const std::string &phone,
                 const std::string &address,
                 const std::string &email,
                 const std::string &notes) {
  m_name = name;
  m_phone = phone;
  m_address = address;
  m_email = email;
  m_notes = notes;
}

Contact::Contact(const std::string &mcsv_str) {
  std::vector<std::string> d_str_ls = g_ult::split_str(mcsv_str, kMCSVDelimiter);
//  std::cout << d_str_ls.size() << std::endl;

  for (int i = 0; i < Contact::kColCount; i++) {
    if(Contact::kColumns[i] == Contact::kColName)
      set_name(d_str_ls[i]);
    else if (Contact::kColumns[i] == Contact::kColPhone)
      set_phone(d_str_ls[i]);
    else if (Contact::kColumns[i] == Contact::kColAddress)
      set_address(d_str_ls[i]);
    else if (Contact::kColumns[i] == Contact::kColEmail)
      set_email(d_str_ls[i]);
    else
      set_notes(d_str_ls[i]);
  }


}

Contact::~Contact() {
//  std::cout << "Contact Instance Destructed." << std::endl;
//  delete m_name;
//  delete m_phone;
//  delete m_address;
//  delete m_email;
//  delete m_notes
}

void Contact::set_name(const std::string &name) {
  m_name = name;
}

std::string Contact::get_name() const {
  return m_name;
}

void Contact::set_phone(const std::string &phone) {
  m_phone = phone;
}

std::string Contact::get_phone() const {
  return m_phone;
}

void Contact::set_address(const std::string &address) {
  m_address = address;
}

std::string Contact::get_address() const {
  return m_address;
}

void Contact::set_email(const std::string &email) {
  m_email = email;
}

std::string Contact::get_email() const {
  return m_email;
}

void Contact::set_notes(const std::string &notes) {
  m_notes = notes;
}

std::string Contact::get_notes() const {
  return m_notes;
}

void Contact::print_info() {
  std::cout << "Name: " << m_name << std::endl;
  std::cout << "Phone: " << m_phone << std::endl;
  std::cout << "Address: " << m_address << std::endl;
  std::cout << "Email: " << m_email << std::endl;
  std::cout << "Notes: " << m_notes << std::endl;
}

std::string Contact::to_mcsv_str() const {
  return m_name + Contact::kMCSVDelimiter +
      m_phone + Contact::kMCSVDelimiter +
      m_address + Contact::kMCSVDelimiter +
      m_email + Contact::kMCSVDelimiter +
      m_notes;
}

std::string Contact::get_mcsv_header() {
  return Contact::kColName + Contact::kMCSVDelimiter +
      Contact::kColPhone + Contact::kMCSVDelimiter +
      Contact::kColAddress + Contact::kMCSVDelimiter +
      Contact::kColEmail + Contact::kMCSVDelimiter +
      Contact::kColNotes;
}

bool Contact::is_match(const std::string &query) {
  if(get_name().find(query)!= std::string::npos)
    return true;

  else if (get_phone().find(query)!= std::string::npos)
    return true;

//  else if (get_address().find(query)!= std::string::npos)
//    return true;
//
//  else if (get_email().find(query)!= std::string::npos)
//    return true;
//
//  else if (get_notes().find(query)!= std::string::npos)
//    return true;

  return false;
}






