//
// Created by fedelonghi on 08/11/17.
//

#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include "./src/message/messages.h"
#include "src/server/Server.h"


using namespace std;

int main(int argc, char** argv) {

    std::cout<<"Servidor Corriendo..."<<std::endl;
    std::cout<<"Bienvenido al Portal ConcuNews!"<<std::endl;

    std::cout<<argv[0]<<std::endl;

    auto *server = new Server();

    std::cout << "Solicite conexion a traves de la siguiente direccion" << std::endl;
    std::cout << "ID: " << server->get_conection_queue_id() << std::endl;

    server->run();

    pid_t pid_connection = fork();
    if (pid_connection == 0){
        //server->set_pid_connection(getpid());
        server->handle_connection_request();
        exit(0);
    }else{
        pid_t pid_cliente = fork();
        if (pid_cliente == 0){
            //server->set_pid_client(getpid());
            server->handle_client_request();
            exit(0);
        }else{
            server->handle_admin_request();
        }
        int status2;
        wait(&status2);
    }
    int status;
    wait(&status);

    delete(server);

    std::cout<<"Bye!"<<std::endl;

    return 0;
}