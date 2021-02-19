/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateException.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 19:06
 */

#ifndef STATEEXCEPTION_H
#define STATEEXCEPTION_H

#include "State.h"

class StateException : public State{
public:
    StateException();
    StateException(const StateException& orig);
    virtual ~StateException();
    virtual State* getNext(Machine *machine) const;
};

#endif /* STATEEXCEPTION_H */

