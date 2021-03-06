//
// Created by fedelonghi on 06/11/17.
//
#ifndef PROYECTO2_SERVER_H
#define PROYECTO2_SERVER_H


#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <set>

#include "../message/messages.h"
#include "../utils/utils.h"


using namespace std;

class Server {
private:
    int *client_id;
    int shmIdClient;
    int *admin_id;
    int shmIdAdmin;
    bool *running;
    int shmIdRunning;
    int conection_queue_id;
    int client_queue_id;
    int admin_queue_id;

    int weather_id;
    int currency_id;

    void create_conection_queue();
    void create_client_queue();
    void create_admin_queue();
    void destroy_queues();

    void create_id();
    void destroy_mem_client_id();

    void create_admin_id();
    void destroy_mem_admin_id();

    void create_running();
    void destroy_mem_running();

    int generate_client_id();

    int generate_admin_id();

    s_request transformServiceRequest(admin_request);

public:

    Server(int, int);
    virtual ~Server();

    int get_conection_queue_id();
    int get_client_queue_id();
    int get_admin_queue_id();

    long read_connection_request();
    void send_connection_established(int, int, int);

    void handle_connection_request();
    service_request read_client_request(int);


    void send_weather_response(int client_id, weather_response response);
    void send_currency_response(int, currency_response response);

    void send_weather_request(string);
    void send_currency_request(string);

    weather_response read_weather_response();
    currency_response read_currency_response();

    void send_update_weather(s_request);
    void send_update_currency(s_request);

    void handle_client_request();
    void handle_admin_request();
    void run();

    bool is_running();

    void stop_running();

};


#endif //PROYECTO2_SERVER_H