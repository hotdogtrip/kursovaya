#include <iostream>
#include "Phonebook.h"
using namespace std;


int main() {
setlocale(LC_ALL, "ru");


Phonebook pb;


// Загружаем данные из файла при запуске
pb.load("contacts.txt");


// Запускаем меню программы
pb.menu();


// Сохраняем данные при выходе
pb.save("contacts.txt");


return 0;
}