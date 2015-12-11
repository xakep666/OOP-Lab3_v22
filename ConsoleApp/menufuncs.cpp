#include <iostream>
#include <string>
#include "menufuncs.h"
using namespace std;
void PrintMenu(const std::string text[],size_t size) {
    for(size_t i=0;i<size;i++) {
        cout << i << ": " <<text[i]<<endl;
    }
}

int getMenuPt(size_t size) {
    uint num;
    do{
        cout << "Введите номер пункта меню: ";
        cin >> num;
        cin.clear();
        cin.ignore();
    }while(!cin.good() || (uint)num>=size);
    return num;
}
