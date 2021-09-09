#include <string.h>
#include "modem.h"
#include "types.h"
#include "terminal.h"
#include "usart2.h"
#include "usart1.h"
#include "timer2.h"

static BOOL serverState=FALSE;
static BOOL wifiConnecting=FALSE;
static BOOL serverConnecting=FALSE;
BOOL getWifiConnecting(){
	return wifiConnecting;
}
void setWifiConnecting(BOOL b){
	wifiConnecting=b;
}

BOOL getServerConnecting(){
	return serverConnecting;
}

void setServerConnecting(BOOL b){
	serverConnecting=b;
}
BOOL getServerState(){
	return serverState;
}
void setServerState(BOOL b){
	serverState=b;
}


void MODEM_init(void){
	//#Client side
	//Dear modem, be in station mode
	USART1_print("AT+CWMODE=1\r\n");
	// wait a second until the previous command is executed
	delay(1);
	//set the modem to establish 1 TCP connections because its a client
	USART1_print("AT+CIPMUX=0\r\n");
	delay(1);

}

void delay(int seconds){
	int counter=0;
	while(1){
		if(TIMER2_expired())
			counter++;
		if(counter==seconds)
			return;
	}
}

void wifiConnect(char *ssid, char *password){
	// this will be the length of the command
	int commandLen=16+strlen(ssid)+strlen(password);
	// this string represents the command that connects the modem to preferred WiFi
	char built_command[commandLen];
	// building the command and adding /r/n at the end
	(void)strcpy(built_command, "AT+CWJAP=\"");
	strcat(built_command,ssid);
	strcat(built_command,"\",\"");
	strcat(built_command,password);
	strcat(built_command,"\"\r\n");
	USART2_print("\nEstablishing connection..\nEnjoy a cup of tea meanwhile =]\n\n");
	//Connect to WiFi
	USART1_print(built_command);
	setWifiConnecting(TRUE);
}

void connectToServer(char *IP){
	setServerConnecting(TRUE);
	// build connection command
	char command[strlen(IP)+25];
	(void)strcpy(command, "AT+CIPSTART=\"TCP\",\"");
	strcat(command,IP);
	(void)strcat(command, "\",80\r\n");
	//Connecting to server using TCP which is @port 80
	USART1_print(command);
}


