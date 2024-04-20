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

// Декоратор фильтрации по содержанию алкоголя
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

// -------------Декораторы для контейнера на основе связанного списка--------------
//Декоратор сортировки по названию
class ListAlcoholNameSortDecorator {
private:
    ListAlcohol& container;

public:
    ListAlcoholNameSortDecorator(ListAlcohol& cont) : container(cont) {}

    void sortByName() {
    // Функция сравнения для сортировки по названию
    auto compareName = [](const Node* a, const Node* b) {
        return a->drink->getName() < b->drink->getName();
    };

    // Создаем временный вектор указателей на узлы
    std::vector<Node*> tempNodes;

    // Заполняем временный вектор узлами из списка
    Node* temp = container.getHead();
    while (temp) {
        tempNodes.push_back(temp);
        temp = temp->next;
    }

    // Сортируем временный вектор узлов
    std::sort(tempNodes.begin(), tempNodes.end(), compareName);

    // Перестраиваем список на основе отсортированного временного вектора
    Node* prev = nullptr;
    for (size_t i = 0; i < tempNodes.size(); ++i) {
        if (prev) {
            prev->next = tempNodes[i];
        } else {
            container.updateList(tempNodes[i]);
        }
        prev = tempNodes[i];
    }
    if (prev) {
        prev->next = nullptr;
    }
}

};


#endif // Decorator