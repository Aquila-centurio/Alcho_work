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

void Wine::displayInfo() 
{
    cout << "Wine: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Grape: " << grapeSort << ", Country: " << country << endl;
}

float Wine::calculateCost(int quantity) 
{
    return price * quantity;
}

void Beer::displayInfo() 
{
    cout << "Beer: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Type: " << type << ", Manufacturer: " << manufacturer << endl;
}
float Beer::calculateCost(int quantity) 
{
    return price * quantity;
}

void Vodka::displayInfo() 
{
    cout << "Vodka: " << name << ", Alcohol: " << alcoholContent << "%, Volume: " << volume << "L, Price: $" << price << ", Country: " << countryOfOrigin << ", Composition: " << composition << endl;
}

float Vodka::calculateCost(int quantity)
{
    return price * quantity;
}


#endif // Method