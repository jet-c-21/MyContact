//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <string>

class Contact {
 private:
  std::string m_name;
  std::string m_phone;
  std::string m_address;
  std::string m_email;
  std::string m_notes;

 public:
  // Constructor Functions
  Contact();
  Contact(const std::string &name, const std::string &phone, const std::string &address,
          const std::string &email, const std::string &notes);

  // Destructor Functions
  ~Contact();

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
};
