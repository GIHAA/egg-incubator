#include "CavyIoTdevelopmentBoard.h"
CavyIoT myIoTdevice;
long t, h, s, p;
int rx = 10;
int tx = 11;
int rst = 13;
void setup()
{
    Serial.begin(9600);
    myIoTdevice.SetPort(rx, tx, rst);
    Serial.println("Setting device buttons!.");

    myIoTdevice.DefineButtonLables("heater", "on", "off",
                                   "motor", "on", "off",
                                   "bulb", "on", "  off",
                                   "fan", "on", "off");
    Serial.println("Wait for a while to connect!.");
    myIoTdevice.StartDevice("WifiSSID", "WiFipassword", /*CavyIoT--->*/ "Username", "password", "device");
}
void loop()
{

    Serial.println("Device Status:-" + myIoTdevice.Status); // Prints the current status of Buttons & working mode of device on Remote Control Panel.
                                                            //  https://developers.cavyiot.com/cpanel.php
    myIoTdevice.loop(); // Updates the Status variable.

    t = random(39, 42);
    h = random(22, 44);
    s = random(5, 12);
    p = random(40, 44);
    myIoTdevice.UpdateSensorData("Temperature", String(t), "C",
                                 "humidity", String(h), "Rh",
                                 "Speed", String(s), "km/hr",
                                 "pressure", String(p), "Psi"

    );
}