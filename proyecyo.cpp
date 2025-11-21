#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

int main() {
    srand(time(NULL));

    int opcion;
    int puntajeTotal = 0;

    int historial[7][2] = {0};

    while (true) {
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver historial" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {

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
                cout << "Responde " << preguntas << " preguntas." << endl;
                cout << "Tiempo maximo: " << tiempoMax << " segundos." << endl;
                cout << "------------------------------" << endl;

                auto tiempoInicio = chrono::steady_clock::now();

                for (int i = 0; i < preguntas; i++) {

                    int a, b, op, correcta, respuesta;
                    string pregunta;

                    a = rand() % (10 * nivel) + 1;
                    b = rand() % (10 * nivel) + 1;
                    op = rand() % 4;

                    if (op == 0) {
                        correcta = a + b;
                        pregunta = to_string(a) + " + " + to_string(b);
                    } else if (op == 1) {
                        correcta = a - b;
                        pregunta = to_string(a) + " - " + to_string(b);
                    } else if (op == 2) {
                        correcta = a * b;
                        pregunta = to_string(a) + " * " + to_string(b);
                    } else {
                        b = rand() % (10 * nivel) + 1;
                        correcta = rand() % (10 * nivel) + 1;
                        a = correcta * b;
                        pregunta = to_string(a) + " / " + to_string(b);
                    }

                    cout << "Pregunta " << i + 1 << ": " << pregunta << " = ";
                    cin >> respuesta;

                    if (respuesta == correcta) {
                        aciertos++;
                        puntajeTotal += 10 * nivel;
                        cout << "✔ Correcto!" << endl;
                    } else {
                        cout << "✘ Incorrecto. Resp correcta: " << correcta << endl;
                    }

                    auto tiempoActual = chrono::steady_clock::now();
                    double segundos = chrono::duration_cast<chrono::seconds>(tiempoActual - tiempoInicio).count();

                    if (segundos > tiempoMax) {
                        cout << endl << "⏳ Tiempo agotado!" << endl;
                        break;
                    }
                }

                historial[nivel - 1][0] = nivel;
                historial[nivel - 1][1] = aciertos;

                cout << "Aciertos en este nivel: " << aciertos << endl;

                if (aciertos < 3) {
                    cout << "No alcanzaste los aciertos necesarios. Fin del juego." << endl;
                    break;
                }
            }

            cout << endl << "Puntaje final: " << puntajeTotal << endl;

            ofstream archivo("historial.txt", ios::app);
            archivo << "===== NUEVA PARTIDA =====" << endl;

            for (int i = 0; i < 7; i++) {
                if (historial[i][0] != 0) {
                    archivo << "Nivel " << historial[i][0]
                            << " - Aciertos: " << historial[i][1] << endl;
                }
            }

            archivo << "Puntaje final: " << puntajeTotal << endl;
            archivo << "==========================" << endl << endl;

            archivo.close();

            cout << "Historial guardado en historial.txt" << endl;
        }

        else if (opcion == 2) {
            cout << endl << "=== HISTORIAL (Ultima partida jugada) ===" << endl;
            for (int i = 0; i < 7; i++) {
                if (historial[i][0] != 0) {
                    cout << "Nivel " << historial[i][0]
                         << ": " << historial[i][1] << " aciertos" << endl;
                }
            }
        }

        else if (opcion == 3) {
            cout << "Gracias por jugar!" << endl;
            return 0;
        }

        else {
            cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}