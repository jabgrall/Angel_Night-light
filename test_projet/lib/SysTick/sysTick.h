/**
 * \file sysTick.h
 *
 *  \brief Mise en place de fonctions basics permettant de cadencer le programme principal.
 *
 */

#ifndef LIB_SYSTICK_SYSTICK_H_
#define LIB_SYSTICK_SYSTICK_H_

extern "C" {
	uint64_t millis(void);
	uint64_t micros(void);
	void systick_setup(void);
	void delay(uint64_t duration);
	void delayMicros(uint64_t duration);
}


#endif /* LIB_SYSTICK_SYSTICK_H_ */
