#include <string.h>
#include "terminal.h"
#include "usart2.h"
#include "usart1.h"
#include "types.h"
#include "modem.h"

static char A_Command_Buffer[TERMINAL_SIZE_OF_COMMAND_BUFFER];
static BOOL waitForSSID=FALSE;
static char ssid[TERMINAL_SIZE_OF_COMMAND_BUFFER];
static BOOL waitForPassword=FALSE;
static char password[TERMINAL_SIZE_OF_COMMAND_BUFFER];


void TERMINAL_handleCommand(void){
    USART2_getCommand(A_Command_Buffer);
    // user is trying to connect to wifi
     if((strcmp(A_Command_Buffer, "WIFICONNECT") == 0) &&!waitForPassword &&!waitForSSID){
    	 //should be expecting SSID from the user now
    	waitForSSID=TRUE;
    	USART2_print("Please enter your WiFi SSID\n");
    }
    else if(waitForSSID){
    	(void)strcpy(ssid, A_Command_Buffer);
    	//should be expecting password from the user now
    	USART2_print("Please enter your Password\n");
    	waitForSSID=FALSE;
    	waitForPassword=TRUE;
    }
    else if(waitForPassword){
    	(void)strcpy(password, A_Command_Buffer);
    	waitForPassword=FALSE;
    	// we have ssid and password, we can connect now
    	wifiConnect(ssid,password);
    }
     // special command to get server IP
    else if(strcmp(A_Command_Buffer,"IP")==0){
    	USART2_print("Server IP is in the first line:\n");
    	USART1_print("AT+CIFSR\r\n");
    }
     // check if WatchDog is working correctly
    else if(strcmp(A_Command_Buffer,"WATCHDOG_IGNORE")==0){
        USART2_print("WatchDog will reset the program in almost 9 seconds\n");
    	while(1);
    }
    // no special commands we've been waiting for. send the command to uart1 as is but don't forget to add /r/n
    else{
    	    strcat(A_Command_Buffer,"\r\n");
    	    USART1_print(A_Command_Buffer);
    }
}
