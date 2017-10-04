#include "SerialHalfDuplex.h"

class KrsServo
{
  public:
    /**
     * コンストラクタ
     * @param TX NCで接続しない
     * @param RX NCで接続しない
     * @param servoID 接続するサーボID
     * @param baudrate defaultだと115200bps
     **/
    KrsServo(PinName tx,PinName rx,int servoID,int baudrate = 115200);

    /**
     * サーボに角度を指令する
     * @param postion 指令するポジションの値
     * @return 現在のポジションの値
     **/
    int setPosition(int postion);

    /**
     * サーボを脱力して現在のサーボの角度をポジションで受け取る
     * @return 現在のポジションの値
     **/
    int setFree();

    /**
     * サーボに角度を指令する
     * @param 指令する角度の値
     * @return 現在のポジションの値
     **/
    int setAngle(float deg);

    /**
     * サーボの角度をポジションで取得する(ICS.3.6のみ) 
     * @return 現在のポジションの値
     **/
    int getPosition();

    /**
     * サーボの角度を弧度で取得する(ICS.3.6のみ) 
     * @return 現在のポジション(弧度)の値
     **/
    int getAngle();

    //ポジションを度へ変換する
    float pos2deg(int position);    
    //度からポジションへ変換する
    int deg2pos(float deg);
  private:
    /**
    * コマンドを送受信する
    **/
    bool write(char *txData,int txLen,char *rxData,int rxLen);
    SerialHalfDuplex ics;
    int _servoID;
};
