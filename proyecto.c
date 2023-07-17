#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITAS 100

//estructura de la cita medica
struct CitaMedica {
    char nombre[50];
    char apellido[50];
    int cedula;
    char especialidad[50];
    char horario[50];
    int mes;
    int dia;
};
 
 //estructura para cada especialidad
struct Especialidad {
    char nombre[50];
    char horariosDisponibles[5][50];
};

//declaracion de las funciones
void agendarCita();
void opciones();
void escribirEnArchivo(char especialidad[], struct CitaMedica cita);
void leerArchivo(char especialidad[]);
void borrarCita(char especialidad[], int cedula);
void actualizarCita(char especialidad[], int cedula, struct CitaMedica nuevaCita);
void buscarCita(char especialidad[], char busqueda[]);
void obtenerHorariosDisponibles(char especialidad[], struct Especialidad especialidades[], int cantidadEspecialidades, char horariosDisponibles[][50]);
int seleccionarHorario(char horariosDisponibles[][50], int cantidadHorarios);
int verificarDisponibilidad(char especialidad[], char horario[], int mes, int dia);
 
//estrucuctura main principal
int main() {

    return 0;
}