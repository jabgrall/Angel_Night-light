/**
 * \file adxl345.cxx
 *
 * \brief File that configure and get data from the accelerometer.
 */

#include "adxl345.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

Adxl345::Adxl345(void)
{
	for(uint8_t i=0; i < bufferSize; i++)
	{
		bufferOut[i] = 0;
		bufferIn[i] = 0;
	}
}

Adxl345::~Adxl345(void)
{

}


void Adxl345::begin()
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_SPI1);

	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO5 | GPIO7 );
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO3);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO1 | GPIO2 | GPIO6 );
	spi_reset(SPI1);

	spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_256, SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);

	spi_enable_software_slave_management(SPI1);
	spi_set_nss_high(SPI1);

	gpio_set(GPIOA, GPIO3);

	/* Enable SPI1 periph. */
	spi_enable(SPI1);

	/* Configure the ADXL345 */
	//Config

	/**
	\section adxl345_regs REGISTER DEFINITIONS

	From datasheet. Copied in order to keep information during developpement.
	*/

	//Initialisation
	/**
	\subsection adxl345_regs_31 Register 0x31—DATA_FORMAT (Read/Write)

	<table>
	<tr><th> Bits	<th> Function			<th> Choosen value
	<tr><td> D7		<td> SELF_TEST			<td> 0
	<tr><td> D6		<td> SPI				<td> 0
	<tr><td> D5		<td> INT_INVERT			<td> 0
	<tr><td> D4		<td> 0					<td> 0
	<tr><td> D3		<td> FULL_RES			<td> 0
	<tr><td> D2		<td> Justify			<td> 0
	<tr><td> D1		<td rowspan="2"> Range	<td> 0
	<tr><td> D0 							<td> 0
	</table>

	The DATA_FORMAT register controls the presentation of data
	to Register 0x32 through Register 0x37. All data, except that for
	the ±16 g range, must be clipped to avoid rollover.

	\paragraph adxl345_regs_31_p1 SELF_TEST Bit

	A setting of 1 in the SELF_TEST bit applies a self-test force to
	the sensor, causing a shift in the output data. A value of 0 disables
	the self-test force.

	\paragraph adxl345_regs_31_p2 SPI Bit

	A value of 1 in the SPI bit sets the device to 3-wire SPI mode,
	and a value of 0 sets the device to 4-wire SPI mode.

	\paragraph adxl345_regs_31_p3 INT_INVERT

	A value of 0 in the INT_INVERT bit sets the interrupts to active
	high, and a value of 1 sets the interrupts to active low.

	\paragraph adxl345_regs_31_p4 FULL_RES Bit

	When this bit is set to a value of 1, the device is in full resolution
	mode, where the output resolution increases with the g range
	set by the range bits to maintain a 4 mg/LSB scale factor. When
	the FULL_RES bit is set to 0, the device is in 10-bit mode, and
	the range bits determine the maximum g range and scale factor.

	\paragraph adxl345_regs_31_p5 Justify Bit

	A setting of 1 in the justify bit selects left-justified (MSB) mode,
	and a setting of 0 selects right-justified mode with sign extension.

	\paragraph adxl345_regs_31_p6 Range Bits

	These bits set the g range as described in Table 21.

	\paragraph adxl345_regs_31_p7 Table 21. g Range Setting

	<table>
	<tr><th colspan="2"> Setting	<th rowspan="2"> g Range
	<tr><th> D1		<th> D0
	<tr><td> 0		<td> 0			<td> ±2 g
	<tr><td> 0		<td> 1			<td> ±4 g
	<tr><td> 1		<td> 0			<td> ±8 g
	<tr><td> 1		<td> 1			<td> ±16 g
	</table>
	*/
	comByte(0x31, true, (0 << 7) + (0 << 6) + (0 << 5) + (0 << 3) + (0 << 2) + 0);


	/**
	\subsection adxl345_regs_38 Register 0x38—FIFO_CTL (Read/Write)

	<table>
	<tr><th> Bits	<th> Function				<th> Choosen value
	<tr><td> D7		<td rowspan="2"> FIFO_MODE	<td> 0
	<tr><td> D6			 						<td> 0
	<tr><td> D5		<td> Trigger				<td> 0
	<tr><td> D4		<td rowspan="5"> Samples	<td> 0
	<tr><td> D3									<td> 0
	<tr><td> D2									<td> 0
	<tr><td> D1							 		<td> 0
	<tr><td> D0 								<td> 0
	</table>

	\paragraph adxl345_regs_38_p1 FIFO_TRIG Bit

	These bits set the FIFO mode, as described in Table 22.

	\paragraph adxl345_regs_38_p2 Table 22. FIFO Modes

	<table>
	<tr><th colspan="2"> Setting <td colspan="2">
	<tr><th> D7		<th> D6		<th> Mode		<th> Function
	<tr><td> 0		<td> 0		<td> Bypass		<td> FIFO is bypassed.
	<tr><td> 0		<td> 1		<td> FIFO		<td> FIFO collects up to 32 values and then stops collecting data, collecting new data only when FIFO is not full.
	<tr><td> 1		<td> 0		<td> Stream		<td> FIFO holds the last 32 data values. When FIFO is full, the oldest data is overwritten with newer data.
	<tr><td> 1		<td> 1		<td> Trigger	<td> When triggered by the trigger bit, FIFO holds the last data samples before the trigger event and then continues to collect data until full. New data is collected only when FIFO is not full.
	</table>

	\paragraph adxl345_regs_38_p3 Trigger Bit

	A value of 0 in the trigger bit links the trigger event of trigger mode
	to INT1, and a value of 1 links the trigger event to INT2.

	\paragraph adxl345_regs_38_p4 Samples Bits

	The function of these bits depends on the FIFO mode selected
	(see Table 23). Entering a value of 0 in the samples bits immediately
	sets the watermark status bit in the INT_SOURCE register,
	regardless of which FIFO mode is selected. Undesirable operation
	may occur if a value of 0 is used for the samples bits when trigger
	mode is used.

	\paragraph adxl345_regs_38_p5 Table 23. Samples Bits Functions

	<table>
	<tr><th> FIFO Mode	<th> Samples Bits Function
	<tr><td> Bypass		<td> None.
	<tr><td> FIFO		<td> Specifies how many FIFO entries are needed to trigger a watermark interrupt.
	<tr><td> Stream		<td> Specifies how many FIFO entries are needed to trigger a watermark interrupt.
	<tr><td> Trigger	<td> Specifies how many FIFO samples are retained in the FIFO buffer before a trigger event.
	</table>
	*/
	comByte(0x38, true, (0 << 6) + (0 << 5) + 0);

	/**
	\subsection adxl345_regs_1E1F20 Register 0x1E, Register 0x1F, Register 0x20—OFSX, OFSY, OFSZ (Read/Write)

	The OFSX, OFSY, and OFSZ registers are each eight bits and offer user-set offset adjustments in twos complement format with a scale factor of 15.6 mg/LSB (that is, 0x7F = 2 g).
	The value stored in the offset registers is automatically added to the acceleration data, and the resulting value is stored in the output data registers. For additional information regarding offset
	calibration and the use of the offset registers, refer to the Offset Calibration section.
	*/
	comByte(0x1E, true, 0);
	comByte(0x1F, true, 0);
	comByte(0x20, true, 0);


	/**
	\subsection adxl345_regs_2C Register 0x2C—BW_RATE (Read/Write)

	<table>
	<tr><th> Bits	<th> Function				<th> Choosen value
	<tr><td> D7		<td> 0						<td> 0
	<tr><td> D6		<td> 0 						<td> 0
	<tr><td> D5		<td> 0						<td> 0
	<tr><td> D4		<td> LOW_POWER				<td> 0
	<tr><td> D3		<td rowspan="4"> Rate		<td> 1
	<tr><td> D2									<td> 0
	<tr><td> D1							 		<td> 1
	<tr><td> D0 								<td> 0
	</table>

	\paragraph adxl345_regs_2C_p1 LOW_POWER Bit

	A setting of 0 in the LOW_POWER bit selects normal operation,
	and a setting of 1 selects reduced power operation, which has
	somewhat higher noise (see the Power Modes section for details).

	\paragraph adxl345_regs_2C_p2 Rate Bits

	These bits select the device bandwidth and output data rate (see
	Table 7 and Table 8 for details). The default value is 0x0A, which
	translates to a 100 Hz output data rate. An output data rate should
	be selected that is appropriate for the communication protocol
	and frequency selected. Selecting too high of an output data rate with
	a low communication speed results in samples being discarded.
	*/
	comByte(0x2C, true, (0 << 4) + 0x0A);



	//Tap et Double Tap
	/**
	\subsection adxl345_regs_1D Register 0x1D—THRESH_TAP (Read/Write)

	The THRESH_TAP register is eight bits and holds the threshold value for tap interrupts. The data format is unsigned, therefore, the magnitude of the tap event is compared with the value in THRESH_TAP for normal tap detection. The scale factor is
	62.5 mg/LSB (that is, 0xFF = 16 g). A value of 0 may result in undesirable behavior if single tap/double tap interrupts are enabled.
	*/
	comByte(0x1D, true, 0);

	/**
	\subsection adxl345_regs_21 Register 0x21—DUR (Read/Write)

	The DUR register is eight bits and contains an unsigned time
	value representing the maximum time that an event must be
	above the THRESH_TAP threshold to qualify as a tap event. The
	scale factor is 625 μs/LSB. A value of 0 disables the single tap/
	double tap functions.
	*/
	comByte(0x21, true, 0);

	/**
	\subsection adxl345_regs_22 Register 0x22—Latent (Read/Write)

	The latent register is eight bits and contains an unsigned time
	value representing the wait time from the detection of a tap
	event to the start of the time window (defined by the window
	register) during which a possible second tap event can be detected.
	The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap
	function.
	*/
	comByte(0x22, true, 0);

	/**
	\subsection adxl345_regs_23 Register 0x23—Window (Read/Write)

	The window register is eight bits and contains an unsigned time
	value representing the amount of time after the expiration of the
	latency time (determined by the latent register) during which a
	second valid tap can begin. The scale factor is 1.25 ms/LSB. A
	value of 0 disables the double tap function.
	*/
	comByte(0x23, true, 0);

	/**
	\subsection adxl345_regs_2A Register 0x2A—TAP_AXES (Read/Write)

	<table>
	<tr><th> Bits	<th> Function				<th> Choosen value
	<tr><td> D7		<td> 0						<td> 0
	<tr><td> D6		<td> 0 						<td> 0
	<tr><td> D5		<td> 0						<td> 0
	<tr><td> D4		<td> 0						<td> 0
	<tr><td> D3		<td> Suppress				<td> 0
	<tr><td> D2		<td> TAP_X enable			<td> 0
	<tr><td> D1		<td> TAP_Y enable			<td> 0
	<tr><td> D0 	<td> TAP_Z enable			<td> 0
	</table>

	\paragraph adxl345_regs_2A_p1 Suppress Bit

	Setting the suppress bit suppresses double tap detection if
	acceleration greater than the value in THRESH_TAP is present
	between taps. See the Tap Detection section for more details.

	\paragraph adxl345_regs_2A_p2 TAP_x Enable Bits

	A setting of 1 in the TAP_X enable, TAP_Y enable, or TAP_Z
	enable bit enables x-, y-, or z-axis participation in tap detection.
	A setting of 0 excludes the selected axis from participation in
	tap detection.
	*/
	comByte(0x2A, true, (0 << 3) + (0 << 2) + (0 << 1) + (0 << 0));



	//Activity and Inactivity
	/**
	\subsection adxl345_regs_27 Register 0x27—ACT_INACT_CTL (Read/Write)

	<table>
	<tr><th> Bits	<th> Function				<th> Choosen value
	<tr><td> D7		<td> ACT ac/dc				<td> 0
	<tr><td> D6		<td> ACT_X enable			<td> 0
	<tr><td> D5		<td> ACT_Y enable			<td> 0
	<tr><td> D4		<td> ACT_Z enable			<td> 0
	<tr><td> D3		<td> INACT ac/dc			<td> 0
	<tr><td> D2		<td> INACT_X enable			<td> 0
	<tr><td> D1		<td> INACT_Y enable			<td> 0
	<tr><td> D0 	<td> INACT_Z enable			<td> 0
	</table>

	\paragraph adxl345_regs_27_p1 ACT AC/DC and INACT AC/DC Bits

	A setting of 0 selects dc-coupled operation, and a setting of 1
	enables ac-coupled operation. In dc-coupled operation, the
	current acceleration magnitude is compared directly with
	THRESH_ACT and THRESH_INACT to determine whether
	activity or inactivity is detected.

	In ac-coupled operation for activity detection, the acceleration
	value at the start of activity detection is taken as a reference
	value. New samples of acceleration are then compared to this
	reference value, and if the magnitude of the difference exceeds
	the THRESH_ACT value, the device triggers an activity interrupt.
	Similarly, in ac-coupled operation for inactivity detection, a
	reference value is used for comparison and is updated whenever
	the device exceeds the inactivity threshold. After the reference
	value is selected, the device compares the magnitude of the
	difference between the reference value and the current acceleration
	with THRESH_INACT. If the difference is less than the value in
	THRESH_INACT for the time in TIME_INACT, the device is
	considered inactive and the inactivity interrupt is triggered.

	\paragraph adxl345_regs_27_p2 ACT_x Enable Bits and INACT_x Enable Bits

	A setting of 1 enables x-, y-, or z-axis participation in detecting
	activity or inactivity. A setting of 0 excludes the selected axis from
	participation. If all axes are excluded, the function is disabled.
	For activity detection, all participating axes are logically OR’ed,
	causing the activity function to trigger when any of the partici-
	pating axes exceeds the threshold. For inactivity detection, all
	participating axes are logically AND’ed, causing the inactivity
	function to trigger only if all participating axes are below the
	threshold for the specified time.
	*/
	comByte(0x27, true, (0 << 7) + (0 << 6) + (0 << 5) + (0 << 4) + (0 << 3) + (0 << 2) + (0 << 1) + (0 << 0));

	/**
	\subsection adxl345_regs_24 Register 0x24—THRESH_ACT (Read/Write)

	The THRESH_ACT register is eight bits and holds the threshold
	value for detecting activity. The data format is unsigned, so the
	magnitude of the activity event is compared with the value in
	the THRESH_ACT register. The scale factor is 62.5 mg/LSB.
	A value of 0 may result in undesirable behavior if the activity
	interrupt is enabled.
	*/
	comByte(0x24, true, 0);

	/**
	\subsection adxl345_regs_25 Register 0x25—THRESH_INACT (Read/Write)

	The THRESH_INACT register is eight bits and holds the threshold
	value for detecting inactivity. The data format is unsigned, so
	the magnitude of the inactivity event is compared with the value
	in the THRESH_INACT register. The scale factor is 62.5 mg/LSB.
	A value of 0 may result in undesirable behavior if the inactivity
	interrupt is enabled.
	*/
	comByte(0x25, true, 0);

	/**
	\subsection adxl345_regs_26 Register 0x26—TIME_INACT (Read/Write)

	The TIME_INACT register is eight bits and contains an unsigned
	time value representing the amount of time that acceleration
	must be less than the value in the THRESH_INACT register for
	inactivity to be declared. The scale factor is 1 sec/LSB. Unlike
	the other interrupt functions, which use unfiltered data (see the
	Threshold section), the inactivity function uses filtered output
	data. At least one output sample must be generated for the
	inactivity interrupt to be triggered. This results in the function
	appearing unresponsive if the TIME_INACT register is set to a
	value less than the time constant of the output data rate. A value
	of 0 results in an interrupt when the output data is less than the
	value in the THRESH_INACT register.
	*/
	comByte(0x26, true, 0);



	//Free Fall
	/**
	\subsection adxl345_regs_28 Register 0x28—THRESH_FF (Read/Write) LOW_POWER Bit

	The THRESH_FF register is eight bits and holds the threshold
	value, in unsigned format, for free-fall detection. The acceleration on
	all axes is compared with the value in THRESH_FF to determine if
	a free-fall event occurred. The scale factor is 62.5 mg/LSB. Note
	that a value of 0 mg may result in undesirable behavior if the free-
	fall interrupt is enabled. Values between 300 mg and 600 mg
	(0x05 to 0x09) are recommended.
	*/
	comByte(0x28, true, 0);

	/**
	\subsection adxl345_regs_29 Register 0x29—TIME_FF (Read/Write)

	The TIME_FF register is eight bits and stores an unsigned time
	value representing the minimum time that the value of all axes
	must be less than THRESH_FF to generate a free-fall interrupt.
	The scale factor is 5 ms/LSB. A value of 0 may result in undesirable
	behavior if the free-fall interrupt is enabled. Values between 100 ms
	and 350 ms (0x14 to 0x46) are recommended.
	*/
	comByte(0x29, true, 0);



	//Interrupts
	/**
	\subsection adxl345_regs_2F Register 0x2F—INT_MAP (R/W)

	<table>
	<tr><th> Bits	<th> Function			<th> Choosen value
	<tr><td> D7		<td> DATA_READY			<td> 0
	<tr><td> D6		<td> SINGLE_TAP			<td> 0
	<tr><td> D5		<td> DOUBLE_TAP			<td> 0
	<tr><td> D4		<td> Activity			<td> 0
	<tr><td> D3		<td> Inactivity			<td> 0
	<tr><td> D2		<td> FREE_FALL			<td> 0
	<tr><td> D1		<td> Watermark			<td> 0
	<tr><td> D0 	<td> Overrun			<td> 0
	</table>

	Any bits set to 0 in this register send their respective interrupts to
	the INT1 pin, whereas bits set to 1 send their respective interrupts
	to the INT2 pin. All selected interrupts for a given pin are OR’ed.
	*/
	comByte(0x2F, true, (0 << 7) + (0 << 6) + (0 << 5) + (0 << 4) + (0 << 3) + (0 << 2) + (0 << 1) + (0 << 0));

	/**
	\subsection adxl345_regs_2E Register 0x2E—INT_ENABLE (Read/Write)

	<table>
	<tr><th> Bits	<th> Function			<th> Choosen value
	<tr><td> D7		<td> DATA_READY			<td> 0
	<tr><td> D6		<td> SINGLE_TAP			<td> 0
	<tr><td> D5		<td> DOUBLE_TAP			<td> 0
	<tr><td> D4		<td> Activity			<td> 0
	<tr><td> D3		<td> Inactivity			<td> 0
	<tr><td> D2		<td> FREE_FALL			<td> 0
	<tr><td> D1		<td> Watermark			<td> 0
	<tr><td> D0 	<td> Overrun			<td> 0
	</table>

	Setting bits in this register to a value of 1 enables their respective
	functions to generate interrupts, whereas a value of 0 prevents
	the functions from generating interrupts. The DATA_READY,
	watermark, and overrun bits enable only the interrupt output;
	the functions are always enabled. It is recommended that interrupts
	be configured before enabling their outputs.
	*/
	comByte(0x2E, true, (0 << 7) + (0 << 6) + (0 << 5) + (0 << 4) + (0 << 3) + (0 << 2) + (0 << 1) + (0 << 0));






	//Start and Power Ctrl
	/**
	\subsection adxl345_regs_2D Register 0x2D—POWER_CTL (Read/Write)

	<table>
	<tr><th> Bits	<th> Function			<th> Choosen value
	<tr><td> D7		<td> 0					<td> 0
	<tr><td> D6		<td> 0					<td> 0
	<tr><td> D5		<td> Link				<td> 0
	<tr><td> D4		<td> AUTO_SLEEP			<td> 0
	<tr><td> D3		<td> Measure			<td> 1
	<tr><td> D2		<td> Sleep				<td> 0
	<tr><td> D1		<td rowspan="2"> Wakeup	<td> 0
	<tr><td> D0 							<td> 0
	</table>

	\paragraph adxl345_regs_2D_p1 Link Bit

	A setting of 1 in the link bit with both the activity and inactivity
	functions enabled delays the start of the activity function until
	inactivity is detected. After activity is detected, inactivity detection
	begins, preventing the detection of activity. This bit serially links
	the activity and inactivity functions. When this bit is set to 0,
	the inactivity and activity functions are concurrent. Additional
	information can be found in the Link Mode section.

	When clearing the link bit, it is recommended that the part be
	placed into standby mode and then set back to measurement
	mode with a subsequent write. This is done to ensure that the
	device is properly biased if sleep mode is manually disabled;
	otherwise, the first few samples of data after the link bit is cleared
	may have additional noise, especially if the device was asleep
	when the bit was cleared.

	\paragraph adxl345_regs_2D_p2 AUTO_SLEEP Bit

	If the link bit is set, a setting of 1 in the AUTO_SLEEP bit enables
	the auto-sleep functionality. In this mode, the ADXL345 auto-
	matically switches to sleep mode if the inactivity function is
	enabled and inactivity is detected (that is, when acceleration is
	below the THRESH_INACT value for at least the time indicated
	by TIME_INACT). If activity is also enabled, the ADXL345
	automatically wakes up from sleep after detecting activity and
	returns to operation at the output data rate set in the BW_RATE
	register. A setting of 0 in the AUTO_SLEEP bit disables automatic
	switching to sleep mode. See the description of the Sleep Bit in
	this section for more information on sleep mode.

	If the link bit is not set, the AUTO_SLEEP feature is disabled
	and setting the AUTO_SLEEP bit does not have an impact on
	device operation. Refer to the Link Bit section or the Link Mode
	section for more information on utilization of the link feature.

	When clearing the AUTO_SLEEP bit, it is recommended that the
	part be placed into standby mode and then set back to measure-
	ment mode with a subsequent write. This is done to ensure that
	the device is properly biased if sleep mode is manually disabled;
	otherwise, the first few samples of data after the AUTO_SLEEP
	bit is cleared may have additional noise, especially if the device
	was asleep when the bit was cleared.

	\paragraph adxl345_regs_2D_p3 Measure Bit

	A setting of 0 in the measure bit places the part into standby mode,
	and a setting of 1 places the part into measurement mode. The
	ADXL345 powers up in standby mode with minimum power
	consumption.

	\paragraph adxl345_regs_2D_p4 Sleep Bit

	A setting of 0 in the sleep bit puts the part into the normal mode
	of operation, and a setting of 1 places the part into sleep mode.
	Sleep mode suppresses DATA_READY, stops transmission of data
	to FIFO, and switches the sampling rate to one specified by the
	wakeup bits. In sleep mode, only the activity function can be used.
	When the DATA_READY interrupt is suppressed, the output
	data registers (Register 0x32 to Register 0x37) are still updated
	at the sampling rate set by the wakeup bits (D1:D0).

	When clearing the sleep bit, it is recommended that the part be
	placed into standby mode and then set back to measurement
	mode with a subsequent write. This is done to ensure that the
	device is properly biased if sleep mode is manually disabled;
	otherwise, the first few samples of data after the sleep bit is
	cleared may have additional noise, especially if the device was
	asleep when the bit was cleared.

	\paragraph adxl345_regs_2D_p5 Wakeup Bits

	These bits control the frequency of readings in sleep mode as
	described in Table 20.

	\paragraph adxl345_regs_2D_p6 Table 20. Frequency of Readings in Sleep Mode
	<table>
	<tr><th colspan="2"> Setting <td>
	<tr><th> D1		<th> D0		<th> Frequency (Hz)
	<tr><th> 0		<td> 0		<td> 8
	<tr><th> 0		<td> 1		<td> 4
	<tr><th> 1		<td> 0		<td> 2
	<tr><th> 1		<td> 1		<td> 1
	</table>
	*/
	comByte(0x2D, true, (0 << 5) + (0 << 4) + (1 << 3) + (0 << 2) + 0);



	//Read Only registers
	/**
	\subsection adxl345_regs_32-37 Register 0x32 to Register 0x37—DATAX0, DATAX1, DATAY0, DATAY1, DATAZ0, DATAZ1 (Read Only)

	These six bytes (Register 0x32 to Register 0x37) are eight bits
	each and hold the output data for each axis. Register 0x32 and
	Register 0x33 hold the output data for the x-axis, Register 0x34 and
	Register 0x35 hold the output data for the y-axis, and Register 0x36
	and Register 0x37 hold the output data for the z-axis. The output
	data is twos complement, with DATAx0 as the least significant
	byte and DATAx1 as the most significant byte, where x represent X,
	Y, or Z. The DATA_FORMAT register (Address 0x31) controls
	the format of the data. It is recommended that a multiple-byte
	read of all registers be performed to prevent a change in data
	between reads of sequential registers.
	*/


	/**
	\subsection adxl345_regs_00 Register 0x00—DEVID (Read Only)

	The DEVID register holds a fixed device ID code of 0xE5 (345 octal).
	*/

	/**
	\subsection adxl345_regs_39 Register 0x39—FIFO_STATUS (Read Only)

	<table>
	<tr><th> Bits	<th> Function
	<tr><td> D7		<td> FIFO_TRIG
	<tr><td> D6		<td> 0
	<tr><td> D5		<td rowspan="6"> Entries
	<tr><td> D4
	<tr><td> D3
	<tr><td> D2
	<tr><td> D1
	<tr><td> D0
	</table>

	\paragraph adxl345_regs_39_p1 FIFO_MODE Bits

	A 1 in the FIFO_TRIG bit corresponds to a trigger event occurring,
	and a 0 means that a FIFO trigger event has not occurred.

	\paragraph adxl345_regs_39_p2 Entries Bits

	These bits report how many data values are stored in FIFO.
	Access to collect the data from FIFO is provided through the
	DATAX, DATAY, and DATAZ registers. FIFO reads must be
	done in burst or multiple-byte mode because each FIFO level is
	cleared after any read (single- or multiple-byte) of FIFO. FIFO
	stores a maximum of 32 entries, which equates to a maximum
	of 33 entries available at any given time because an additional
	entry is available at the output filter of the device.
	*/

	/**
	\subsection adxl345_regs_2B Register 0x2B—ACT_TAP_STATUS (Read Only)

	<table>
	<tr><th> Bits	<th> Function
	<tr><td> D7		<td> 0
	<tr><td> D6		<td> ACT_X source
	<tr><td> D5		<td> ACT_Y source
	<tr><td> D4		<td> ACT_Z source
	<tr><td> D3		<td> Asleep
	<tr><td> D2		<td> TAP_X source
	<tr><td> D1		<td> TAP_Y source
	<tr><td> D0 	<td> TAP_Z source
	</table>

	\paragraph adxl345_regs_2B_p1 ACT_x Source and TAP_x Source Bits
	These bits indicate the first axis involved in a tap or activity
	event. A setting of 1 corresponds to involvement in the event,
	and a setting of 0 corresponds to no involvement. When new
	data is available, these bits are not cleared but are overwritten by
	the new data. The ACT_TAP_STATUS register should be read
	before clearing the interrupt. Disabling an axis from participation
	clears the corresponding source bit when the next activity or
	single tap/double tap event occurs.

	\paragraph adxl345_regs_2B_p2 Asleep Bit

	A setting of 1 in the asleep bit indicates that the part is asleep,
	and a setting of 0 indicates that the part is not asleep. This bit
	toggles only if the device is configured for auto sleep. See the
	AUTO_SLEEP Bit section for more information on autosleep
	mode.
	*/

	/**
	\subsection adxl345_regs_30 Register 0x30—INT_SOURCE (Read Only)

	<table>
	<tr><th> Bits	<th> Function
	<tr><td> D7		<td> DATA_READY
	<tr><td> D6		<td> SINGLE_TAP
	<tr><td> D5		<td> DOUBLE_TAP
	<tr><td> D4		<td> Activity
	<tr><td> D3		<td> Inactivity
	<tr><td> D2		<td> FREE_FALL
	<tr><td> D1		<td> Watermark
	<tr><td> D0 	<td> Overrun
	</table>

	Bits set to 1 in this register indicate that their respective functions
	have triggered an event, whereas a value of 0 indicates that the
	corresponding event has not occurred. The DATA_READY,
	watermark, and overrun bits are always set if the corresponding
	events occur, regardless of the INT_ENABLE register settings,
	and are cleared by reading data from the DATAX, DATAY, and
	DATAZ registers. The DATA_READY and watermark bits may
	require multiple reads, as indicated in the FIFO mode descriptions
	in the FIFO section. Other bits, and the corresponding interrupts,
	are cleared by reading the INT_SOURCE register.
	*/
}

