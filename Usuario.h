//Axel Godoy y Erika Garcia
//Clase Usuario que hereda de la clase Persona

#include <iostream>
#include "Persona.h"
using namespace std;
#pragma once


class Usuario : public Persona { //Clase hija de Persona
private:
    int numMenus;
public:
    Usuario() : numMenus(0) {} //Constructor por omision
    Usuario(const string& nombre, int edad, int peso, int altura, int numMenus) : Persona(nombre, edad, peso, altura), numMenus(numMenus) {} //Constructor
    Usuario(const Persona& persona) : Persona(persona) {} //Constructor copia
    ~Usuario() {} //Destructor

    int getNumMenus() const { //Funcion para obtener el numero de menus
        return numMenus;
    }

    void incrementarNumMenus() { //Funcion para incrementar el numero de menus
        numMenus++;
    }
};