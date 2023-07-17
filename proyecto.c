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

    // Obtener horarios disponibles para la especialidad seleccionada
    struct Especialidad especialidades[] = {
        {"Pediatria", {"08:00 AM", "08:30 AM", "09:00 AM", "09:30 AM", "10:00 AM"}},
        {"Medicina general", {"09:00 AM", "09:30 AM", "10:00 AM", "10:30 AM", "11:00 AM"}},
        {"Ginecologia", {"02:00 PM", "02:30 PM", "03:00 PM", "03:30 PM", "04:00 PM"}},
        {"Odontologia", {"11:00 AM", "11:30 AM", "12:00 PM", "12:30 PM", "01:00 PM"}},
        {"Psicologia", {"04:00 PM", "04:30 PM", "05:00 PM", "05:30 PM", "06:00 PM"}}
    };
    char horariosDisponibles[5][50];
    obtenerHorariosDisponibles(cita.especialidad, especialidades, sizeof(especialidades) / sizeof(especialidades[0]), horariosDisponibles);

    printf("Horarios disponibles para %s:\n", cita.especialidad);
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, horariosDisponibles[i]);
    }

    int seleccionHorario = seleccionarHorario(horariosDisponibles, 5);
    strcpy(cita.horario, horariosDisponibles[seleccionHorario - 1]);

    printf("Ingrese el mes de la cita (1-12): ");
    scanf("%d", &cita.mes);
    printf("Ingrese el día del mes de la cita: ");
    scanf("%d", &cita.dia);

    // Verificar disponibilidad de la cita
    int disponibilidad = verificarDisponibilidad(cita.especialidad, cita.horario, cita.mes, cita.dia);
    if (disponibilidad == 0) {
        printf("Cita reservada. El horario y día seleccionados ya están ocupados.\n");
    } else {
        escribirEnArchivo(cita.especialidad, cita);
        printf("Cita agendada exitosamente.\n");
    }
}

void opciones() {
    int opcion;
    char especialidad[50];
    int cedula;
    struct CitaMedica nuevaCita;
    char busqueda[50];

    printf("----- Opciones -----\n");
    printf("1. Escribir en archivo\n");
    printf("2. Leer archivo\n");
    printf("3. Borrar cita\n");
    printf("4. Actualizar cita\n");
    printf("5. Buscar cita\n");
    printf("6. Cerrar\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            printf("Ingrese la especialidad: ");
            scanf("%s", especialidad);
            printf("Ingrese los datos de la cita:\n");
            printf("Nombre: ");
            scanf("%s", nuevaCita.nombre);
            printf("Apellido: ");
            scanf("%s", nuevaCita.apellido);
            printf("Número de cédula: ");
            scanf("%d", &nuevaCita.cedula);
            printf("Horario de la cita: ");
            scanf("%s", nuevaCita.horario);
            printf("Mes de la cita (1-12): ");
            scanf("%d", &nuevaCita.mes);
            printf("Día del mes de la cita: ");
            scanf("%d", &nuevaCita.dia);
            escribirEnArchivo(especialidad, nuevaCita);
            printf("Cita escrita en archivo.\n");
            break;
        case 2:
            printf("Ingrese la especialidad: ");
            scanf("%s", especialidad);
            leerArchivo(especialidad);
            break;
        case 3:
            printf("Ingrese la especialidad: ");
            scanf("%s", especialidad);
            printf("Ingrese el número de cédula: ");
            scanf("%d", &cedula);
            borrarCita(especialidad, cedula);
            printf("Cita borrada del archivo.\n");
            break;
        case 4:
            printf("Ingrese la especialidad: ");
            scanf("%s", especialidad);
            printf("Ingrese el número de cédula: ");
            scanf("%d", &cedula);
            printf("Ingrese los nuevos datos de la cita:\n");
            printf("Nombre: ");
            scanf("%s", nuevaCita.nombre);
            printf("Apellido: ");
            scanf("%s", nuevaCita.apellido);
            printf("Horario de la cita: ");
            scanf("%s", nuevaCita.horario);
            printf("Mes de la cita (1-12): ");
            scanf("%d", &nuevaCita.mes);
            printf("Día del mes de la cita: ");
            scanf("%d", &nuevaCita.dia);
            actualizarCita(especialidad, cedula, nuevaCita);
            printf("Cita actualizada en el archivo.\n");
            break;
        case 5:
            printf("Ingrese la especialidad: ");
            scanf("%s", especialidad);
            printf("Ingrese el nombre o número de cédula a buscar: ");
            scanf("%s", busqueda);
            buscarCita(especialidad, busqueda);
            break;
        case 6:
            printf("Cerrando opciones.\n");
            break;
        default:
            printf("Opción inválida. Por favor, seleccione una opción válida.\n");
            break;
    }
}

