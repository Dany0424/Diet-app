//Axel Godoy y Erika Garcia
//Clase de una persona que sera heredada a la clase usuario

#include <iostream>
using namespace std;
#pragma once


class Persona {
private:
    string nombre;
    int edad;
    int peso;
    int altura;

public:
    Persona() {} //Constructor por omision
    Persona(const string& nombre, int edad, int peso, int altura) : nombre(nombre), edad(edad), peso(peso), altura(altura) {} //Constructor
    Persona(const Persona& otro) : nombre(otro.nombre), edad(otro.edad), peso(otro.peso), altura(otro.altura) {} //Constructor copia
    ~Persona() {} //Destructor

    string getNombre() const { //Funcion para obtener el nombre
        return nombre;
    }

    int getEdad() const { //Funcion para obtener la edad
        return edad;
    }

    int getPeso() const { //Funcion para obtener el peso
        return peso;
    }

    int getAltura() const { //Funcion para obtener la altura
        return altura;
    }
};