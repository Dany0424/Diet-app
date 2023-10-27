//Axel Godoy y Erika Garcia
//Clase SistemaInformacion

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Menu.h"
#include "Grupo.h"
#include "Usuario.h"
using namespace std;
#pragma once


class SistemaInformacion {
private:
    map<int, Menu> menus;
    map<int, Grupo> grupos;
    Usuario usuario;

public: 
    SistemaInformacion() {} //Constructor por omision
    SistemaInformacion(const Usuario& usuario) : usuario(usuario) {} //Constructor
    SistemaInformacion(const SistemaInformacion& otro) : menus(otro.menus), grupos(otro.grupos), usuario(otro.usuario) {} //Constructor copia
    ~SistemaInformacion() {} //Destructor

    void cargarGruposDesdeArchivo(const string& nombreArchivo) { //Carga los grupos desde un archivo
        ifstream archivo(nombreArchivo);

        if (!archivo) {
            cout << "Error al abrir el archivo " << nombreArchivo << endl;
            return;
        }

        string linea;
        int grupoActual = 0;

        while (getline(archivo, linea)) {
            if (linea.substr(0, 6) == "Grupo ") { //Si la linea empieza con "Grupo ", se crea un nuevo grupo
                grupoActual++;
                grupos.emplace(grupoActual, Grupo(linea.substr(7))); 
            } else if (!linea.empty()) {
                int posSeparador = linea.find('-'); //Se busca el separador '-'
                string nombreAlimento = linea.substr(2, posSeparador - 3);  //Se obtiene el nombre del alimento
                string caloriasStr = linea.substr(posSeparador + 2); //Se obtienen las calorias del alimento
                int calorias;

                try { //Excepcion para cuando las calorias no son un numero
                    calorias = stoi(caloriasStr);
                } catch (const std::invalid_argument&) {
                    cout << "Error: Las calorías no son un número válido para el alimento '" << nombreAlimento << "'. Se omitirá el alimento." << endl;
                    continue;
                }

                grupos.at(grupoActual).agregarAlimento(Alimento(nombreAlimento, calorias));
            }
        }

        archivo.close();
    }


    void registrarUsuario() { //Funcion para registrar un usuario
        string nombre;
        int edad, peso, altura;

        cout << "----- Registro de Usuario -----" << endl;
        cout << "Ingrese su nombre: ";
        cin.ignore();
        getline(cin, nombre); //No hay valiacion en el nombre ya que existen nombres con numeros o caracteres especiales

        while(true) {
            cout << "Ingrese su edad: ";
            cin >> edad;

            if(cin.fail()) { // Comprobamos si ocurrió un error en la última operación de entrada
                cin.clear(); // Limpia el estado de error en cin
                cin.ignore(); // Ignora los caracteres de entrada incorrectos
                cout << "Edad ingresada no es válida. Por favor, vuelve a intentarlo." << endl;
            } else {
                break; // Si la entrada fue exitosa, rompemos el bucle
            }
        }
        
        while(true) {
            cout << "Ingrese su peso en kg: ";
            cin >> peso;

            if(cin.fail()) { // Comprobamos si ocurrió un error en la última operación de entrada
                cin.clear(); // Limpia el estado de error en cin
                cin.ignore(); // Ignora los caracteres de entrada incorrectos
                cout << "Peso ingresado no es válida. Por favor, vuelve a intentarlo." << endl;
            } else {
                break; // Si la entrada fue exitosa, rompemos el bucle
            }
        }

        while(true) {
            cout << "Ingrese su altura en cm: ";
            cin >> altura;

            if(cin.fail()) { // Comprobamos si ocurrió un error en la última operación de entrada
                cin.clear(); // Limpia el estado de error en cin
                cin.ignore(); // Ignora los caracteres de entrada incorrectos
                cout << "Alturada ingresada no es válida. Por favor, vuelve a intentarlo." << endl;
            } else {
                break; // Si la entrada fue exitosa, rompemos el bucle
            }
        }

        usuario = Usuario(nombre, edad, peso, altura, 0);
        cout << "----- Usuario registrado exitosamente -----" << endl;
    }

