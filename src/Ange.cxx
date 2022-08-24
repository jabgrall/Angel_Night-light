/**
 * \file 
 * \brief Fichier main du programme.
 */


#include "Light.h"
#include "sysTick.h"
#include "adxl345.h"

Light::gpioConfig outRouge, outBleu, outVert;
Light::timerConfig timerOne;
Light::pwmConfig pwmRouge, pwmBleu, pwmVert;
Light ledCmd(&pwmRouge, &pwmBleu, &pwmVert);
Adxl345 axcel;

void demoColor(void);
void demoColor2(bool resetMinuterie = false);
void interaction(void);



/**
 * \mainpage
 *
 * \brief Programme principal de gestion de l'ange.
 *
 * @return
 *
 * Le code permet de lancer trois activité selon les besoins :
 * \li Demo de variation des couleurs.
 * \li Choix d'une couleur par intéraction avec l'ange. Cette couleur servira de base pour la troisième activité.
 * \li Enclenchement d'une couleur pulsante activée par une variation du niveau sonore.
 *
 * \todo Mettre en place les interruptions de l'accéléromètre : single tap, double tap. => construction du menu
 * \todo mettre en place l'activité 2 : intéraction
 * \todo Mettre en place l'activité 3 : suivit du son
 * \todo Optimisation énergétique du système.
 * \todo Utilisation du free fall ? Montrer son mécontentement lorsqu'il tombe.
 *
 * Pour plus de détails pour les différents modules, regarder les fichiers suivants :
 * \li \ref Light.h
 * \li \ref sysTick.h
 * \li \ref Ange.cxx
 *
 *
 * Voici un diagramme permettant de représenter le principe des menus mis en place :
 *
\startuml {Etats.svg}
	state "Démo" as demo {

	state "Affiche bleu" as bleu
	bleu : Pour indiquer
	bleu : le mode en cours

	state "Mode démo" as Demo
	Demo : Fait varier la couleur
	Demo : automatiquement

	[*] --> bleu
	bleu --> Demo : 2 secondes
	}

	state "Intéraction" as inter {

	state "Affiche rouge" as rouge
	rouge : Pour indiquer
	rouge : le mode en cours

	state "Mémoire" as mem
	mem : Affiche la couleur
	mem : mémorisée.

	state "Choix de la couleur" as choix
	choix : Faire tourner l'ange
	choix : affiche une couleur en particulier
	choix : Suivant l'axe de rotation, on
	choix : agis soit sur X, soit sur Y
	choix : soit sur Z.

	[*] --> rouge
	rouge --> mem : 2 secondes
	mem --> choix : single tap
	choix --> mem : single tap

	}

	state "Sonore" as micro {
	state "Affiche vert" as vert
	vert : Pour indiquer
	vert : le mode en cours

	state "Pulsation" as pulse
	pulse : Fait pulser la couleur
	pulse : mémorisée.

	state "Éteinte" as off
	off : N'affiche plus aucune
	off : lumière.

	[*] --> vert
	vert --> pulse : 2 secondes
	pulse --> off : aucun son
	off -> pulse : présence de son
	}

	demo --> inter : double tap
	inter -> micro : double tap
	micro --> demo : double tap
\enduml
 *
 */

int main(void)
{

	//Initialise l'horloge système
	rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

	//Configuration du module de contrôle des leds.

	//GPIO Rouge
	outRouge.gpioRCC = RCC_GPIOA;
	outRouge.port = GPIOA;
	outRouge.pin = GPIO8;
	outRouge.mode = GPIO_MODE_OUTPUT_10_MHZ;
	outRouge.useAFIO = true;

	//GPIO Bleu
	outBleu.gpioRCC = RCC_GPIOA;
	outBleu.port = GPIOA;
	outBleu.pin = GPIO10;
	outBleu.mode = GPIO_MODE_OUTPUT_10_MHZ;
	outBleu.useAFIO = true;

	//GPIO Vert
	outVert.gpioRCC = RCC_GPIOA;
	outVert.port = GPIOA;
	outVert.pin = GPIO9;
	outVert.mode = GPIO_MODE_OUTPUT_10_MHZ;
	outVert.useAFIO = true;

	//Configuration du timer
	timerOne.timerRCC = RCC_TIM1;
	timerOne.timer = TIM1;
	timerOne.presc = 3;

	//Configuration de la PWM Rouge
	pwmRouge.outSig = &outRouge;
	pwmRouge.timer = &timerOne;
	pwmRouge.comp = TIM_OC1;
	pwmRouge.pwmType = TIM_OCM_PWM2;
	pwmRouge.calib = 800;

	//Configuration de la PWM Bleu
	pwmBleu.outSig = &outBleu;
	pwmBleu.timer = &timerOne;
	pwmBleu.comp = TIM_OC3;
	pwmBleu.pwmType = TIM_OCM_PWM2;
	pwmBleu.calib = 700;

	//Configuration de la PWM Bleu
	pwmVert.outSig = &outVert;
	pwmVert.timer = &timerOne;
	pwmVert.comp = TIM_OC2;
	pwmVert.pwmType = TIM_OCM_PWM2;
	pwmVert.calib = 600;

	//Initialise SysTick
	systick_setup();

	ledCmd.begin();

	//Adxl345: typical startup time 1.4ms
	delay(20);
	axcel.begin();

	uint8_t menu = 0;
	bool changeMenu = false;

	while(true)
	{
		if(axcel.isDoubleTap())
		{
			menu++;
			changeMenu = true;
		}
		if(menu == 0)
		{
			if(changeMenu)
			{
				ledCmd.setColor(0x00, 0x00, 0xFF);
				delay(2000);
				changeMenu=false;
				demoColor2(true);
			}
			else
				demoColor2();
		}
		else if (menu == 1)
		{
			if (changeMenu)
			{
				ledCmd.setColor(0xFF, 0x00, 0x00);
				delay(2000);
				changeMenu = false;
			}
		}
		else
			menu = 0;
	}

    return 0;
}


