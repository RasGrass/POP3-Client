#include <iostream>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/POP3ClientSession.h>
#include "DbusNotifier.h"
#include <unistd.h>

using namespace std;
using namespace Poco::Net;

int main(int argc, char *argv[]) {
	string host = "pop1.mail.com";
	int port = 110;
	string user = "mikolaj.manski@mail.com";
	string pass = "test1234";
	cout << " Im here3";
	int pobierz = getopt(argc, argv, "u:p:");

	switch (pobierz) {
		case 'u':
			user = optarg;
			break;
		case 'p':
			pass = optarg;
			break;
		default:
			abort();
	}

			try {
				POP3ClientSession session(host);
				session.login(user, pass);
				POP3ClientSession::MessageInfoVec messages;
				session.listMessages(messages);
				//int latestEmail = session.messageCount();
				int latestEmail = 2;
				MailMessage message;
				
					session.listMessages(messages);
					int temp = messages.size();
					cout << temp << endl;
					if (latestEmail <= temp) {
						//	cout << " Im here ";
						latestEmail = temp;
						session.retrieveMessage(latestEmail, message);
						cout << "From: " << message.getSender() << endl;
						cout << "Subject: " << message.getSubject() << endl;
						DbusNotifier::notify(message.getSender(), message.getSubject());
					}
					


				
				session.close();
			} catch (POP3Exception &e) {
				cerr << e.displayText() << endl;
			} catch (NetException &e) {
				cerr << e.displayText() << endl;
			}
			return 0;
	}
