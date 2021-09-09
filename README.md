# EmbddedProject

#### About the program

This program is meant to implement the communication between two separate STM32cards one acts as
a server another as a client. after they are connected when either side blue button is pushed the other
STM32card led will switch its state by this order (ON->BLINKING->OFF).
#### How to run the program

Connect your STM32 cards to the PC, download on one of them the server_side program and client_side
on another, connect them to individual Tera Terms, on both cards write WIFICONNECT command which
will ask you then for you SSID and password ( client side will ask for IP server in addition)
If succeeded, a message will be printed implying that on Tera Term, then push the blue button on either
of the cards and watch the other’s led change. If client failed to connect due to typo/wrong IP address
you can use SVRCONNECT on client side to try connecting again.

#### Available commands

| CLIENT SIDE   | SERVER SIDE   | Details |
| ------------- |:-------------:| :-----|
| WIFICONNECT   | WIFICONNECT   | Connects the modem to Wi-Fi, when entered the programwill ask for SSID, password for the desired Wi-Fi |
| WATCHDOG_IGNORE | WATCHDOG_IGNORE |   Enters infinite loop (for testing if the WatchDog is doing its job). |
| SVRCONNECT |  /  |    Asks for the server IP address you want to connect to,when inserted it connects to it.  |
| Modem commands: AT+”Command”   | Modem commands: AT+”Command” | (Where “Command” is your desired command) *without quotes Will send your command directly to the modem.|

#### Changing the led on the other side process
When button pressed on either card, using USART1 it sends the special command that we defined
“CHANGE_LED” to the other side. USART1 on the other side receives the command, distinguishes the
command, and sends the command the led to go to the next state where we defined an enum which
tells us the current state, and what state to go to next. 
