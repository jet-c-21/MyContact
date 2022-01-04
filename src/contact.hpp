//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/2/22
//

#ifndef MYCONTACT_SRC_CONTACT_HPP_
#define MYCONTACT_SRC_CONTACT_HPP_

#include <string>

#define UNDERLINE "\033[4m"
#define CLOSE_UNDERLINE "\033[0m"

class Contact {
 public:
  static const int kColCount = 5;
  static const std::string kColumns[];

 private:
  static const std::string kMCSVDelimiter;
  static const std::string kColName;
  static const std::string kColPhone;
  static const std::string kColAddress;
  static const std::string kColEmail;
  static const std::string kColNotes;

  std::string m_name;
  std::string m_phone;
  std::string m_address;
  std::string m_email;
  std::string m_notes;

 public:
  // Constructor
  Contact();
  Contact(const std::string &name, const std::string &phone, const std::string &address,
          const std::string &email, const std::string &notes);
  explicit Contact(const std::string &mcsv_str);

  // Destructor
  ~Contact();

  // Static Method
  static std::string get_mcsv_header();

  void set_name(const std::string &name);
  std::string get_name() const;

  void set_phone(const std::string &phone);
  std::string get_phone() const;

  void set_address(const std::string &address);
  std::string get_address() const;

  void set_email(const std::string &email);
  std::string get_email() const;

  void set_notes(const std::string &notes);
  std::string get_notes() const;

  void print_info();
  std::string to_mcsv_str() const;

  bool is_match(const std::string &query);

};

#endif //MYCONTACT_SRC_CONTACT_HPP_
