#include "contact.h"
#include <sstream>

string Contact::trim(const string& s) const{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");

    if (start == string::npos)
        return "";

    return s.substr(start, end - start + 1);
}
// проверяем имя, емейл, телефон, дату

bool Contact::valname(const string& s) const{
    regex pattern(R"(^[A-Za-zА-Яа-яЁё -][A-Za-zА-Яа-яЁё -]*$)");
    return regex_match(s, pattern);
}

bool Contact::valemail(const string& s) const {
    regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex_match(s, pattern);
}

bool Contact::valphone(const string& s) const {
    regex pattern(R"(^(\+7|8)\(?\d{3}\)?\d{3}-?\d{2}-?\d{2}$)");
    return regex_match(s, pattern);
}

bool Contact::valdate(const string& s) const{
    regex pattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
    if (!regex_match(s, pattern)) return false;

    int day = stoi(s.substr(0,2));
    int month = stoi(s.substr(3, 2));
    int year = stoi(s.substr(6, 4));

    if (month < 1 || month > 12) return false;
    int daysinmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 20, 31};

    bool visokos = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (month == 2 && visokos) {
        if (day > 29) return false;
    } else{
        if (day > daysinmonth[month - 1]) return false;
    }

    return day >= 1;
}


// Вводим данные 

void Contact::input() {
    string s;

    do {
        cout << "Введите ваше имя: ";
        getline(cin, s);
        s = trim(s);
        if (!valname(s))
            cout << "Некорректное имя. Попробуйте ещё раз. \n";
    } while (!valname(s));
    name = s;

    do {
        cout << "Введите вашу фамилию: ";
        getline(cin, s);
        s = trim(s);
        if (!valname(s))
            cout << "Некорректная фамилия. Попробуйте ещё раз. \n";
    } while (!valname(s));
    surname = s;

    cout << "Введите ваше отчество: ";
    getline(cin, otchestvo);
    otchestvo = trim(otchestvo);


    cout << "Введите ваш адрес: ";
    getline(cin, s);
    address = trim(address);

    do{
        cout << "Введите ваш email: ";
        getline(cin, s);
        s = trim(s);
        if (!valemail(s))
            cout << "Некорректный email. Попробуйте ещё раз.";
    } while (!valemail(s));
    email = s;
    
    do {
        cout << "Введите вашу дату рождения: ";
        getline(cin, s);
        s = trim(s);
        if (!valdate(s))
            cout << "Некорректная дата рождения. Попробуйте ещё раз: ";
    } while (!valdate(s));
    bd = s;

    phones.clear();
    cout << "Введите номера телефонов (в конце нажмите Enter): \n";
    while(true){
        cout << "Телефон: ";
        getline(cin, s);
        s = trim(s);
        if(s.empty()) break;
        if(!valphone(s)){
            cout << "Некорректный номер. Попробуйте ещё раз: \n";
            continue;
        }

        phones.push_back(s);
    }
};

// Вывод контакта

void Contact::print() const{
    cout << surname << " " << name;
    if (!otchestvo.empty())
        cout << " " << otchestvo;
    cout << "\n Адрес: " << address << "\n Email: " << email
    << "\n Дата Рождения: " << bd << "\n Номера телефонов: ";

    for (auto& p : phones)
        cout << " " << p << endl;
}

// Сериализация
string Contact::serialize() const{
    string phonesstring;
    for (int i = 0; i < phones.size(); i++){
        phonesstring += phones[i];
        if (i < phones.size() - 1)
            phonesstring += "|";
    }
    return name + ";" + surname + ";" + otchestvo + ";" + email + ";" + address + ";" + bd + ";" + phonesstring;

}


// Десериализация
Contact Contact::deserialize(const string& line) {
    Contact c;
    stringstream ss(line);
    string field;

    vector<string> parts;
    while (getline(ss, field, ";"))
        parts.push_back(field);

    c.name = parts[0];
    c.surname = parts[1];
    c.otchestvo = parts[2];
    c.address = parts[3];
    c.bd = parts[4];
    c.email = parts[5];

    string phonesstring = parts[6];
    size_t start = 0, pos;
    while ((pos = phonesstring.find('|', start)) != string::npos){
        c.phones.push_back(phonesstring.substr(start, pos - start));
        start = pos + 1;
    }
    if (start < phonesstring.size())
        c.phones.push_back(phonesstring.substr(start));

    return c;
}

// поиск 
bool Contact::match(const string& q) const {
    string low = q;
    for (auto& ch : low) ch = tolower(ch);
    
    auto contains = [&](const string& s) {
        string t = s;
        for (auto& ch : t) ch = tolower(ch);
        return t.find(low) != string::npos;
    };

    if (contains(name)) return true;
    if (contains(surname)) return true;
    if (contains(email)) return true;

    for (auto& p : phones)
        if (contains(p)) return true;

    return false;
}

