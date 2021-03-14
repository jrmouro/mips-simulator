/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: ronaldo
 * 
 * Created on 11 de Março de 2021, 16:17
 */

#include <vector>

#include "Menu.h"

Menu::Menu(std::string title) : title(title) {
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

bool Menu::addItem(MenuItem item) {
    this->itens.push_back(item);
    return true;
}

bool Menu::selectItem() {
    int input;
    std::cout << "Digite a opção desejada: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (itens.size() > 0 && input > 0 && input <= itens.size()) {
        return itens[input - 1].GetTarget()();
    }
    return false;
}

void Menu::start() {
    std::cout << *this << std::endl;
    while (selectItem())
        std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Menu& obj) {
    int i = 1;
    os << obj.title << std::endl;
    for (auto menuitem : obj.itens) {
        os << i << " - " << menuitem << std::endl;
        i++;
    }
    return os;
}
