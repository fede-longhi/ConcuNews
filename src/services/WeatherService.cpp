//
// Created by fedelonghi on 26/11/17.
//

#include "WeatherService.h"
#include "../message/messages.h"

#include <fstream>

WeatherService::WeatherService() {
    this->create_conection_queue();

    loadDatabase();

    //TODO esto aca solo para testear
    weather_data data1 {};

    data1.temperature = 4005;
    data1.humidity = 4005;
    data1.pressure = 4005;

    std::string city = "FinisTerre";

    addData(data1, city);

    saveDatabase();

    this->running = true;
}

void WeatherService::loadDatabase() {

    std::ifstream dbfile("./wdb.csv");

    string city;
    float temperature;
    float pressure;
    float humidity;

    while (dbfile >> city >> temperature >> pressure >> humidity) {
        weather_data data{};
        data.humidity = humidity;
        data.pressure = pressure;
        data.temperature = temperature;
        this->database[city] = data;
    }

    dbfile.close();
}

//Cambiar para que escriba y lea del mismo archivo . Capaz guardar un archivo de backup
void WeatherService::saveDatabase() {

    map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, weather_data>::iterator
            it = database.begin();


    ofstream outputFile;
    outputFile.open("./program3data.txt");

    while (it != database.end()) {
        std::string city = it->first;

        weather_data data = it->second;

        outputFile << city << " " <<  data.temperature << " " << data.pressure << " " << data.humidity << endl;

        it++;
    }

    outputFile.close();
}

void WeatherService::addData(weather_data data, std::string city){
    database[city] = data;
}


WeatherService::~WeatherService() {
    msgctl(this->queue_id, IPC_RMID, NULL);
    saveDatabase();
}

s_request WeatherService::read_request() {
    s_request message{};
    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message) - sizeof(long), SERVICE_REQUEST, 0);
    if (bytes < 0) EXIT();
    std::cout << "Weather: Mensage recibido: " << message.key << '\n';
    return message;
}

void WeatherService::send_response(weather_response response) {
    response.mtype = SERVICE_RESPONSE_W;
    int send_result = msgsnd(this->queue_id, &response, sizeof(response) - sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Weather: Mensage enviado" << std::endl;
}

weather_response WeatherService::getInfo(std::string city) {
    weather_response response{};
    std::strcpy(response.city, city.c_str());


    const map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, weather_data>::iterator &pos = database.find(
            city);
    if (pos == database.end()) {

        response.pressure = -1;
        response.temperature = -1;
        response.humidity = -1;

    } else {
        weather_data data = pos->second;
        response.pressure = data.pressure;
        response.temperature = data.temperature;
        response.humidity = data.humidity;
    }

    return response;
}

void WeatherService::run() {
    while (this->isRunning()) {
        s_request request = this->read_request();
        if(request.code == SERVICE_REQUEST){
            weather_response response = this->getInfo(request.key);
            this->send_response(response);
        }else if(request.code == UPDATE_WEATHER_CODE){
            std::cout<<"Weather: Actualizando datos del tiempo"<<std::endl;
            weather_data data{};
            data.pressure = request.pressure;
            data.humidity = request.hummidity;
            data.temperature = request.temperature;
            addData(data, request.key);
            saveDatabase();
        }else if(request.code == CLOSE_SERVER){
            this->stopRunning();
        }else{
            std::cout<<"Weather: Codigo incorrecto"<<std::endl;
        }

    }
}

bool WeatherService::isRunning() {
    return this->running;
}

void WeatherService::create_conection_queue() {
    //creo archivo para usar path
    std::ofstream outfile("wq");
    outfile.close();

    key_t key = ftok("./wq", 'z');
    if (key < 0) EXIT();

    this->queue_id = msgget(key, IPC_CREAT | 0644);
    if (this->queue_id < 0) EXIT();
}

int WeatherService::getQueue_id() const {
    return queue_id;
}

void WeatherService::stopRunning() {
    this->running = false;
}
