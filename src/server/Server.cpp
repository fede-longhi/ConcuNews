//
// Created by fedelonghi on 06/11/17.
//

#include "Server.h"
#include "../message/messages.h"

Server::Server() {
    this->create_conection_queue();
    this->create_client_queue();
    this->create_admin_queue();
    this->create_id();
    *this->client_id = LAST_PROTECTED_ID + 1;
    this->create_admin_id();
    *this->admin_id = LAST_ADMIN_PROTECTED_ID + 1;
    this->create_running();
    *this->running = false;
}

Server::~Server() {
    this->destroy_queues();
    this->destroy_mem_client_id();
    this->destroy_mem_admin_id();
    this->destroy_mem_running();
}

void Server::create_conection_queue() {
    //creo archivo para usar path
    std::ofstream outfile ("queue_file");
    outfile.close();

    key_t key = ftok("./queue_file", 'a');
    if (key < 0 ) EXIT();

    this->conection_queue_id = msgget(key, IPC_CREAT|0644);
    if (this->conection_queue_id < 0) EXIT();
}

void Server::destroy_queues() {
    msgctl(this->conection_queue_id, IPC_RMID, NULL);
    msgctl(this->client_queue_id, IPC_RMID, NULL);
    msgctl(this->admin_queue_id, IPC_RMID, NULL);
}

void Server::create_client_queue() {
    std::ofstream outfile ("queue_file");
    outfile.close();

    key_t key = ftok("./queue_file", 'b');
    if (key < 0 ) EXIT();

    this->client_queue_id = msgget(key, IPC_CREAT|0644);
    if (this->client_queue_id < 0) EXIT();
}

void Server::create_admin_queue() {
    std::ofstream outfile ("queue_file");
    outfile.close();

    key_t key = ftok("./queue_file", 'c');
    if (key < 0 ) EXIT();

    this->admin_queue_id = msgget(key, IPC_CREAT|0644);
    if (this->admin_queue_id < 0) EXIT();
}

int Server::generate_client_id() {
    int id = *this->client_id;
    *this->client_id += LAST_PROTECTED_ID;
    return id;
}

int Server::generate_admin_id() {
    int id = *this->admin_id;
    *this->admin_id += LAST_ADMIN_PROTECTED_ID;
    return id;
}

int Server::get_conection_queue_id() {
    return this->conection_queue_id;
}

long Server::read_connection_request() {
    connection_request mensaje;

    ssize_t bytes = msgrcv(this->conection_queue_id, &mensaje, sizeof(mensaje)-sizeof(long), -LAST_CONNECTION_CODE, 0);
    if (bytes < 0) EXIT();

    std::cout << "Mensage recibido: " << mensaje.mtype << '\n';

    return mensaje.mtype;
}

