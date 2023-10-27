//Axel Godoy y Erika Garcia
//Clase de un menu

#include <iostream>
#include <ctime>
#include <vector>
#include "AlimentoMenu.h"
#include "Usuario.h"
using namespace std;
#pragma once


class Menu {
private:
    Usuario usuario;
    int limiteCalorias;
    time_t fecha;
    vector<const AlimentoMenu*> alimentosMenu;

public:
    Menu() {} //Constructor por omision
    Menu(const Usuario& usuario, int limiteCalorias, tm* fecha) : usuario(usuario), limiteCalorias(limiteCalorias), fecha(mktime(fecha)) {} //Constructor
    Menu(const Menu& otro) : usuario(otro.usuario), limiteCalorias(otro.limiteCalorias), fecha(otro.fecha), alimentosMenu(otro.alimentosMenu) {} //Constructor copia
    ~Menu() {} //Destructor

    void agregarAlimento(const AlimentoMenu& alimento) { //Funcion para agregar alimentos al menu
        alimentosMenu.push_back(&alimento);
    }

    int getCaloriasConsumidas() const {
        int totalCalorias = 0;

        for (const auto& alimento : alimentosMenu) {
            totalCalorias += alimento->getCalorias(); //Suma las calorias de los alimentos
        }

        return totalCalorias;
    }

    //Funcion para mostrar el resumen del menu
    void mostrarResumen() const {
        cout << "\nMenú creado por: " << usuario.getNombre() << endl;
        cout << "Fecha de creación: " << asctime(localtime(&fecha));
        cout << "Alimentos en el menú:" << endl;

        for (const auto& alimento : alimentosMenu) {
            cout << "- " << alimento->getNombre() << " (" << alimento->getCalorias() << " kcal)" << endl;
        }

        cout << "Calorías totales: " << getCaloriasConsumidas() << " kcal" << endl;

        if (getCaloriasConsumidas() <= limiteCalorias) { //Compara las calorias consumidas con el limite de calorias
            cout << "Se ha alimentado bien." << endl;
        } else {
            cout << "Se ha pasado del límite calórico." << endl;
        }
    }

    tm* getFecha() const { //Obtiene la fecha
        return localtime(&fecha);
    }
};