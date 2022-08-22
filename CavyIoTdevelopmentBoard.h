// public domain libray for interfacing firmware ------------version 0.01
#ifndef CavyIoT_h
#define CavyIoT_h
#include "Arduino.h"
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ARC32) || (ARDUINO >= 100 && ARDUINO < 10500)
#include <SoftwareSerial.h>
#endif
#include <stdlib.h>
#include <avr/wdt.h>

class CavyIoT
{
public:
  CavyIoT();
  //-------------------------------------------------------------------------------------------------------------
  String Status;
  void loop();
  void softwareReset(uint8_t prescaller);
  void SetPort(int r, int t, int reset);
  bool DefineButtonLables(String S1, String S1action1, String S1action2,
                          String S2, String S2action1, String S2action2,
                          String S3, String S3action1, String S3action2,
                          String S4, String S4action1, String S4action2);
  bool StartDevice(String wifissid, String wifipassword, String username, String password, String device);
  void ShowDemo(String wifissid, String wifipassword, String username, String password, String device);
  void UpdateSensorData(String S1, String S1value, String S1unit,
                        String S2, String S2value, String S2unit);
  void UpdateSensorData(String S1, String S1value, String S1unit,
                        String S2, String S2value, String S2unit,
                        String S3, String S3value, String S3unit);
  void UpdateSensorData(String S1, String S1value, String S1unit,
                        String S2, String S2value, String S2unit,
                        String S3, String S3value, String S3unit,
                        String S4, String S4value, String S4unit);

