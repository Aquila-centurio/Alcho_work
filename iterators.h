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



#endif // Iterator