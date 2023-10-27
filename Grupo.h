//Axel Godoy y Erika Garcia
//Clase Grupo que hereda de la clase AlimentoMenu

#include <iostream>
#include <vector>
#include "AlimentoMenu.h"
#include "Alimento.h"
using namespace std;
#pragma once


class Grupo : public AlimentoMenu { 
private:
    string nombre;
    vector<Alimento> alimentos;

public:
    Grupo() {} //Constructor por omision
    Grupo(const string& nombre) : nombre(nombre) {} //Constructor
    Grupo(const Grupo& otro) : nombre(otro.nombre), alimentos(otro.alimentos) {} //Constructor copia
    ~Grupo() {} //Destructor

    void agregarAlimento(const Alimento& alimento) { //Funcion para agregar alimentos al grupo
        alimentos.push_back(alimento);
    }

    string getNombre() const override {
        return nombre;
    }

    int getCalorias() const override {
        int totalCalorias = 0;

        for (const auto& alimento : alimentos) {
            totalCalorias += alimento.getCalorias();
        }

        return totalCalorias;
    }

    const vector<Alimento>& getAlimentos() const {
        return alimentos;
    }
};