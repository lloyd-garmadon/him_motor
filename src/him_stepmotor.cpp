/***********************************************************************
* FILENAME:
*       him_stepmotor.cpp
*
* DESCRIPTION:
*       Him Arduino Step Motor Routines.
*
* NOTES:
*       This library was written just for fun.
*
* AUTHOR:
*       Sven Himstedt
*
* COPYRIGHT: 
*       Sven Himstedt 2018, All rights reserved.
*
* LICENSE:
*       This library is free software.
*       You can redistribute it and/or modify it.
*       But give credit or you are an asshole.
*
* START DATE:
*       2018/01/01
*
* CHANGES:
*
***********************************************************************/

#define HIM_LIBRARY_COMPILE

#include "Arduino.h"

#include "him_stepmotor.h"



int HimStepMotor::s_phases_table[HIM_STEP_MOTOR_PHASE_TABLE_SIZE][4] = { 
    HIM_STEP_MOTOR_PHASE_TABLE_0,
    HIM_STEP_MOTOR_PHASE_TABLE_1,
    HIM_STEP_MOTOR_PHASE_TABLE_2,
    HIM_STEP_MOTOR_PHASE_TABLE_3,
    HIM_STEP_MOTOR_PHASE_TABLE_4,
    HIM_STEP_MOTOR_PHASE_TABLE_5,
    HIM_STEP_MOTOR_PHASE_TABLE_6,
    HIM_STEP_MOTOR_PHASE_TABLE_7 };



HimStepMotor::HimStepMotor(unsigned int pin_1, unsigned int pin_2, unsigned int pin_3, unsigned int pin_4, int mode, bool invert) :
    m_invert(invert),
    m_mode(mode),
    m_pin_1(pin_1),
    m_pin_2(pin_2),
    m_pin_3(pin_3),
    m_pin_4(pin_4)
{
    pinMode(m_pin_1, OUTPUT);
    pinMode(m_pin_2, OUTPUT);
    pinMode(m_pin_3, OUTPUT);
    pinMode(m_pin_4, OUTPUT);

    if(mode == HIM_STEP_MOTOR_MODE_HALFPHASE) {
        m_phase_start     = HIM_STEP_MOTOR_PHASE_TABLE_START_HALFPHASE;
        m_phase_end       = HIM_STEP_MOTOR_PHASE_TABLE_END_HALFPHASE;
        m_phase_increment = HIM_STEP_MOTOR_PHASE_TABLE_INC_HALFPHASE;
    } else if(mode == HIM_STEP_MOTOR_MODE_FULL1PHASE) {
        m_phase_start     = HIM_STEP_MOTOR_PHASE_TABLE_START_FULL1PHASE;
        m_phase_end       = HIM_STEP_MOTOR_PHASE_TABLE_END_FULL1PHASE;
        m_phase_increment = HIM_STEP_MOTOR_PHASE_TABLE_INC_FULL1PHASE;
    } else {
        m_phase_start     = HIM_STEP_MOTOR_PHASE_TABLE_START_FULL2PHASE;
        m_phase_end       = HIM_STEP_MOTOR_PHASE_TABLE_END_FULL2PHASE;
        m_phase_increment = HIM_STEP_MOTOR_PHASE_TABLE_INC_FULL2PHASE;
    }
    m_phase = m_phase_start;
    
    step_forward();
    set_direction(HIM_STEP_MOTOR_STOP);
}

HimStepMotor::~HimStepMotor()
{
}

void HimStepMotor::set_direction(int dir)
{
    if((!m_invert && (dir == HIM_STEP_MOTOR_FORWARD)) || (m_invert && (dir == HIM_STEP_MOTOR_BACKWARD))) {
        m_direction = HIM_STEP_MOTOR_FORWARD;
    } else if((!m_invert && (dir == HIM_STEP_MOTOR_BACKWARD)) || (m_invert && (dir == HIM_STEP_MOTOR_FORWARD))) {
        m_direction = HIM_STEP_MOTOR_BACKWARD;
    } else {
        m_direction = HIM_STEP_MOTOR_STOP;
    }
}

int HimStepMotor::get_direction()
{
    if((!m_invert && (m_direction == HIM_STEP_MOTOR_FORWARD)) || (m_invert && (m_direction == HIM_STEP_MOTOR_BACKWARD))) {
        return HIM_STEP_MOTOR_FORWARD;
    } else if((!m_invert && (m_direction == HIM_STEP_MOTOR_BACKWARD)) || (m_invert && (m_direction == HIM_STEP_MOTOR_FORWARD))) {
        return HIM_STEP_MOTOR_BACKWARD;
    } else {
        return m_direction;
    }
}

void HimStepMotor::step()
{
    if(m_direction == HIM_STEP_MOTOR_FORWARD) {
        m_phase += m_phase_increment;
        if(m_phase > m_phase_end) {
            m_phase = m_phase_start;
        }
    } else if(m_direction == HIM_STEP_MOTOR_BACKWARD) {
        m_phase -= m_phase_increment;
        if(m_phase < m_phase_start) {
            m_phase = m_phase_end;
        }
    }
    if(m_direction != HIM_STEP_MOTOR_STOP) {
        digitalWrite(m_pin_1, s_phases_table[m_phase][0]);
        digitalWrite(m_pin_2, s_phases_table[m_phase][1]);
        digitalWrite(m_pin_3, s_phases_table[m_phase][2]);
        digitalWrite(m_pin_4, s_phases_table[m_phase][3]);
    }
}

void HimStepMotor::step_forward()
{
    set_direction(HIM_STEP_MOTOR_FORWARD);
    step();
}

void HimStepMotor::step_backward()
{
    set_direction(HIM_STEP_MOTOR_BACKWARD);
    step();
}
