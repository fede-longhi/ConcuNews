//
// Created by fedelonghi on 24/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/message/messages.h"
#include "src/admin/Admin.h"


using namespace std;

int main(int argc, char** argv) {

    if (argc != 2){
        std::cout << "Tengo que recibir un parametro" << std::endl;
        return 1;
    }

    int id_queue = atoi( argv[1] );

    Admin *admin = new Admin();

    std::cout << "Iniciando Administrador" << std::endl;

    std::cout << "Estableciendo conexion con id: "<< id_queue << std::endl;
    admin->set_queueid(id_queue);
    admin->establish_connection();
    std::cout << "Conexion establecida - id asociado: "<< admin->get_id() << std::endl;

    std::cout << "Update Weather" <<std::endl;
    admin_request weather{};
    weather.pressure = 1024;
    weather.temperature = 23.4;
    std::strcpy(weather.city, "Buenos Aires");
    weather.hummidity = 20.3;
    admin->update_weather(weather);

    std::cout << "Update Currency" <<std::endl;
    admin_request currency{};
    currency.value = 10.2;
    std::strcpy(weather.city, "Dolar");
    admin->update_currency(currency);

    std::cout << "Cerrando servidor" << std::endl;
    admin->close_server();

    delete(admin);

    return 0;
}