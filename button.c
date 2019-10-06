// Based on NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <math.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NEOPIXEL_PIN 6
#define BUTTON_PIN 2
#define LED_PIN 13

#define NUMPIXELS 14

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define PI 3.14159
// Frequency of color oscillation, cycles per second
#define F_COLOR 0.7
// Frequency of pulses, cycles per second
#define F_PULSE 1.6
// Length of pulse, in pixels
#define L_PULSE 9
// Speed of pulse, in pixels per second
#define V_PULSE 9.1
// Time step, in ms
#define DT 3

#define BRIGHTNESS 1.0

void setup() {
    // For Adafruit Trinket, more is needed here
    pixels.begin();
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

}


int rgb(int t) {
    // Accept a time in ms. Return a color channel (0 to 255).
    int wt = int(t*F_COLOR*255/1000.) % 255;
    if(wt < 85) {return 85 + 2*wt;}
    if(wt < 170) {return 255-2*(wt-85);}
    return 85;
}


double alpha(int t, int i) {
    // Accept a time in ms and an integer position. Return the intensity of that location at that time
    float deg = int(180*F_PULSE*(t/1000. - i*1./L_PULSE)) % 360;
    if(deg < 180) {return 0;}
    return BRIGHTNESS*sin(deg*PI/180)*sin(deg*PI/180);
}


int* rgba(int t, int i) {
    static int channels[3];
    channels[0] = int(rgb(t)*alpha(t, i));
    channels[1] = int(rgb(t+85)*alpha(t, i));
    channels[2] = int(rgb(t+170)*alpha(t, i));
    return channels;
}


void loop() {
    int t = 0;
    int button_state = 0;

    while(true) {

        button_state = digitalRead(BUTTON_PIN);

        if(button_state == HIGH) {
            digitalWrite(LED_PIN, HIGH);
        } else {
            digitalWrite(LED_PIN, LOW);
        }

        pixels.clear();
        t += DT;

        if(button_state == LOW) {
            for(int i=0; i<NUMPIXELS; i++) {
                int* channels = rgba(t, i);
                pixels.setPixelColor(i, pixels.Color(channels[0], channels[1], channels[2]));
            }
        }

        pixels.show();

        delay(DT);
    }
}
