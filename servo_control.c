//this is servo_control.c

int servo_pin;
unsigned long CCPR = 0;
unsigned long current_period = 0;
const unsigned long total_period = 3750;

#INT_CCP1
void compare_CCP1_interrupt()
{
    if((current_period > 0) && (current_period < total_period))
    {
        if(input(servo_pin))
        {
            output_low(servo_pin);
            CCPR = total_period - current_period;
        }
        else
        {
            output_high(servo_pin);
            CCPR = current_period;
        }
    }
    else
    {
        if(current_period == total_period)  output_high(servo_pin);
        if(current_period == 0)             output_low(servo_pin);
    }

    CCP_1_HIGH = CCPR >> 8;
    CCP_1_LOW = CCPR;
}

void servo_attach(char servo_port_inp, int servo_pin_inp)
{
    if(servo_port_inp == 'B')
    {
        if(servo_pin_inp == 0)  servo_pin = PIN_B0;
        else if(servo_pin_inp == 1)  servo_pin = PIN_B1;
        else if(servo_pin_inp == 2)  servo_pin = PIN_B2;
        else if(servo_pin_inp == 3)  servo_pin = PIN_B3;
        else if(servo_pin_inp == 4)  servo_pin = PIN_B4;
        else if(servo_pin_inp == 5)  servo_pin = PIN_B5;
        else if(servo_pin_inp == 6)  servo_pin = PIN_B6;
        else if(servo_pin_inp == 7)  servo_pin = PIN_B7;
    }
    else if(servo_port_inp == 'C')
    {
        if(servo_pin_inp == 0)  servo_pin = PIN_C0;
        else if(servo_pin_inp == 1)  servo_pin = PIN_C1;
        else if(servo_pin_inp == 2)  servo_pin = PIN_C2;
        else if(servo_pin_inp == 3)  servo_pin = PIN_C3;
        else if(servo_pin_inp == 4)  servo_pin = PIN_C4;
        else if(servo_pin_inp == 5)  servo_pin = PIN_C5;
        else if(servo_pin_inp == 6)  servo_pin = PIN_C6;
        else if(servo_pin_inp == 7)  servo_pin = PIN_C7;
    }
    else if(servo_port_inp == 'D')
    {
        if(servo_pin_inp == 0)  servo_pin = PIN_D0;
        else if(servo_pin_inp == 1)  servo_pin = PIN_D1;
        else if(servo_pin_inp == 2)  servo_pin = PIN_D2;
        else if(servo_pin_inp == 3)  servo_pin = PIN_D3;
        else if(servo_pin_inp == 4)  servo_pin = PIN_D4;
        else if(servo_pin_inp == 5)  servo_pin = PIN_D5;
        else if(servo_pin_inp == 6)  servo_pin = PIN_D6;
        else if(servo_pin_inp == 7)  servo_pin = PIN_D7;
    }
    
    output_drive(servo_pin);
    output_low(servo_pin);
    
    CCPR = 0;
    
    setup_ccp1(CCP_COMPARE_RESET_TIMER);
    
    setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_8 );
    set_timer1(0);
    
    enable_interrupts(INT_CCP1);
    enable_interrupts(GLOBAL);
}

void servo_write(int angle)
{
    double on_time = (angle/180.0) + 1.0;
    current_period = total_period * (on_time / 20.0);
}
