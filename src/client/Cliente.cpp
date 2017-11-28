//
// Created by fedelonghi on 05/11/17.
//

#include "Cliente.h"
#include "../message/messages.h"
#include <string>
#include <iostream>

Cliente::Cliente(){
    this->client_id = -1;
    this->queue_id = -1;
}

Cliente::~Cliente() {
}

int Cliente::get_id() {
    return this->client_id;
}

int Cliente::request_connection() {
    if (this->queue_id<0){
        std::cout<<"Need a queue id to establish connection!"<<std::endl;
        EXIT();
    }

    connection_request mensaje;
    mensaje.mtype = CONNECTION_REQUEST_ID;

    int send_result = msgsnd(this->queue_id, &mensaje, sizeof(mensaje)-sizeof(long), 0);

    if (send_result < 0){
        std::cout<<"Fallo request connection"<<std::endl;
        EXIT();
    }

    return 0;
}

void Cliente::read_connection_response() {
    connection_response mensaje{};

    ssize_t bytes = msgrcv(this->queue_id, &mensaje, sizeof(mensaje)-sizeof(long), ESTABLISHED_CONNECTION_ID, 0);
    if (bytes < 0) EXIT();

    std::cout << "Mensage recibido" << '\n';

    this->client_id = mensaje.id;
    this->queue_id = mensaje.queue_id; //cambio el queue id para que mande mensajes al client queue

    std::cout<<"Cliente asociado a id: "<< this->client_id <<std::endl;
    std::cout<<"Direccion de cola: "<< this->queue_id <<std::endl;
}

void Cliente::establish_connection() {
    this->request_connection();
    this->read_connection_response();
}


void Cliente::send_request(service_request message) {
    message.client_id = this->client_id;
    int send_result = msgsnd(this->queue_id, &message, sizeof(message)-sizeof(long), 0);

    if (send_result < 0){
        std::cout<<"Fallo request de servicio"<<std::endl;
        EXIT();
    }
}

void Cliente::request_weather(string city) {
    service_request message{};
    message.mtype = WEATHER_CODE;
    std::strcpy(message.code, city.c_str());
    this->send_request(message);
}

void Cliente::request_currency(string coin){
    service_request message{};
    message.mtype = CURRENCY_CODE;
    std::strcpy(message.code, coin.c_str());
    this->send_request(message);
}

weather_response Cliente::read_weather_response() {
    weather_response message{};

    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message)-sizeof(long), this->client_id + WEATHER_CODE, 0);
    if (bytes < 0) EXIT();

    std::cout << "Leo Weather Response" << std::endl;

    return message;
}

currency_response Cliente::read_currency_response() {
    currency_response message;

    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message)-sizeof(long), this->client_id+CURRENCY_CODE, 0);
    if (bytes < 0) EXIT();

    std::cout << "Leo Currency Response" << std::endl;

    return message;
}

void Cliente::set_queueid(int id) {
    this->queue_id = id;
}
