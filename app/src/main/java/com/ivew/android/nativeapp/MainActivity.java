package com.ivew.android.nativeapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.iview.android.nativelib.NativeUnity;

public class MainActivity extends AppCompatActivity {

    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.text);
        textView.setText(NativeUnity.stringFromJNI());

        NativeUnity.controlLeftRightMotor(30, 0, 50);
    }
}
