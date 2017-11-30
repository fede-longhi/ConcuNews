# ConcuNews

## Ejecucion

### Servicios
Para ejecutar los sercicios basta con llamarlos desde la consola:  
`./weather_service`  
`./currency_service`  
Ambos devolveran un id (weather_service_id, currency_service_id). Este nos servira para conectar el servidor con los servicios.

### Ejecucion del servidor
El servidor recibe como parametros el id de weather service y el de currency service, en ese orden:  
`./server <weather_service_id> <currency_service_id>`  
A su vez el servidor devolvera un id (server_id) para que los clientes y administradores puedan conectarse.  

### Ejecucion de clientes y administradores
Los clientes y administradores se ejecutan de la misma manera. Ambos reciben el id del servidor para poder comunicarse con este:  
`./client <server_id>`  
`./admin <server_id>`  
Cuando se ejecutan se abre la consola interactiva correspondiente.
