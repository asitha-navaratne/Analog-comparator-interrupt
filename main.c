#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_DDR		DDRA			///< DDR of indicator LED.
#define LED_PORT	PORTA			///< Port of indicator LED.
#define LED_PIN		PA0			///< Pin of indicator LED.

void PORT_INIT(void);
void COMPARATOR_INIT(void);

/*!
 *	@brief ISR for Analog Comparator Interrupt; turn on LED if an interrupt occurs.
 */

ISR(ANA_COMP_vect){
	LED_PORT ^= (1<<LED_PIN);
}

int main(void){
	PORT_INIT();
	COMPARATOR_INIT();
	
	sei();					///< Enable global interrupts.
	
	while(1);
}

/*!
 *	@brief Initialize ports.
 */

void PORT_INIT(void){
	LED_DDR |= (1<<LED_PIN);
}

/*!
 *	@brief Initialize Analog Comparator.
 */

void COMPARATOR_INIT(void){
	ACSR = 0x00;				///< Enable Analog Comparator by setting ACD to 0.
	ACSR |= (1<<ACIE)|(1<<ACIS1);		///< Enable Analog Comparator Interrupt and set Interrupt Mode to Falling Output Edge.
}
