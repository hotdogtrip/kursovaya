#include "phonebook.h"
#include <iostream>
#include <fstream>
using namespace std;

void Phonebook::addcontact(){
    Contact c;
    c.input();
    contacts.push_back(c);
}

void Phonebook::showall() const{
    if (contacts.empty()){
        cout << "Список пуст" << endl;
        return;
    }
    for (const auto& c : contacts) c.print();
}

void Phonebook::save(const string& file) const{
    ofstream out(file);
    if(!out){
        cout << "Ошибка" << endl;
        return;
    }
    for (const auto& c : contacts) out << c.serialize() << "\n";
    cout << "Данные сохранены" << endl;
}

void Phonebook::load(const string& file){
    ifstream in(file);
    if (!in) return;
    string line;
    while(getline(in, line)) contacts.push_back(Contact::deserialize(line));
}

void Phonebook::menu(){
    int cmd;
    while (true){
        cout << "\n 1 - Добавить контакт";
        cout << "\n 2 - Показать все контакты";
        cout << "\n 3 - Сохранить в файл";
        cout << "\n 4 - Поиск";
        cout << "\n 5 - Выход";
        cout << "\n";

        cin >> cmd;
        cin.ignore();

        if (cmd == 1) addcontact();
        else if (cmd == 2) showall();
        else if (cmd == 3) save("contacts.txt");
        else if (cmd == 4) search();
        else if (cmd == 5) break;
    }
}
void Phonebook::search() const {
    if (contacts.empty()) {
        cout << "Пусто\n";
        return;
    }

    cout << "Введите строку для поиска: ";
    string q;
    getline(cin, q);

    bool found = false;

    for (const auto& c : contacts) {
        if (c.match(q)) {
            c.print();
            found = true;
        }
    }

    if (!found)
        cout << "Ничего не найдено\n";
}