/**
 * \file 
 * \brief Fichier main du programme.
 */


#include "Light.h"
#include "adxl345.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

Light::gpioConfig outRouge, outBleu, outVert;
Light::timerConfig timerOne;
Light::pwmConfig pwmRouge, pwmBleu, pwmVert;
Light ledCmd(&pwmRouge, &pwmBleu, &pwmVert);
Adxl345 axcel;
TaskHandle_t demoTask = NULL, colorChTask = NULL, minuterieTask = NULL;
EventGroupHandle_t demoTaskSpd = NULL, colorChTaskSpd = NULL, minuterieTaskSpd = NULL;

void demoColor(void);
void demoColor2(void* param);
void interaction(void* param);
void minuterie(void* param);
void menuTask(void* param);


uint16_t lastColorSaved=0, lastBrightSaved=0;


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

	xTaskCreate(menuTask, "Menu", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	vTaskStartScheduler();

	while(true)
	{

	}

	return 0;
}


/**
 * \brief Task du menu
 */

void menuTask(void* param)
{
	uint8_t menu = 0;
	EventGroupHandle_t accelEvH;
	EventBits_t accelEvB;
	const TickType_t delay2000ms = pdMS_TO_TICKS(2000UL), delay20ms = pdMS_TO_TICKS(20UL);

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
	//systick_setup();

	ledCmd.begin();

	//Adxl345: typical startup time 1.4ms
	vTaskDelay(delay20ms);
	axcel.begin();

	accelEvH = axcel.getAccelEventGp();

	//Create task for each menu element
	configASSERT(xTaskCreate(demoColor2,"Change color", configMINIMAL_STACK_SIZE, NULL, 1, &demoTask));
	configASSERT(xTaskCreate(interaction,"Choose color", configMINIMAL_STACK_SIZE, NULL, 1, &colorChTask));
	configASSERT(xTaskCreate(minuterie,"Start Minuterie", configMINIMAL_STACK_SIZE, demoTask, 1, &minuterieTask));

	//Create Suspension semaphores
	demoTaskSpd = xEventGroupCreate();
	colorChTaskSpd = xEventGroupCreate();
	minuterieTaskSpd = xEventGroupCreate();


	//Select initial Task
	while(true)
	{
		if(menu == 0)
		{
			xEventGroupClearBits(colorChTaskSpd, 0x01);
			ledCmd.setColor(0x00, 0x00, 0xFF);
			vTaskDelay(delay2000ms);
			xEventGroupSetBits(demoTaskSpd, 0x01);
			xEventGroupSetBits(minuterieTaskSpd, 0x01);
		}
		else if (menu == 1)
		{
			xEventGroupClearBits(demoTaskSpd, 0x01);
			xEventGroupClearBits(minuterieTaskSpd, 0x01);
			ledCmd.setColor(0xFF, 0x00, 0x00);
			vTaskDelay(delay2000ms);
			xEventGroupSetBits(colorChTaskSpd, 0x01);
		}

		accelEvB = xEventGroupWaitBits(accelEvH, 0x01, pdTRUE, pdFALSE, portMAX_DELAY);
		if(accelEvB & 0x01)
		{
			menu++;
			if(menu > 1)
				menu = 0;
		}
	}
}

/**
 * \brief Code de démo de couleur
 *
 * Cette fonction permet de faire varier la couleur avec un rouge prédominant. Elle tient compte de la gestion temporelle et peut être appelée autant de fois que nécéssaire.
 * Base de temps minmale : 3ms.
 */

