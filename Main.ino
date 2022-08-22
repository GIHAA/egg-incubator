#define SERVO 9
Servo myservo;

DHT dht(8, DHT11);

//---------------For communication with DevBoard ----------------------------
#define rx 10
#define tx 11
#define rst 13

CavyIoT myIoTdevice;

int routerScheme = 1;
long int current_time;
long int start_time = millis();
long int Interval = 6 * 60 * 60 * 1000; // Timer Six hour
// Interval=60000;//Uncomment for checking servo functions TimerOne minute.

float temp;
float hum;
int angle;

void setup()
{
    Serial.begin(9600);
    myIoTdevice.SetPort(rx, tx, rst);
    dht.begin();
    myservo.write(45);
    myservo.attach(9);
    myservo.detach();

    Serial.println("Setting device buttons!.");
    myIoTdevice.DefineButtonLables("Heat", "on", "off",
                                   "Humid", "on", "off",
                                   "E-Fan", "on", "  off",
                                   "I-Fan", "on", "off");
    Serial.println("Wait for a while to connect!");

    myIoTdevice.StartDevice
        /*Your Wi-Fi router->*/ ("WiFi-SSID", "WiFi-password",
        /* CavyIoT------>*/ "Username", "password", "Device"); //
}

void loop()
{
    current_time = millis();
    myIoTdevice.loop();
    Serial.println("Device Status:-" + myIoTdevice.Status);

    //---------Read values from sensor and angle of servo---------------------

    temp = dht.readTemperature();
    hum = dht.readHumidity();

    //----------------Sending data to server----------------------------------
    myIoTdevice.UpdateSensorData("Temperature", String(temp), "C",
                                 "humidity", String(hum), "Rh",
                                 "Tray-Angle", String(angle), "deg");
    //-------------------Check timer for router scheme-------------------------
    if (current_time - start_time > Interval)
    {
        myservo.attach(9);
        rotateTray(routerScheme);
        start_time = current_time;
        // Uncomment for debug
        // Serial.print("Servo is working ,router scheme :");
        // Serial.println(routerScheme);
    }

} 
void rotateTray(int scheme)
{
    int current_position = myservo.read();

    if (scheme == 0)
    {
        for (current_position; current_position <= 45; current_position += 1)
        {
            angle = current_position;
            myservo.write(current_position); 
            delay(50);                      
        }
    }
    if (scheme == 1)
    {
        for (current_position; current_position <= 90; current_position += 1)
        {
            angle = current_position;
            myservo.write(current_position); 
            delay(50);                      
        }
    }
    if (scheme == 2)
    {
        for (current_position; current_position >= 45; current_position -= 1)
        {
            angle = current_position;
            myservo.write(current_position); 
            delay(50);                       
        }
    }
    if (scheme == 3)
    {

        for (current_position; current_position >= 0; current_position -= 1)
        {
            angle = current_position;
            myservo.write(current_position); 
            delay(50);                       
        }
    }

    routerScheme = routerScheme + 1;
    myservo.detach();
    if (routerScheme > 3)
        routerScheme = 0;
}