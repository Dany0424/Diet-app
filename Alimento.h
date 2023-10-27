//Axel Godoy y Erika Garcia
//Clase Alimento que hereda de la clase AlimentoMenu

#include <iostream>
#include "AlimentoMenu.h"
using namespace std;
#pragma once


class Alimento : public AlimentoMenu{ 
private:
    string nombre;
    int calorias;

public:
    Alimento() {} //Constructor por omision
    Alimento(const string& nombre, int calorias) : nombre(nombre), calorias(calorias) {} //Constructor
    Alimento(const Alimento& otro) : nombre(otro.nombre), calorias(otro.calorias) {} //Constructor copia
    ~Alimento() {} //Destructor

    string getNombre() const override {
        return nombre;
    }

    int getCalorias() const override {
        return calorias;
    }

    bool operator==(const Alimento& otro) const {  //Sobrecarga del operador ==
    return nombre == otro.nombre && calorias == otro.calorias; 
    }   

};