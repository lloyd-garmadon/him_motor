/***********************************************************************
* FILENAME:
*       him_motor.cpp
*
* DESCRIPTION:
*       Him Arduino Motor Control Routines.
*
* NOTES:
*       This library was written just for fun.
*
* AUTHOR:
*       Sven Himstedt
*
* COPYRIGHT: 
*       Sven Himstedt 2016, All rights reserved.
*
* LICENSE:
*       This library is free software.
*       You can redistribute it and/or modify it.
*       But give credit or you are an asshole.
*
* START DATE:
*       2016/07/01
*
* CHANGES:
*
***********************************************************************/

#define HIM_LIBRARY_COMPILE

#include "Arduino.h"

#include "him_motor.h"



HimMotor::HimMotor(unsigned int pin_inA, unsigned int pin_inB, bool invert) :
    m_invert(invert),
    m_pin_inA(pin_inA),
    m_pin_inB(pin_inB),
    m_initialized(true)
{
    if(m_initialized) {
        pinMode(m_pin_inA, OUTPUT);
        pinMode(m_pin_inB, OUTPUT);
    } 
    
    halt();
}

HimMotor::~HimMotor()
{
    halt();
}

bool HimMotor::isInitialized()
{
    return m_initialized;
}

void HimMotor::halt()
{
    if(m_initialized) {
        digitalWrite(m_pin_inA, 0);
        digitalWrite(m_pin_inB, 0);
    }
}

void HimMotor::setDirection(int direction)
{
    // invert direction  pins A/B
    //   0        1        1/0
    //   0       -1        0/1
    //   1        1        0/1
    //   1       -1        1/0
    if(m_initialized) {
        if((!m_invert && (direction > 0)) || (m_invert && (direction < 0))) {
            digitalWrite(m_pin_inA, 1);
            digitalWrite(m_pin_inB, 0);
        } else if((!m_invert && (direction < 0)) || (m_invert && (direction > 0))) {
            digitalWrite(m_pin_inA, 0);
            digitalWrite(m_pin_inB, 1);
        } else {
            digitalWrite(m_pin_inA, 0);
            digitalWrite(m_pin_inB, 0);
        }
    }
}





HimMotorSimple::HimMotorSimple(unsigned int pin_inA, unsigned int pin_inB, bool invert) :
    HimMotor(pin_inA, pin_inB, invert)
{
}

HimMotorSimple::~HimMotorSimple()
{
}

void HimMotorSimple::stop()
{
    setDirection(HIM_MOTOR_STOP);
}

void HimMotorSimple::forward()
{
    setDirection(HIM_MOTOR_FORWARD);
}

void HimMotorSimple::backward()
{
    setDirection(HIM_MOTOR_BACKWARD);
}



HimMotorPWM::HimMotorPWM(unsigned int pin_inA, unsigned int pin_inB, bool invert) : 
    HimMotor(pin_inA, pin_inB, invert),
    m_speed_max(100),
    m_speed(0)
{
}

HimMotorPWM::~HimMotorPWM()
{
}

void HimMotorPWM::setMaxSpeed(int value)
{
    m_speed = m_speed * value / m_speed_max;
    m_speed_max = value;
}


int HimMotorPWM::incrementSpeed(int value)
{
    return setSpeed(m_speed + value);
}


int HimMotorPWM::decrementSpeed(int value)
{
    return setSpeed(m_speed - value);
}


int HimMotorPWM::getSpeed()
{
    return m_speed;
}
    

HimMotor3PinPWM::HimMotor3PinPWM(unsigned int pin_inA, unsigned int pin_inB, unsigned int pin_en, bool invert) : 
    HimMotorPWM(pin_inA, pin_inB, invert),
    m_pin_en(pin_en)
{
    // check for a pwm pin correct pins
    switch(m_pin_en) {
        case 5:     //  Timer 0
        case 6:     //  Timer 0
        case 9:     //  Timer 1
        case 10:    //  Timer 1
        case 3:     //  Timer 2
        case 11:    //  Timer 2
            break;
        default:
            m_initialized = false;
    }
    
    if(m_initialized) {
        pinMode(m_pin_en, OUTPUT);
    }
    
    stop();
}

HimMotor3PinPWM::~HimMotor3PinPWM()
{
}

int HimMotor3PinPWM::stop()
{
    if(!m_initialized) {
        return 0;
    } else {
        m_speed = 0;

        analogWrite(m_pin_en, 0);

        return m_speed;
    }
}


int HimMotor3PinPWM::setSpeed(int value)
{
    if(!m_initialized) {
        return 0;
    } else {
        if(value > m_speed_max) {
            m_speed = m_speed_max;
        } else if(value < -m_speed_max) {
            m_speed = -m_speed_max;
        } else {
            m_speed = value;
        }

        int pwm = ((m_speed < 0) ? -m_speed : m_speed) * 255 / m_speed_max;
        int dir = ((m_speed < 0) ? HIM_MOTOR_BACKWARD : HIM_MOTOR_FORWARD);

        analogWrite(m_pin_en, pwm);
        setDirection(dir);

        return m_speed;
    }
}






HimMotor2PinPWM::HimMotor2PinPWM(unsigned int pin_inA, unsigned int pin_inB, bool invert) : 
    HimMotorPWM(pin_inA, pin_inB, invert)
{
    // check for a pwm pin correct pins
    switch(pin_inA) {
        case 5:     //  Timer 0
        case 6:     //  Timer 0
        case 9:     //  Timer 1
        case 10:    //  Timer 1
        case 3:     //  Timer 2
        case 11:    //  Timer 2
            break;
        default:
            m_initialized = false;
    }
    
    stop();
}

HimMotor2PinPWM::~HimMotor2PinPWM()
{
}

int HimMotor2PinPWM::stop()
{
    m_speed = 0;

    halt();

    return m_speed;
}


int HimMotor2PinPWM::setSpeed(int value)
{
    if(!m_initialized) {
        return 0;
    } else {
        if(value > m_speed_max) {
            m_speed = m_speed_max;
        } else if(value < -m_speed_max) {
            m_speed = -m_speed_max;
        } else {
            m_speed = value;
        }

        int speed = (m_invert) ? m_speed : -m_speed;
        int pwm   = ((speed < 0) ? m_speed_max + speed : speed) * 255 / m_speed_max;
        int dir   = ((speed < 0) ? 1                       : 0      );

        analogWrite(m_pin_inA, pwm);
        digitalWrite(m_pin_inB, dir);

        return m_speed;
    }
}

