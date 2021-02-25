/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State9.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 19:22
 */

#ifndef STATE9_H
#define STATE9_H

#include "State.h"

class State9 : public State{
public:
    State9();
    State9(const State9& orig);
    State9(Machine*);
    virtual ~State9();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE9_H */

