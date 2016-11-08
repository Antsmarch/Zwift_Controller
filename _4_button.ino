/*Remote for three modes for controller

*/

#include <Bounce.h>
#include <EEPROM.h>

const int button1 = 20; //pu
const int button2 = 19; //chat
const int button3 = 18; //discord
const int button4 = 17; //toggle

Bounce pushbutton1 = Bounce(button1, 50); //set debounce time
Bounce pushbutton2 = Bounce(button2, 50);
Bounce pushbutton3 = Bounce(button3, 50);
Bounce pushbutton4 = Bounce(button4, 50);

byte RES;

void setup() {
  Check_EEPROM();
  pinMode(button1, INPUT_PULLUP);  //Power Up
  pinMode(button2, INPUT_PULLUP);  //Chat text selections
  pinMode(button3, INPUT_PULLUP);  //Chat discord
  pinMode(button4, INPUT_PULLUP);  //toggle modes
  pinMode(13, OUTPUT);  //This is indication that a button has been recieved !!
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);

  //RES = EEPROM.read(0); //read first EEPROM address
  //if (RES !=

}//end setup

int Conv = 1; //default
int V = 0;  //view
int xt = 0;  //exit variable
int TOGGLE = 0;  //toggle between modes
int EXIT;
int s = 0; //mode state
int Yp = 380; //value to shift mouse up or down (GLOBAL) //
int Yr = 6600; //default coordinates
int Xr = 17400; //default coordinates
int XY = 0; //coordinates state
int mc = 0; //mouse click state
int dir = 0; //direction click state
byte STARTUP = 0;


void loop() {

  if (STARTUP == 0)
  {
    Keyboard.print("mSelect Resolution");
    delay(1500);
    ESC();
    Set_Monitor_Res();
    Keyboard.print("mSelect Aero Bike");
    delay(1500);
    ESC();
    Set_Aero_Bike();
    STARTUP = 1;
    Yp = Yp/Conv; //value to shift mouse up or down (GLOBAL) //
    Yr = Yr/Conv; //default coordinates
    Xr = Xr/Conv; //default coordinates
  }

  if (TOGGLE == 0)//Chat mode
  {
    PushUpdate();
    if (s == 0)
    {
      Keyboard.print("M");
      Keyboard.print("CHAT MODE");
      delay(750); //do nothing for 0.5 seconds
      ESC();
    }//end if statement


    if (pushbutton1.fallingEdge())
    {
      PU(); //throw down the powerup
    }
    if (pushbutton2.fallingEdge())
    {
      Chat();
    }
    if (digitalRead(18) == LOW)
    {
      Discord();
      delay(250); //delay to not spam with key while button is depressed
    }
    if (pushbutton4.fallingEdge())
    {
      TOGGLE = 1;
      BLINK();
    }
    s = 1; //update s so Chat mode doesnt appear
  }//end mode 0

  if (TOGGLE == 1)//View mode
  {
    PushUpdate();
    if (s == 1)
    {
      Keyboard.print("M");
      Keyboard.print("View Mode");
      delay(750); //do nothing for 0.5 seconds
      ESC();
    }
    if (pushbutton1.fallingEdge())
    {
      PU(); //throw down the powerup
    }
    if (pushbutton2.fallingEdge())
    {
      View(); //Cycle through the views
    }
    if (pushbutton3.fallingEdge())
    {
      F10();  //Screen shot
    }
    if (pushbutton4.fallingEdge())
    {
      TOGGLE = 2;
    }
    s = 2; //update s so Chat mode doesnt appear
  }//end mode 1

  if (TOGGLE == 2)//Direction Mode
  {
    PushUpdate();
    if (s == 2)
    {
      Keyboard.print("M");
      Keyboard.print("Direction Mode");
      delay(750); //do nothing for 0.5 seconds
      ESC();
      dir = 0; //
    }

    if (pushbutton1.fallingEdge())
    {
      PU(); //throw down the powerup
    }
    if (pushbutton2.fallingEdge())
    {
      if (dir == 0)
      {
        Left();
      }

      if (dir == 1)
      {
        Up();
      }
      if (dir == 2)
      {
        Right();
      }
      dir++;
      if (dir == 3)
      {
        dir = 0; //reset dir to 0
      }

    }// end up right leght
    if (pushbutton3.fallingEdge())
    {
      Down(); //Reverse
    }
    if (pushbutton4.fallingEdge())
    {
      TOGGLE = 3;
    }
    s = 3; //update s so Chat mode doesnt appear
  }//end more view mode

  if (TOGGLE == 3) //Equipment Mode
  {
    PushUpdate();
    if (s == 3)
    {
      Keyboard.print("M");
      Keyboard.print("Equipment Mode");
      delay(750); //do nothing for 0.5 seconds
      ESC();
    }

    if (pushbutton2.fallingEdge())
    {
      TT();
    }
    if (pushbutton3.fallingEdge())
    {
      Madone();
    }

    if (pushbutton4.fallingEdge())
    {
      TOGGLE = 4; //
    }
    s = 4; //update s so Chat mode doesnt appear
  }//end Equipment Mode

  if (TOGGLE == 4)
  {
    if (s == 4)
    {
      Keyboard.print("M");
      Keyboard.print("See Rider Mode");
      delay(750); //do nothing for 0.5 seconds
      ESC();
      Mouse.moveTo(Xr, Yr); //set position to rider side
      delay(150);
    }

    if (XY == 0)
    {
      Xr = 14500/Conv; //set to default Xcoord value
      Yr = 5500/Conv; //set to default Ycoord value
      XY = 1; //set to 1
    }
    PushUpdate();
    if (pushbutton1.fallingEdge())
    {
      if (mc == 1)
      {
        Mouse.click();
        delay(50);
      }

      if (mc == 2)
      {
        RideOn();
      }
      if (mc == 0)
      {
        GoBack();
      }
      mc++;
      if (mc == 3)
      {
        mc = 0;
      }

    }//end push button1 if

    if (pushbutton2.fallingEdge())
    {
      Mouse_Up();
      mc = 1;
    }

    if (pushbutton3.fallingEdge())
    {
      Mouse_Down();
      mc = 1;
    }

    if (pushbutton4.fallingEdge())
    {
      TOGGLE = 0; //return to mode 1
      Xr = 1450/Conv; //set to original
      Yr = 550/Conv; //set to original
      XY = 0; //set to 0
      
    }
    s = 0; //set s to 0
  }//end view rider mode
}//end void loop


