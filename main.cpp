#include <iostream>
#include "classes.h"
#include "methods.h"
#include "classes.h"
#include "iterators.h"
#include "containers.h"
#include "fabricMethods.h"
#include <sqlite3.h>

//#include "methods.h"
using namespace std;   


int main(){
    std::cout << "Hello, from Alchogol_work!\n";
    
    
    srand((time(NULL)));

    WineFactory wineFactory;
    BeerFactory beerFactory;
    VodkaFactory vodkaFactory;

    ArrayAlcohol alcoholContainer;

    int numDrinks = rand() % 10 + 5; 
    for (int i = 0; i < numDrinks; ++i) {
     
        AlcoholFactory* factory;
        int randomFactory = rand() % 3; 
        switch (randomFactory) {
            case 0:
                factory = &wineFactory;
                break;
            case 1:
                factory = &beerFactory;
                break;
            case 2:
                factory = &vodkaFactory;
                break;
            default:
                factory = &wineFactory; 
                break;
        }

     
        AlcoholDrink* drink = factory->createDrink();
        alcoholContainer.addDrink(drink);
    }

    alcoholContainer.displayContents();

    // ----------------------------------------------

    cout << "А тут SQL \n";

    SQLiteWineFactory sqliteWineFactory;
    SQLiteBeerFactory sqliteBeerFactory;
    SQLiteVodkaFactory sqliteVodkaFactory;

    SQLiteAlcohol SQLalcoholContainer("mydatabase.db");
   
    srand((time(NULL)));

    int inumDrinks = rand() % 10 + 5; 
    for (int i = 0; i < inumDrinks; ++i) {
        AlcoholFactory* factory;
        int randomFactory = rand() % 3; 
        switch (randomFactory) {
            case 0:
                factory = &sqliteWineFactory;
                break;
            case 1:
                factory = &sqliteBeerFactory;
                break;
            case 2:
                factory = &sqliteVodkaFactory;
                break;
            default:
                factory = &sqliteWineFactory; 
                break;
        }

        AlcoholDrink* drink = factory->createDrink();
        SQLalcoholContainer.addDrink(drink);
    }

    SQLalcoholContainer.displayContents();

    return 0;
    
}

