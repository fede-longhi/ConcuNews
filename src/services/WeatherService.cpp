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
}

void WeatherService::loadDatabase() {

    std::ifstream dbfile("/home/navent/Fede/ConcuNews/src/wdb.csv");

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


    //TODO prueba
    cout << getInfo("BuenosAires").city << endl;
    cout << getInfo("BuenosAires").temperature << endl;
    cout << getInfo("BuenosAires").pressure << endl;
    cout << getInfo("BuenosAires").humidity << endl;


}

//Cambiar para que escriba y lea del mismo archivo . Capaz guardar un archivo de backup
void WeatherService::saveDatabase() {

    map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, weather_data>::iterator
            it = database.begin();


    ofstream outputFile;
    outputFile.open("/home/navent/Fede/ConcuNews/src/program3data.txt");

    while (it != database.end()) {
        // Accessing KEY from element pointed by it.
        std::string city = it->first;

        // Accessing VALUE from element pointed by it.
        weather_data data = it->second;

        outputFile << city << " " <<  data.temperature << " " << data.pressure << " " << data.humidity << endl;

        // Increment the Iterator to point to next entry
        it++;
    }

    outputFile.close();
    cout << "Done!\n";


}

void WeatherService::addData(weather_data data, std::string city){

    database[city] = data;

}


WeatherService::~WeatherService() {
    msgctl(this->queue_id, IPC_RMID, NULL);
}

string WeatherService::read_request() {
    s_request message;

    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message) - sizeof(long), SERVICE_REQUEST, 0);
    if (bytes < 0) EXIT();

    std::cout << "Mensage recibido: " << message.code << '\n';

    return message.code;
}

void WeatherService::send_response(weather_response response) {
    response.mtype = SERVICE_RESPONSE_W;
    int send_result = msgsnd(this->queue_id, &response, sizeof(response) - sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Mensage enviado" << std::endl;
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
//    string i=0;
    string i;
    //TODO true?
    while (true) {
        i = this->read_request();
        weather_response response = this->getInfo(i);
        this->send_response(response);
    }
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


float WeatherService::getPressure(int) {
    return 1024;
}

float WeatherService::getHummidity(int) {
    return 10;
}

float WeatherService::getTemperature(int) {
    return 30;
}
