#include "light_uav.h"

Light_uav::Light_uav(QObject *parent): QObject(parent)
{
    qDebug() << __FUNCTION__;
    // this->led_timer = new QTimer(this);
    // this->led_timer->setSingleShot(true);
    // this->led_timer->setInterval(250);
    //this->run();
    blinking_loop();
}

Light_uav::~Light_uav()
{
    this->deleteLater();
}

void Light_uav::sleep()
{
    qDebug() << __FUNCTION__;
    led_timer = new QTimer;
    loop = new QEventLoop;

    if (shutdown == true)
    {
        led_timer->stop();
    }
    else
    {
        connect(led_timer,      SIGNAL(timeout()),       loop,       SLOT(quit()));
        led_timer->start(500);
        loop->exec();
    }

}

void Light_uav::blinking_loop()
{
    qDebug() << __FUNCTION__;
    connect(this, SIGNAL(blink_loop()), this, SLOT(blinking()));
}

////////
void Light_uav::blinking() //red , blue loop
{
    //qDebug() << __FUNCTION__;
    //if continue to blink     
    if(blink)
    {
        if(previous_led)//prev led is red
        {
            if(previous_led_state)//on
            {
                previous_led_state = false;
                previous_led = true;
                emit blink_loop();
                //led_timer->start();
            }
            else //off
            { 
                setpoint_led_blue();
                sleep(); //pause 500ms
                previous_led_state = true;
                previous_led = false;
                emit blink_loop();
                //led_timer->start();
            }
        }
        else    //prev led is blue
        {
            if(previous_led_state)//on
            {
                previous_led_state = false;
                previous_led = false;
                emit blink_loop();
                //led_timer->start();
            }
            else //off
            { 
                setpoint_led_red();
                sleep();
                previous_led_state = true;
                previous_led = true;
                emit blink_loop();
                //led_timer->start();
            }
        }
    }
    else 
    {
        qDebug() << "LED Loop stop";
    }
 }  

////////
void Light_uav::setpoint_detected_led()
{
    //qDebug() << __FUNCTION__;
    blink = true;
    blinking();
}

void Light_uav::setpoint_led_off() //1
{
    qDebug() << __FUNCTION__;
    blink = false;
        Data_Manager::rgb[0] = 0;   //r max 31
        Data_Manager::rgb[1] = 0;   //g max 63,
        Data_Manager::rgb[2] = 0;   //b max 31
        Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );
        emit setpoint_updated();
}

void Light_uav::setpoint_led_red() //2
{
    qDebug() << __FUNCTION__;
        Data_Manager::rgb[0] = 6;       //r min 2, max 31
        Data_Manager::rgb[1] = 0;       //g min2, max 63,
        Data_Manager::rgb[2] = 0;       //b min 2, max 31
        Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );
        emit setpoint_updated();
}

void Light_uav::setpoint_led_green() //3
{
    qDebug() << __FUNCTION__;
         for (int i =0; i <= 5; i++)
     {
    //update led setpoint
    Data_Manager::rgb[0] = 0;       //r min 2, max 31
    Data_Manager::rgb[1] = 12;      //g min2, max 63,
    Data_Manager::rgb[2] = 0;       //b min 2, max 31
    Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );

    // qDebug() << "temp_r = " << hex << temp_r << "; pwm_sp = " << hex << Data_Manager::pwm_sp;
    emit setpoint_updated();
     }
}

void Light_uav::setpoint_led_blue() //4
{
    qDebug() << __FUNCTION__;
        Data_Manager::rgb[0] = 0;       //r min 2, max 31
        Data_Manager::rgb[1] = 0;       //g min2, max 63,
        Data_Manager::rgb[2] = 6;       //b min 2, max 31
        Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );
        emit setpoint_updated();
}

void Light_uav::setpoint_led_yellow() //5
{
    qDebug() << __FUNCTION__;

         for (int i =0; i <= 5; i++)
     {
    //update led setpoint
    Data_Manager::rgb[0] = 6;       //r min 2, max 31
    Data_Manager::rgb[1] = 12;      //g min2, max 63,
    Data_Manager::rgb[2] = 0;       //b min 2, max 31
    Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );

    // qDebug() << "temp_r = " << hex << temp_r << "; pwm_sp = " << hex << Data_Manager::pwm_sp;
    emit setpoint_updated();
     }
}
     
void Light_uav::setpoint_led_cyan() //6
{
    qDebug() << __FUNCTION__;

         for (int i =0; i <= 5; i++)
     {
    //update led setpoint
    Data_Manager::rgb[0] = 0;       //r min 2, max 31
    Data_Manager::rgb[1] = 12;       //g min2, max 63,
    Data_Manager::rgb[2] = 6;       //b min 2, max 31
    Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );

    // qDebug() << "temp_r = " << hex << temp_r << "; pwm_sp = " << hex << Data_Manager::pwm_sp;
    emit setpoint_updated();
     }
}

void Light_uav::setpoint_led_purple() //7
{
    qDebug() << __FUNCTION__;

         for (int i =0; i <= 5; i++)
     {
    //update led setpoint
    Data_Manager::rgb[0] = 6;       //r min 2, max 31
    Data_Manager::rgb[1] = 0;       //g min2, max 63,
    Data_Manager::rgb[2] = 6;       //b min 2, max 31
    Data_Manager::pwm_sp =  (static_cast<uint16_t>(Data_Manager::rgb[0]) << 11 ) | (static_cast<uint16_t>(Data_Manager::rgb[1] & 0x3F) << 5 ) | (static_cast<uint16_t>(Data_Manager::rgb[2] & 0X1F) );

    // qDebug() << "temp_r = " << hex << temp_r << "; pwm_sp = " << hex << Data_Manager::pwm_sp;
    emit setpoint_updated();
     }
}

void Light_uav::shutdown_led()
{
    qDebug() << __FUNCTION__;
    shutdown = true;
    setpoint_led_off();
    sleep();
}



