//
// Created by fedelonghi on 06/11/17.
//

#include "Server.h"


Server::Server(int weather_id, int currency_id) {
    this->create_conection_queue();
    this->create_client_queue();
    this->create_admin_queue();
    this->create_id();
    *this->client_id = LAST_PROTECTED_ID + 1;
    this->create_admin_id();
    *this->admin_id = LAST_ADMIN_PROTECTED_ID + 1;
    this->create_running();
    *this->running = false;
    this->weather_id = weather_id;
    this->currency_id = currency_id;
}

Server::~Server() {
    this->destroy_queues();
    this->destroy_mem_client_id();
    this->destroy_mem_admin_id();
    this->destroy_mem_running();
}

int Server::get_client_queue_id() {
    return this->client_queue_id;
}

int Server::get_admin_queue_id() {
    return this->admin_queue_id;
}

int Server::get_conection_queue_id() {
    return this->conection_queue_id;
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

void Server::destroy_queues() {
    msgctl(this->conection_queue_id, IPC_RMID, nullptr);
    msgctl(this->client_queue_id, IPC_RMID, nullptr);
    msgctl(this->admin_queue_id, IPC_RMID, nullptr);
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

long Server::read_connection_request() {
    connection_request mensaje;

    ssize_t bytes = msgrcv(this->conection_queue_id, &mensaje, sizeof(mensaje)-sizeof(long), -LAST_CONNECTION_CODE, 0);
    if (bytes < 0) EXIT();

    std::cout << "Server: Mensage recibido: " << mensaje.mtype << '\n';

    return mensaje.mtype;
}

void Server::send_connection_established(int type, int id, int queue_id) {
    connection_response response{};
    response.mtype = type;
    response.id = id;
    response.queue_id = queue_id;
    int send_result = msgsnd(this->conection_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
    std::cout << "Server: Mensage enviado al cliente con id: "<< response.id << '\n';
}

void Server::handle_connection_request() {
    while (this->is_running()){
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
        service_request request = this->read_client_request(-LAST_PROTECTED_ID);
        std::cout<<"Server: Request recibido del cliente: "<<request.client_id<<std::endl;
        if (request.mtype == WEATHER_CODE){
            std::cout<<"Server: Solicitud de tiempo"<<std::endl;
            std::cout<<"Ciudad: "<<request.code<<std::endl;

            //Comunicacion con el servicio
            this->send_weather_request(request.code);
            weather_response response = this->read_weather_response();

            this->send_weather_response(request.client_id, response);
            std::cout<<"Server: Respuesta enviada"<<std::endl;
        }else if (request.mtype == CURRENCY_CODE){
            std::cout<<"Server: Solicitud de moneda"<<std::endl;
            std::cout<<"Moneda: "<<request.code<<std::endl;

            //Comunicacion con el servicio
            this->send_currency_request(request.code);
            currency_response response = this->read_currency_response();

            this->send_currency_response(request.client_id, response);
            std::cout<<"Server: Respuesta enviada"<<std::endl;
        }else{
            std::cout<<"Error: codigo de mensaje invalido"<<std::endl;
        }
    }
}

service_request Server::read_client_request(int code) {
    service_request request{};
    ssize_t bytes = msgrcv(this->client_queue_id, &request, sizeof(request)-sizeof(long), code, 0);
    if (bytes < 0) EXIT();
    return request;
}

void Server::send_weather_request(string ciudad) {
    s_request request{};
    request.mtype = SERVICE_REQUEST;
    request.code = SERVICE_REQUEST;
    std::strcpy(request.key, ciudad.c_str());
    int send_result = msgsnd(this->weather_id, &request, sizeof(request)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

weather_response Server::read_weather_response() {
    weather_response response{};
    ssize_t bytes = msgrcv(this->weather_id, &response, sizeof(response)-sizeof(long), SERVICE_RESPONSE_W, 0);
    if (bytes < 0) EXIT();
    return response;
}

void Server::send_weather_response(int client_id, weather_response response) {
    response.mtype = client_id+WEATHER_CODE;
    int send_result = msgsnd(this->client_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

void Server::send_currency_request(string moneda) {
    s_request request{};
    request.mtype = SERVICE_REQUEST;
    request.code = SERVICE_REQUEST;
    std::strcpy(request.key, moneda.c_str());
    int send_result = msgsnd(this->currency_id, &request, sizeof(request)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

currency_response Server::read_currency_response() {
    currency_response response{};
    ssize_t bytes = msgrcv(this->currency_id, &response, sizeof(response)-sizeof(long), SERVICE_RESPONSE_C, 0);
    if (bytes < 0) EXIT();
    return response;
}

void Server::send_currency_response(int client_id, currency_response response) {
    response.mtype = client_id + CURRENCY_CODE;
    int send_result = msgsnd(this->client_queue_id, &response, sizeof(response)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

void Server::handle_admin_request() {
    while (this->is_running()){
        admin_request request{};
        ssize_t bytes = msgrcv(this->admin_queue_id, &request,
                               sizeof(request)-sizeof(long), -LAST_ADMIN_PROTECTED_ID, 0);
        if (bytes < 0) EXIT();
        std::cout<<"Server: Admin request recibido"<<std::endl;
        if (request.mtype == CLOSE_SERVER){
            std::cout<<"Server: Cerrando servidor"<<std::endl;
            this->stop_running();
        }else if(request.mtype == UPDATE_WEATHER_CODE){
            std::cout<<"Server: Updating Weather"<<std::endl;
            s_request s_req = this->transformServiceRequest(request);
            this->send_update_weather(s_req);
        }else if(request.mtype == UPDATE_CURRENCY_CODE){
            std::cout<<"Server: Updating Currency"<<std::endl;
            s_request service_request = this->transformServiceRequest(request);
            this->send_update_currency(service_request);
        }else{
            std::cout<<"Server: Unknown code"<<std::endl;
        }
    }
}

s_request Server::transformServiceRequest(admin_request origin) {
    s_request final{};
    final.code = origin.code;
    strcpy(final.key, origin.key);
    final.hummidity = origin.hummidity;
    final.pressure = origin.pressure;
    final.temperature = origin.temperature;
    final.value = origin.value;
    return final;
}

void Server::send_update_weather(s_request request) {
    request.mtype = SERVICE_REQUEST;
    request.code = UPDATE_WEATHER_CODE;
    int send_result = msgsnd(this->weather_id, &request, sizeof(request)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}

void Server::send_update_currency(s_request request) {
    request.mtype = SERVICE_REQUEST;
    request.code = UPDATE_CURRENCY_CODE;
    int send_result = msgsnd(this->currency_id, &request, sizeof(request)-sizeof(long), 0);
    if (send_result < 0) EXIT();
}


void Server::create_id() {
    std::ofstream outfile ("mem_file");
    outfile.close();

    key_t key = ftok("./mem_file", 'a');
    if (key < 0 ) EXIT();

    this->shmIdClient = shmget(key, sizeof(int), 0644|IPC_CREAT);
    if (shmIdClient < 0) EXIT();

    void* tmpPtr = shmat(this->shmIdClient, nullptr, 0);
    if(tmpPtr != (void*) -1) {
        this->client_id = (int *) tmpPtr;
    }else{
        EXIT();
    }
}

void Server::destroy_mem_client_id() {
    int errorDt = shmdt ( (void *) this->client_id);
    if ( errorDt != -1 ){
        shmctl (this->shmIdClient, IPC_RMID, nullptr);
    }else{
        EXIT();
    }
}

void Server::destroy_mem_running(){
    int errorDt = shmdt ( (void *) this->running);
    if ( errorDt != -1 ){
            shmctl (this->shmIdRunning, IPC_RMID, nullptr);
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
        shmctl (this->shmIdAdmin, IPC_RMID, nullptr);
    }else{
        EXIT();
    }
}
