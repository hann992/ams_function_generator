#include <avr/io.h>

void configurePWM(uint16_t dutyCycle, uint16_t frequency) {
    // Calculate the prescaler and compare value based on the desired frequency
    uint32_t prescalerValue = F_CPU / (2UL * (frequency/2)) - 1;
    uint16_t compareValue = (uint16_t)(prescalerValue * (dutyCycle / 100.0));

    // Configure Timer/Counter1 for PWM generation
    TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Set non-inverting mode and Fast PWM mode (16-bit)
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10); // Fast PWM mode, no prescaler
    ICR1 = prescalerValue; // Set TOP value for the frequency
    OCR1A = compareValue; // Set compare value for the duty cycle

    // Configure the PWM pin as an output
    DDRB |= (1 << PB5);
}