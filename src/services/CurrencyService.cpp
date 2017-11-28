//
// Created by fedelonghi on 26/11/17.
//

#include <fstream>
#include "CurrencyService.h"

void CurrencyService::create_conection_queue() {

}

CurrencyService::CurrencyService() {

    loadDatabase();



    //TODO testeo
    addData(45,"dolar");

    saveDatabase();

}

void CurrencyService::run() {

}

int CurrencyService::getQueue_id() const {
    return 0;
}

CurrencyService::~CurrencyService() {

}

void CurrencyService::loadDatabase() {

    std::ifstream dbfile("./cdb.csv");

    std::string currency;
    float value;

    while (dbfile >> currency >> value) {
        this->database[currency] = value;
    }

    dbfile.close();


}

//Cambiar para que escriba y lea del mismo archivo . Capaz guardar un archivo de backup
void CurrencyService::saveDatabase() {


    std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, float>::iterator it = database.begin();


    std::ofstream outputFile;
    outputFile.open("./program4data.txt");

    while (it != database.end()) {
        std::string city = it->first;

        float value = it->second;

        outputFile << city << " " <<  value << std::endl;

        it++;
    }

    outputFile.close();
    std::cout << "Done!\n";


}

void CurrencyService::addData(float value, std::string currency){

    database[currency] = value;

}