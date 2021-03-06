//
// Created by fedelonghi on 05/11/17.
//
#ifndef PROYECTO2_MESSAGES_H
#define PROYECTO2_MESSAGES_H


#include <ctime>
#include <string>

#define N 50

/* ********** Connection Messages **** */
#define CONNECTION_REQUEST_ID 1
#define CONNECTION_ADMIN_REQUEST 2
#define LAST_CONNECTION_CODE 2
#define ESTABLISHED_CONNECTION_ID 3
#define ESTABLISHED_ADMIN_CONNECTION_ID 4
/* *********************************** */

/* ********** Admin Messages ********* */
#define UPDATE_WEATHER_CODE 2
#define UPDATE_CURRENCY_CODE 3
#define CLOSE_SERVER 4
#define LAST_ADMIN_PROTECTED_ID 4
/* *********************************** */

/* ********** Client Messages ******** */
#define WEATHER_CODE 1
#define CURRENCY_CODE 2
#define CLOSE_CONNECTION 3
#define LAST_PROTECTED_ID 3
/* *********************************** */

/* ********** Services Messages ****** */
#define SERVICE_REQUEST 1
#define SERVICE_RESPONSE_W 2
#define SERVICE_RESPONSE_C 3
/* *********************************** */

using namespace std;

typedef struct {
    long mtype = CONNECTION_REQUEST_ID;
}connection_request;

typedef struct {
    long mtype;
    int id;
    int queue_id;
}connection_response;

typedef struct {
    long mtype;
    char code[N];
    int client_id;
}service_request;

typedef struct {
    long mtype; //id + WEATHER_CODE
    char city[50];
    //codigo resultado
    float temperature;
    float pressure;
    float humidity;
}weather_response;

typedef struct {
    long mtype;
    char coin[N];//codigo resultado
    float value;
}currency_response;


typedef struct {
    long mtype;
    int code = CLOSE_CONNECTION;
}close_connection;

typedef struct {
    long mtype;
    int code;
    char key[N];
    float temperature;
    float pressure;
    float hummidity;
    float value;
}admin_request;

typedef struct{
    long mtype;
    int code;
    char key[N];
    float temperature;
    float pressure;
    float hummidity;
    float value;
}s_request;


typedef struct {
    float temperature;
    float pressure;
    float humidity;
}weather_data;


#endif //PROYECTO2_MESSAGES_H
