/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State6.h
 * Author: ronaldo
 *
 * Created on 14 de Fevereiro de 2021, 17:42
 */

#ifndef STATE6_H
#define STATE6_H

#include "State.h"

class State6 : public State{
public:
    State6();
    State6(const State6& orig);
    virtual ~State6();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE6_H */

