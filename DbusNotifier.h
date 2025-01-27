#ifndef DBUS_NOTIFER_H
#define DBUS_NOTIFER_H

#include <dbus/dbus.h>
#include <string>

class DbusNotifier {

public:
    static void notify(const std::string &summary, const std::string &body);

private:
    static int buildMessage(DBusMessage *notifyMsg, const std::string &summary, const std::string &body);
};

#endif
