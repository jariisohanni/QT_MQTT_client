#ifndef MQTTMESSAGE_H
#define MQTTMESSAGE_H

#include <string>

using namespace std;

class MqttMessage
{
public:
    MqttMessage();

    const string &getMessage() const;
    void setMessage(const string &newMessage);

    const string &getSender() const;
    void setSender(const string &newSender);

    string print();
private:
    string message;
    string sender;
};

#endif // MQTTMESSAGE_H
