#include "mbed.h"
#include "KrsServo.h"
#include "SerialHalfDuplex.h"

//通信失敗した場合の試行回数
#define MAXTRY 5

KrsServo::KrsServo(PinName tx,PinName rx,int id,int baudrate):ics(tx,rx)
{
  ics.baud(baudrate);
  _servoID = id;
}

bool KrsServo::write(char *txData,int txLen,char *rxData,int rxLen)
{
  int rxSize = 0;//受信した数

  for (int i = 0; i< txLen; i++) {
    ics.putc(txData[i]);
  }
  for (int i = 0; i< rxLen; i++) {
    rxData[i]= ics.getc();
    rxSize++;
  }

  //受信数確認
  if (rxSize != rxLen) {
    return false;
  }

  wait_ms(5);
  return true;
}

int KrsServo::setPosition(int postion)
{
  //コマンドの成否(今のプログラムだと失敗すると止まるので成否を確認する必要がない)
  //bool exit_status = 0;

  //受信したデータ
  int data = 0;
  //送受信するデータのバイト数
  const int txLen = 3,rxLen = 3;
  char txData[txLen], rxData[rxLen];

  txData[0] = 0x80 | _servoID;
  txData[1] = (unsigned char)(postion >> 7 & 0x7F);
  txData[2] = (unsigned char)(postion & 0x7F);

  write(txData,txLen,rxData,rxLen);

  data = (int)(rxData[1] & 0x7F);
  data = (data << 7) + (int)rxData[2];

  return data;
}

int KrsServo::setFree()
{
  return setPosition(0);
}

int KrsServo::setAngle(float deg){
  return setPosition(deg2pos(deg));
}

int KrsServo::getPosition()
{
  //コマンドの成否
  //bool exit_status = 0;
  //受信するデータ
  int data = 0;
  //送受信するコマンドのバイト数
  const int txLen = 3,rxLen = 4;
  char txData[txLen], rxData[rxLen];

  write(txData,txLen,rxData,rxLen);

  data = (int)(rxData[2] & 0x7F);
  data = (data << 7) + (int)rxData[3];

  return data;
}

float KrsServo::pos2deg(int pos)
{
  pos = pos - 7500;
  float deg = pos  / 29.633;

  return deg;
}

int KrsServo::deg2pos(float deg)
{
  int pos = deg * 29.633;
  pos = pos + 7500;

  return pos;
}
