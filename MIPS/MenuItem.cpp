/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuItem.cpp
 * Author: ronaldo
 * 
 * Created on 11 de Março de 2021, 16:18
 */

#include "MenuItem.h"

MenuItem::MenuItem(std::string description, std::function<bool()> target) : description(description), target(target) {
}

MenuItem::MenuItem(const MenuItem& orig) : description(orig.description), target(orig.target){
}

MenuItem::~MenuItem() {
}

 std::string MenuItem::GetDescription() const {
        return description;
    }

    void MenuItem::SetDescription(std::string description) {
        this->description = description;
    }

    std::function<bool() > MenuItem::GetTarget() const {
        return target;
    }

    void MenuItem::SetTarget(std::function<bool() > target) {
        this->target = target;
    }

    std::ostream& operator<<(std::ostream& os, const MenuItem& obj) {
        os << obj.description;
        return os;
    }
