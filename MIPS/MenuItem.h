/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuItem.h
 * Author: ronaldo
 *
 * Created on 11 de Março de 2021, 16:18
 */

#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>
#include <functional>

class MenuItem {

public:
    MenuItem(std::string, std::function<bool()>);
    MenuItem(const MenuItem& orig);
    virtual ~MenuItem();
    std::string GetDescription() const;
    void SetDescription(std::string description);
    std::function<bool() > GetTarget() const;
    void SetTarget(std::function<bool() > target);
    friend std::ostream& operator<<(std::ostream& os, const MenuItem& obj);
    
private:
    std::string description;
    std::function<bool()> target;
    
};

#endif /* MENUITEM_H */

