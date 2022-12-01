#include <avr/interrupt.h>

#include <Arduino.h>


// Duration s, Frequenzy, Multiplier, Duty %
uint16_t pwm_step[][4] = {
        {5, 250,  1, 10},
        {5, 500,  1, 25},
        {5, 750,  1, 50},
        {5, 1000, 1, 75}
};

uint16_t count_top;


int main() {

    init();

    DDRB |= (1 << PB1);                             // set D9 (OC1A) to output
    TCCR1A = TCCR1B = 0;                            // reset timer 1

    /* mode: fast PWM, TOP = OCR1A */
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    TCCR1A |= (1 << COM1A1);                        // N-INV
    TCCR1B |= (1 << CS00);                          // Prescale 1


    while (1) {
        for (unsigned int i = 0; i < (sizeof pwm_step / 8); i++) {

            count_top = (uint16_t) ((16000.0 / pwm_step[i][1]) * 1000) / pwm_step[i][2];

            ICR1 = count_top;
            OCR1A = (uint16_t) (count_top / (100.0 / pwm_step[i][3]));

            // _delay_ms hat keine Lust bei größeren Arrays?
            delay(1000 * pwm_step[i][0]);

        }

        /**
        for(auto & i : pwm_step){

            count_top = (uint16_t) ((16000.0 / i[1]) * 1000) / i[2];

            ICR1 = count_top;
            OCR1A = (uint16_t) (count_top / (100 / i[3]));

            _delay_ms(i[0]);

        }
        */

    }

}