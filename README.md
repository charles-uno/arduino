

I've been using the Arduino web app. I believe it loads the neopixel library under the hood -- not exactly sure how else to get access to that library. You should be able to see my same code here: https://create.arduino.cc/editor/charles_uno/f7381318-9554-4b2c-85b3-cdabbfb8b64d

This code is meant for a 14-element neopixel strip. Connect the neopixel strip to `5V`, `GND`, and digital out `6`. Connect the button to `5V`, `GND`, and digital output `2`.

You should see a pulse of light which travels along the length of the 14-pixel strip, while also changing color through an off-white rainbow. Behavior can be configured via the following variables up top:

- `F_COLOR` -- Frequency of color change, in rainbows per second.
- `F_PULSE` -- Frequency of the pulse. Increase this to have pulses more often.
- `L_PULSE` -- Length of the pulse, in pixels.
- `V_PULSE` -- Velocity of the pulse, in pixels per second.

The time step is set by `DT`, in milliseconds. The current value seems to work pretty well. Increasing the time step will make the code less computationally demanding, but it might look choppy.
