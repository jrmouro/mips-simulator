/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 07:48
 */

#ifndef STATE_H
#define STATE_H

#include "Memory.h"
#include "ToJson.h"

class Machine;
class State : public ToJson{
public:    
    State(std::string description);
    State(const State& orig);
    virtual ~State();
    bool operator==(const State& right) const;
    virtual State* getNext(Machine *machine) const = 0;
    std::string getDescription() const;
    
    virtual std::string getJson() const;
    
    friend std::ostream& operator<<(std::ostream& os, const State& obj);

private:    
    std::string description;
};

#endif /* STATE_H */

