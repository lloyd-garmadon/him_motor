/***********************************************************************
* FILENAME:
*       him_stepmotor.h
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

#ifndef _HIM_STEP_MOTOR_H_
#define _HIM_STEP_MOTOR_H_



#define HIM_STEP_MOTOR_MODE_FULL2PHASE   0
#define HIM_STEP_MOTOR_MODE_FULL1PHASE   1
#define HIM_STEP_MOTOR_MODE_HALFPHASE    2

#define HIM_STEP_MOTOR_PHASE_TABLE_0 {1, 0, 0, 0 }
#define HIM_STEP_MOTOR_PHASE_TABLE_1 {1, 1, 0, 0 }
#define HIM_STEP_MOTOR_PHASE_TABLE_2 {0, 1, 0, 0 }
#define HIM_STEP_MOTOR_PHASE_TABLE_3 {0, 1, 1, 0 }
#define HIM_STEP_MOTOR_PHASE_TABLE_4 {0, 0, 1, 0 }
#define HIM_STEP_MOTOR_PHASE_TABLE_5 {0, 0, 1, 1}
#define HIM_STEP_MOTOR_PHASE_TABLE_6 {0, 0, 0, 1}
#define HIM_STEP_MOTOR_PHASE_TABLE_7 {1, 0, 0, 1}
#define HIM_STEP_MOTOR_PHASE_TABLE_SIZE 8

#define HIM_STEP_MOTOR_PHASE_TABLE_START_FULL2PHASE    1
#define HIM_STEP_MOTOR_PHASE_TABLE_END_FULL2PHASE      7
#define HIM_STEP_MOTOR_PHASE_TABLE_INC_FULL2PHASE      2
#define HIM_STEP_MOTOR_PHASE_TABLE_START_FULL1PHASE    0
#define HIM_STEP_MOTOR_PHASE_TABLE_END_FULL1PHASE      6
#define HIM_STEP_MOTOR_PHASE_TABLE_INC_FULL1PHASE      2
#define HIM_STEP_MOTOR_PHASE_TABLE_START_HALFPHASE     0
#define HIM_STEP_MOTOR_PHASE_TABLE_END_HALFPHASE       7
#define HIM_STEP_MOTOR_PHASE_TABLE_INC_HALFPHASE       2

#define HIM_STEP_MOTOR_FORWARD   1
#define HIM_STEP_MOTOR_BACKWARD -1
#define HIM_STEP_MOTOR_STOP      0



class HimStepMotor
{
public:
    HimStepMotor(unsigned int pin_1, unsigned int pin_2, unsigned int pin_3, unsigned int pin_4, int mode, bool invert);
    ~HimStepMotor();

    void set_direction(int dir);
    int get_direction();

    void step_forward();
    void step_backward();

    void step();

private:
    bool m_invert;
    int m_mode;

    unsigned int m_pin_1;
    unsigned int m_pin_2;
    unsigned int m_pin_3;
    unsigned int m_pin_4;

    int m_phase;
    int m_phase_start;
    int m_phase_end;
    int m_phase_increment;
    static int s_phases_table[HIM_STEP_MOTOR_PHASE_TABLE_SIZE][4];

    int m_direction;
};



#endif /* _HIM_STEP_MOTOR_H_ */
