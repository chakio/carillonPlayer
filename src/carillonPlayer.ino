#include <Servo.h>
#include <MIDI.h>
#include "Ws2822s.h"
#define NUM_PIXELS 10 // 使用するWS2822Sの数
#define LED_PIN 2 // WS2822SのDAIピンにつなげるArduinoのピン番号
#define ADR_PIN 1

#define sorenoidLeft 4
#define sorenoidRight 5
Ws2822s LED(LED_PIN, NUM_PIXELS);
Servo servoLeft;
Servo servoRight;
Servo servoCenter;
int sound = 0;
// MIDIからToneに変換-------------------------------------
int  m2t[127] = {
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,2,
3,4,5,6,7,8,9,10,11,12,
13,14,15,16,17,18,19,20,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0};

int targets[20][3][3];//どの音、センターの角度、手とセンター
int history[3];
int candidate[6];
int mini;
int minitarget;
int changeFlag=0;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi1);

double servoArgLeft;
double servoArgRight;
double servoArgCenter;
double l1 = 20;
double l2 = 220;
double d1,d2;


void setup() 
{
  for(int i=0;i<20;i++)
  {
    for(int j=0;j<3;j++)
    {
      for(int k=0;k<3;k++)
      {
        targets[i][j][k]=0;
      }
    }
  }
  //座標設定
  for(int i=0;i<12;i++)
  {
    targets[i][0][1]=115;
    targets[i+4][1][1]=89;
    targets[i+8][2][1]=65;
  }
  targets[0][0][0]=115;
  targets[1][0][0]=109;
  targets[2][0][0]=102;
  targets[3][0][0]=96;
  targets[4][0][0]=91;
  targets[5][0][0]=85;
  targets[6][0][2]=102;
  targets[7][0][2]=97;
  targets[8][0][2]=91;
  targets[9][0][2]=85;
  targets[10][0][2]=79;
  targets[11][0][2]=72;

  targets[4][1][0]=116;
  targets[5][1][0]=110;
  targets[6][1][0]=104;
  targets[7][1][0]=98;
  targets[8][1][0]=92;
  targets[9][1][0]=86;
  targets[10][1][2]=101;
  targets[11][1][2]=96;
  targets[12][1][2]=90;
  targets[13][1][2]=84;
  targets[14][1][2]=78;
  targets[15][1][2]=71;
  
  targets[8][2][0]=114;
  targets[9][2][0]=108;
  targets[10][2][0]=102;
  targets[11][2][0]=96;
  targets[12][2][0]=90;
  targets[13][2][0]=84;
  targets[14][2][2]=100;
  targets[15][2][2]=94;
  targets[16][2][2]=89;
  targets[17][2][2]=83;
  targets[18][2][2]=76;
  targets[19][2][2]=69;
  

  midi1.begin();
  Serial.begin(9600);
  pinMode(sorenoidLeft,OUTPUT);
  pinMode(sorenoidRight,OUTPUT);
  servoLeft.attach(6);
  servoRight.attach(7);
  servoCenter.attach(3);
  servoLeft.write(90);
  servoRight.write(90);
  servoCenter.write(88);
  for(int i=0;i<3;i++)
  {
    history[i]=90;
  }
}

void loop() {
  uint8_t code;
  uint8_t ch,data1,data2;
  ch = 1;   //Read channel set;
  if (midi1.read()) {
    midi1.setInputChannel(ch);  // Channel
    switch(midi1.getType()) {
      case midi::NoteOn:
        data1 = midi1.getData1();    // note no
        if(m2t[data1]!=0)
        {
         changeFlag = 1;
         sound = m2t[data1]-1;
        }      
        break;
      default:
        break;
    }                     
  }
 
  if(changeFlag==1)
  {
    //候補挙げ
    for(int i=0;i<3;i++)
    {
      for(int j=0;j<2;j++)
      {
        if(targets[sound][i][j] !=0 && targets[sound][i][j+1] !=0)
        {
          if(j==1)
          {
            candidate[2*i+j]=max(abs(targets[sound][i][j]-history[j])*1,abs(targets[sound][i][j+1]-history[j+1]));
          }
          else
          {
            candidate[2*i+j]=max(abs(targets[sound][i][j]-history[j]),abs(targets[sound][i][j+1]-history[j+1])*1);
          }
        }
        else
        {
          candidate[2*i+j]=360;
        }
      }  
    }

    //最小値のターゲット見つける
    mini=400;
    minitarget=0;
    for(int i=0;i<6;i++)
    {
      if(candidate[i]<=mini)
      {
        minitarget=i;
        mini=candidate[i];
      }
    }
  
    //サーボ移動
    if(minitarget%2==0)//左手
    {
     servoLeft.write(targets[sound][(int)minitarget/2][0]);
     servoCenter.write(targets[sound][(int)minitarget/2][1]);
     delay(100);
     history[0]=targets[sound][(int)minitarget/2][0];
     history[1]=targets[sound][(int)minitarget/2][1];
     digitalWrite(sorenoidLeft,HIGH);
     delay(30);
     digitalWrite(sorenoidLeft,LOW);
    }
    else//右手
    {
      servoRight.write(targets[sound][(int)minitarget/2][2]);
      servoCenter.write(targets[sound][(int)minitarget/2][1]);
      delay(100);
      history[2]=targets[sound][(int)minitarget/2][2];
      history[1]=targets[sound][(int)minitarget/2][1];
      digitalWrite(sorenoidRight,HIGH);
      delay(30);
      digitalWrite(sorenoidRight,LOW);
    }
    changeFlag=0;
  }
}
