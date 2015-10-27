/*
 * torqueSensorController.c
 *
 * Created: 23.04.2013 13:00:46
 *  Author: duenda
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define F_CPU  11.0952E+6
#define SLEEP_PERIOD_MS   700
#define ledPort PORTB
#define ledPin  PORTB1
#define ledDDRPort DDRB
#define buzzerPort  PORTB
#define buzzerPin   PORTB2
#define buzzerDDRPort DDRB



#define maxLogStringSz  80
char    logString [maxLogStringSz];
uint32_t  cycleCnt;

void USART_Init( unsigned int ubrr )
{	
	//Set baud rate 
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Set frame format: 8data, 1stop bit 
	UCSR0C = (3<<UCSZ00);
}


static int uart_putchar(char c1)
{	
   while (!(UCSR0A & (1<<UDRE0)));                    
   UDR0 = c1;
   return 0;
}


void info_printf( char *emsg, ...)
{
	va_list ap;
	uint8_t  res;
	char* ptr;
	uint16_t  cnt;
	va_start(ap, emsg);
	
	res = vsnprintf(logString, maxLogStringSz-1,  emsg, ap);
	if (res > 0)  {
		cnt = 0;
		logString [maxLogStringSz-1] = 0;
		ptr = logString;
		while( (*ptr) && (cnt < maxLogStringSz) )  {
			uart_putchar(*ptr);
			++ptr;
			++cnt;
		}
	}

	va_end(ap);
}	
	//	printf(emsg, ap);

void tmr_init();
void initLED();
void initBuzzer();
void setBuzzerOff();
void setBuzzerOn();
void toggleLED();
void saveBuzzerStateSwitchOff();
void restoreBuzzerState();
void advanceBuzzerState();

void initHW()
{
//	USART_Init( 142 );   // baud 4800 at 11.0592 mhz, single uart speed
	USART_Init( 71 );   // baud 9600 at 11.0592 mhz, single uart speed
//	USART_Init (11 );   // baud 57.6k  at 11.0592 mhz, single uart speed
	cycleCnt = 0;
	tmr_init();
	initLED();
	initBuzzer();
}

ISR(TIMER1_COMPA_vect)
{
//	toggleLED();
}


void tmr_init(void)
{
 	
	TCCR1A = 0x00;	//normal operation, no output to port   


	TCCR1B =  (0<<ICNC1) |(0<<ICES1) |(0<<WGM13) |(1<<WGM12)   // no noise canceler,no waveform generation	
				|(1<<CS12)  |(0<<CS11)  |(1<<CS10);		//   prescaler set to 1024          
     
	TCCR1C = 0x00;		// no force ouput compare
	 
	TCNT1 = 0;
 
	// Calculate and set delay
	OCR1A  = (uint16_t)(((F_CPU/1024)*SLEEP_PERIOD_MS)/1000) - 1;
 
	// Enable interrupt on compare match
	TIMSK1 |= (1<<OCIE1A);   //   
	sei();
}

uint16_t lastADCVal;

uint8_t interruptDone;

ISR(ADC_vect)
{
	lastADCVal   = ADC;                     // Read the ADC Result
//	ADCSRA |= (1 << ADIF);					// Acknowledge the ADC Interrupt Flag, should be done by hardware anyhow
	interruptDone = 1;						// atomicity given by single clock instruction for 8 bit value moves
}


int getADCValue(uint16_t* val)
{
	uint16_t cnt;
	saveBuzzerStateSwitchOff();
	for (cnt=0;cnt > 0xFF; cnt ++) {};   // give it some time to relax AVCC, tobe tested
	
	ADCSRA   = (1<< ADEN) | (1<< ADIE) 	| (7 << ADPS0);   // Enable ADC with Clock prescaled by 128 ; 
														//  If Clock speed is 16MHz, then ADC clock = 16MHz/128 = 125kHz, enable interrupt
	ADCSRB   = 0b00000000;        			// single conversion mode
    DIDR0    = 0b00111111;        			// Disable Digital Input on ADC Channel 0 to reduce power consumption
    ADMUX    = (1<< REFS0)  ;       			// Disable Left-Adjust and select 5V internal ref voltage and ADC Channel 0 as input

	interruptDone = 0;
	sei();									// Enable Global Interrupts
	
//	MCUCR &= 0b11000011;
//	MCUCR |= (1<< SE) | (1<< SM0) | (1<<SE);				//  choose ADC noise reduction and enable sleep mode
	
//  sleep instruction
//    __asm__ __volatile__ ("sleep\n\t"::);
	
	sleep_enable();
	set_sleep_mode(SLEEP_MODE_ADC);
    sleep_mode(); 	
	
	sleep_disable();
	
	while (! interruptDone) {}               
											// explicitly check that interrupt was first, 
											// atomicity is given by single cycle instruction code when setting/reading a char (no cli sei needed)
	*val = lastADCVal;	
    ADCSRA  = 0x00;							// disable adc until next time to save power
	restoreBuzzerState();
//	advanceBuzzerState();
	return 1;
}

uint8_t  buzzerState;

void initLED()
{
	ledDDRPort  |= (1<<ledPin);        			// Set ledDDRPort.ledPin  as output
}

void setLEDon()
{
	
	ledPort   |= (1<< ledPin);        			// Initialize PORTB.0 with logic "one"
}

void setLEDoff()
{
	ledPort   &= ~(1<<ledPin) ;
}

void toggleLED()
{
	ledPort ^=  (1<<ledPin);	
}

void initBuzzer()
{
	buzzerDDRPort  |= (1<<buzzerPin);        			// Set ledDDRPort.ledPin  as output
	setBuzzerOff();
}

void setBuzzerOn()
{
	
	buzzerPort   &= ~(1<<buzzerPin);        			// Initialize PORTB.0 with logic "one"
}

void setBuzzerOff()
{
	buzzerPort   |= (1<<buzzerPin) ;
}

void toggleBuzzer()
{
	buzzerPort ^=  (1<<buzzerPin);	
}

void saveBuzzerStateSwitchOff()
{
	buzzerState = buzzerPort & (1<<buzzerPin);
	setBuzzerOff();
}

void restoreBuzzerState()
{
	if (buzzerState == 0) {
		setBuzzerOn();
	} else {
		setBuzzerOff();
	}
}

void advanceBuzzerState()
{
	if (cycleCnt % 2) {
		setBuzzerOn();
	} else 	{
		setBuzzerOff();	
	}
}


void sendADCvalue(uint16_t adcV)
{
	info_printf("DATA 01V%04u |||\n",adcV);
}



void performJob()
{
	uint16_t adcVal;
	toggleLED();
//	setLEDon();
	if (getADCValue(&adcVal))  {
		sendADCvalue(adcVal);
	}
//	setLEDoff();
}

void sleepDeep()
{
		
	// Initialise timer
//	tmr_init();
 
	// Enable interrupt
	sei();
//	MCUCR &= 0b11000011;
//	MCUCR |= (1<< SE) ;				//  choose Idle mode and enable sleep mode
	
//  sleep instruction
//    __asm__ __volatile__ ("sleep\n\t"::);

	sleep_enable();
	set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode(); 
	sleep_disable();
	++ cycleCnt;
	MCUCR &= ~(1<<SE);				//  disable sleep modes
}


int main(void)
{
    while(1)
    {
		initHW();
        //TODO:: Please write your application code 
		while (1)
		{
			performJob();
			sleepDeep();
		}
    }
}