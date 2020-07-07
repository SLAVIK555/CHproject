#ifndef MQTTCLASS_H
#define MQTTCLASS_H

#include "fvnpclass.h"
#include "mqtt/client.h"
#include "mqtt/callback.h"
#include "mqtt/connect_options.h"
#include "mqtt/topic.h"

// порт подключения к mqtt
#define mqtt_port 1883
// Длинна имени топика обязательно 15 символов, для этого примера, иначе внести изменения в функцию callback()
#define mqtt_topic_p "/home/mqtt/param"
#define mqtt_topic_t "/home/mqtt/rtime"

class MQTTclass
{
public:
    MQTTclass();

    void clientfunc(Client& client);
};

#endif // MQTTCLASS_H
