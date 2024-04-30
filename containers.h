#ifndef Container
#define Container

#include <iostream>
#include <string>
#include <vector>
#include "classes.h"
#include "iterators.h"
#include "sqlite3.h"

using namespace std;

// Функция для выполнения SQL запроса с проверкой результата
void executeSQL(sqlite3* db, const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error executing SQL statement: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

// Базовый класс для контейнеров
class AlcoholContainer {
public:
    virtual ~AlcoholContainer() {}
    virtual void addDrink(AlcoholDrink* drink) = 0;
    virtual void removeDrink(const string& drinkName) = 0;
    virtual void displayContents() const = 0;
    virtual AlcoholDrink* findDrink(const string& drinkName) const = 0;
};

// Контейнер на основе массива
class ArrayAlcohol : public AlcoholContainer {
private:
    vector<AlcoholDrink*> drinks;

public:
    vector<AlcoholDrink*> seeDrink (){
        return drinks;
    }
    void addDrink(AlcoholDrink* drink) override {
        drinks.push_back(drink);
    }

    void removeDrink(const string& drinkName) override {
        for (auto it = drinks.begin(); it != drinks.end(); ++it) {
            if ((*it)->getName() == drinkName) {
                delete *it;
                drinks.erase(it);
                break;
            }
        }
    }

    void displayContents() const override {
        // Отображение информации о каждом напитке
        for (const auto& drink : drinks) {
            drink->displayInfo();
        }
    }

    AlcoholDrink* findDrink(const string& drinkName) const override {
        // Поиск напитка по имени
        for (const auto& drink : drinks) {
            if (drink->getName() == drinkName) {
                return drink;
            }
        }
        return nullptr; // Напиток не найден
    }
};

// ---------------------- SQLite container

class SQLiteAlcohol : public AlcoholContainer {
private:
    sqlite3* db;

public:
    SQLiteAlcohol(const string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            exit(1);
        } else {
            cout << "Opened database successfully" << endl;
        }

        // Создание таблицы drinks при инициализации
        string createTableSQL = "CREATE TABLE IF NOT EXISTS drinks ("
                                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "Name TEXT NOT NULL,"
                                "AlcoholContent REAL,"
                                "Volume REAL,"
                                "Price REAL,"
                                "Type TEXT,"
                                "Manufacturer TEXT,"
                                "CountryOfOrigin TEXT,"
                                "Composition TEXT"
                                "GrapeSort TEXT"
                                "Country TEXT"
                                ");";
        executeSQL(db, createTableSQL);
    }

    ~SQLiteAlcohol() {
        sqlite3_close(db);
    }

    void addDrink(AlcoholDrink* drink) override {
        char* errMsg;
        string insertSQL;
        if (dynamic_cast<Wine*>(drink)) {
            Wine* wine = dynamic_cast<Wine*>(drink);
            insertSQL = "INSERT INTO drinks (name, alcoholContent, volume, price, grapeSort, country) "
                           "VALUES ('" + wine->getName() + "', " + to_string(wine->getAlcoholContent()) + ", "
                           + to_string(wine->getVolume()) + ", " + to_string(wine->getPrice()) + ", '"
                           + wine->getGrapeSort() + "', '" + wine->getCountry() + "');";
        } else if (dynamic_cast<Beer*>(drink)) {
            Beer* beer = dynamic_cast<Beer*>(drink);
            insertSQL = "INSERT INTO drinks (name, alcoholContent, volume, price, type, manufacturer) "
                           "VALUES ('" + beer->getName() + "', " + to_string(beer->getAlcoholContent()) + ", "
                           + to_string(beer->getVolume()) + ", " + to_string(beer->getPrice()) + ", '"
                           + beer->getType() + "', '" + beer->getManufacturer() + "');";
        } else if (dynamic_cast<Vodka*>(drink)) {
            Vodka* vodka = dynamic_cast<Vodka*>(drink);
            insertSQL = "INSERT INTO drinks (name, alcoholContent, volume, price, countryOfOrigin, composition) "
                           "VALUES ('" + vodka->getName() + "', " + to_string(vodka->getAlcoholContent()) + ", "
                           + to_string(vodka->getVolume()) + ", " + to_string(vodka->getPrice()) + ", '"
                           + vodka->getCountryOfOrigin() + "', '" + vodka->getComposition() + "');";
        }

        int rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
        
    }

    void removeDrink(const string& drinkName) override {
        char* errMsg;
        string deleteSQL = "DELETE FROM drinks WHERE name = '" + drinkName + "';";

        int rc = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "Error deleting data: " << errMsg << endl;
            sqlite3_free(errMsg);
        } else {
            cout << "Drink removed successfully" << endl;
        }
    }

    void displayContents() const override {
        sqlite3_stmt* stmt;
        string selectSQL = "SELECT * FROM drinks;";

        int rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
        if (rc == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                float alcoholContent = sqlite3_column_double(stmt, 2);
                float volume = sqlite3_column_double(stmt, 3);
                float price = sqlite3_column_double(stmt, 4);

                if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) == "SQLiteWine") {
                    string grapeSort = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
                    string country = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));

                    cout << "Wine: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume
                         << "L, Price: $" << price << ", Grape: " << grapeSort << ", Country: " << country << endl;
                } else if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) == "SQLiteBeer") {
                    string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                    string manufacturer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

                    cout << "Beer: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume
                         << "L, Price: $" << price << ", Type: " << type << ", Manufacturer: " << manufacturer << endl;
                } else if (string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) == "SQLiteVodka") {
                    string countryOfOrigin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
                    string composition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));

                    cout << "Vodka: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume
                         << "L, Price: $" << price << ", Country: " << countryOfOrigin << ", Composition: " << composition << endl;
                }
            }
            sqlite3_finalize(stmt);
        } else {
            cerr << "Error querying data: " << sqlite3_errmsg(db) << endl;
        }
    }

    AlcoholDrink* findDrink(const string& drinkName) const override {
        sqlite3_stmt* stmt;
        string selectSQL = "SELECT * FROM drinks WHERE name = ?;";

        int rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, drinkName.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
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
            sqlite3_finalize(stmt);
        } else {
            cerr << "Error querying data: " << sqlite3_errmsg(db) << endl;
        }

        return nullptr; // Напиток не найден
    }

    sqlite3* getDatabaseHandle() const {
        return db;
    }
};

#endif // Container