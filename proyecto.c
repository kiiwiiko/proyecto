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
    int opcion;

    do {
        printf("----- Panel de Control -----\n");
        printf("1. Agendar cita\n");
        printf("2. Opciones\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agendarCita();
                break;
            case 2:
                opciones();
                break;
            case 3:
                printf("¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}

void agendarCita() {
    struct CitaMedica cita;
    int opcion;
    int seleccionada = 0;

    printf("----- Agendar Cita -----\n");
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", cita.nombre);
    printf("Ingrese el apellido del paciente: ");
    scanf("%s", cita.apellido);
    printf("Ingrese el número de cédula: ");
    scanf("%d", &cita.cedula);

    do {
        printf("Elija la especialidad:\n");
        printf("1. Pediatria\n");
        printf("2. Medicina general\n");
        printf("3. Ginecologia\n");
        printf("4. Odontologia\n");
        printf("5. Psicologia\n");
        printf("Ingrese la opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                strcpy(cita.especialidad, "Pediatria");
                seleccionada = 1;
                break;
            case 2:
                strcpy(cita.especialidad, "Medicina general");
                seleccionada = 1;
                break;
            case 3:
                strcpy(cita.especialidad, "Ginecologia");
                seleccionada = 1;
                break;
            case 4:
                strcpy(cita.especialidad, "Odontologia");
                seleccionada = 1;
                break;
            case 5:
                strcpy(cita.especialidad, "Psicologia");
                seleccionada = 1;
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (!seleccionada);

    