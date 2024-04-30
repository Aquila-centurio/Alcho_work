#ifndef Iterator
#define Iterator

#include <iostream>
#include <string>
#include <vector>
#include "classes.h"
#include "containers.h"

using namespace std;

// Итератор для ArrayAlcohol
class ArrayAlcoholIterator {
private:
    vector<AlcoholDrink*>::iterator current; // Текущий элемент
    vector<AlcoholDrink*>::iterator end;     // Конец контейнера

public:
    ArrayAlcoholIterator(vector<AlcoholDrink*>& drinks) : current(drinks.begin()), end(drinks.end()) {}

    bool hasNext() const {
        return current != end;
    }

    AlcoholDrink* getNext() {
        if (hasNext()) {
            return *(current++);
        }
        return nullptr;
    }
};


//  Итератор для SQLiteAlcohol

class SQLiteAlcoholIterator {
private:
    sqlite3* db;
    sqlite3_stmt* stmt;

public:
    SQLiteAlcoholIterator(SQLiteAlcohol& container) {
        db = container.getDatabaseHandle();

        string selectSQL = "SELECT * FROM drinks;";
        int rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        }
    }

    ~SQLiteAlcoholIterator() {
        sqlite3_finalize(stmt);
    }

    bool hasNext() const {
        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    AlcoholDrink* getNext() {
        if (hasNext()) {
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            float alcoholContent = sqlite3_column_double(stmt, 1);
            float volume = sqlite3_column_double(stmt, 2);
            float price = sqlite3_column_double(stmt, 3);

            if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))) == "Wine") {
                string grapeSort = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                string country = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

                return new Wine(name, alcoholContent, volume, price, grapeSort, country);
            } else if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))) == "Beer") {
                string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                string manufacturer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

                return new Beer(name, alcoholContent, volume, price, type, manufacturer);
            } else if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))) == "Vodka") {
                string countryOfOrigin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                string composition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

                return new Vodka(name, alcoholContent, volume, price, countryOfOrigin, composition);
            }
        }

        return nullptr;
    }
};

#endif // Iterator