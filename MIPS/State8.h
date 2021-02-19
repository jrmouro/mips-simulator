/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State8.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 19:22
 */

#ifndef STATE8_H
#define STATE8_H

#include "State.h"

class State8 : public State{
public:
    State8();
    State8(const State8& orig);
    virtual ~State8();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE8_H */

