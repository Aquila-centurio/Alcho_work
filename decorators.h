#ifndef Decorator
#define Decorator

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "classes.h"
#include "iterators.h"
#include "containers.h"


using namespace std;

// ------------ Декораторы для контейнера на основе массива---------------


class ArrayAlcoholNameSortDecorator {
private:
    ArrayAlcohol& container;

public:
    ArrayAlcoholNameSortDecorator(ArrayAlcohol& cont) : container(cont) {}

    void sortByName() {
        std::sort(container.seeDrink().begin(), container.seeDrink().end(), [](AlcoholDrink* a, AlcoholDrink* b) {
            return a->getName() < b->getName();
        });
    }
};

class ArrayAlcoholPriceSortDecorator {
private:
    ArrayAlcohol& container;

public:
    ArrayAlcoholPriceSortDecorator(ArrayAlcohol& cont) : container(cont) {}

    void sortByPrice() {
        std::sort(container.seeDrink().begin(), container.seeDrink().end(), [](AlcoholDrink* a, AlcoholDrink* b) {
            return a->getPrice() < b->getPrice();
        });
    }
};

class ArrayAlcoholAlcoholContentFilterDecorator {
private:
    ArrayAlcohol& container;
    float minAlcoholContent;

public:
    ArrayAlcoholAlcoholContentFilterDecorator(ArrayAlcohol& cont, float minAlcohol)
        : container(cont), minAlcoholContent(minAlcohol) {}

    void filterByAlcoholContent() {
        container.seeDrink().erase(std::remove_if(container.seeDrink().begin(), container.seeDrink().end(), 
            [this](AlcoholDrink* drink) { return drink->getAlcoholContent() < minAlcoholContent; }), 
            container.seeDrink().end());
    }
};


//--------------- Декораторы для SQL
class SQLiteAlcoholNameSortDecorator {
private:
    SQLiteAlcoholIterator iterator;
    vector<AlcoholDrink*> sortedDrinks;

public:
    SQLiteAlcoholNameSortDecorator(SQLiteAlcohol& container) : iterator(container) {}

    void sortByName() {
        while (iterator.hasNext()) {
            sortedDrinks.push_back(iterator.getNext());
        }

        std::sort(sortedDrinks.begin(), sortedDrinks.end(), [](AlcoholDrink* a, AlcoholDrink* b) {
            return a->getName() < b->getName();
        });

        for (const auto& drink : sortedDrinks) {
            cout << drink->getName() << endl;
        }
    }
};

// Декоратор для сортировки по цене
class SQLiteAlcoholPriceSortDecorator {
private:
    SQLiteAlcoholIterator iterator;
    vector<AlcoholDrink*> sortedDrinks;

public:
    SQLiteAlcoholPriceSortDecorator(SQLiteAlcohol& container) : iterator(container) {}

    void sortByPrice() {
        while (iterator.hasNext()) {
            sortedDrinks.push_back(iterator.getNext());
        }

        std::sort(sortedDrinks.begin(), sortedDrinks.end(), [](AlcoholDrink* a, AlcoholDrink* b) {
            return a->getPrice() < b->getPrice();
        });

        for (const auto& drink : sortedDrinks) {
            cout << drink->getName() << endl;
        }
    }
};

// Декоратор для фильтрации по содержанию алкоголя
class SQLiteAlcoholAlcoholContentFilterDecorator {
private:
    SQLiteAlcoholIterator iterator;
    float minAlcoholContent;

public:
    SQLiteAlcoholAlcoholContentFilterDecorator(SQLiteAlcohol& container, float minAlcohol)
        : iterator(container), minAlcoholContent(minAlcohol) {}

    void filterByAlcoholContent() {
        while (iterator.hasNext()) {
            AlcoholDrink* drink = iterator.getNext();
            if (drink->getAlcoholContent() >= minAlcoholContent) {
                cout << drink->getName() << endl;
            }
        }
    }
};


#endif // Decorator