void Server::send_connection_established(int type, int id, int queue_id) {
    connection_response response{};
    response.mtype = type;
    response.id = id;
    response.queue_id = queue_id;
    int send_result = msgsnd(this->conection_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Mensage enviado al cliente con id: "<< response.id << '\n';
}

void Server::handle_connection_request() {
    while (this->is_running()){
        std::cout<<"Esperando conexion..."<<std::endl;
        long type = this->read_connection_request();
        if (type == CONNECTION_REQUEST_ID){
            this->send_connection_established(ESTABLISHED_CONNECTION_ID,
                                              this->generate_client_id(),
                                              this->get_client_queue_id()
            );
            std::cout<<"Conexion establecida con cliente"<<std::endl;
        }else if (type == CONNECTION_ADMIN_REQUEST){
            this->send_connection_established(ESTABLISHED_ADMIN_CONNECTION_ID,
                                              this->generate_admin_id(),
                                              this->get_admin_queue_id()
            );
            std::cout<<"Conexion establecida con administrador"<<std::endl;
        }else{
            std::cout<<"Error codigo de conexion invalido"<<std::endl;
        }
    }
}

void Server::handle_client_request() {
    while (this->is_running()){
        std::cout<<"Esperando client request..."<<std::endl;
        service_request request = this->read_client_request(-LAST_PROTECTED_ID);
        std::cout<<"Request recibido del cliente: "<<request.client_id<<std::endl;
        if (request.mtype == WEATHER_CODE){
            std::cout<<"Solicitud de tiempo"<<std::endl;
            std::cout<<"Ciudad: "<<request.code<<std::endl;
            //TODO look for weather in weather service

            this->send_weather_request(request.code);

            weather_response response = this->read_weather_response();

            this->send_weather_response(request.client_id, response);
            std::cout<<"Respuesta enviada"<<std::endl;
        }else if (request.mtype == CURRENCY_CODE){
            std::cout<<"Solicitud de moneda"<<std::endl;
            //TODO look for currency in currency service
            this->send_currency_response(request.client_id, request.code);
            std::cout<<"Respuesta enviada"<<std::endl;
        }else{
            std::cout<<"Error: codigo de mensaje invalido"<<std::endl;
        }
    }
}

service_request Server::read_client_request(int code) {
    std::cout<<"Por leer request"<<std::endl;
    service_request request{};
    ssize_t bytes = msgrcv(this->client_queue_id, &request, sizeof(request)-sizeof(long), code, 0);
    if (bytes < 0) EXIT();
    return request;
}

void Server::send_weather_request(string ciudad) {

    s_request request;
    request.mtype = SERVICE_REQUEST;
    std::strcpy(request.code, ciudad.c_str());
//    int send_result = msgsnd(ID_WEATHER_SERVICE, &request, sizeof(request)-sizeof(long), 0);
//    if (send_result < 0) EXIT();

}

weather_response Server::read_weather_response() {

    std::cout<<"Por leer request"<<std::endl;
    weather_response response{};
//    ssize_t bytes = msgrcv(ID_WEATHER_SERVICE, &response, sizeof(response)-sizeof(long), NO ESTOY SEGURO QUE VA ACA, 0);
//    if (bytes < 0) EXIT();
    return response;


}


void Server::send_weather_response(int client_id, weather_response response) {
    int send_result = msgsnd(this->client_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

void Server::send_currency_response(int client_id, string moneda) {
    currency_response response{};
    response.mtype = client_id + CURRENCY_CODE;
    response.value = 30;
    std::strcpy(response.coin, moneda.c_str());
    int send_result = msgsnd(this->client_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

void Server::handle_admin_request() {
    while (this->is_running()){
        std::cout<<"Esperando admin request..."<<std::endl;
        admin_request request{};
        ssize_t bytes = msgrcv(this->admin_queue_id, &request,
                               sizeof(request)-sizeof(long), -LAST_ADMIN_PROTECTED_ID, 0);
        if (bytes < 0) EXIT();
        std::cout<<"Admin request recibido"<<std::endl;
        if (request.mtype == CLOSE_SERVER){
            std::cout<<"Cerrando servidor"<<std::endl;
            this->stop_running();
        }else if(request.mtype == UPDATE_WEATHER_CODE){
            std::cout<<"Updating Weather"<<std::endl;
            //TODO update weather
        }else if(request.mtype == UPDATE_CURRENCY_CODE){
            std::cout<<"Updating Currency"<<std::endl;
            //TODO update currency
        }else{
            std::cout<<"Unknown code"<<std::endl;
            //TODO update currency
        }
    }
}

void Server::create_id() {
    std::ofstream outfile ("mem_file");
    outfile.close();

    key_t key = ftok("./mem_file", 'a');
    if (key < 0 ) EXIT();

    this->shmIdClient = shmget(key, sizeof(int), 0644|IPC_CREAT);
    if (shmIdClient < 0) EXIT();

    void* tmpPtr = shmat(this->shmIdClient, NULL, 0);
    if(tmpPtr != (void*) -1) {
        this->client_id = (int *) tmpPtr;
    }else{
        EXIT();
    }
}

void Server::destroy_mem_client_id() {
    int errorDt = shmdt ( (void *) this->client_id);
    if ( errorDt != -1 ){
        shmctl (this->shmIdClient, IPC_RMID, NULL);
    }else{
        EXIT();
    }
}

void Server::destroy_mem_running(){
    int errorDt = shmdt ( (void *) this->running);
    if ( errorDt != -1 ){
            shmctl (this->shmIdRunning, IPC_RMID, NULL);
    }else{
        EXIT();
    }
}

void Server::run(){
    *this->running=true;
}

void Server::create_running() {
    std::ofstream outfile ("mem_file2");
    outfile.close();

    key_t key = ftok("./mem_file2", 'a');
    if (key < 0 ) EXIT();

    this->shmIdRunning = shmget(key, sizeof(bool), 0644|IPC_CREAT);
    if (shmIdRunning < 0) EXIT();

    void* tmpPtr = shmat(this->shmIdRunning, nullptr, 0);
    if(tmpPtr != (void*) -1) {
        this->running = (bool *) tmpPtr;
    }else{
        EXIT();
    }
}

bool Server::is_running() {
    return *this->running;
}

void Server::stop_running() {
    *this->running = false;
    //TODO revisar los mtype
    //envio mensajes a las colas de clientes y conexion para que no queden esperando.
    service_request message_client{};
    message_client.mtype = CLOSE_CONNECTION;
    int send_result_client = msgsnd(this->client_queue_id, &message_client, sizeof(message_client)-sizeof(long), 0);
    connection_request message_connection{};
    message_connection.mtype = CONNECTION_REQUEST_ID;
    int send_result_connection = msgsnd(this->conection_queue_id, &message_connection, sizeof(message_connection)-sizeof(long), 0);
}

int Server::get_client_queue_id() {
    return this->client_queue_id;
}

int Server::get_admin_queue_id() {
    return this->admin_queue_id;
}

void Server::create_admin_id() {
    std::ofstream outfile ("mem_file");
    outfile.close();

    key_t key = ftok("./mem_file", 'b');
    if (key < 0 ) EXIT();

    this->shmIdAdmin = shmget(key, sizeof(int), 0644|IPC_CREAT);
    if (shmIdAdmin < 0) EXIT();

    void* tmpPtr = shmat(this->shmIdAdmin, nullptr, 0);
    if(tmpPtr != (void*) -1) {
        this->admin_id = (int *) tmpPtr;
    }else{
        EXIT();
    }
}

void Server::destroy_mem_admin_id() {
    int errorDt = shmdt ( (void *) this->admin_id);
    if ( errorDt != -1 ){
        shmctl (this->shmIdAdmin, IPC_RMID, NULL);
    }else{
        EXIT();
    }
}
