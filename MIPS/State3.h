/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State3.h
 * Author: ronaldo
 *
 * Created on 15 de Fevereiro de 2021, 04:34
 */

#ifndef STATE3_H
#define STATE3_H

#include "State.h"

class State3 : public State{
public:
    State3();
    State3(const State3& orig);
    State3(Machine*);
    virtual ~State3();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE3_H */

