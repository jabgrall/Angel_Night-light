/**
 * \file
 * \brief Bibliothèque qui permet de contr̂oler les PWM pour afficher une couleur sur une led RGB.
 * 
 * Elle permet d'envoyer un code type couleur pour effectuer l'éclairage de la ledRGB.
 */


#ifndef LIGHT_H
#define LIGHT_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

class Light
{
public:
	/**
	 * \brief Configuration des sorties qui seront assoiciées au timer pour gérer une PWM.
	 */
	struct gpioConfig
	{
		enum rcc_periph_clken gpioRCC; ///< Horloge RCC du GPIO à initialiser.
		uint32_t port; ///< Port du GPIO. Cf. \ref gpio_port_id
		uint8_t mode; ///< Comportement du GPIO : Input, output avec différentes fréquences. Cf. \ref gpio_mode
		uint8_t altFct = GPIO_CNF_OUTPUT_ALTFN_PUSHPULL; ///< Configuration de la pin. Cf. \ref gpio_cnf
		uint16_t pin; ///< Définition de la pin. Cf. \ref gpio_pin_id
		bool useAFIO; ///< Permet d'utiliser le périphérique des fonctions alternrougeatives. Si activé, lance l'horloge dédiée.
	};

	/**
	 * \brief Configuration spécifique d'une timer pour générer les PWMs des leds de couleurs.
	 */
	struct timerConfig
	{
		rcc_periph_clken timerRCC; ///< Horloge RCC du timer à initialiser.
		uint32_t timer; ///< Nom du timer à initialiser. Cf. \ref tim_reg_base
		/**
		 * Permet d'indiquer le type de division d'horloge pour le timer. Cf. \ref tim_x_cr1_cdr
		 *
		 * Bits 9:8 CKD: Clock division
		 *
		 * This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and sampling clock used by the digital filters (ETR, TIx),
		 * \li 00: t DTS = t CK_INT
		 * \li 01: t DTS = 2 × t CK_INT
		 * \li 10: t DTS = 4 × t CK_INT
		 * \li 11: Reserved
		 */
		uint32_t clkDiv = TIM_CR1_CKD_CK_INT;

		/**
		 * Indique le mode de fonctionnement du timer : sur front ou centré. Cf. \ref tim_x_cr1_cms
		 *
		 * Bits 6:5 CMS: Center-aligned mode selection
		 *
		 * \li 00: Edge-aligned mode. The counter counts up or down depending on the direction bit
		 * (DIR).
		 *
		 * \li 01: Center-aligned mode 1. The counter counts up and down alternatively. Output compare
		 * interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
		 * only when the counter is counting down.
		 *
		 * \li 10: Center-aligned mode 2. The counter counts up and down alternatively. Output compare
		 * interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
		 * only when the counter is counting up.
		 *
		 * \li 11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare
		 * interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
		 * both when the counter is counting up or down.
		 *
		 * Note: It is not allowed to switch from edge-aligned mode to center-aligned mode as long as
		 * the counter is enabled (CEN=1)
		 */
		uint32_t centAlMode = TIM_CR1_CMS_EDGE;

		/**
		 * Indique la direction de comptage. Cf. \ref tim_x_cr1_dir
		 *
		 * Bit 4 DIR: Direction
		 * 0: Counter used as upcounter
		 * 1: Counter used as downcounter
		 */
		uint32_t dir = TIM_CR1_DIR_UP;
		uint32_t presc; ///< Permet d'ajuster le prescaler du timer. \warning Il est nécéssaire de prévoir une fréquence d'horloge #colStep fois supérieure à la fréquence attendue. Ceci afin de donner une granularité de 256 pas à la couleur.
	};

	/**
	 * \brief Élément structurel qui permet d'associer un timer à un GPIO. Un élément permet de définir la sortie pour une des couleurs de la led.
	 */
	struct pwmConfig
	{
		gpioConfig *outSig; ///< Définie le périphérique du signal de sortie.
		timerConfig *timer; ///< Indique les paramètres du timer utilisé. Paramètres globaux aux PWMs de ce timer matériel.
		enum tim_oc_id comp; ///< Indique le comparateur utilisé pour la PWM. Cf. #tim_oc_id
		enum tim_oc_mode pwmType = TIM_OCM_PWM1; ///< Permet de renseigner le type de comportement de la PWM. Cf. #tim_oc_mode
		uint16_t calib = calibBase; ///< Permet de définir un paramètre de calibration de l'intensité de la couleur. Doit être inférieur ou égal à : #Light::calibBase
	};

	Light(pwmConfig *rouge, pwmConfig *bleu, pwmConfig *vert);
	virtual ~Light(void);

	void begin(void);
	void end(void);
	void setColor(uint16_t rouge, uint16_t vert, uint16_t bleu);
	void setColorTwoAxes(uint16_t color, uint16_t brightness);

private:
	pwmConfig *led[3]; ///< Paramétrage des PWM pour la couleur rouge, verte, bleue de la led couleur.
	const uint8_t colStep = 8; ///< Nombre de bits des informations de couleurs à fournir par l'utilisateur. Basée sur la définition "HTML" de la couleur (codée sur 8 bits).
	const uint32_t initCol[3] = {0, 0, 0}; ///< Niveau de couleur définie à l'initialisation de l'objet.
	static const uint16_t calibBase = 1024; ///< Définit la base du compteur du timer. Utilisé pour éffectuer la calibration des couleurs.
	bool isActivated; ///< Permet d'indiquer si les leds ont ́eté initialisées ou pas.
};

#endif
