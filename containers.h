#ifndef Container
#define Container

#include <iostream>
#include <string>
#include <vector>
#include "classes.h"
#include "iterators.h"


using namespace std;

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



#endif // Container