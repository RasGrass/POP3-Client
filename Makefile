CC:=g++
CCQ=tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
CFLAGS=`pkg-config --cflags dbus-1`
SRCS:=main.cpp DbusNotifier.cpp
OBJS:=$(subst .cpp,.o, $(SRCS))
LDLIBS=-Llib -lCppUnitd -lCppUnitd -lPocoFoundation -lPocoFoundationd -lPocoJSON -lPocoJSONd -lPocoNet -lPocoNetd -lPocoUtil -lPocoUtild -lPocoXML -lPocoXMLd `pkg-config --libs dbus-1`

pop3_client: $(OBJS)
	@$(CC) $(CFLAGS) -o pop3_client $(OBJS) $(LDLIBS) 
	@echo "Wiadomość z pliku binarnego" >> pop3_client

pop3_client_q: $(OBJS)
	CC=tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
	@$(CC) $(CFLAGS) -o pop3_client $(OBJS) $(LDLIBS) 
	@echo "Wiadomość z pliku binarnego" >> pop3_client

%.o: %.cpp
	@$(CC) $(CFLAGS)-c -g -Iinclude $<

.PHONY:clean

clean:
	rm -f pop3_client $(OBJS)
