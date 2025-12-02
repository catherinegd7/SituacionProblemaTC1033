#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include "Transaction.h"
#include "Category.h"
#include "Analyzer.h"
using namespace std;
int main() {
    Analyzer analyzer;

    try {
        analyzer.loadData();   // solo carga
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar todos los carros\n";
        cout << "2. Filtrar por rango de fechas\n";
        cout << "3. Mayor transaccion\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            analyzer.printTransactions();
        }
        else if (opcion == 2) {
            string ini, fin;
            cout << "Fecha inicio (YYYY-MM-DD): ";
            cin >> ini;
            cout << "Fecha fin (YYYY-MM-DD): ";
            cin >> fin;
            try {
                auto y1 = analyzer.parseDate(ini);
                auto y2 = analyzer.parseDate(fin);

                auto filtradas = analyzer.filtrarRangoFechas(y1, y2);

                for (auto& tx : filtradas) {
                    cout << tx << endl;
                }
            }
            catch (const exception& e) {
                cerr << "Error al filtrar: " << e.what() << endl;
            }
        }
        else if (opcion == 3) {
            analyzer.getTopDay();
            analyzer.getTopStore();
            analyzer.getTopCategory();
        }

    } while (opcion != 0);

    return 0;
}