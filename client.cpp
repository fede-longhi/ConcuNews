//
// Created by fedelonghi on 08/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/message/messages.h"
#include "src/client/Cliente.h"
#include "src/message/messages.h"


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

    bool cerrar = false;
    while (not cerrar){
        std::cout<<"Requests al servidor\n"<<"1-Weather\n2-Currency\n3-Cerrar"<<std::endl;
        int opt;
        cin>>opt;
        if (opt==1){
            std::cout<<"Solicitando datos del tiempo..."<<std::endl;
            std::cout<<"Elija una ciudad"<<std::endl;
            string ciudad;
            cin>>ciudad;
            std::cout<<"Solicitando estado del tiempo en "<<ciudad<<std::endl;
            client->request_weather(ciudad);
            weather_response message = client->read_weather_response();
            if(message.pressure<0){
                std::cout << "\n----------------------------------"<<std::endl;
                std::cout << "No se ha enontrado a "<<message.city<<" en la base de datos"<<std::endl;
                std::cout << "----------------------------------\n"<<std::endl;
            }else{
                std::cout << "\n----------------------------------"<<std::endl;
                std::cout << "Informe del tiempo en " <<message.city<<std::endl;
                std::cout << "Temperatura: " <<message.temperature<<"°C"<<std::endl;
                std::cout << "Humedad: " <<message.humidity<<"%"<<std::endl;
                std::cout << "Presion: " <<message.pressure<<"hPa"<<std::endl;
                std::cout << "----------------------------------\n"<<std::endl;
            }
        }else if(opt==2){
            std::cout<<"Solicitando valor de moneda..."<<std::endl;
            std::cout<<"Elija una moneda"<<std::endl;
            string moneda;
            cin>>moneda;
            std::cout<<"Solicitando valor de "<<moneda<<std::endl;
            client->request_currency(moneda);
            currency_response message = client->read_currency_response();
            if(message.value<0){
                std::cout << "\n----------------------------------"<<std::endl;
                std::cout << "Valor de "<<moneda<<" no esta en la base de datos"<<std::endl;
                std::cout << "----------------------------------\n"<<std::endl;
            }else{
                std::cout << "\n----------------------------------"<<std::endl;
                std::cout << "Valor de "<<moneda<<": "<<message.value<<std::endl;
                std::cout << "----------------------------------\n"<<std::endl;
            }

        }else if(opt==3){
            cerrar=true;
        }else{
            std::cout<<"Opcion Invalida"<<std::endl;
        }
    }

    delete(client);

    return 0;
}