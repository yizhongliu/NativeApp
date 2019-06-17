package com.iview.android.nativelib;

public class NativeUnity {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();

    public static native void controlLeftRightMotor(int steps, int direction, int delay);
}
