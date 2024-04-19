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
#include <algorithm> // Добавляем заголовочный файл для std::sort

// Декоратор сортировки по названию для ArrayAlcohol
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

// Декоратор сортировки по цене для ArrayAlcohol
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



// -------------Декораторы для контейнера на основе связанного списка--------------

#endif // Decorator