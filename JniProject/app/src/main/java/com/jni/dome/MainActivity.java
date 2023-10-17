package com.jni.dome;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.UUID;


/**
 * Jni开发的一般流程
 * 1.定义好本地的native方法
 * 2.javah命令生成.h的头文件
 * 3.拷贝 xxx.n\jni_md.h\jni.h到编译器中并依赖进入
 * 4.实现头文件中的native方法
 * 5.生成动态库，java引入即可
 */

// System.loadLibrary :加载apk中libs目录下的.so库
// System.load :加载具体路径上的.so库,去服务器上下载  再进行加载(data/data)

public class MainActivity extends AppCompatActivity {

    /********************Java属性、方法 - Start*********************/

    public String name = "Delusion";

    public static int age = 13;

    public static String getUuid(){
        return UUID.randomUUID().toString();
    }


    public int onPlus(int number1, int number2) {
        int num = number1 + number2;
        Log.e("----->", "onPlus: " + num);
        return num;
    }
    /********************Java属性、方法 - End*********************/


    /**********************JNI 方法 - Start***********************/

    static {
        System.loadLibrary("native-lib");
    }

    public native String stringFromJNI();

    public native Point createPoint();

    public native void changeName();

    public native static void changeAge();

    public native void callPlusMethod();

    public static native String callUuidMethod();

    /**********************JNI 方法 - End***********************/


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Point point = createPoint();
        Log.e("---->", "Point: x--->"+point.x+"   y--->"+point.y);
        changeName();
        Log.e("---->", "changeName:"+name);
        changeAge();
        Log.e("---->", "changeAge:"+age);
        callPlusMethod();
        String  uuid= callUuidMethod();
        Log.e("---->", "callUuidMethod:"+uuid);


        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }
}
