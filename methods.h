#ifndef Method
#define Method
#include <iostream>
#include <string>
#include <vector>
#include "classes.h"

using namespace std;

string AlcoholDrink::getName() const { return name; }
float AlcoholDrink::getPrice() const { return price; }
float AlcoholDrink::getAlcoholContent() const { return alcoholContent; }
float AlcoholDrink::getVolume() const {return volume;}

void Wine::displayInfo() 
{
    cout << "Wine: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Grape: " << grapeSort << ", Country: " << country << endl;
}

float Wine::calculateCost(int quantity) 
{
    return price * quantity;
}

string Wine::getGrapeSort() const {return grapeSort;}
string Wine::getCountry() const {return country;}

void Beer::displayInfo() 
{
    cout << "Beer: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Type: " << type << ", Manufacturer: " << manufacturer << endl;
}
float Beer::calculateCost(int quantity) 
{
    return price * quantity;
}

string Beer::getType() const {return type;}
string Beer::getManufacturer() const {return manufacturer;}


void Vodka::displayInfo() 
{
    cout << "Vodka: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Country: " << countryOfOrigin << ", Composition: " << composition << endl;
}

float Vodka::calculateCost(int quantity)
{
    return price * quantity;
}

string Vodka::getCountryOfOrigin() const{return countryOfOrigin;}
string Vodka::getComposition() const {return composition;}

#endif // Method