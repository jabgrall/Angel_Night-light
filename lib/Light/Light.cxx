/**
 * \file
 * \brief Définition des fonctions de contr̂ole des PWM des leds.
 */

#include "Light.h"



/**
 * \brief Initialisation de l'objet.
 *
 * On doit renseigner les paramètres de configuration des timers, PWM et GPIO pour une led couleur uniauement.
 * Les paramètres sont a renseigner par le biais des structures dédiées et passées par pointeur.
 * La création des structures est à faire avant la création de l'objet Light afin d'effectuer le passage de pointeur.
 * Cependant, il est possible de renseigner les paramètres avant l'appel de la fonction #Light::begin.
 *
 * @param rouge
 * @param bleu
 * @param vert
 *
 * \warning La configuration des timers est fait dans l'ordre suivant : Rouge, vert, bleu. Dans le cas où on utilise
 * le même timer pour plusieures couleurs, c'est la configuration de la dernière couleur qui est utilisée.
 *
 */
Light::Light(pwmConfig *rouge, pwmConfig *bleu, pwmConfig *vert)
{
	led[2] = bleu;
	led[1] = vert;
	led[0] = rouge;
	isActivated = false;
}

/**
 * \brief Destructeur de l'objet
 */

Light::~Light(void)
{
}


/**
 * \brief Initialise l'objet
 *
 * \remark Veillez renseigner les structures de paramétrage de l'objet passés par pointeur en paramètre lors de la création de l'objet avant l'appel de cette fonction.
 *
 * \warning L'appel de cette fonction permet la mise en place de la configuration de l'objet, des GPIO et des timers. Les PWMs sont activées à la fin de l'activation de cette fonction.
 */

void Light::begin(void)
{
	if (!isActivated)
	{
		for(uint8_t i = 0; i < 3; i++)
		{
			if (led[i] != nullptr)
			{
				//Configuration des sorties
				if (led[i]->outSig != nullptr)
				{
					rcc_periph_clock_enable(led[i]->outSig->gpioRCC);

					if (led[i]->outSig->useAFIO)
					{
						rcc_periph_clock_enable(RCC_AFIO);
					}

					gpio_set_mode(led[i]->outSig->port, led[i]->outSig->mode, led[i]->outSig->altFct, led[i]->outSig->pin);
				}

				//Configuration des timers
				if (led[i]->timer != nullptr)
				{
					rcc_periph_clock_enable(led[i]->timer->timerRCC);
					timer_set_mode(led[i]->timer->timer, led[i]->timer->clkDiv, led[i]->timer->centAlMode, led[i]->timer->dir);
					timer_set_oc_mode(led[i]->timer->timer, led[i]->comp, led[i]->pwmType);
					timer_enable_oc_output(led[i]->timer->timer, led[i]->comp);
					if((led[i]->timer->timer == TIM1) or (led[i]->timer->timer == TIM8))
					{
						timer_enable_break_main_output(led[i]->timer->timer);
					}
					timer_set_prescaler(led[i]->timer->timer, led[i]->timer->presc);
					timer_set_oc_value(led[i]->timer->timer, led[i]->comp, initCol[i]);
					timer_set_period(led[i]->timer->timer, calibBase);
				}
			}
		}

		//Lancement des timers
		for (uint8_t i = 0; i < 3; i++)
		{
			timer_enable_counter(led[i]->timer->timer);
		}

		isActivated = true;
	}
}


/**
 * \brief Permet de mettre à jour la couleur de la led
 *
 * @param rouge
 * @param vert
 * @param bleu
 *
 * \remark La granularité de l'information de couleur à définir ici est dimensionné par #colStep.
 */

