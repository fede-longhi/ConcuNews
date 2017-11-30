//
// Created by fedelonghi on 24/11/17.
//

#include <iostream>
#include <cstring>

#include "./src/message/messages.h"
#include "src/admin/Admin.h"
#include "src/message/messages.h"


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

    bool cerrar = false;
    while (not cerrar){
        std::cout<<"Requests al servidor\n"<<"1-Update Weather\n2-Update Currency\n3-Cerrar Servidor\n4-Cerrar Administrador"<<std::endl;
        int opt;
        cin>>opt;
        if (opt==1){
            admin_request weather{};
            std::cout<<"Actualizando datos del tiempo..."<<std::endl;
            std::cout<<"Elija la ciudad\n::";
            cin>>weather.key;
            std::cout<<"Temperatura en "<<weather.key<<": ";
            cin>>weather.temperature;
            std::cout<<"Presion en "<<weather.key<<": ";
            cin>>weather.pressure;
            std::cout<<"Humedad en "<<weather.key<<": ";
            cin>>weather.hummidity;
            admin->update_weather(weather);
        }else if(opt==2){
            admin_request currency{};
            std::cout<<"Update Currency"<<std::endl;
            std::cout<<"Elija una moneda\n::";
            cin>>currency.key;
            std::cout<<"Valor de "<<currency.key<<": ";
            cin>>currency.value;
            admin->update_currency(currency);
        }else if(opt==3){
            std::cout << "Cerrando servidor" << std::endl;
            admin->close_server();
            cerrar = true;
        }else if(opt==4){
            cerrar = true;
        }else{
            std::cout<<"Opcion Invalida"<<std::endl;
        }
    }

    delete(admin);

    return 0;
}