char ViewString[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
void View()
{
  if (V == 11)
  {
    V = 0; //reset View to 0
  }
  Keyboard.print(ViewString[V]); //view
  V++;
}

void ET() //Exit and Toggle
{
  EXIT = 1;
  TOGGLE++;
}

void Discord()
{
  Keyboard.set_key1(KEYPAD_ASTERIX);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(10);
  BLINK();
}

int newcount = 99;
int count = 0;

void Chat()
{
  newcount = 99;
  count = 0;
  xt = 0;
  while (xt == 0)
  {
    PushUpdate();  //poll buttons
    if (pushbutton2.fallingEdge())
    {
      count++;
      ESC();
    }
    if (count != newcount)
    {
      switch (count)
      {
        case 0:
          Keyboard.print("mI'll Pull");
          break;


        case 1:
          Keyboard.print("mNext Pull");
          break;

        case 2:
          Keyboard.print("mLet's work together and chase them down");
          break;

        case 3:
          Keyboard.print("mMy legs are Toast!");
          break;

        case 4:
          Keyboard.print("mGo Go Go");
          break;

        case 5:
          Keyboard.print("mZpower please do not lead group");
          break;

        case 6:
          Keyboard.print("mAll I have are canned responses");
          break;

        case 7:
          Keyboard.print("mOk");
          break;

        case 8:
          Keyboard.print("mRegroup");
          break;


        case 9:
          ENTER();
          xt = 1; //exit chat mode
          break;


      } //end switch case statements
      newcount = count; //update count
    } //end if statemene to enter switch statement
    if (pushbutton1.fallingEdge())
    {
      ENTER();
      xt = 1; //exit chat mode
    }
  }//end while loop
}//end chat dialog function

void ENTER()
{
  Keyboard.set_key1(KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(10);
}

void ESC()
{
  Keyboard.set_key2(KEY_ESC);
  Keyboard.send_now();
  Keyboard.set_key2(0);
  Keyboard.send_now();
  delay(10);
}

void F10()
{
  Keyboard.set_key3(KEY_F10);
  Keyboard.send_now();
  Keyboard.set_key3(0);
  Keyboard.send_now();
  delay(10);

}

void del()
{
  Keyboard.set_key4(KEY_BACKSPACE);
  Keyboard.send_now();
  Keyboard.set_key4(0);
  Keyboard.send_now();
  delay(10);
}

void Down()
{
  Keyboard.set_key5(KEY_DOWN);
  Keyboard.send_now();
  Keyboard.set_key5(0);
  Keyboard.send_now();
  delay(10);
}

void Up()
{
  Keyboard.set_key5(KEY_UP);
  Keyboard.send_now();
  Keyboard.set_key5(0);
  Keyboard.send_now();
  delay(10);
}

void Right()
{
  Keyboard.set_key5(KEY_RIGHT);
  Keyboard.send_now();
  Keyboard.set_key5(0);
  Keyboard.send_now();
  delay(10);
}

void Left()
{
  Keyboard.set_key5(KEY_LEFT);
  Keyboard.send_now();
  Keyboard.set_key5(0);
  Keyboard.send_now();
  delay(10);
}

void PU()
{
  Keyboard.set_key5(KEY_SPACE);
  Keyboard.send_now();
  Keyboard.set_key5(0);
  Keyboard.send_now();
  delay(10);
  BLINK();
}

void PushUpdate()
{
  pushbutton1.update();
  pushbutton2.update();
  pushbutton3.update();
  pushbutton4.update();
}
int X1 = 16480;
int Y1 = 2380;
int X2 = 16480;
int Y2 = 2900;
int X3 = 15750;
int Y3 = 3040;
int X4 = 10280;
int Y4 = 9700;

void TT()
{
  X1 = X1/ Conv;
  Y1 = Y1 / Conv;
  X2 = X2 / Conv;
  Y2 = Y2 / Conv;
  X3 = X3 / Conv;
  Y3 = Y3 / Conv;
  X4 = X4 / Conv;
  Y4 = Y4 / Conv;

  Keyboard.print("T"); //equipment menu
  delay(500);
  Mouse.moveTo(X1, Y1); //(1648,238)(1372,206)
  Mouse.set_buttons(1, 0, 0); //hold left button
  delay(250);
  Mouse.moveTo(X2, Y2); //move the mouse while holding (1648, 290) (1372, 247)
  delay(500);
  Mouse.set_buttons(0, 0, 0); //release left button
  delay(150);
  Mouse.moveTo(X3, Y3); //Select TT Bike (1575,304) (1205,256)
  delay(150);
  Mouse.click(); //left click
  Mouse.moveTo(X4, Y4); //move to okay button (1028,970) (857,808)
  delay(150);
  Mouse.click();
}//end TT function

int Mx1 = 15380;
int My1 = 3890;
int Mx2 = 10280;
int My2 = 9700;

void Madone()
{
  Mx1 = 15380/Conv;
  My1 = 3890/Conv;
  Mx2 = 10280/Conv;
  My2 = 9700/Conv;
  Keyboard.print("T"); //equipment menu
  delay(250);
  Mouse.moveTo(Mx1, My1); //Madone (1538, 389) (1190, 320)
  delay(150);
  Mouse.click(); //left click
  delay(150);
  Mouse.moveTo(Mx2, My2); //move to okay button (1028,970) (857,808)
  delay(150);
  Mouse.click(); //left click
}

int Rx1 = 10390;
int Ry1 = 1710;

void RideOn()
{
  Rx1 = 10390 / Conv;
  Ry1 = 1710 / Conv;
  Mouse.moveTo(Rx1, Ry1);  //move to Ride on location //(1039, 171) (794, 136)
  delay(50);
  Mouse.click();
  delay(50);
  Mouse.moveTo(Xr, Yr);
}

int Gx1 = 540;
int Gy1 = 10500;

void GoBack()
{
  Gx1 = 540 / Conv;
  Gy1 = 10500 / Conv;
  Mouse.moveTo(Gx1, Gy1);  //return to rider (54, 1050) (50, 822)
  delay(50);
  Mouse.click();
  delay(50);
  Mouse.moveTo(Xr, Yr);
}

void BLINK()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}


void Mouse_Up()
{
  Yr = Yr + Yp;
  Mouse.moveTo(Xr, Yr);
  delay(50);
  mc = 1;
}

void Mouse_Down()
{
  Yr = Yr - Yp;
  Mouse.moveTo(Xr, Yr);
  delay(50);
  mc = 1;
}

byte ResChoice = 0;
byte Res_Default = 0;
int TIME = 0;
int T_offset;
int E_Choice;

void Set_Monitor_Res()
{
  T_offset = millis();
  while (TIME < 10000)
  {
    PushUpdate();
    if (pushbutton1.fallingEdge())
    {
      Conv = 10;
      Mouse.screenSize(1920, 1080);
      ResChoice = 0;
      Keyboard.print("m1080p Selected");
      delay(1000);
      ESC();
      Res_Default = 1;
    }
    if (pushbutton2.fallingEdge())
    {
      Conv = 12;
      Mouse.screenSize(1600, 900);
      ResChoice = 1;
      Keyboard.print("m1600x900 Selected");
      delay(1000);
      ESC();
      Res_Default = 1;
    }
    if (pushbutton3.fallingEdge())
    {
      Conv = 10;
      Mouse.screenSize(1280, 720);
      Keyboard.print("m720p Selected");
      delay(1000);
      ESC();
      //some other resolution like 4K
      ResChoice = 2;
      Res_Default = 1;
    }
    if (pushbutton4.fallingEdge())
    {
      Conv = 10;
      Mouse.screenSize(3840, 2060);
      Keyboard.print("m4k Selected");
      delay(1000);
      ESC();
      //some other resolotion like 720p
      ResChoice = 3;
      Res_Default = 1;
    }
    TIME = millis() - T_offset; //subtract current time by time stamp entering function
  }//end while statement

  if (Res_Default == 0)
  {
    ResChoice = EEPROM.read(0);
    switch (ResChoice)
    {
      case 0: //1080p
        Mouse.screenSize(1920, 1080);
        Conv = 10;
        break;

      case 1: //standard laptop resolution
        Mouse.screenSize(1600, 900);
        Conv = 12;
        break;

      case 2: //720p
        Mouse.screenSize(1280, 720);
        Conv = 15;
        break;

      case 3: //4k
        Mouse.screenSize(3840, 2160);
        Conv = 10;
        break;

    }//end switch case statement
  }//end default no choice statement

  if (Res_Default == 1)
  {
    EEPROM.write(0, ResChoice);
    switch (ResChoice)
    {
      case 0:
        Mouse.screenSize(1920, 1080);
        Conv = 10;
        break;

      case 1:
        Mouse.screenSize(1600, 900);
        Conv = 12;
        break;

      case 2:
        Mouse.screenSize(1280, 720);
        Conv = 15;
        break;

      case 3:
        Mouse.screenSize(3840, 2160);
        Conv = 10;
        break;

    }//end switch case
    Keyboard.print(ResChoice);
    Keyboard.print(Conv);
  }//end if Res_Default statement

}//end resolution function

void Check_EEPROM() //Check to see if EEPROM has been written to
{
  if (EEPROM.read(1) != 1)
  {
    EEPROM.write(1, 1); //write eeprom has been written to
    EEPROM.write(0, 0); //write default 1080p res to address 0
  }
}

void Z_Aero()
{
  //XY Coordinates for Zwift Aero
  Keyboard.print("mZwift Aero Selected");
}

void S5()
{
  //XY Coordinates for S5
  Keyboard.print("mCervelo S5 Selected");
}

void Canyon()
{
  //XY Coordinates for Canyon Aero bike
  Keyboard.print("mCanyon Aero Selected");
}

void Z_Carbon()
{
  //XY Coordinates for Canyon Aero bike
  Keyboard.print("mZwift Carbon Selected");
}

Set_Aero_Bike()
{
  //stuff here
}
