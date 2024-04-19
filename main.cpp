#include <iostream>
#include "classes.h"
//#include "methods.h"
using namespace std;   

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


int main(int, char**){
    std::cout << "Hello, from Alchogol_work!\n";
    // Создание объектов алкогольных напитков
    Wine wine("Merlot", 12.5, 0.75, 20.0, "Merlot", "France");
    Beer beer("Heineken", 5.0, 0.5, 3.0, "Lager", "Netherlands");
    Vodka vodka("Absolut", 40.0, 1.0, 25.0, "Sweden", "Potatoes");
    
}