void escribirEnArchivo(char especialidad[], struct CitaMedica cita) {
    FILE *archivo;
    archivo = fopen(especialidad, "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s;%s;%d;%s;%s;%d;%d\n", cita.nombre, cita.apellido, cita.cedula, cita.especialidad, cita.horario, cita.mes, cita.dia);
    fclose(archivo);
}

void leerArchivo(char especialidad[]) {
    FILE *archivo;
    char linea[100];

    archivo = fopen(especialidad, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("----- Citas Médicas de la Especialidad: %s -----\n", especialidad);
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);
}

void borrarCita(char especialidad[], int cedula) {
    FILE *archivo;
    FILE *temp;
    char linea[100];

    archivo = fopen(especialidad, "r");
    temp = fopen("temp.txt", "w");

    if (archivo == NULL || temp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        char *cedulaStr = strtok(linea, ";");
        int cedulaActual = atoi(cedulaStr);

        if (cedulaActual != cedula) {
            fputs(linea, temp);
        }
    }

    fclose(archivo);
    fclose(temp);

    remove(especialidad);
    rename("temp.txt", especialidad);
}

void actualizarCita(char especialidad[], int cedula, struct CitaMedica nuevaCita) {
    FILE *archivo;
    FILE *temp;
    char linea[100];

    archivo = fopen(especialidad, "r");
    temp = fopen("temp.txt", "w");

    if (archivo == NULL || temp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        char *cedulaStr = strtok(linea, ";");
        int cedulaActual = atoi(cedulaStr);

        if (cedulaActual == cedula) {
            fprintf(temp, "%s;%s;%d;%s;%s;%d;%d\n", nuevaCita.nombre, nuevaCita.apellido, nuevaCita.cedula, nuevaCita.especialidad, nuevaCita.horario, nuevaCita.mes, nuevaCita.dia);
        } else {
            fputs(linea, temp);
        }
    }

    fclose(archivo);
    fclose(temp);

    remove(especialidad);
    rename("temp.txt", especialidad);
}

void buscarCita(char especialidad[], char busqueda[]) {
    FILE *archivo;
    char linea[100];

    archivo = fopen(especialidad, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("----- Resultados de la búsqueda -----\n");
    while (fgets(linea, sizeof(linea), archivo)) {
        char *nombre = strtok(linea, ";");
        char *apellido = strtok(NULL, ";");
        char *cedulaStr = strtok(NULL, ";");
        int cedula = atoi(cedulaStr);

        if (strcmp(nombre, busqueda) == 0 || strcmp(apellido, busqueda) == 0 || cedula == atoi(busqueda)) {
            printf("%s", linea);
        }
    }

    fclose(archivo);
}

void obtenerHorariosDisponibles(char especialidad[], struct Especialidad especialidades[], int cantidadEspecialidades, char horariosDisponibles[][50]) {
    for (int i = 0; i < cantidadEspecialidades; i++) {
        if (strcmp(especialidades[i].nombre, especialidad) == 0) {
            for (int j = 0; j < 5; j++) {
                strcpy(horariosDisponibles[j], especialidades[i].horariosDisponibles[j]);
            }
            break;
        }
    }
}

int seleccionarHorario(char horariosDisponibles[][50], int cantidadHorarios) {
    int opcion;

    do {
        printf("Seleccione un horario: ");
        scanf("%d", &opcion);

        if (opcion < 1 || opcion > cantidadHorarios) {
            printf("Opción inválida. Por favor, seleccione una opción válida.\n");
        }
    } while (opcion < 1 || opcion > cantidadHorarios);

    return opcion;
}

int verificarDisponibilidad(char especialidad[], char horario[], int mes, int dia) {
    FILE *archivo;
    char linea[100];

    archivo = fopen(especialidad, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        char *cedulaStr = strtok(linea, ";");
        strtok(NULL, ";"); // Ignorar apellido
        strtok(NULL, ";"); // Ignorar nombre
        strtok(NULL, ";"); // Ignorar especialidad
        char *horarioCita = strtok(NULL, ";");
        char *mesStr = strtok(NULL, ";");
        char *diaStr = strtok(NULL, ";");
        int mesCita = atoi(mesStr);
        int diaCita = atoi(diaStr);

        if (strcmp(horarioCita, horario) == 0 && mesCita == mes && diaCita == dia) {
            fclose(archivo);
            return 0; // Cita ocupada
        }
    }

    fclose(archivo);
    return 1; // Cita disponible
}
