#include "Turnero.h"

using namespace std;

void agregarTurno();
void verTurnosPorMes();
bool ValidarFecha(int d, int m, int a);

void agregarTurno()
{
    Turnero turno;
    turno.cargar();

    while (!ValidarFecha(turno.getFechaAsignada().getDia(), turno.getFechaAsignada().getMes(), turno.getFechaAsignada().getAnio()))
    {
        cout << endl
             << "Fecha invalida, ingrese fecha de nuevo: " << endl;
        turno.getFechaAsignada().cargar();
    }

    FILE *pArchivo = fopen("Turnos.dat", "ab");
    if (pArchivo == NULL)
    {
        cout << "Error al abrir el archivo para escritura." << endl;
        system("pause");
        return;
    }

    bool ok = (fwrite(&turno, sizeof(Turnero), 1, pArchivo) == 1);
    if (ok)
    {
        cout << endl
             << "Consulta agregado con exito." << endl;
    }
    else
    {
        cout << endl
             << "Error al escribir en el archivo." << endl;
    }
    system("pause");
    fclose(pArchivo);
    return;
}

void verTurnosPorMes()
{
    int mes;
    cout << "MES DEL TURNO : ";
    cin >> mes;

    FILE *pArchivo = fopen("Turnos.dat", "rb");
    if (pArchivo == NULL)
    {
        cout << endl
             << "Error al abrir el archivo para lectura." << endl;
        system("pause");
        return;
    }
    Turnero turnos;
    int i = 0;
    bool encontrado = false;
    while (fread(&turnos, sizeof(Turnero), 1, pArchivo))
    {
        if (turnos.getFechaAsignada().getMes() == mes)
        {
            turnos.mostrar();
        }
        i++;
    }
    system("pause");
    fclose(pArchivo);
    return;
}


bool ValidarFecha(int d, int m, int a)
{
    int vecdiasxmes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool fechavalida = false;
    if (a > 0)
    { // Validacion para que a�o sea mayor a 0
        if (((a % 4 == 0) && (a % 100 != 0)) || (a % 400 == 0))
        { // validacion de a�os bisiestos
            vecdiasxmes[1] = 29;
        }
        if (m >= 1 && m <= 12)
        { // validacion de que el mes ingresado este entre 1 y 12
            if (d >= 1 && d <= vecdiasxmes[m - 1])
            {
                fechavalida = true;
            }
        }
    }
    return fechavalida;
}