#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <cstring>

#include "./src/message/messages.h"
#include "./src/utils/utils.h"
#include "src/message/messages.h"


using namespace std;

int main(int argc, char** argv) {

    unsigned int idhandler = 3;


    if (argc > 1){
        if ( argv[1][0] == 'c'){

            int id_queue = 0;
            std::cin >> id_queue;
            std::cout << "Cliente" << std::endl;
            std::cout << "Enviando Mensaje" << std::endl;
            connection_request mensaje;
            mensaje.mtype = 10;
            int send_result_cliente = msgsnd(id_queue, &mensaje, sizeof(mensaje)-sizeof(long), 0);
            if (send_result_cliente < 0)
                EXIT();
            return 0;

        }
    }

    std::cout << "Portal Corriendo" << std::endl;

    key_t key = ftok(argv[0], 'a');
    if (key < 0 )
        EXIT();

    int id_queue = msgget(key, IPC_CREAT|0644);
    if (id_queue < 0)
        EXIT();
    std::cout << "Queue ID: " << id_queue << std::endl;

    // Envio mensaje
    connection_request mensaje;

    mensaje.mtype = CONNECTION_REQUEST_ID;

    int send_result = msgsnd(id_queue, &mensaje, sizeof(mensaje)-sizeof(long), 0);
    if (send_result < 0)
        EXIT();
    std::cout << "Mensage enviado" << '\n';

    ssize_t bytes = msgrcv(id_queue, &mensaje, sizeof(mensaje)-sizeof(long), CONNECTION_REQUEST_ID, 0);
    if (bytes < 0)
        EXIT();
    std::cout << "Mensage recibido: " << mensaje.mtype << '\n';

    std::cout << "Mensage es: " << mensaje.mtype << '\n';


    // Respuesta

    connection_response mensaje_response;
    mensaje_response.mtype = ESTABLISHED_CONNECTION_ID;
    mensaje_response.id = idhandler;
    idhandler += 2;

    int send_result2 = msgsnd(id_queue, &mensaje_response, sizeof(mensaje_response)-sizeof(long), 0);
    if (send_result2 < 0)
        EXIT();
    std::cout << "Mensage enviado al cliente" << '\n';

    ssize_t bytes2 = msgrcv(id_queue, &mensaje_response, sizeof(mensaje_response)-sizeof(long), ESTABLISHED_CONNECTION_ID, 0);
    if (bytes2 < 0) EXIT();
    std::cout << "Mensage recibido: " << mensaje_response.id << '\n';


    bool running =  true;
    while (running){
        ssize_t bytes_m = msgrcv(id_queue, &mensaje_response, sizeof(mensaje_response)-sizeof(long), 10, 0);
        if (bytes_m < 0) EXIT();
        std::cout << "Mensaje Recibido" << std::endl;
        running = false;
    }



    return 0;
}