//void demoColor(void)
//{
//
//	static uint8_t incRouge = 0xBF, incVert = 0x5F, incBleu = 0x5F;
//	static bool upRouge = true, upVert = true, upBleu = false, updateColor = true;
//	static uint64_t delayRouge = millis(), delayVert = millis(), delayBleu = millis();
//
//	if (updateColor)
//	{
//		ledCmd.setColor(incRouge, incVert, incBleu);
//		updateColor = false;
//
//
//	}
//
//	//Change color
//	if ((millis() - delayRouge) > 3)
//	{
//		if (upRouge)
//		{
//			incRouge++;
//			if (incRouge == 0xFF)
//				upRouge = !upRouge;
//		}
//		else
//		{
//			incRouge--;
//			if (incRouge == 0xBF)
//				upRouge = !upRouge;
//		}
//		delayRouge = millis();
//		updateColor = true;
//	}
//
//	if ((millis() - delayVert) > 7)
//	{
//		if (upVert)
//		{
//			incVert++;
//			if (incVert == 0x7F)
//				upVert = !upVert;
//		}
//		else
//		{
//			incVert--;
//			if (incVert == 0x00)
//				upVert = !upVert;
//		}
//		delayVert = millis();
//		updateColor = true;
//	}
//
//	if ((millis() - delayBleu) > 5)
//	{
//		if (upBleu)
//		{
//			incBleu++;
//			if (incBleu == 0x7F)
//				upBleu = !upBleu;
//		}
//		else
//		{
//			incBleu--;
//			if (incBleu == 0x00)
//				upBleu = !upBleu;
//		}
//		delayBleu = millis();
//		updateColor = true;
//	}
//
//	delay(50);
//}


/**
 * \brief Used to stop the demoColor2 Task
 */

void minuterie(void* param)
{
	TaskHandle_t demoTaskTemp = (TaskHandle_t) param;
	uint16_t delayToStop = 30, counting = 0;
	const TickType_t delayChecking = pdMS_TO_TICKS(1000UL);

	//Set itself to suspension
	xEventGroupClearBits(minuterieTaskSpd, 0x01);

	while(true)
	{
		//Check first if the task has to be suspended.
		if((xEventGroupWaitBits(minuterieTaskSpd, 0x01, pdFALSE, pdFALSE, 0) & 0x01) == 0)
		{
			//Task has to be suspended
			//Init first
			counting = 0;
			//Wait until end of suspension
			xEventGroupWaitBits(minuterieTaskSpd, 0x01, pdFALSE, pdFALSE, portMAX_DELAY);
		}

		//Else, waiting
		vTaskDelay(delayChecking);

		counting++;

		if(counting >= delayToStop)
		{
			//Once delay is done, stop demoTaskTemp task
			ulTaskNotifyValueClearIndexed(demoTaskTemp, 0, 0x01);
			ledCmd.setColor(0x00, 0x00, 0x00);
			ledCmd.end();

			//Set itself to suspension
			ulTaskNotifyValueClearIndexed(NULL, 0, 0x01);
		}
	}
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

void demoColor2(void* param)
{
	const uint16_t brightHigh = 0x3F, brightLow = 0x10, inTime = 1700 / (brightHigh - brightLow), outTime = 4000 / (brightHigh - brightLow);
	uint16_t incColor = 0x00, incBright = brightHigh, time = outTime;
	static bool upBright = false, updateColor = true;
	static uint16_t delayColor = 0, delayBright = 0;
	const uint8_t loopTime = 5;
	const TickType_t delay1ms = pdMS_TO_TICKS(5);


	//Set itself to suspension
	xEventGroupClearBits(demoTaskSpd, 0x01);

	while(true)
	{
		//Check first if the task has to be suspended.
		if((xEventGroupWaitBits(demoTaskSpd, 0x01, pdFALSE, pdFALSE, 0) & 0x01) == 0)
		{
			//Task has to be suspended
			//Init first
			incColor = 0x00;
			incBright = brightHigh;

			//Wait until end of suspension
			xEventGroupWaitBits(demoTaskSpd, 0x01, pdFALSE, pdFALSE, portMAX_DELAY);
		}

		if (updateColor)
		{
			ledCmd.setColorTwoAxes(incColor, incBright);
			updateColor = false;
		}

		vTaskDelay(delay1ms);

		//Change color
		delayColor += loopTime;
		if (delayColor > 40)
		{
			incColor++;
			if (incColor >= (uint16_t)(6 *0xFF))
				incColor = 0x00;

			delayColor = 0;
			updateColor = true;
		}

		delayBright += loopTime;
		if (delayBright > time)
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
			delayBright = 0;
			updateColor = true;
		}
	}
}

