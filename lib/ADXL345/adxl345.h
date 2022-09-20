/**
 * \file adxl345.h
 *
 * \brief File that configure and get data from the accelerometer.
 */

#ifndef LIB_ADXL345_ADXL345_H_
#define LIB_ADXL345_ADXL345_H_
#include <stdint.h>
#include <FreeRTOS.h>
#include <event_groups.h>
#include <task.h>

class Adxl345
{
public:
	struct data
	{
		int16_t x;
		int16_t y;
		int16_t z;
	};

	struct TaskDataDef
	{
		Adxl345* object;
	} TaskData;

	Adxl345(void);
	virtual ~Adxl345(void);

	void begin();
	data getData();
	bool isTap();
	bool isDoubleTap();

	EventGroupHandle_t getAccelEventGp();


	void interruptManagment(void* parameters);
	static void interruptManagment_Task(void* parameters);

private:
	static const uint8_t bufferSize = 8;
	uint8_t bufferIn[bufferSize], bufferOut[bufferSize];
	void com(uint8_t addr, bool setWrite, uint8_t nbData);
	uint8_t comByte(uint8_t addr, bool setWrite = false, uint8_t inData = 0);
	bool isTapInt = false, isDoubleTapInt = false;

	EventGroupHandle_t accelEventGp;

	void updateInterrupt(void);
};


#endif /* LIB_ADXL345_ADXL345_H_ */
