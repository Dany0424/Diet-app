//Axel Godoy y Erika Garcia
//Aplicacion Principal

#include <iostream>
#include "SistemaInformacion.h"
using namespace std;


int main() {
    SistemaInformacion sistema;

    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de grupos alimenticios: "; //Ingresar el nombre del archivo con los grupos alimenticios y sus alimentos
    cin >> nombreArchivo;

    sistema.cargarGruposDesdeArchivo(nombreArchivo);

    bool registrado = false;
    int opcion;

    //Crear un usuario antes de poder crear menus
    while (!registrado) {
        cout << "\n----- Menú Principal -----" << endl;
        cout << "1. Registrar Usuario" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese la opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                sistema.registrarUsuario();
                registrado = true;
                break;
            case 2:
                return 0;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }
    }

    bool salir = false;

    //Menu principal de la aplicacion
    while (!salir) {
        cout << "\n----- Menú de Opciones -----" << endl;
        cout << "1. Crear Menú" << endl;
        cout << "2. Mostrar Reporte Diario" << endl;
        cout << "3. Mostrar Reporte Semanal" << endl;
        cout << "4. Mostrar Reporte Mensual" << endl;
        cout << "5. Mostrar Reporte Trimestral" << endl;
        cout << "6. Mostrar Reporte Anual" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese la opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int limiteCalorias;
                while(true) {
                    cout << "\nIngrese el límite de calorías para el menú: ";
                    cin >> limiteCalorias;

                    if(cin.fail()) { // Comprobamos si ocurrió un error en la última operación de entrada
                        cin.clear(); // Limpia el estado de error en cin
                        cin.ignore(); // Ignora los caracteres de entrada incorrectos
                        cout << "Valor ingresada no es válida. Por favor, vuelve a intentarlo." << endl;
                    } else {
                        sistema.crearMenu(limiteCalorias);
                        break; // Si la entrada fue exitosa, rompemos el bucle
                    }
                }
            }
            case 2: {
                time_t now = time(0);
                sistema.mostrarReporteDiario(now);
                break;
            }
            case 3:
                sistema.mostrarReporteSemanal();
                break;
            case 4:
                sistema.mostrarReporteMensual();
                break;
            case 5:
                sistema.mostrarReporteTrimestral();
                break;
            case 6:
                sistema.mostrarReporteAnual();
                break;
            case 7:
                salir = true;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }
    }

    return 0;
}

