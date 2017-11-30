//
// Created by fedelonghi on 26/11/17.
//

#include <fstream>
#include "CurrencyService.h"
#include "../message/messages.h"

CurrencyService::CurrencyService() {
    this->create_conection_queue();
    loadDatabase();
    addData(17,"dolar");
    saveDatabase();
    this->running=true;
}

CurrencyService::~CurrencyService() {
    this->running=false;
    saveDatabase();
}

void CurrencyService::create_conection_queue() {
    //creo archivo para usar path
    std::ofstream outfile("cq");
    outfile.close();

    key_t key = ftok("./cq", 'c');
    if (key < 0) EXIT();

    this->queue_id = msgget(key, IPC_CREAT | 0644);
    if (this->queue_id < 0) EXIT();
}

void CurrencyService::run() {
    while (this->isRunning()){
        s_request request = this->read_request();
        if(request.code == SERVICE_REQUEST){
            currency_response response = this->getInfo(request.key);
            this->send_response(response);
        }else if(request.code == UPDATE_CURRENCY_CODE){
            std::cout<<"Currency: Actualizando datos de moneda"<<std::endl;
            addData(request.value,request.key);
            saveDatabase();
        }else if(request.code == CLOSE_SERVER){
            this->stopRunning();
        }else{
            std::cout<<"Currency: Codigo incorrecto"<<std::endl;
        }
    }

}

bool CurrencyService::isRunning() {
    return this->running;
}

void CurrencyService::stopRunning() {
    this->running=false;
}

s_request CurrencyService::read_request() {
    s_request message{};
    ssize_t bytes = msgrcv(this->queue_id, &message, sizeof(message) - sizeof(long), SERVICE_REQUEST, 0);
    if (bytes < 0) EXIT();
    std::cout << "Currency: Mensage recibido: " << message.key << '\n';
    return message;
}

currency_response CurrencyService::getInfo(string currency) {
    currency_response response{};
    std::strcpy(response.coin, currency.c_str());

    const map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, float>::iterator &pos = database.find(
            currency);
    if (pos == database.end()) {
        response.value = -1;
    } else {
        float data = pos->second;
        response.value = data;
    }

    return response;
}

void CurrencyService::send_response(currency_response response) {
    response.mtype = SERVICE_RESPONSE_C;
    int send_result = msgsnd(this->queue_id, &response, sizeof(response) - sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Currency: Mensage enviado" << std::endl;
}

int CurrencyService::getQueue_id() const {
    return this->queue_id;
}

void CurrencyService::loadDatabase() {

    std::ifstream dbfile("./cdb.csv");

    std::string currency;
    float value;

    while (dbfile >> currency >> value) {
        this->database[currency] = value;
    }

    dbfile.close();


}

//Cambiar para que escriba y lea del mismo archivo . Capaz guardar un archivo de backup
void CurrencyService::saveDatabase() {

    std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, float>::iterator it = database.begin();

    std::ofstream outputFile;
    outputFile.open("./program4data.txt");

    while (it != database.end()) {
        std::string city = it->first;

        float value = it->second;

        outputFile << city << " " <<  value << std::endl;

        it++;
    }

    outputFile.close();
}

void CurrencyService::addData(float value, std::string currency){
    database[currency] = value;
}