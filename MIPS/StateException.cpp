/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateException.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 19:06
 */

#include "StateException.h"

StateException::StateException(std::string msg):State("State Exception: " + msg) {}

StateException::StateException(const StateException& orig):State(orig) {}

StateException::~StateException() {}

State* StateException::getNext(Machine *machine)const{
    return new StateException(*this);
}

