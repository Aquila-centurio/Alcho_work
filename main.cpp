#include <iostream>
#include "classes.h"
#include "methods.h"
//#include "methods.h"
using namespace std;   


int main(int, char**){
    std::cout << "Hello, from Alchogol_work!\n";
    // Создание объектов алкогольных напитков
    Wine wine("Merlot", 12.5, 0.75, 20.0, "Merlot", "France");
    Beer beer("Heineken", 5.0, 0.5, 3.0, "Lager", "Netherlands");
    Vodka vodka("Absolut", 40.0, 1.0, 25.0, "Sweden", "Potatoes");
    
}
