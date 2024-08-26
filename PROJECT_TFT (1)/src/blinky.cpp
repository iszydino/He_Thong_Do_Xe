#define BLYNK_TEMPLATE_ID "TMPL6bEwGWp7S"
#define BLYNK_TEMPLATE_NAME "Park Car"
#define BLYNK_AUTH_TOKEN "YokLkLetIQ2JzY7GYkuxqh4BGu8SDlRZ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32_SSL.h>
#include "blinky.h"

char auth[] = "YokLkLetIQ2JzY7GYkuxqh4BGu8SDlRZ";
char ssid[] = "Manhngu";
char pass[] = "27012005";

void connect_blynk()
{
     Blynk.begin(auth, ssid, pass);
}

void truyendulieu_blynk()
{
     for (int i = 0; i < 5; i++)
     {
          value[i] = digitalRead(park_car[i]);
     }
}

void xuatdulieu_blynk()
{
     Blynk.run();

     if (value[0] == 0)
     {
          Blynk.virtualWrite(V0, 1);
     }
     else if(value[0] == 1)
     {
          Blynk.virtualWrite(V0, 0);
     }

     if (value[1] == 0)
     {
          Blynk.virtualWrite(V1, 1);
     }
     else if(value[1]==1)
     {
          Blynk.virtualWrite(V1, 0);
     }

     if (value[2] == 0)
     {
          Blynk.virtualWrite(V2, 1);
     }
     else if(value[2]==1)
     {
          Blynk.virtualWrite(V2, 0);
     }

     if (value[3] == 0)
     {
          Blynk.virtualWrite(V3, 1);
     }
     else if(value[3] == 1)
     {
          Blynk.virtualWrite(V3, 0);
     }

     if (value[4] == 0)
     {
          Blynk.virtualWrite(V4, 1);
     }
     else if(value[4] == 1)
     {
          Blynk.virtualWrite(V4, 0);
     }
}


