//
// Created by fedelonghi on 26/11/17.
//

#ifndef PROYECTO2_CURRENCYSERVICE_H
#define PROYECTO2_CURRENCYSERVICE_H


class CurrencyService {
private:
    int queue_id;

    void create_conection_queue();

public:
    CurrencyService();

    void run();

    int getQueue_id() const;

    virtual ~CurrencyService();
};


#endif //PROYECTO2_CURRENCYSERVICE_H
