//
// Created by fedelonghi on 08/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/message/messages.h"
#include "src/client/Cliente.h"


using namespace std;

int main(int argc, char** argv) {

    if (argc != 2){
        std::cout << "Tengo que recibir un parametro" << std::endl;
        return 1;
    }

    int id_queue = atoi(argv[1] );

    auto *client = new Cliente();

    std::cout << "Iniciando Cliente" << std::endl;

    std::cout << "Estableciendo conexion con id: "<< id_queue << std::endl;
    client->set_queueid(id_queue);
    client->establish_connection();
    std::cout << "Conexion establecida - id asociado: "<<  client->get_id() << std::endl;

    std::cout << "Solicitando Tiempo" <<std::endl;
    client->request_weather(1);
    weather_response message = client->read_weather_response();
    std::cout << "Mensaje Tiempo Recibido " <<message.temperature<<std::endl;

    std::cout << "Solicitando Moneda" <<std::endl;
    client->request_currency(1);
    client->read_currency_response();
    std::cout << "Mensaje Moneda recibido" <<std::endl;

    delete(client);

    return 0;
}