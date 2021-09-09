#include "watchdog.h"
#include "stm32f303xe.h"

void WATCHDOG_init(){
	// Start/Enable the WatchDog
	IWDG->KR=0x0000CCCC;
	// enable access to modify the IWDG_PR, IWDG_RLR registers (Reference manual p.760)
	IWDG->KR=0x00005555;
	// prescaler
	IWDG->PR=7;
	IWDG->RLR=1000;
	// Wait for the registers to be updated
	while(IWDG->SR);
	// Refresh the counter
	WATCHDOG_pet();

}

void WATCHDOG_pet(){
	// Refresh the counter
	IWDG->KR=0x0000AAAA;
}