  //------------------------------------------------------------------  -----------------------------------------

private:
  bool user_port_defined = false;
  int _r = 0;
  int _t = 1;
  long int _baud = 9600;
  int readline(int readch, char *buffer, int len)
  {
    static int pos = 0;
    int rpos;

    if (readch > 0)
    {
      switch (readch)
      {
      case '\n':
        rpos = pos;
        pos = 0;     // Reset position index ready for next time
        return rpos; // Ignore new-lines
        break;
      case ('\r'): // Return on CR
        rpos = pos;
        pos = 0; // Reset position index ready for next time
        return rpos;
        break;
      default:
        if (pos < len - 1)
        {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
      }
    }
    // No end of line has been found, so return -1.
    return -1;
  }
};

//---------------------------------------------------------------------------------------------------------------------------------

CavyIoT::CavyIoT(){}; // Constructor
//=================================================================================================================================
void CavyIoT::SetPort(int r, int t, int reset)
{
  _r = r;
  _t = t;
  pinMode(reset, OUTPUT);
  digitalWrite(reset, LOW);
  delay(10);
  digitalWrite(reset, HIGH);
  delay(200);
}

bool CavyIoT::StartDevice(String wifissid, String wifipassword,
                          String username, String password, String device)
{
  String command = "<StartDevice(";
  command = command + wifissid + "," + wifipassword + "," + username + "," + password + "," + device + ")>";
  String recd;
  static char buffer[80];
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
  for (int i = 0; i < 25; i++)
  {
    while (readline(port.read(), buffer, 80) < 0)
      ;
    recd = buffer;
    if (recd.startsWith("<", 0) && recd.endsWith(">Ok!"))
    {
      String message = recd.substring((recd.indexOf('<') + 1), (recd.indexOf('>')));
      i = 26;
      Serial.println("Device Started !");
      return (true);
    }
    if (recd.startsWith("<", 0) && recd.endsWith(">Error!"))
    {
      Serial.println("Oops Error !");
      return (false);
    }
  }
}
bool CavyIoT::DefineButtonLables(String S1, String S1action1, String S1action2,
                                 String S2, String S2action1, String S2action2,
                                 String S3, String S3action1, String S3action2,
                                 String S4, String S4action1, String S4action2)
{
  String command = "<DefineButtonLables(";
  command = command +
            S1 + "," + S1action1 + "," + S1action2 + "," +
            S2 + "," + S2action1 + "," + S2action2 + "," +
            S3 + "," + S3action1 + "," + S3action2 + "," +
            S4 + "," + S4action1 + "," + S4action2 + "," +
            ")>";
  String recd;
  static char buffer[80];
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
  for (int i = 0; i < 25; i++)
  {
    while (readline(port.read(), buffer, 80) < 0)
      ;
    recd = buffer;
    if (recd.startsWith("<", 0) && recd.endsWith(">Ok!"))
    {
      String message = recd.substring((recd.indexOf('<') + 1), (recd.indexOf('>')));
      i = 26;
      Serial.println("Lables Defined!");
      return (true);
    }
    if (recd.startsWith("<", 0) && recd.endsWith(">Error!"))
    {
      Serial.println("Oops Error !");
      return (false);
    }
  }
}
//------------------
void CavyIoT::UpdateSensorData(String S1, String S1value, String S1unit,
                               String S2, String S2value, String S2unit)
{
  String command = "<UpdateSensorData(";
  command = command +
            S1 + "," + S1value + "," + S1unit + "," +
            S2 + "," + S2value + "," + S2unit +
            ")>";
  String recd;
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
}
//----------------------
//------------------
void CavyIoT::UpdateSensorData(String S1, String S1value, String S1unit,
                               String S2, String S2value, String S2unit,
                               String S3, String S3value, String S3unit)
{
  String command = "<UpdateSensorData(";
  command = command +
            S1 + "," + S1value + "," + S1unit + "," +
            S2 + "," + S2value + "," + S2unit + "," +
            S3 + "," + S3value + "," + S3unit +
            ")>";
  String recd;
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
}
//----------------------
void CavyIoT::UpdateSensorData(String S1, String S1value, String S1unit,
                               String S2, String S2value, String S2unit,
                               String S3, String S3value, String S3unit,
                               String S4, String S4value, String S4unit)
{
  String command = "<UpdateSensorData(";
  command = command +
            S1 + "," + S1value + "," + S1unit + "," +
            S2 + "," + S2value + "," + S2unit + "," +
            S3 + "," + S3value + "," + S3unit + "," +
            S4 + "," + S4value + "," + S4unit +
            ")>";
  String recd;
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
}
void CavyIoT::ShowDemo(String wifissid, String wifipassword,
                       String username, String password, String device)
{
  String command = "<ShowDemo(";
  command = command + wifissid + "," + wifipassword + "," + username + "," + password + "," + device + ")>";
  String recd;
  String message;
  static char buffer[100];
  SoftwareSerial port(_r, _t);
  port.begin(_baud);
  port.println(command);
  Serial.println("Wait ......System is checking configuration...");
  for (int i = 0; i < 25; i++)
  {
    while (readline(port.read(), buffer, 100) < 0)
      ;
    recd = buffer;
    if (recd.startsWith("<", 0) && recd.endsWith(">Ok!"))
    {
      message = recd.substring((recd.indexOf('<') + 1), (recd.indexOf('>')));
      i = 26;
    }
  }
  Serial.println("done..");
  Serial.println(message);
}
void CavyIoT::softwareReset(uint8_t prescaller)
{
  wdt_enable(prescaller);
  while (1)
  {
  }
}

void CavyIoT::loop()
{
  String recd;
  static char buffer[500];
  SoftwareSerial port(_r, _t);
  port.begin(_baud);

  for (int i = 0; i < 25; i++)
  {
    while (readline(port.read(), buffer, 500) < 0)
      ;
    recd = buffer;
    if (recd.startsWith("<", 0) && recd.endsWith(">Ok!"))
    {
      String message = recd.substring((recd.indexOf('<') + 1), (recd.indexOf('>')));
      i = 26; // Serial.print("Device Status:");Serial.println(message);
      if (message == "RESET")
        softwareReset(WDTO_60MS);
      Status = message;
    }
  }
}

#endif