void Light::setColor(uint16_t rouge, uint16_t vert, uint16_t bleu)
{
	uint32_t calVal;
	if (!isActivated)
	{
		begin();
	}

	if(isActivated)
	{
		if (rouge < (uint16_t)(1 << colStep))
		{
			calVal = ((uint32_t)calibBase * rouge) >> colStep;
			timer_set_oc_value(led[0]->timer->timer, led[0]->comp, calVal);
		}

		if (vert < (uint16_t)(1 << colStep))
		{
			calVal = ((uint32_t)calibBase * vert) >> colStep;
			timer_set_oc_value(led[1]->timer->timer, led[1]->comp, calVal);
		}

		if (bleu < (uint16_t)(1 << colStep))
		{
			calVal = ((uint32_t)calibBase * bleu) >> colStep;
			timer_set_oc_value(led[2]->timer->timer, led[2]->comp, calVal);
		}
	}
}

void Light::setColorTwoAxes(uint16_t color, uint16_t brightness)
{
	uint16_t rouge = 0, vert = 0, bleu = 0;

	if (!isActivated)
	{
		begin();
	}

	if (isActivated)
	{
		//Mix 1 : Rouge stable, vert croissant, bleu nul
		if(color < (uint16_t)(1 * 0xFF))
		{
			rouge = 0xFF;
			vert = (color - 0x00);
			bleu = 0x00;
		}
		//Mix 2 : Rouge d�croissant, vert stable, bleu nul
		else if (color < (uint16_t)(2 * 0xFF))
		{
			rouge = 0x00FF - (color - (uint16_t)(1 * 0xFF));
			vert = 0xFF;
			bleu = 0x00;
		}
		//Mix 3 : Rouge nul, vert stable, bleu croissant
		else if (color < (uint16_t)(3 * 0xFF))
		{
			rouge = 0x00;
			vert = 0xFF;
			bleu = (color - (uint16_t)(2 * 0xFF));
		}
		//Mix 4 : Rouge nul, vert d�croissant, bleu stable
		else if (color < (uint16_t)(4 * 0xFF))
		{
			rouge = 0x00;
			vert = 0x00FF - (color - (uint16_t)(3 * 0xFF));
			bleu = 0xFF;
		}
		//Mix 5 : Rouge croissant, vert nul, bleu stable
		else if (color < (uint16_t)(5 * 0xFF))
		{
			rouge = (color - (uint16_t)(4 * 0xFF));
			vert = 0x00;
			bleu = 0xFF;
		}
		else if (color < (uint16_t)(6 * 0xFF))
		//Mix 6 : Rouge stable, vert nul, bleu d�croissant
		{
			rouge = 0xFF;
			vert = 0x00;
			bleu = 0x00FF - (color - (uint16_t)(5 * 0xFF));
		}
		else
		//Saturation
		{
			rouge = 0xFF;
			vert = 0x00;
			bleu = 0x01;
		}

		//Mise en place du niveau de blanc et de noir.
		if(brightness < 0xFF)
		{
			//Noir
			rouge = (rouge * brightness) / 0xFF;
			vert = (vert * brightness) / 0xFF;
			bleu = (bleu * brightness) / 0xFF;
		}
		else if (brightness <= (uint16_t)(2 * 0xFF))
		{
			//Blanc
			rouge = ((0xFF - rouge) * (brightness - 0xFF)) / 0xFF + rouge;
			vert = ((0xFF - vert) * (brightness - 0xFF)) / 0xFF + vert;
			bleu = ((0xFF - bleu) * (brightness - 0xFF)) / 0xFF + bleu;
		}
		else
		{
			rouge = 0xFF;
			vert = 0xFF;
			bleu = 0xFF;
		}

		setColor(rouge, vert, bleu);
	}
}


/**
 * \brief Allows to disable the leds. Useful in order to keep some battery when the led are not used.
 */

void Light::end(void)
{
	if (isActivated)
	{
		isActivated = false;

		//Arrêt des timers
		for (uint8_t i = 0; i < 3; i++)
		{
			timer_disable_counter(led[i]->timer->timer);
		}

		for(uint8_t i = 0; i < 3; i++)
		{
			if (led[i] != nullptr)
			{
				//Configuration des sorties à l'état haute impédance
				if (led[i]->outSig != nullptr)
				{
					gpio_set_mode(led[i]->outSig->port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, led[i]->outSig->pin);
				}
			}
		}
	}
}
