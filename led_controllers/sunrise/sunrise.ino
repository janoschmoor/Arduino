// the idea of this file is to build a lights animation that runs on < 150 leds, where over the period of 30 minutes 3 dots spawn:
// yellow, red to blue or something. they move slowly and can blend inbetween pixels (subpixel rendering)
// when they move along the strip they pull the led target value closer to their own which chould also be a way
// of morphing between their own values. 
// this strip will be mounted under the bed ;)

#include <FastLED.h>
#define NUM_LEDS 60 // 60
CRGB leds[NUM_LEDS];
CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];

long last_time;
float fade = 0.2; // 0.1 fades absolute 10% per second

class Dot {
  private:
    float position;
    float velocity;
    CRGB color;

  public:
    Dot(float startPos, float startVel, CRGB startColor) {
      position = startPos;
      velocity = startVel;
      color = startColor;
    }

    void update(float dt) {
      position = (position + velocity * dt);
      if (position > (float) NUM_LEDS - 0.5 || position < 0.5) {
        velocity *= -1;
        position = (position + 2.0 * velocity * dt);
      }
    }

    void render(float dt) {

      int px = ((int) position);

      float distance = (position - (float) px);
      if (velocity > 0) {
        distance = 1-distance;
      }
      float intensity = easing(distance);

      brightness[px] = max(intensity, brightness[px]);

      float blendamt = 0.02;

      targets[px] = blend(targets[px], color, blendamt*255);

      // Serial.println(distance);
      
      // float render_dist = 2;

      // for (int px = (int) (position - render_dist) + 1; px < (int) (position + render_dist)+1; px++) {
        
      //   if (px < -0.001 || px >= NUM_LEDS ) {continue;}
        
      //   // for each pixel within the renderdistance

      //   float distance = (px - position) / (render_dist / 2.0);

      //   if ((distance < 0.0 && velocity > 0.0) || (distance > 0.0 && velocity < 0.0)) {continue;}

      //   float intensity = easing(distance);
      //   intensity = intensity > 0.01 ? intensity : 0.0;

      //   //leds[px] = blend(CRGB::Black, color, (int) (intensity * 255));

      //   targets[px] = blend(targets[px], color,3);
      //   brightness[px] = ((brightness[px])>(intensity)?(brightness[px]):(intensity));
      // }
    }

    //    Helper
    float easing(float x) {
      float res;

      //double sided quad
      //res = (1 + -1*(x*x));
      
      //double sided linear
      //res = abs(x) <= 1.0 ? 1.0 - abs(x) : 0.0;

      // one sided
      if (x < 0) return 0.0;
      // res = 1.0 - x*x; // quad fast light up
      res = (x-1)*(x-1); // quad slow light up
      // res = (x-1)*(x-1)*(x-1); // cube slow light up
      res = constrain(res, 0.0, 1.0);

      return res >= 0.0 ? res : 0.0;
    }
};

Dot dots[] = {
  Dot(NUM_LEDS / 2, -1.0, CHSV(60, 255, 255)),
  Dot(NUM_LEDS / 2, 1.8, CHSV(280, 255, 255)),
  Dot(NUM_LEDS / 2, 1.3, CHSV(0, 255, 255))
};

//Dot dot(0.0, 5.0, blend(CRGB::Purple, CRGB::Black, 0)); // Example dot object












void setup() {
  // Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  last_time = millis();
  // FastLED.setBrightness(100);
}


void loop() {

  float delta = ((float) millis() - (float) last_time) / 1000;
  last_time = millis();

  for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
    dots[i].update(delta);
    dots[i].render(delta);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = blend(CRGB::Black, targets[i], (int) (brightness[i] * 255));
    brightness[i] = max(brightness[i] - fade * delta, 0.0);
  }

  FastLED.show();
  delay(3); // Adjust the delay time as needed
}







