#ifndef MainH
#define MainH
#include <iostream>
#include <string>


using namespace std;

// Базовый класс Алкогольный напиток
class AlcoholDrink 
{
protected:
    string name;
    float alcoholContent;
    float volume;
    float price;

public:
    virtual ~AlcoholDrink() {}
    virtual void displayInfo() = 0;
    virtual float calculateCost(int quantity) = 0;
    string getName() const { return name; }
};

// Класс Вино
class Wine : public AlcoholDrink
 {
private:
    string grapeSort;
    string country;

public:
    Wine(string _name, float _alcoholContent, float _volume, float _price, string _grapeSort, string _country)
        : grapeSort(_grapeSort), country(_country) 
    {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override
    {
        cout << "Wine: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Grape: " << grapeSort << ", Country: " << country << endl;
    }

    float calculateCost(int quantity) override {
        return price * quantity;
    }
};

// Класс Пиво
class Beer : public AlcoholDrink 
{
private:
    string type;
    string manufacturer;

public:
    Beer(string _name, float _alcoholContent, float _volume, float _price, string _type, string _manufacturer)
        : type(_type), manufacturer(_manufacturer) 
    {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override 
    {
        cout << "Beer: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Type: " << type << ", Manufacturer: " << manufacturer << endl;
    }

    float calculateCost(int quantity) override 
    {
        return price * quantity;
    }
};

// Класс Водка
class Vodka : public AlcoholDrink 
{
private:
    string countryOfOrigin;
    string composition;

public:
    Vodka(string _name, float _alcoholContent, float _volume, float _price, string _countryOfOrigin, string _composition)
        : countryOfOrigin(_countryOfOrigin), composition(_composition) 
    {
        name = _name;
        alcoholContent = _alcoholContent;
        volume = _volume;
        price = _price;
    }

    void displayInfo() override 
    {
        cout << "Vodka: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Country: " << countryOfOrigin << ", Composition: " << composition << endl;
    }

    float calculateCost(int quantity) override 
    {
        return price * quantity;
    }
};



#endif // MainH