void Adxl345::com(uint8_t addr, bool setWrite, uint8_t nbData)
{
	uint8_t firstByte = 0;
	volatile uint8_t dataFirst;

	firstByte = ((setWrite ? 0 : 1) << 7) + ((nbData > 1 ? 1 : 0) << 6) + (0x3F & addr);

	//Connect to client
	gpio_clear(GPIOA, GPIO3);

	//Send first byte
	spi_send(SPI1, firstByte);

	//Continue communication
	for (uint8_t i = 0; i < nbData + 1; i++)
	{
		//First write.
		if(i < nbData)
			spi_send(SPI1, (setWrite ? bufferOut[i] : 0));

		//Then, read back
		if (i == 0)
			dataFirst = spi_read(SPI1);
		else
			bufferIn[i-1] = spi_read(SPI1);
	}

	//Disconnect from client
	gpio_set(GPIOA, GPIO3);

	//Wait 150ns before next communication
	for(uint8_t i = 0; i < 10; i++)
	{
		__asm__("nop");
	}
}

uint8_t Adxl345::comByte(uint8_t addr, bool setWrite, uint8_t inData)
{
	bufferOut[0] = inData;
	com(addr, setWrite, 1);
	return bufferIn[0];
}


Adxl345::data Adxl345::getData(void)
{
	data valOut;

	//Init Data
	for (uint8_t i = 0; i < bufferSize; i++)
	{
		bufferIn[i] = 0;
		bufferOut[i] = 0;
	}

	//Get Data
	com(0x32, false, 6);

	//Prepare data
	valOut.x = (int16_t)((bufferIn[1] << 8) + bufferIn[0]);
	valOut.y = (int16_t)((bufferIn[3] << 8) + bufferIn[2]);
	valOut.z = (int16_t)((bufferIn[5] << 8) + bufferIn[4]);

	return valOut;
}

bool Adxl345::isTape()
{

}

bool Adxl345::isDoubleTap()
{

}
