//
// Created by fedelonghi on 05/11/17.
//
#ifndef PROYECTO2_MESSAGES_H
#define PROYECTO2_MESSAGES_H


#include <ctime>
#include <string>

/* ********** Connection Messages **** */
#define CONNECTION_REQUEST_ID 1
#define CONNECTION_ADMIN_REQUEST 2
#define LAST_CONNECTION_CODE 2
#define ESTABLISHED_CONNECTION_ID 3
#define ESTABLISHED_ADMIN_CONNECTION_ID 4
/* *********************************** */

/* ********** Admin Messages ********* */
#define UPDATE_WEATHER_CODE 1
#define UPDATE_CURRENCY_CODE 2
#define CLOSE_SERVER 3
#define LAST_ADMIN_PROTECTED_ID 3
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
    long mtype; //service_request
    char code[50];
    int client_id;
    //string r;
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
    float temperature;
    float pressure;
    float humidity;
}weather_data;

typedef struct {
    long mtype;
    char coin[50];//codigo resultado
    float value;
}currency_response;


typedef struct {
    long mtype;
    int code = CLOSE_CONNECTION;
}close_connection;

typedef struct {
    long mtype;
    int code;
    char city[50];
    float temperature;
    float pressure;
    float hummidity;
    float value;
    char coin[50];
}admin_request;

typedef struct{
    long mtype;
    char code[50];
}s_request;


#endif //PROYECTO2_MESSAGES_H
