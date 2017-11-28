//
// Created by fedelonghi on 28/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/services/WeatherService.h"

using namespace std;

int main(int argc, char** argv) {

    std::cout<<"Servicio de Tiempo"<<std::endl;

    auto *service = new WeatherService();

    std::cout<<"Make request with id: "<<service->getQueue_id()<<std::endl;

    service->run();

    delete(service);

    std::cout<<"Bye!"<<std::endl;

    return 0;
}
