//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <iostream>
#include "contact.hpp"

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