    void crearMenu(int limiteCalorias) { //Crea un menu
        time_t now = time(0);
        tm* fecha = localtime(&now);

        Menu menu(usuario, limiteCalorias, fecha);

        bool agregarAlimento = true;

        //Ciclo para agregar alimentos al menu
        while (agregarAlimento) {
            cout << "\n----- Agregar Alimento al Menú -----" << endl;
            cout << "Seleccione el grupo alimenticio: " << endl;

            int i = 1;
            for (const auto& grupo : grupos) {
                cout << i << ". " << grupo.second.getNombre() << endl;
                i++;
            }

            int opcionGrupo;
            cout << "\nIngrese el número del grupo: ";
            cin >> opcionGrupo;

            if (opcionGrupo <= 0 || opcionGrupo > grupos.size()) {
                cout << "Número de grupo inválido. Intente nuevamente." << endl;
                continue;
            }

            const auto& grupoSeleccionado = grupos.find(opcionGrupo);
            if (grupoSeleccionado == grupos.end()) {
                cout << "Grupo inválido. Intente nuevamente." << endl;
                continue;
            }

            cout << "\nSeleccione el alimento del grupo: " << endl;

            int j = 1;
            for (const auto& alimento : grupoSeleccionado->second.getAlimentos()) {
                cout << j << ". " << alimento.getNombre() << " (" << alimento.getCalorias() << " kcal)" << endl;
                j++;
            }

            int opcionAlimento;
            cout << "\nIngrese el número del alimento: ";
            cin >> opcionAlimento;

            const auto& alimentoSeleccionado = grupoSeleccionado->second.getAlimentos();
            if (opcionAlimento <= 0 || opcionAlimento > alimentoSeleccionado.size()) {
                cout << "Número de alimento inválido. Intente nuevamente." << endl;
                continue;
            }

            const auto& alimento = alimentoSeleccionado[opcionAlimento - 1];
            menu.agregarAlimento(alimento);

            cout << "\n¿Desea agregar otro alimento al menú? (1: Sí / 0: No): ";
            cin >> agregarAlimento;

            cin.ignore(); 
        }

            if (usuario.getNumMenus() >= 4) {
                cout << "Ha alcanzado el límite diario de menús. No puede crear más menús hoy." << endl;
                return;
        }

        int menuId = menus.size() + 1;
        menus.emplace(menuId, menu);
        usuario.incrementarNumMenus(); // Incrementar el contador de menús creados por el usuario

        cout << "\nMenú creado exitosamente con ID: " << menuId << endl;
    }

    //Reportes diarios
    void mostrarReporteDiario(const time_t& fecha) {
        tm* fechaReporte = localtime(&fecha);

        cout <<"\n----- Reporte Diario - "<<fechaReporte->tm_mday<<"/"<<fechaReporte->tm_mon + 1<<"/"<<fechaReporte->tm_year + 1900<<" -----"<< endl;

        int totalCalorias = 0;

        for (const auto& menu : menus) {
            if (menu.second.getFecha()->tm_mday == fechaReporte->tm_mday &&
                menu.second.getFecha()->tm_mon == fechaReporte->tm_mon &&
                menu.second.getFecha()->tm_year == fechaReporte->tm_year) {
                menu.second.mostrarResumen();
                totalCalorias += menu.second.getCaloriasConsumidas();
            }
        }

        mostrarResumenCalorias(totalCalorias);
    }

    //Reportes semanales
void mostrarReporteSemanal() {
    cout << "\n----- Reporte Semanal -----"<< endl;

    time_t now = time(0);
    tm* fechaActual = localtime(&now);

    int totalCalorias = 0;

    for (const auto& menu : menus) {
        if (menu.second.getFecha()->tm_year == fechaActual->tm_year && 
            menu.second.getFecha()->tm_yday >= fechaActual->tm_yday - 6) {
            totalCalorias += menu.second.getCaloriasConsumidas();
            }
        }

        mostrarResumenCalorias(totalCalorias);
    }


    //Reportes mensuales
void mostrarReporteMensual() {
    cout << "\n----- Reporte Mensual -----"<< endl;

    time_t now = time(0);
    tm* fechaActual = localtime(&now);

    int totalCalorias = 0;

    for (const auto& menu : menus) {
        if (menu.second.getFecha()->tm_year == fechaActual->tm_year &&
            menu.second.getFecha()->tm_mon == fechaActual->tm_mon) { 
            totalCalorias += menu.second.getCaloriasConsumidas();
            }
        }

        mostrarResumenCalorias(totalCalorias);
    }


    //Reportes trimestrales
void mostrarReporteTrimestral() {
    cout << "\n----- Reporte Trimestral -----"<< endl;

    time_t now = time(0);
    tm* fechaActual = localtime(&now);

    int totalCalorias = 0;

    for (const auto& menu : menus) {
        if (menu.second.getFecha()->tm_year == fechaActual->tm_year &&
            menu.second.getFecha()->tm_mon >= fechaActual->tm_mon - 2) {
            totalCalorias += menu.second.getCaloriasConsumidas();
            }
        }

        mostrarResumenCalorias(totalCalorias);
    }


    //Reportes Anuales
void mostrarReporteAnual() {
    cout <<"\n----- Reporte Anual -----"<< endl;

    time_t now = time(0);
    tm* fechaActual = localtime(&now);

    int totalCalorias = 0;

    for (const auto& menu : menus) {
        if (menu.second.getFecha()->tm_year == fechaActual->tm_year) {
            totalCalorias += menu.second.getCaloriasConsumidas();
            }
        }

        mostrarResumenCalorias(totalCalorias);
    }


private:
    void mostrarResumenCalorias(int totalCalorias) {
        cout << "Total de calorías consumidas: " << totalCalorias << " kcal" << endl;

        if (totalCalorias <= 2500) { //Calorías diarias recomendadas
            cout << "Se ha alimentado bien." << endl;
        } else {
            cout << "Se ha pasado del límite calórico." << endl;
        }
    }
};