#ifndef MainH
#define MainH

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс Алкогольный напиток
class AlcoholDrink {
protected:
    string name;
    float alcoholContent;
    float volume;
    float price;

public:
    virtual ~AlcoholDrink() {}
    virtual void displayInfo() = 0;
    virtual float calculateCost(int quantity) = 0;
    string getName() const;
    float getPrice() const;
    float getAlcoholContent() const;
};

// Класс Вино
class Wine : public AlcoholDrink {
private:
    string grapeSort;
    string country;

public:
    Wine(string _name, float _alcoholContent, float _volume, float _price, string _grapeSort, string _country)
        : grapeSort(_grapeSort), country(_country) {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override;
    float calculateCost(int quantity) override;
};

// Класс Пиво
class Beer : public AlcoholDrink {
private:
    string type;
    string manufacturer;

public:
    Beer(string _name, float _alcoholContent, float _volume, float _price, string _type, string _manufacturer)
        : type(_type), manufacturer(_manufacturer) {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override;
    float calculateCost(int quantity) override;
};

// Класс Водка
class Vodka : public AlcoholDrink {
private:
    string countryOfOrigin;
    string composition;

public:
    Vodka(string _name, float _alcoholContent, float _volume, float _price, string _countryOfOrigin, string _composition)
        : countryOfOrigin(_countryOfOrigin), composition(_composition) {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override;
    float calculateCost(int quantity) override;
};

#endif // MainH
