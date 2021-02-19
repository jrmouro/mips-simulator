/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToJson.h
 * Author: ronaldo
 *
 * Created on 18 de Fevereiro de 2021, 19:08
 */

#ifndef TOJSON_H
#define TOJSON_H

#include <string>

class ToJson {
public:
    virtual std::string getJson() const = 0;
};

#endif /* TOJSON_H */

