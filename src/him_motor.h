/***********************************************************************
* FILENAME:
*       him_motor.h
*
* DESCRIPTION:
*       HIm Arduino Motor Control Routines.
*
* NOTES:
*       This library was written just for fun.
*
* AUTHOR:
*       Sven Himstedt
*
* COPYRIGHT: 
*       Sven Himstedt 2017, All rights reserved.
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

#ifndef _HIM_MOTOR_H_
#define _HIM_MOTOR_H_



#define HIM_MOTOR_FORWARD   1
#define HIM_MOTOR_BACKWARD -1
#define HIM_MOTOR_STOP      0



class HimMotor
{
public:
    HimMotor(unsigned int pin_inA, unsigned int pin_inB, bool invert);
    ~HimMotor();

    bool isInitialized();

    void halt();

protected:
    void setDirection(int direction);

    bool m_initialized;
    bool m_invert;

    unsigned int m_pin_inA;
    unsigned int m_pin_inB;
};



class HimMotorSimple : public HimMotor
{
public:
    HimMotorSimple(unsigned int pin_inA, unsigned int pin_inB, bool invert);
    ~HimMotorSimple();

    void stop();

    void forward();
    void backward();
};



class HimMotorPWM : public HimMotor
{
public:
    HimMotorPWM(unsigned int pin_inA, unsigned int pin_inB, bool invert);
    ~HimMotorPWM();

    virtual int stop() = 0;
    virtual int setSpeed(int value) = 0;

    int incrementSpeed(int value);
    int decrementSpeed(int value);
    int getSpeed();

    void setMaxSpeed(int value);

protected:
    int m_speed;
    int m_speed_max;
};



class HimMotor3PinPWM : public HimMotorPWM
{
public:
    HimMotor3PinPWM(unsigned int pin_inA, unsigned int pin_inB, unsigned int pin_en, bool invert);
    ~HimMotor3PinPWM();

    int stop();
    int setSpeed(int value);

private:
    unsigned int m_pin_en;
};



class HimMotor2PinPWM : public HimMotorPWM
{
public:
    HimMotor2PinPWM(unsigned int pin_inA, unsigned int pin_inB, bool invert);
    ~HimMotor2PinPWM();

    int stop();
    int setSpeed(int value);
};



#endif /* _HIM_MOTOR_H_ */
