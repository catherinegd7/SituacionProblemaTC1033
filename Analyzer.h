#if !defined(Analyzer_h)
#define Analyzer_h

#include<vector>
#include<fstream>
#include<string>
#include<filesystem>
#include<chrono>
#include<iostream>
using namespace std;
using namespace std::chrono;
#include "Splitcommas.h"
#include "Category.h"
#include "Transaction.h"

class Analyzer {
private:
    vector<Transaction> transactions{};
   
public:
    Analyzer() = default;
    year_month_day parseDate(const string& dateStr);
    vector<Transaction> filtrarRangoFechas(const year_month_day& inicio, const year_month_day& fin);
    
    void loadData(const filesystem::path& base = filesystem::current_path());
    void printTransactions();
    void getTopDay();
    void getTopStore();
    void getTopCategory();
};


year_month_day Analyzer::parseDate(const string& dateStr) {
    // Implementación simplificada: en un caso real, parsear correctamente la fecha
    int yearInt = stoi(dateStr.substr(0, 4));
    int monthInt = stoi(dateStr.substr(5, 2));
    int dayInt = stoi(dateStr.substr(8, 2));

    year_month_day ymd{
        year{yearInt},
        month{static_cast<unsigned>(monthInt)},
        day{static_cast<unsigned>(dayInt)}
    };

    if (!ymd.ok()) {
        throw invalid_argument("Invalid date: " + dateStr);
    }

    return ymd;
}

vector<Transaction> Analyzer::filtrarRangoFechas(const year_month_day& inicio, const year_month_day& fin)
{
    vector<Transaction> resultado;

    for (const auto& tx : transactions) {
        if (tx.date >= inicio && tx.date <= fin) {
            resultado.push_back(tx);
        }
    }

    return resultado;
}

void Analyzer::loadData(const filesystem::path& base) {
    filesystem::path file = base / "transactions.csv";
    if (!filesystem::exists(file) || !filesystem::is_regular_file(file)) {
        throw runtime_error("transactions.csv not found");
    }
    ifstream in(file);
    if (!in) throw runtime_error("Cannot open transactions.csv");
    string line;
    size_t lineNumber = 0; // almacena el número de línea
    while (getline(in, line)) {
        lineNumber++;
        if (lineNumber > 1) { 
            auto fields = splitCommas(line);
            if (fields.size() != 5) {
                throw runtime_error("Invalid transaction format: " + line);
            }
            Transaction tx;
            tx.txid = string(fields[0]);
            tx.date = parseDate(string(fields[1]));
            try {
                tx.category = stringToCategory(string(fields[2]));
            } catch (const invalid_argument& e) {
                throw runtime_error("Invalid category in line " + to_string(lineNumber) + ": " + e.what());
            }
            tx.amount = stod(string(fields[3]));
            tx.store = string(fields[4]);
            transactions.push_back(tx);
        }
    }
}

void Analyzer::printTransactions() {
    for (const auto& tx : transactions) {
        cout << tx << endl;
    }
}

void Analyzer::getTopDay() {
    Transaction maxTx = transactions[0];

    for (const auto& tx : transactions) {
        if (tx.amount > maxTx.amount) {
            maxTx = tx; 
        }
    }

    int y = (int)maxTx.date.year();
    unsigned m = (unsigned)maxTx.date.month();
    unsigned d = (unsigned)maxTx.date.day();
    cout << "Fecha de mayor transaccion: " << y << "-" << m << "-" << d << endl;

}
void Analyzer::getTopStore() {
    Transaction maxTx = transactions[0];

    for (const auto& tx : transactions) {
        if (tx.amount > maxTx.amount) {
            maxTx = tx; 
        }
    }
    cout << "Tienda de mayor transaccion: " << maxTx.store << endl;
}
void Analyzer::getTopCategory() {
    Transaction maxTx = transactions[0];

    for (const auto& tx : transactions) {
        if (tx.amount > maxTx.amount) {
            maxTx = tx; 
        }
    }
    cout << "Categoria de mayor transaccion: " << categoryToString(maxTx.category) << endl;
}
#endif // Analyzer_h