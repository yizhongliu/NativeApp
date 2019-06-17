//
// Created by llm on 19-6-17.
//

#include <jni.h>
#include<iostream>
#include<string>

#include <android/log.h>
#include <fstream>


#include "motor_control.h"

extern "C"{
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
}

#define LEFT_RIGHT_MOTOR_DEV     "/dev/motor_gpio_left_right"


#define LOG_TAG    "left_rightor_mot"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)c

static int motor_fd;

bool control_motor_gpio(int gpio, int state)
{
    struct motor_data data;
    data.gpio = gpio;
    data.state = state;
    if((ioctl(motor_fd, (int)VS_SET_MOTOR_ENABLE, &data)) < 0)
    {
        LOGE("%s  %d %d error", __FUNCTION__, gpio, state);
        return false;
    }
    return true;
}

void set_motor_enable(int enable)
{
    control_motor_gpio(MOTO_LEFT_RIGHT_ENABLE_GPIO, enable);
}

void control_motor(int steps, int direction, int delay) {

    control_motor_gpio(MOTO_LEFT_RIGHT_DIR_GPIO, direction);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = delay;
    int motor_out_pwm = 0;
    control_motor_gpio(MOTO_LEFT_RIGHT_STEP_GPIO, motor_out_pwm);
    while(steps--)
    {
        motor_out_pwm = !motor_out_pwm;
        control_motor_gpio(MOTO_LEFT_RIGHT_STEP_GPIO, motor_out_pwm);
        tv.tv_sec = 0;
        tv.tv_usec = delay;
        select(0, NULL, NULL, NULL, &tv);
        motor_out_pwm = !motor_out_pwm;
        control_motor_gpio(MOTO_LEFT_RIGHT_STEP_GPIO, motor_out_pwm);
        tv.tv_sec = 0;
        tv.tv_usec = delay;
        select(0, NULL, NULL, NULL, &tv);
    }
}

extern "C" JNIEXPORT void
Java_com_iview_android_nativelib_NativeUnity_controlLeftRightMotor(
        JNIEnv *env,
        jobject /* this */,
        jint steps,
        jint direction,
        jint delay) {

   int motor_fd = open(LEFT_RIGHT_MOTOR_DEV, O_RDWR);
   if (motor_fd < 0) {
       LOGE("Can't open file %s", LEFT_RIGHT_MOTOR_DEV);
       return;
   }

   set_motor_enable(MOTOR_ENABLE);

   control_motor(steps, direction, delay);

   set_motor_enable(MOTOR_DISABLE);

   close(motor_fd);
}