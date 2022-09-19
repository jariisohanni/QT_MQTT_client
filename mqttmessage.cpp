#include "mqttmessage.h"

MqttMessage::MqttMessage()
{
    message = "";
    sender = "";
}

string MqttMessage::print()
{
    return ("From" + sender + " - " + message);
}

const string &MqttMessage::getMessage() const
{
    return message;
}

void MqttMessage::setMessage(const string &newMessage)
{
    message = newMessage;
}

const string &MqttMessage::getSender() const
{
    return sender;
}

void MqttMessage::setSender(const string &newSender)
{
    sender = newSender;
}