/**
 * \brief Code de démo de couleur
 *
 * Cette fonction permet de faire varier la couleur avec un rouge prédominant. Elle tient compte de la gestion temporelle et peut être appelée autant de fois que nécéssaire.
 * Base de temps minmale : 3ms.
 */

void demoColor(void)
{

	static uint8_t incRouge = 0xBF, incVert = 0x5F, incBleu = 0x5F;
	static bool upRouge = true, upVert = true, upBleu = false, updateColor = true;
	static uint64_t delayRouge = millis(), delayVert = millis(), delayBleu = millis();

	if (updateColor)
	{
		ledCmd.setColor(incRouge, incVert, incBleu);
		updateColor = false;


	}

	//Change color
	if ((millis() - delayRouge) > 3)
	{
		if (upRouge)
		{
			incRouge++;
			if (incRouge == 0xFF)
				upRouge = !upRouge;
		}
		else
		{
			incRouge--;
			if (incRouge == 0xBF)
				upRouge = !upRouge;
		}
		delayRouge = millis();
		updateColor = true;
	}

	if ((millis() - delayVert) > 7)
	{
		if (upVert)
		{
			incVert++;
			if (incVert == 0x7F)
				upVert = !upVert;
		}
		else
		{
			incVert--;
			if (incVert == 0x00)
				upVert = !upVert;
		}
		delayVert = millis();
		updateColor = true;
	}

	if ((millis() - delayBleu) > 5)
	{
		if (upBleu)
		{
			incBleu++;
			if (incBleu == 0x7F)
				upBleu = !upBleu;
		}
		else
		{
			incBleu--;
			if (incBleu == 0x00)
				upBleu = !upBleu;
		}
		delayBleu = millis();
		updateColor = true;
	}

	delay(50);
}


/**
 * \brief Code de démo de couleur version 2
 *
 * Cette fonction permet de faire varier la couleur sur l'ensemble du spectre. Elle fait également varier l'intensité lumineuse avec une légère pulsation : donne l'impression d'une respiration régulière.
 * Elle tient compte de la gestion temporelle et peut être appelée autant de fois que nécéssaire.
 *
 * \remark Les constantes définies dans la fonction permettent de configurer les niveaux d'intensitées lumineuses ainsi que les bases de temps.
 *
 * \warning La mise à 0 de l'intensité lumineuse est frappante et peut réveiller l'enfant.
 */

void demoColor2(bool resetMinuterie)
{
	const uint16_t brightHigh = 0x3F, brightLow = 0x10, inTime = 1700 / (brightHigh - brightLow), outTime = 4000 / (brightHigh - brightLow);
	static uint16_t incColor = 0x00, incBright = brightHigh, time = outTime;
	static bool upBright = false, updateColor = true, minuterieOK = true;
	static uint64_t delayColor = millis(), delayBright = millis(), minuterie = millis(), measAxcel = millis();

	if(resetMinuterie)
	{
		minuterie = millis();
		updateColor = true;
		minuterieOK = true;
	}

	if (updateColor)
	{
		if (((millis() - minuterie) < (uint64_t)(30 * 60 * 1000)))
		{
			if (minuterieOK)
			{
				ledCmd.setColorTwoAxes(incColor, incBright);
				updateColor = false;
			}
		}
		else
		{
			ledCmd.setColor(0x00, 0x00, 0x00);
			updateColor = false;
			minuterieOK = false;
			ledCmd.end();
		}

	}

	//Change color
	if ((millis() - delayColor) > 40)
	{
		incColor++;
		if (incColor >= (uint16_t)(6 *0xFF))
			incColor = 0x00;

		delayColor = millis();
		updateColor = true;
	}

	if ((millis() - delayBright) > time)
	{
		if (upBright)
		{
			incBright++;
			if (incBright == brightHigh)
			{
				upBright = !upBright;
				time = outTime;
			}
		}
		else
		{
			incBright--;
			if (incBright == brightLow)
			{
				upBright = !upBright;
				time = inTime;
			}
		}
		delayBright = millis();
		updateColor = true;
	}
}

/**
 * \brief Display color according to position of the accelerometer.
 */

void interaction(bool firstCall)
{
	const uint64_t waitTime = 10;
	static uint16_t savedColor = 0x00, savedBright = 0x00;
	static uint64_t delayMeasure = millis(), delay;
	Adxl345::data axcelData;
	static bool isDisplay = true;

	if (firstCall)
	{
		ledCmd.setColorTwoAxes(savedColor, savedBright);
		isDisplay = true;
	}

	if ((millis() > delay + waitTime) && !isDisplay)
	{
		//Measure Acceleration
		axcelData = axcel.getData();
		//calc
	}
}
