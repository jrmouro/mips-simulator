/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Estage.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 07:48
 */

#include "State.h"

State::State(std::string description) : description(description) {
}

State::State(const State& orig) : description(orig.description) {
}

State::~State() {
}

bool State::operator==(const State& right) const {
    return this->description == right.description;
}

std::string State::getDescription() const {
    return description;
}

std::string State::getJson() const {

    std::stringbuf buffer;
    std::ostream os(&buffer);

    os << "{ \"description\":\"" << this->description << "\" }";

    return buffer.str();

}

std::ostream& operator<<(std::ostream& os, const State& obj) {
    os << obj.description;
    return os;
}
