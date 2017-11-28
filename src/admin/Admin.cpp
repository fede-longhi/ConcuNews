//
// Created by fedelonghi on 24/11/17.
//

#include "Admin.h"
#include "../message/messages.h"

Admin::Admin() {
    this->admin_id = -1;
    this->queue_id = -1;

}

int Admin::get_id() {
    return this->admin_id;
}

int Admin::request_connection() {
    if (this->queue_id<0){
        std::cout<<"Need a queue id to establish connection!"<<std::endl;
        EXIT();
    }

    connection_request mensaje;
    mensaje.mtype = CONNECTION_ADMIN_REQUEST;

    int send_result = msgsnd(this->queue_id, &mensaje, sizeof(mensaje)-sizeof(long), 0);

    if (send_result < 0){
        std::cout<<"Fallo request connection"<<std::endl;
        EXIT();
    }
    return 0;
}

void Admin::read_connection_response() {
    connection_response mensaje;

    ssize_t bytes = msgrcv(this->queue_id, &mensaje, sizeof(mensaje)-sizeof(long), ESTABLISHED_ADMIN_CONNECTION_ID, 0);
    if (bytes < 0) EXIT();

    std::cout << "Mensage recibido" << '\n';

    this->admin_id = mensaje.id;
    this->queue_id = mensaje.queue_id; //cambio el queue id para que mande mensajes al admin queue

    std::cout<<"Admin asociado a id: "<< this->admin_id <<std::endl;
}

void Admin::establish_connection() {
    this->request_connection();
    this->read_connection_response();
}

void Admin::update_weather(admin_request message) {
    message.mtype = UPDATE_WEATHER_CODE;
    int send_result = msgsnd(this->queue_id, &message, sizeof(message)-sizeof(long), 0);

    if (send_result < 0){
        std::cout<<"Fallo close server message"<<std::endl;
        EXIT();
    }
}

void Admin::update_currency(admin_request message) {
    message.mtype = UPDATE_CURRENCY_CODE;
    int send_result = msgsnd(this->queue_id, &message, sizeof(message) - sizeof(long), 0);

    if (send_result < 0) {
        std::cout << "Fallo close server message" << std::endl;
        EXIT();
    }
}

void Admin::close_server() {
    if (this->queue_id<0){
        std::cout<<"Need a queue id to send messages!"<<std::endl;
        EXIT();
    }

    admin_request message{};
    message.mtype = CLOSE_SERVER;
    message.code = this->admin_id;

    int send_result = msgsnd(this->queue_id, &message, sizeof(message)-sizeof(long), 0);

    if (send_result < 0){
        std::cout<<"Fallo close server message"<<std::endl;
        EXIT();
    }
}

void Admin::set_queueid(int id) {
    this->queue_id = id;

}

Admin::~Admin() {

}
