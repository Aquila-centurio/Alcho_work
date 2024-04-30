#ifndef Fabric
#define Fabric

#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "classes.h" 
#include <sqlite3.h>



class AlcoholFactory {
public:
    virtual ~AlcoholFactory() {}
    virtual AlcoholDrink* createDrink() = 0;
};


class WineFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {
     
        string name = "Wine";
        float alcoholContent = rand() % 11 + 10;  
        float volume = rand() % 50 + 5;       
        float price = rand() % 51 + 50;          
        vector<string> countries = {"France", "Italy", "Spain"};
        vector<string> grapeVarieties = {"Merlot", "Cabernet Sauvignon", "Chardonnay"};
        string country = countries[rand() % countries.size()];
        string grapeSort = grapeVarieties[rand() % grapeVarieties.size()];

        return new Wine(name, alcoholContent, volume, price, grapeSort, country);
    }
};

class BeerFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {

        string name = "Beer";
        float alcoholContent = rand() % 6 + 3;   
        float volume = rand() % 30 + 33;     
        float price = rand() % 21 + 10;          
    
        vector<string> types = {"lager", "El", "Staut", "Porter"};
        vector<string> manufacturers = {"Bavaria", "Baltika", "Ireland"};
        string type = types[rand() % types.size()];
        string manufacturer = manufacturers[rand() % manufacturers.size()];
       

        return new Beer(name, alcoholContent, volume, price, type, manufacturer);
    }
};


class VodkaFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {
   
        string name = "Vodka";
        float alcoholContent = rand() % 31 + 30;  
        float volume = rand() % 70 + 30;       
        float price = rand() % 41 + 20;          

        vector<string> countries = {"Russia", "Belarus", "Ukraine"};
        vector<string> compositions = {"Tsarskaya", "Stolichnaya", "Husky"};
        string countryOfOrigin = countries[rand() % countries.size()];
        string composition = compositions[rand() % compositions.size()];
       

        return new Vodka(name, alcoholContent, volume, price, countryOfOrigin, composition);
    }
};

// ----------- SQL ---------

class SQLiteWineFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {
        string name = "SQLiteWine";
        
        float alcoholContent = rand() % 6 + 3;   
        float volume = rand() % 30 + 33;     
        float price = rand() % 21 + 10;      
        vector<string> countries = {"France", "Italy", "Spain"};
        vector<string> grapeVarieties = {"Merlot", "Cabernet Sauvignon", "Chardonnay"};
        string country = countries[rand() % countries.size()];
        string grapeSort = grapeVarieties[rand() % grapeVarieties.size()];

        return new Wine(name, alcoholContent, volume, price, grapeSort, country);
    }
};


class SQLiteBeerFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {
       
        string name = "SQLiteBeer";

        float alcoholContent = rand() % 6 + 3;   
        float volume = rand() % 30 + 33;     
        float price = rand() % 21 + 10;             
        vector<string> types = {"lager", "El", "Staut", "Porter"};
        vector<string> manufacturers = {"Bavaria", "Baltika", "Ireland"};
        string type = types[rand() % types.size()];
        string manufacturer = manufacturers[rand() % manufacturers.size()];

        return new Beer(name, alcoholContent, volume, price, type, manufacturer);
    }
};

class SQLiteVodkaFactory : public AlcoholFactory {
public:
    AlcoholDrink* createDrink() override {
  
        string name = "SQLiteVodka";

        float alcoholContent = rand() % 31 + 30;  
        float volume = rand() % 70 + 30;       
        float price = rand() % 41 + 20;    

        vector<string> countries = {"Russia", "Belarus", "Ukraine"};
        vector<string> compositions = {"Tsarskaya", "Stolichnaya", "Husky"};
        string countryOfOrigin = countries[rand() % countries.size()];
        string composition = compositions[rand() % compositions.size()];

        return new Vodka(name, alcoholContent, volume, price, countryOfOrigin, composition);
    }
};



#endif // Fabric