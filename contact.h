#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include <regex>

#include <iostream>
using namespace std;

class Contact {
private:
    string name;
    string surname;
    string otchestvo;
    string address;
    string bd;
    string email;
    vector <string> phones;

    bool valname(const string& s) const;
    bool valemail(const string& s) const;
    bool valphone(const string& s) const;
    bool valdate(const string& s) const;

    string trim(const string& s) const;

public:
    void input();
    void print() const;

    string serialize() const;
    static Contact deserialize(const string& line);

    bool match(const string& q) const;

    string getname() const {return name;}
    string getsurname() const {return surname;}
    string getemail() const {return email;}

};
#endif

