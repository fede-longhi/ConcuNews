//
// Created by fedelonghi on 28/11/17.
//

//
// Created by fedelonghi on 08/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/services/CurrencyService.h"

using namespace std;

int main(int argc, char** argv) {

    std::cout<<"Servicio de Moneda"<<std::endl;

    auto *service = new CurrencyService();

    service->run();

    delete(service);

    std::cout<<"Bye!"<<std::endl;

    return 0;
}

