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

// Контейнер на основе связанного списка
class ListAlcohol : public AlcoholContainer {
private:
    struct Node {
        AlcoholDrink* drink;
        Node* next;
        Node(AlcoholDrink* _drink) : drink(_drink), next(nullptr) {} // Конструктор узла
    };
    Node* head; // Указатель на начало списка

public:
    ListAlcohol() : head(nullptr) {} // Конструктор

    void addDrink(AlcoholDrink* drink) override {
        // При пустом списке создаем новый узел, при наличии перемещаемся в конец
        if (!head) {
            head = new Node(drink);
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new Node(drink);
        }
    }

    void removeDrink(const string& drinkName) override {
        Node* curr = head;
        Node* prev = nullptr;
        while (curr) {
            if (curr->drink->getName() == drinkName) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr->drink;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void displayContents() const override {
        Node* temp = head;
        while (temp) {
            temp->drink->displayInfo();
            temp = temp->next;
        }
    }

    AlcoholDrink* findDrink(const string& drinkName) const override {
        Node* temp = head;
        while (temp) {
            if (temp->drink->getName() == drinkName) {
                return temp->drink;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    ~ListAlcohol() { // Деструктор для узлов
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp->drink;
            delete temp;
            temp = next;
        }
    }
};

#endif // Container