#ifndef WATCHDOG_H_
#define WATCHDOG_H_


/******************************************************************************
WATCHDOG_init
Description:
	initialize independent WatchDog
	Steps to initialize it accord to Reference Manual P.759:
	1. Enable the IWDG by writing 0x0000CCCC in the IWDG_KR register.
	2. Enable register access by writing 0x0000 5555 in the IWDG_KR register.
	3. Write the IWDG prescaler by programming IWDG_PR from 0 to 7.
	4. Write the reload register (IWDG_RLR).
	5. Wait for the registers to be updated (IWDG_SR = 0x00000000).
	6. Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000AAAA).
******************************************************************************/
void WATCHDOG_init();

/******************************************************************************
WATCHDOG_pet
Description: pet WatchDog (refresh the counter)
******************************************************************************/
void WATCHDOG_pet();


#endif /* WATCHDOG_H_ */
