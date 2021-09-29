/**
 * \file sysTick.c
 * \brief Implémentation des fonctions permettant de cadencer le programme.
 */

#include <stdint.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>



//Prototypes
/**
 * Variable de sauvegarde des milli secondes écoulées.
 */
static volatile uint64_t _millis = 0;
//static volatile uint64_t _micros = 0;
//static volatile uint64_t _thouthandMicros = 0;

void systick_setup(void);

uint64_t millis(void);
//uint64_t micros(void);

void delay(uint64_t duration);
//void delayMicros(uint64_t duration);

//Implémentation des fonctions

/**
 * \brief Permet d'initialiser SysTick
 *
 * A appeler au démarrage du code. Permet d'activer SysTick sur une base de temps de 1ms.
 *
 */
void systick_setup(void) {
	// Set the systick clock source to our main clock
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	// Clear the Current Value Register so that we start at 0
	STK_CVR = 0;
	// In order to trigger an interrupt every microsecond, we can set the reload
	// value to be the speed of the processor / 1000 - 1
	systick_set_reload(rcc_ahb_frequency / 1000 - 1);
	// Enable interrupts from the system tick clock
	systick_interrupt_enable();
	// Enable the system tick counter
	systick_counter_enable();
}

/**
 * \brief Renvoi une valeur en milli seconde depuis le lancement du programme
 * @return Valeur retour. Est sujet à de l'overflow.
 *
 */
uint64_t millis(void) {
    return _millis;
}

///**
// * \brief Renvoi une valeur en micro seconde depuis le lancement du programme
// * @return Valeur retour. Est sujet à de l'overflow.
// *
// */
//uint64_t micros(void) {
//    return _micros;
//}


// This is our interrupt handler for the systick reload interrupt.
// The full list of interrupt services routines that can be implemented is
// listed in libopencm3/include/libopencm3/stm32/f0/nvic.h

/**
 * \brief Fonction incrémentant _millis et _micros
 *
 * Appelée par l'intéruption du système SysTick, elle permet l'incrémentation de _millis et de _micros
 */
void sys_tick_handler(void) {
    // Increment our monotonic clock
	//_micros++;
	//_thouthandMicros++;
	//if(_thouthandMicros >= 1000)
	//{
		_millis++;
	//	_thouthandMicros = 0;
	//}
}

// Delay a given number of milliseconds in a blocking manner
/**
 * \brief Stop l'exécution du programme pendant un laps de temps définit par duration.
 * @param duration (en milli seconde)
 */
void delay(uint64_t duration) {
    const uint64_t until = millis() + duration;
    while (millis() < until);
}

//// Delay a given number of microseconds in a blocking manner
///**
// * \brief Stop l'exécution du programme pendant un laps de temps définit par duration.
// * @param duration (en micro seconde)
// */
//void delayMicros(uint64_t duration) {
//    const uint64_t until = micros() + duration;
//    while (micros() < until);
//}

