//
// Created by fedelonghi on 26/11/17.
//

#include "WeatherService.h"
#include "../message/messages.h"

WeatherService::WeatherService() {
    this->create_conection_queue();
}

WeatherService::~WeatherService() {
    msgctl(this->queue_id, IPC_RMID, NULL);
}

int WeatherService::read_request() {
    s_request message;

    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message)-sizeof(long), SERVICE_REQUEST, 0);
    if (bytes < 0) EXIT();

    std::cout << "Mensage recibido: " << message.code << '\n';

    return message.code;
}

void WeatherService::send_response(weather_response response) {
    response.mtype = SERVICE_RESPONSE_W;
    int send_result = msgsnd(this->queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Mensage enviado"<<std::endl;
}

weather_response WeatherService::getInfo(int code) {
    weather_response response{};
    response.code = code;
    response.pressure = this->getPressure(code);
    response.temperature = this->getTemperature(code);
    response.humidity = this->getHummidity(code);
    return response;
}

void WeatherService::run() {
    int i=0;
    while(i<10){
        i=this->read_request();
        weather_response response = this->getInfo(i);
        this->send_response(response);
    }
}

void WeatherService::create_conection_queue() {
    //creo archivo para usar path
    std::ofstream outfile ("wq");
    outfile.close();

    key_t key = ftok("./wq", 'z');
    if (key < 0 ) EXIT();

    this->queue_id = msgget(key, IPC_CREAT|0644);
    if (this->queue_id < 0) EXIT();
}

int WeatherService::getQueue_id() const {
    return queue_id;
}


float WeatherService::getPressure(int) {
    return 1024;
}

float WeatherService::getHummidity(int) {
    return 10;
}

float WeatherService::getTemperature(int) {
    return 30;
}