/**
 * \brief Display color according to position of the accelerometer.
 */

void interaction(void* param)
{
	Adxl345::data axcelData;
	const uint8_t maxData=5, gVal = 128;
	uint8_t saveIndex=0;
	uint16_t dataColor[maxData], dataBright[maxData];
	EventGroupHandle_t singleTapEv = axcel.getAccelEventGp();
	bool display=true;
	const TickType_t delay100ms = pdMS_TO_TICKS(10);
	uint32_t moy = 0;

	//Set itself to suspension
	xEventGroupClearBits(colorChTaskSpd, 0x01);

	//Clear Single tap Bits
	xEventGroupClearBits(singleTapEv, 0x02);

	for(uint8_t i=0; i < maxData; i++)
	{
		dataColor[i] = 0;
		dataBright[i] = 0;
	}

	while(true)
	{

		//Check first if the task has to be suspended.
		if((xEventGroupWaitBits(colorChTaskSpd, 0x01, pdFALSE, pdFALSE, 0) & 0x01) == 0)
		{
			//Task has to be suspended
			//Init first
			//In case previous state was suspension: restart

			for(uint8_t i=0; i < maxData; i++)
			{
				dataColor[i] = 0;
				dataBright[i] = 0;
			}

			//Wait until end of suspension
			xEventGroupWaitBits(colorChTaskSpd, 0x01, pdFALSE, pdFALSE, portMAX_DELAY);
		}

		EventBits_t singleTap = xEventGroupClearBits(singleTapEv, 0x02);

		if(singleTap & 0x02)
			display = !display;

		ledCmd.setColorTwoAxes(lastColorSaved, lastBrightSaved);

		if(!display)
		{
			axcelData = axcel.getData();

			//Compute Color and save it
			int16_t x = axcelData.x, absX = 0;
			int16_t y = axcelData.y, absY = 0;

			if(x < 0)
				absX = -x;
			else
				absX = x;

			if(y < 0)
				absY = -y;
			else
				absY = y;

			if((absX >= absY) && (x > 0) && (y >=0))
			{
				dataColor[saveIndex] = (uint16_t)(((int32_t)191 * (int32_t) y) / x);
			}
			else if((absY >= absX) && (y > 0))
			{
				dataColor[saveIndex] = (uint16_t)(383 - ((int32_t)191 * (int32_t) x) / y);
			}
			else if((absX >= absY) && (x < 0))
			{
				dataColor[saveIndex] = (uint16_t)(765 + ((int32_t)191 * (int32_t) y) / x);
			}
			else if((absY >= absX) && (y < 0))
			{
				dataColor[saveIndex] = (uint16_t)(1148 - ((int32_t)191 * (int32_t) x) / y);
			}
			else if(x != 0)
			{
				dataColor[saveIndex] = (uint16_t)(1530 + ((int32_t)191 * (int32_t) y) / x);
			}


			moy = 0;
			for(uint8_t i =0; i<maxData; i++)
			{
				moy += dataColor[i];
			}

			lastColorSaved = (uint16_t)(moy / maxData);

			//Compute Brightness and save it
			int16_t z = -axcelData.z;
			int32_t tempVal;

			tempVal = ((int32_t)z * 0x3F) / gVal + 0x3F;

			if(tempVal > (2 * 0xFF+1))
				tempVal = 2 * 0xFF;
			else if(tempVal < 0)
				tempVal = 0;

			dataBright[saveIndex] = (uint16_t) tempVal;

			moy = 0;
			for(uint8_t i =0; i<maxData; i++)
			{
				moy += dataBright[i];
			}

			lastBrightSaved = (uint16_t)(moy / maxData);

			saveIndex++;
			if(saveIndex >= maxData)
				saveIndex = 0;

			vTaskDelay(delay100ms);
		}
	}
}


void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	for( ;; );
}
/*-----------------------------------------------------------*/


void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amout of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}

void vApplicationTickHook( void )
{

}
