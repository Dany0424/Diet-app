//Axel Godoy y Erika Garcia
//Clase abstracta AlimentoMenu que sera heredada a las clases Alimento y Grupo

#include <iostream>
using namespace std;
#pragma once


class AlimentoMenu {  
public:
    AlimentoMenu() {} //Constructor por omision
    virtual ~AlimentoMenu() {} //Destructor
    virtual string getNombre() const = 0; //Funcion virtual pura
    virtual int getCalorias() const = 0; //Funcion virtual pura
};