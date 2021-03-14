/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: ronaldo
 *
 * Created on 11 de Março de 2021, 16:17
 */

#ifndef MENU_H
#define MENU_H

#include <unordered_map>
#include <iostream>
#include <limits>
#include "MenuItem.h"

class Menu {
public:
    Menu(std::string);
    Menu(const Menu& orig);
    virtual ~Menu();
    bool addItem(MenuItem);
    friend std::ostream& operator<<(std::ostream& os, const Menu& obj);
    bool selectItem();
    void start();
    
private:
    std::vector<MenuItem> itens;
    std::string title;
    

};

#endif /* MENU_H */

