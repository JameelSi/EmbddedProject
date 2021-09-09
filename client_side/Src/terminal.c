#include <string.h>
#include "terminal.h"
#include "usart2.h"
#include "usart1.h"
#include "timer2.h"
#include "types.h"
#include "modem.h"
static char A_Command_Buffer[TERMINAL_SIZE_OF_COMMAND_BUFFER];
static BOOL waitForSSID=FALSE;
static char ssid[128];
static BOOL waitForPassword=FALSE;
static char password[128];
static BOOL waitForIP=FALSE;
static char IP[128];

void setWaitForIP(BOOL b){
	waitForIP=b;
}

void TERMINAL_handleCommand(void){
    USART2_getCommand(A_Command_Buffer);
    // Special command to connect to modem
     if((strcmp(A_Command_Buffer, "WIFICONNECT") == 0) &&!waitForPassword &&!waitForSSID&&!waitForIP){
    	 // we're expecting wifi SSID now
    	waitForSSID=TRUE;
    	USART2_print("Please enter your WiFi SSID\n");
    }
    else if(waitForSSID){
    	(void)strcpy(ssid, A_Command_Buffer);
    	USART2_print("Please enter your Password\n");
    	// we're expecting wifi password now
    	waitForSSID=FALSE;
    	waitForPassword=TRUE;
    }
    else if(waitForPassword){
    	(void)strcpy(password, A_Command_Buffer);
    	waitForPassword=FALSE;
    	// we have wifi details now, let's connect to it
    	wifiConnect(ssid, password);
    }
    else if(waitForIP){
    	(void)strcpy(IP, A_Command_Buffer);
    	waitForIP=FALSE;
    	// should've got the ssid and password, initilaize the modem
    	connectToServer(IP);
    }
     // Special command to connect to server
    else if((strcmp(A_Command_Buffer, "SVRCONNECT") == 0)){
    	 // we're expecting IP now
    	waitForIP=TRUE;
    	USART2_print("Please enter the server IP\n");
    }
     // check if WatchDog is working correctly
    else if(strcmp(A_Command_Buffer,"WATCHDOG_IGNORE")==0){
    	USART2_print("WatchDog will reset the program in almost 9 seconds\n");
    	while(1);
    }
    //Send command to modem
    else{
    	    strcat(A_Command_Buffer,"\r\n");
    	    USART1_print(A_Command_Buffer);
    }
}
