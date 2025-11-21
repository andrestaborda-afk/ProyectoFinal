#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
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
            respuestaCorrecta = a / b;
            pregunta = to_string(a) + " / " + to_string(b) + " (entero)";
            break;
    }
}

int main() {
    srand(time(NULL));

    int opcion;
    int puntajeTotal = 0;

    int historial[7][2] = {0};

    while (true) {
        cout << endl << endl;
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver historial" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                puntajeTotal = 0;

                for (int nivel = 1; nivel <= 7; nivel++) {
                    int preguntas = 5;
                    int aciertos = 0;

                    cout << endl << endl;
                    cout << "=== NIVEL " << nivel << " ===" << endl;
                    cout << "Responde " << preguntas << " preguntas." << endl;
                    cout << "Tiempo máximo: " << 15 - nivel << " segundos." << endl;
                    cout << "------------------------------" << endl;

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
                            cout << "Correcto!" << endl;
                        } else {
                            cout << "Incorrecto. Respuesta correcta: " << correcta << endl;
                        }

                        auto tiempoActual = chrono::steady_clock::now();
                        double segundos = chrono::duration_cast<chrono::seconds>(tiempoActual - tiempoInicio).count();

                        if (segundos > 15 - nivel) {
                            cout << endl << "Tiempo agotado!" << endl;
                            break;
                        }
                    }

                    historial[nivel - 1][0] =