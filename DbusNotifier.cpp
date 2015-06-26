#include <iostream>
#include "DbusNotifier.h"
#include <cstdio>

void DbusNotifier::notify(const std::string &tytul, const std::string &tresc) {
	DBusMessage* wiadomosc;
	DBusConnection* polaczenie;
	DBusError error;

	dbus_error_init(&error);
	polaczenie = dbus_bus_get(DBUS_BUS_SESSION, &error);

	wiadomosc = dbus_message_new_method_call("org.freedesktop.Notifications",
			"/org/freedesktop/Notifications",
			"org.freedesktop.Notifications",
			"Notify");
	buildMessage(wiadomosc, tytul, tresc);

	dbus_connection_send(polaczenie, wiadomosc, NULL);
	dbus_connection_flush(polaczenie);

	dbus_message_unref(wiadomosc);
}

int DbusNotifier::buildMessage(DBusMessage *notifyMsg, const std::string &tytul, const std::string &tresc) {
	DBusMessageIter args, actions, hints;
	const char *appName = "POP3-client";
	int replacesId = -1;
	const char *appIcon = "dialog-information";
	int timeout = 0;

	dbus_message_iter_init_append(notifyMsg, &args);
	int returnCode = dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &appName);
	returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &replacesId);
	returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &appIcon);
	returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &tytul);
	returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &tresc);

	returnCode |= dbus_message_iter_open_container(&args, DBUS_TYPE_ARRAY, DBUS_TYPE_STRING_AS_STRING, &actions);
	returnCode |= dbus_message_iter_close_container(&args, &actions);

	returnCode |= dbus_message_iter_open_container(&args,
			DBUS_TYPE_ARRAY,
			DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
			DBUS_TYPE_STRING_AS_STRING
			DBUS_TYPE_VARIANT_AS_STRING
			DBUS_DICT_ENTRY_END_CHAR_AS_STRING,
			&hints);
	returnCode |= dbus_message_iter_close_container(&args, &hints);

	returnCode |= dbus_message_iter_append_basic(&args, DBUS_TYPE_INT32, &timeout);

	return returnCode;
}
