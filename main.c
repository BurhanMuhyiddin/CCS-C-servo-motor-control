//this is main.c

#include <config.h>
#include <servo_control.c>

void main()
{
    //Attach servo motor to the port D pin 0
    servo_attach('D', 0);

    while(TRUE)
    {
        //Write angle to the servo motor
        servo_write(50);
    }
}
