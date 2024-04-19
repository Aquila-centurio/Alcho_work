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

// Итератор для ListAlcohol
class ListAlcoholIterator {
private:
    struct Node {
        AlcoholDrink* drink;
        Node* next;
        Node(AlcoholDrink* _drink) : drink(_drink), next(nullptr) {} // Конструктор узла
    };
    Node* current; // Текущий элемент

public:
    ListAlcoholIterator(Node* start) : current(start) {}

    bool hasNext() const {
        return current != nullptr;
    }

    AlcoholDrink* getNext() {
        if (hasNext()) {
            AlcoholDrink* drink = current->drink;
            current = current->next;
            return drink;
        }
        return nullptr;
    }
};



#endif // Iterator