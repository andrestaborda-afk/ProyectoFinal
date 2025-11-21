#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

void generarPregunta(int nivel, int &respuestaCorrecta, string &pregunta) {
    int a, b, op;
    a = rand() % (10 * nivel) + 1;
    b = rand() % (10 * nivel) + 1;
    op = rand() % 4;

    switch (op) {
        case 0: 
            respuestaCorrecta = a + b;
            pregunta = to_string(a) + " + " + to_string(b);
            break;

        case 1: 
            respuestaCorrecta = a - b;
            pregunta = to_string(a) + " - " + to_string(b);
            break;

        case 2: 
            respuestaCorrecta = a * b;
            pregunta = to_string(a) + " * " + to_string(b);
            break;

        case 3: 
            b = rand() % (10 * nivel) + 1;          
            respuestaCorrecta = rand() % (10 * nivel) + 1;  
            a = respuestaCorrecta * b;              
            pregunta = to_string(a) + " / " + to_string(b);
            break;
    }
}

void guardarHistorialEnArchivo(int historial[][2], int puntajeFinal) {
    ofstream archivo("historial.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir historial.txt\n";
        return;
    }

    archivo << "===== NUEVA PARTIDA =====\n";

    for (int i = 0; i < 7; i++) {
        if (historial[i][0] != 0) {
            archivo << "Nivel " << historial[i][0]
                    << " - Aciertos: " << historial[i][1] << "\n";
        }
    }

    archivo << "Puntaje final: " << puntajeFinal << "\n";
    archivo << "==========================\n\n";

    archivo.close();
}

int main() {
    srand(time(NULL));

    int opcion;
    int puntajeTotal = 0;

    int historial[7][2] = {0};

    while (true) {
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Jugar\n";
        cout << "2. Ver historial\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                puntajeTotal = 0;

                for (int i = 0; i < 7; i++) {
                    historial[i][0] = 0;
                    historial[i][1] = 0;
                }

                for (int nivel = 1; nivel <= 7; nivel++) {
                    int preguntas = 5;
                    int aciertos = 0;

                    int tiempoMax = 18 - nivel; 

                    cout << "=== NIVEL " << nivel << " ===" << endl;
                    cout << "Responde " << preguntas << " preguntas.\n";
                    cout << "Tiempo máximo: " << tiempoMax << " segundos.\n";
                    cout << "------------------------------\n";

                    auto tiempoInicio = chrono::steady_clock::now();

                    for (int i = 0; i < preguntas; i++) {
                        string pregunta;
                        int correcta, respuesta;

                        generarPregunta(nivel, correcta, pregunta);

                        cout << "Pregunta " << i + 1 << ": " << pregunta << " = ";
                        cin >> respuesta;

                        if (respuesta == correcta) {
                            aciertos++;
                            puntajeTotal += 10 * nivel;
                            cout << "? Correcto!\n";
                        } else {
                            cout << "? Incorrecto. Resp correcta: " << correcta << "\n";
                        }

                        auto tiempoActual = chrono::steady_clock::now();
                        double segundos = chrono::duration_cast<chrono::seconds>(tiempoActual - tiempoInicio).count();

                        if (segundos > tiempoMax) {
                            cout << "\n? Tiempo agotado!\n";
                            break;
                        }
                    }

                    historial[nivel - 1][0] = nivel;
                    historial[nivel - 1][1] = aciertos;

                    cout << "Aciertos en este nivel: " << aciertos << "\n";

                    if (aciertos < 3) {
                        cout << "No alcanzaste los aciertos necesarios. Fin del juego.\n";
                        break;
                    }
                }

                cout << "\nPuntaje final: " << puntajeTotal << "\n";

                guardarHistorialEnArchivo(historial, puntajeTotal);
                cout << "Historial guardado en historial.txt\n";

                break;
            }

            case 2:
                cout << "\n=== HISTORIAL (Última partida jugada) ===\n";
                for (int i = 0; i < 7; i++) {
                    if (historial[i][0] != 0) {
                        cout << "Nivel " << historial[i][0]
                             << ": " << historial[i][1] << " aciertos\n";
                    }
                }
                break;

            case 3:
                cout << "Gracias por jugar!\n";
                return 0;

            default:
                cout << "Opcion invalida.\n";
        }
    }

    return 0;
}