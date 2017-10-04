#include "mbed.h"
#include "KrsServo.h"

int main() {

    Serial pc(USBTX,USBRX);
    //TXをD1,RXをD0，サーボのIDを0に設定
    KrsServo servo(D1,D0,0);
    
    while(1) {
        //90度に角度を設定
        servo.setAngle(90);
        wait(10);
        //270度に角度を設定
        servo.setAngle(270);
        wait(10);
        //サーボを脱力して角度を設定
        int angle = servo.setFree();
        pc.printf("%d\r\n",angle);
        wait(10);
    }
}
