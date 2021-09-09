#ifndef MODEM_H_
#define MODEM_H_



/******************************************************************************
Includes
******************************************************************************/
#include "types.h"


/******************************************************************************
modemInit
Description: This function is called to initialize the modem and set it as a client.
******************************************************************************/
void MODEM_init();


/******************************************************************************
delay
Description:
	A function that enters a loop until the parameter passed to it(seconds)
	Passes, the function uses TMR2 which counts to 1 second so it waits int seconds
	Number of times until the TMR2 raise a flag. its main purpose is to delay
	The commands passed to USART1 to make sure that they took their time to be
	Executed
******************************************************************************/
void delay(int seconds);

/******************************************************************************
wifiConnect
Description:
	This function builds the command that connects the modem to wifi with the ssid
	And password it gets upon triggering
******************************************************************************/
void wifiConnect(char *ssid,char *password);

/******************************************************************************
getServerState
Description: A getter for serverState Variable
******************************************************************************/
BOOL getServerState();

/******************************************************************************
setServerState
	Description: A setter for serverState Variable
******************************************************************************/
void setServerState(BOOL b);

/******************************************************************************
getWifiConnecting
Description: A getter for wifiConnecting Variable
******************************************************************************/
BOOL getWifiConnecting();

/******************************************************************************
setWifiConnecting
Description: A setter for wifiConnecting Variable
******************************************************************************/
void setWifiConnecting(BOOL b);

/******************************************************************************
connectToServer
Description:
	When triggered this function builds and sends to modem the command to connect to the
	Server which its IP recieves as a variable called IP
******************************************************************************/
void connectToServer(char *IP);
// setters and getters
BOOL getServerConnecting();
void setServerConnecting(BOOL b);

#endif /* MODEM_H_ */
