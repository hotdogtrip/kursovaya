#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "contact.h"
#include <vector>
#include <string>
using namespace std;

class Phonebook {
private:
    vector <Contact> contacts;

public:
    void addcontact(); // добавить контакт
    void showall() const; // показать все контакты
    void save(const string& file) const; // сохранить в файл
    void load(const string& file); // загрузить контакты из файла
    void menu(); // показать менб
    void search() const;
};

#endif