#include <string.h>
#include "terminal.h"
#include "usart2.h"
#include "usart1.h"
#include "types.h"
#include "modem.h"
#include "led.h"
#include "button.h"
static char A_Rx_Buffer[TERMINAL_SIZE_OF_COMMAND_BUFFER];

void USART1TERMINAL_handleCommand(){
		// get the command
		USART1_getCommand(A_Rx_Buffer);
		if(strstr(A_Rx_Buffer, "CHANGE_LED") != NULL) {
				LED_change_state();
		}
		// wait a second ! connection failed :/
		else if( getWifiConnecting() && strstr(A_Rx_Buffer, "FAIL") != NULL){
			USART2_print("\nConnection failed please make sure you entered the WiFi SSID or password\n"
					"correctly and use WIFICONNECT command again to connect\n\n");
			setWifiConnecting(FALSE);
		}
		// client has disconnected :/
		else if(strstr(A_Rx_Buffer, "0,CLOSED") != NULL){
			setClientState(FALSE);
			USART2_print("Client has disconnected\n");
		}
		// Yuppers ! client is here !
		else if(strstr(A_Rx_Buffer, "0,CONNECT") != NULL){
			USART2_print("Client has connected\n");
			setClientState(TRUE);
		}
		// connected to wifi
		else if(getWifiConnecting() && strstr(A_Rx_Buffer, "OK") != NULL){
			setWifiConnecting(FALSE);
			setServer();
		}
		// no special commands we were waiting for has been inserted. well, send the command as is to usart2
		else
			USART2_print(A_Rx_Buffer);

}
