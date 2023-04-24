#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Set PB0 as output
    DDRB |= (1 << PB0);
    
    while (1)
    {
        // Toggle PB0
        PORTB ^= (1 << PB0);
        
        // Delay for 500ms
        _delay_ms(500);
    }
    
    return 0;
}
