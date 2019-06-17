//
// Created by llm on 19-6-17.
//

#ifndef NATIVEAPP_MOTOR_CONTROL_H
#define NATIVEAPP_MOTOR_CONTROL_H

extern "C"{
#include <sys/ioctl.h>
}

#define MOTO_UP_DOWN_ENABLE_GPIO       66
#define MOTO_UP_DOWN_STEP_GPIO         65
#define MOTO_UP_DOWN_DIR_GPIO          67

#define MOTO_LEFT_RIGHT_ENABLE_GPIO    69
#define MOTO_LEFT_RIGHT_STEP_GPIO      70
#define MOTO_LEFT_RIGHT_DIR_GPIO       71

#define MOTOR_ENABLE 0
#define MOTOR_DISABLE 1

struct motor_data{
    int gpio;
    int state;
};
#define MOTOR_MAGIC 'x'
#define VS_SET_GPIO   		 _IOWR(MOTOR_MAGIC, 0x0, struct motor_data)
#define VS_GET_GPIO   		 _IOWR(MOTOR_MAGIC, 0x1, struct motor_data)
#define VS_SET_MOTOR_ENABLE  _IOWR(MOTOR_MAGIC, 0x2, struct motor_data)

#endif //NATIVEAPP_MOTOR_CONTROL_H
