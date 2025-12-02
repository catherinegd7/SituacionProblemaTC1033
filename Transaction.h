#pragma once
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;
#include "Category.h"

struct Transaction {
    string txid;
    // fecha de la transacción
    year_month_day date;
    // catgoria (enum)
    Category category;
    // monto de la transacción
    double amount;
    // tienaa
    string store;

    // operator<< para imprimir la transacción
    friend ostream& operator<<(ostream& os, const Transaction& tx) {

        int y = (int)tx.date.year();
        unsigned m = (unsigned)tx.date.month();
        unsigned d = (unsigned)tx.date.day();

        os << "Transaction = " << tx.txid
           << " | Date = " << y << "-" << m << "-" << d
           << " | Category = " << static_cast<int>(tx.category)
           << " | Amount = " << tx.amount
           << " | Store = " << tx.store;

        return os;
    }
};