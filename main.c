#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LedControl.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);                                                                              
int DIN = 11;
int CS = 7;
int CLK = 13;
int BUTTON_PIN = 12;
int BUTTON_GROUND = 10;
int LEDstat[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
int buttonControl = 1;
int pastTemp = 0;

LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
  pinMode(10, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  for (int i = 7; i >= 0; i--) {    // i is the y value
    for (int n = 0; n <= 7; n++) {  // n is the x vvalue
      lc.setLed(0, n, i, true);
      delay(10);
    }
  }
  for (int i = 0; i <= 15; i++) {
    lc.setIntensity(0, i);
    delay(50);
  }
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
}

//--------------------------------------turn off all LED---------------------
void turnOffLED() {
  lc.clearDisplay(0);
  for (int i = 0; i <= 7; i++) {
    for (int n = 0; n <= 7; n++) {
      LEDstat[n][i] = 0;
    }
  }
}

//--------------------------------------turn off all LED---------------------
int buttonTest() {
  int digitalButtonValue = digitalRead(10);
  if (LOW == digitalButtonValue) {
    buttonControl = buttonControl + 1;
    Serial.println(buttonControl);
    delay(500);
  }
  if (buttonControl >= 4) {
    buttonControl = 1;
    Serial.println(buttonControl);
    delay(500);
    turnOffLED();
  }
  return buttonControl;
}

//causes all pixels to fall down
void fall() {
  for (int i = 7; i >= 0; i--) {    // i is the y value
    for (int n = 0; n <= 7; n++) {  // n is the x vvalue
      if (LEDstat[n][i] == 1 && i != 0) {
        if (LEDstat[n][i - 1] == 0) {
          LEDstat[n][i] = 0;
          LEDstat[n][i - 1] = 1;

        } else if (LEDstat[n][i - 1] == 1) {
          // immediate bottom not empty

          if (n == 0) {
            if (LEDstat[n + 1][i - 1] == 0) {
              LEDstat[n][i] = 0;
              LEDstat[n + 1][i - 1] = 1;
            }
          } else if (n == 7) {
            if (LEDstat[n - 1][i - 1] == 0) {
              LEDstat[n][i] = 0;
              LEDstat[n - 1][i - 1] = 1;
            }
          } else {
            int ran = random(1, 3);  // numbers 1 and 2
            int leftside = 0;
            int rightside = 0;
            if (LEDstat[n - 1][i - 1] == 0) {
              leftside = 1;
            }
            if (LEDstat[n + 1][i - 1] == 0) {
              rightside = 2;
            }

            if (leftside != 0 && rightside != 0) {
              if (leftside == ran) {
                LEDstat[n][i] = 0;
                LEDstat[n - 1][i - 1] = 1;

              } else if (rightside == ran) {
                LEDstat[n][i] = 0;
                LEDstat[n + 1][i - 1] = 1;
              }
            } else if (leftside == 1) {
              LEDstat[n][i] = 0;
              LEDstat[n - 1][i - 1] = 1;

            } else if (rightside == 2) {
              LEDstat[n][i] = 0;
              LEDstat[n + 1][i - 1] = 1;
            }
          }
        }
      }

      if (LEDstat[n - 1][i - 1] == 1) {
        lc.setLed(0, n - 1, i - 1, true);
      }
      if (LEDstat[n][i] == 0) {
        lc.setLed(0, n, i, false);
      }
      if (LEDstat[n + 1][i - 1] == 1) {
        lc.setLed(0, n + 1, i - 1, true);
      }
      if (LEDstat[n][i - 1] == 1) {
        lc.setLed(0, n, i - 1, true);
      }
    }
  }

  for (int x = 4; x >= 0; x--) {
    for (int i = 7; i >= 0; i--) {    // i is the y value
      for (int n = 0; n <= 7; n++) {  // n is the x vvalue
        if (LEDstat[n][i] == 1 && i != 0) {
          if (LEDstat[n][i - 1] == 0) {
            LEDstat[n][i] = 0;
            LEDstat[n][i - 1] = 1;

          } else if (LEDstat[n][i - 1] == 1) {
            // immediate bottom not empty

            if (n == 0) {
              if (LEDstat[n + 1][i - 1] == 0) {
                LEDstat[n][i] = 0;
                LEDstat[n + 1][i - 1] = 1;
              }
            } else if (n == 7) {
              if (LEDstat[n - 1][i - 1] == 0) {
                LEDstat[n][i] = 0;
                LEDstat[n - 1][i - 1] = 1;
              }
            } else {
              int ran = random(1, 3);  // numbers 1 and 2
              int leftside = 0;
              int rightside = 0;
              if (LEDstat[n - 1][i - 1] == 0) {
                leftside = 1;
              }
              if (LEDstat[n + 1][i - 1] == 0) {
                rightside = 2;
              }

              if (leftside != 0 && rightside != 0) {
                if (leftside == ran) {
                  LEDstat[n][i] = 0;
                  LEDstat[n - 1][i - 1] = 1;

                } else if (rightside == ran) {
                  LEDstat[n][i] = 0;
                  LEDstat[n + 1][i - 1] = 1;
                }
              } else if (leftside == 1) {
                LEDstat[n][i] = 0;
                LEDstat[n - 1][i - 1] = 1;

              } else if (rightside == 2) {
                LEDstat[n][i] = 0;
                LEDstat[n + 1][i - 1] = 1;
              }
            }
          }
        }

        if (LEDstat[n - 1][i - 1] == 1) {
          lc.setLed(0, n - 1, i - 1, true);
        }
        if (LEDstat[n][i] == 0) {
          lc.setLed(0, n, i, false);
        }
        if (LEDstat[n + 1][i - 1] == 1) {
          lc.setLed(0, n + 1, i - 1, true);
        }
        if (LEDstat[n][i - 1] == 1) {
          lc.setLed(0, n, i - 1, true);
        }

      }
    }
  }
  delay(500);
}

//returns a random number for firework effect
int randomShift() { return (random(-2, 2)); }

//displays different patterns based on button presses
void pattern() {
  buttonTest();

  // HEART
  for (int i = 4; i <= 5; i++) {
    lc.setLed(0, 0, i, true);
    lc.setLed(0, 7, i, true);
    LEDstat[0][i] = 1;
    LEDstat[7][i] = 1;
  }
  for (int i = 2; i <= 6; i++) {
    lc.setLed(0, 1, i, true);
    lc.setLed(0, 6, i, true);
    LEDstat[1][i] = 1;
    LEDstat[6][i] = 1;
  }
  for (int i = 1; i <= 6; i++) {
    lc.setLed(0, 2, i, true);
    lc.setLed(0, 5, i, true);
    LEDstat[2][i] = 1;
    LEDstat[5][i] = 1;
  }
  for (int i = 0; i <= 5; i++) {
    lc.setLed(0, 3, i, true);
    lc.setLed(0, 4, i, true);
    LEDstat[3][i] = 1;
    LEDstat[4][i] = 1;
  }
  if (dht.readTemperature() >= 28 || dht.readTemperature() <= 15 || dht.readHumidity() >= 70) {
    fall();
  }
  delay(2000);
  turnOffLED();
  buttonTest();

  // Define car size
  int startX = -4;  // Start off-screen to the left
  int endX = 8;     // End off-screen to the right

  // Loop to make the car move horizontally across the screen
  for (int x = startX; x <= endX; x++) {
    // Draw the car body (top and bottom rows)
    lc.setLed(0, x, 1, true);      // Top-left corner
    lc.setLed(0, x + 1, 1, true);  // Top-middle
    lc.setLed(0, x + 2, 1, true);  // Top-right corner

    buttonTest();
    lc.setLed(0, x, 0, true);      // Bottom-left corner
    lc.setLed(0, x + 1, 0, true);  // Bottom-middle
    lc.setLed(0, x + 2, 0, true);  // Bottom-right corner

    // Draw the car wheels (at the bottom row)
    lc.setLed(0, x + 1, 0, true);   // Left wheel
    lc.setLed(0, x + 1, -1, true);  // Right wheel
    buttonTest();
    delay(200);  // Pause to simulate motion

    // Erase the car body and wheels
    lc.setLed(0, x, 1, false);
    lc.setLed(0, x + 1, 1, false);
    lc.setLed(0, x + 2, 1, false);
    buttonTest();
    lc.setLed(0, x, 0, false);
    lc.setLed(0, x + 1, 0, false);
    lc.setLed(0, x + 2, 0, false);

    lc.setLed(0, x + 1, 0, false);
    lc.setLed(0, x + 1, -1, false);
  }
  turnOffLED();
  buttonTest();

  // Step 1: Firework launch
  for (int y = 0; y <= 5; y++) {  // Launch stops at y = 5
    lc.setLed(0, 3, y, true);     // Turn on LED as it "moves up"

    delay(100);                 // Pause for animation effect
    lc.setLed(0, 3, y, false);  // Turn off the previous LED
  }

  // Step 2: Explosion (Circular Rings with Randomness)
  int centerX = 3, centerY = 5;  // Center of the explosion

  // Ring 1: Immediate neighbors around the center
  lc.setLed(0, centerX, centerY, true);                                      // Center point
  lc.setLed(0, centerX - 1 + randomShift(), centerY + randomShift(), true);  // Left
  lc.setLed(0, centerX + 1 + randomShift(), centerY + randomShift(), true);  // Right
  lc.setLed(0, centerX + randomShift(), centerY - 1 + randomShift(), true);  // Down
  lc.setLed(0, centerX + randomShift(), centerY + 1 + randomShift(), true);  // Up
  delay(150);
  buttonTest();
  // Ring 2: Diagonal neighbors (slightly randomized positions)
  lc.setLed(0, centerX - 1 + randomShift(), centerY - 1 + randomShift(), true);  // Bottom-left
  lc.setLed(0, centerX + 1 + randomShift(), centerY - 1 + randomShift(), true);  // Bottom-right
  lc.setLed(0, centerX - 1 + randomShift(), centerY + 1 + randomShift(), true);  // Top-left
  lc.setLed(0, centerX + 1 + randomShift(), centerY + 1 + randomShift(), true);  // Top-right
  delay(150);

  // Ring 3: Outer circle (2 units from the center, with slight randomness)
  lc.setLed(0, centerX - 2 + randomShift(), centerY + randomShift(), true);  // Far left
  lc.setLed(0, centerX + 2 + randomShift(), centerY + randomShift(), true);  // Far right
  lc.setLed(0, centerX + randomShift(), centerY - 2 + randomShift(), true);  // Far down
  lc.setLed(0, centerX + randomShift(), centerY + 2 + randomShift(), true);  // Far up

  lc.setLed(0, centerX - 2 + randomShift(), centerY - 1 + randomShift(), true);  // Mid left-down
  lc.setLed(0, centerX + 2 + randomShift(), centerY - 1 + randomShift(), true);  // Mid right-down
  lc.setLed(0, centerX - 2 + randomShift(), centerY + 1 + randomShift(), true);  // Mid left-up
  lc.setLed(0, centerX + 2 + randomShift(), centerY + 1 + randomShift(), true);  // Mid right-up
  lc.setLed(0, centerX - 1 + randomShift(), centerY - 2 + randomShift(), true);  // Mid bottom-left
  lc.setLed(0, centerX + 1 + randomShift(), centerY - 2 + randomShift(), true);  // Mid bottom-right
  lc.setLed(0, centerX - 1 + randomShift(), centerY + 2 + randomShift(), true);  // Mid top-left
  lc.setLed(0, centerX + 1 + randomShift(), centerY + 2 + randomShift(), true);  // Mid top-right
  delay(150);
  buttonTest();
  // Step 3: Fade out the explosion (Reverse order)
  // Fade outer ring
  lc.setLed(0, centerX - 2 + randomShift(), centerY + randomShift(), false);
  lc.setLed(0, centerX + 2 + randomShift(), centerY + randomShift(), false);
  lc.setLed(0, centerX + randomShift(), centerY - 2 + randomShift(), false);
  lc.setLed(0, centerX + randomShift(), centerY + 2 + randomShift(), false);

  lc.setLed(0, centerX - 2 + randomShift(), centerY - 1 + randomShift(), false);
  lc.setLed(0, centerX + 2 + randomShift(), centerY - 1 + randomShift(), false);
  lc.setLed(0, centerX - 2 + randomShift(), centerY + 1 + randomShift(), false);
  lc.setLed(0, centerX + 2 + randomShift(), centerY + 1 + randomShift(), false);
  lc.setLed(0, centerX - 1 + randomShift(), centerY - 2 + randomShift(), false);
  lc.setLed(0, centerX + 1 + randomShift(), centerY - 2 + randomShift(), false);
  lc.setLed(0, centerX - 1 + randomShift(), centerY + 2 + randomShift(), false);
  lc.setLed(0, centerX + 1 + randomShift(), centerY + 2 + randomShift(), false);
  delay(100);
  buttonTest();
  // Fade diagonal neighbors
  lc.setLed(0, centerX - 1 + randomShift(), centerY - 1 + randomShift(), false);
  lc.setLed(0, centerX + 1 + randomShift(), centerY - 1 + randomShift(), false);
  lc.setLed(0, centerX - 1 + randomShift(), centerY + 1 + randomShift(), false);
  lc.setLed(0, centerX + 1 + randomShift(), centerY + 1 + randomShift(), false);
  delay(300);
  // Fade immediate neighbors
  lc.setLed(0, centerX - 1 + randomShift(), centerY + randomShift(), false);
  lc.setLed(0, centerX + 1 + randomShift(), centerY + randomShift(), false);
  lc.setLed(0, centerX + randomShift(), centerY - 1 + randomShift(), false);
  lc.setLed(0, centerX + randomShift(), centerY + 1 + randomShift(), false);
  if (dht.readTemperature() >= 28 || dht.readTemperature() <= 15 || dht.readHumidity() >= 70) {
    fall();
  }
  // Fade center
  lc.setLed(0, centerX, centerY, false);
  buttonTest();
  turnOffLED();
  if (random(1, 30) == 5) {
    int crescent[8][8] = {{0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0},
                          {0, 1, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
    buttonTest();
    // Loop through the 8x8 grid and set LEDs for the crescent shape
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        if (crescent[y][x] == 1) {
          lc.setLed(0, x, y, true);  // Turn on the LED for the crescent shape
          LEDstat[x][y] = 1;
        } else {
          lc.setLed(0, x, y, false);  // Make sure all other LEDs are off
          LEDstat[x][y] = 0;
        }
      }
    }
    if (dht.readTemperature() >= 28 || dht.readTemperature() <= 15 || dht.readHumidity() >= 70) {
      fall();
    }
  }
  delay(1000);
  buttonTest();
}

void temp() {
  int Temperature = dht.readTemperature();  // Read temperature in *C (default)
  int Humidity = dht.readHumidity();
  //  Serial.print("Temperature = ");  // print temperature on the serial monitor
  // Serial.println(Temperature);
  // Serial.print("Humidity = ");// Print humidity on the serial monitor
  // Serial.println(Humidity);
  buttonTest();

  if (Temperature != pastTemp) {
    turnOffLED();
  }
  if (Temperature == 16) {
    lc.setLed(0, 1, 6, true);

    lc.setLed(0, 1, 5, true);

    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);

    lc.setLed(0, 1, 1, true);
    // Ones digit (6)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 5, 3, true);
    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 5, 2, true);
    // lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

  } else if (Temperature == 17) {
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 1, 5, true);
    lc.setLed(0, 1, 4, true);
    lc.setLed(0, 1, 3, true);
    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 1, 1, true);
    // Ones digit (7)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 7, 2, true);

    //   lc.setLed(0, 7, 1, true);

  } else if (Temperature == 18) {
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 1, 5, true);
    lc.setLed(0, 1, 4, true);
    lc.setLed(0, 1, 3, true);
    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 1, 1, true);

    // Ones digit (8)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 5, 3, true);
    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

    lc.setLed(0, 5, 1, true);
    lc.setLed(0, 6, 1, true);
    lc.setLed(0, 7, 1, true);

  }

  else if (Temperature == 19) {
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 1, 5, true);
    lc.setLed(0, 1, 4, true);
    lc.setLed(0, 1, 3, true);
    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 1, 1, true);

    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 7, 2, true);

    lc.setLed(0, 5, 1, true);
    lc.setLed(0, 6, 1, true);
    lc.setLed(0, 7, 1, true);
  } else if (Temperature == 20) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (0)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 5, 3, true);
    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

  }

  else if (Temperature == 21) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (1)
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 6, 5, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 6, 3, true);
    lc.setLed(0, 6, 2, true);

  }

  else if (Temperature == 22) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (2)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 7, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 5, 4, true);

    lc.setLed(0, 5, 3, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

  }

  else if (Temperature == 23) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (3)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 7, 4, true);
    lc.setLed(0, 6, 4, true);

    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 7, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 5, 2, true);

  }

  else if (Temperature == 24) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (4)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);
    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 7, 3, true);
    lc.setLed(0, 7, 2, true);

  }

  else if (Temperature == 25) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (5)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

  }

  else if (Temperature == 26) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (6)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 5, 5, true);

    lc.setLed(0, 5, 4, true);
    lc.setLed(0, 6, 4, true);
    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 5, 3, true);
    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 5, 2, true);
    // lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

    lc.setLed(0, 5, 2, true);
    lc.setLed(0, 6, 2, true);
    lc.setLed(0, 7, 2, true);

  }

  else if (Temperature == 27) {
    // Tens digit (2)
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 2, 6, true);
    lc.setLed(0, 3, 6, true);

    lc.setLed(0, 3, 5, true);

    lc.setLed(0, 3, 4, true);
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 1, 4, true);

    lc.setLed(0, 1, 3, true);

    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 2, true);

    // Ones digit (7)
    lc.setLed(0, 5, 6, true);
    lc.setLed(0, 6, 6, true);
    lc.setLed(0, 7, 6, true);

    lc.setLed(0, 7, 5, true);

    lc.setLed(0, 7, 4, true);

    lc.setLed(0, 7, 3, true);

    lc.setLed(0, 7, 2, true);

    // lc.setLed(0, 7, 1, true);
  }
  if (Temperature >= 28 || Temperature <= 15 || Humidity >= 70) {
    // Serial.println("over");
    fall();
    // Serial.println("fall");
    buttonControl = 1;
    turnOffLED();
  }

  buttonTest();
  pastTemp = Temperature;
}

void catTail() {
  for (int i = 0; i <= 5; i++) {
    lc.setLed(0, 5, i, true);
    lc.setLed(0, 6, i, true);
    LEDstat[5][i] = 1;
    LEDstat[6][i] = 1;
  }
  for (int i = 4; i <= 6; i++) {
    lc.setLed(0, 4, i, true);
    lc.setLed(0, 7, i, true);
    LEDstat[4][i] = 1;
    LEDstat[7][i] = 1;
  }
  for (int i = 0; i <= 2; i++) {
    lc.setLed(0, 4, i, true);
    lc.setLed(0, 7, i, true);
    LEDstat[4][i] = 1;
    LEDstat[7][i] = 1;
  }

  if (random(1, 3) == 1) {
    lc.setLed(0, 2, 1, true);
    lc.setLed(0, 3, 0, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 3, 3, true);
    LEDstat[2][1] = 1;
    LEDstat[3][0] = 1;
    LEDstat[2][2] = 1;
    LEDstat[3][3] = 1;
    lc.setLed(0, 1, 3, false);
    LEDstat[1][3] = 0;
    delay(3000);
  } else {
    lc.setLed(0, 2, 1, true);
    lc.setLed(0, 3, 0, true);
    lc.setLed(0, 2, 2, true);
    lc.setLed(0, 1, 3, true);
    LEDstat[2][1] = 1;
    LEDstat[3][0] = 1;
    LEDstat[2][2] = 1;
    LEDstat[1][3] = 1;
    lc.setLed(0, 3, 3, false);
    LEDstat[3][3] = 0;
    delay(3000);
  }
  if (random(1, 200) == 56) {
    turnOffLED();
    // Vertical bar on the left
    // Vertical bar on the left
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 1, 5, true);
    lc.setLed(0, 1, 4, true);
    lc.setLed(0, 1, 3, true);
    lc.setLed(0, 1, 2, true);
    lc.setLed(0, 1, 1, true);
    buttonTest();
    // Upper diagonal (top right)
    lc.setLed(0, 3, 5, true);
    lc.setLed(0, 4, 6, true);
    lc.setLed(0, 4, 2, true);
    lc.setLed(0, 4, 1, true);

    // Lower diagonal (bottom right)
    lc.setLed(0, 2, 4, true);
    lc.setLed(0, 3, 3, true);
    delay(10000);
    // Vertical bar on the left
    // Vertical bar on the left
    lc.setLed(0, 1, 6, false);
    lc.setLed(0, 1, 5, false);
    lc.setLed(0, 1, 4, false);
    lc.setLed(0, 1, 3, false);
    lc.setLed(0, 1, 2, false);
    lc.setLed(0, 1, 1, false);

    // Upper diagonal (top right)
    lc.setLed(0, 3, 5, false);
    lc.setLed(0, 4, 6, false);
    lc.setLed(0, 4, 2, false);
    lc.setLed(0, 4, 1, false);

    // Lower diagonal (bottom right)
    lc.setLed(0, 2, 4, false);
    lc.setLed(0, 3, 3, false);
    turnOffLED();
  }
  if (dht.readTemperature() >= 32 || dht.readTemperature() <= 15 || dht.readHumidity() >= 80) {
    lc.setLed(0, 0, 7, true);
    lc.setLed(0, 1, 7, true);
    lc.setLed(0, 2, 7, true);
    lc.setLed(0, 1, 6, true);
    lc.setLed(0, 1, 5, true);
  } else {
    lc.setLed(0, 0, 7, false);
    lc.setLed(0, 1, 7, false);
    lc.setLed(0, 2, 7, false);
    lc.setLed(0, 1, 6, false);
    lc.setLed(0, 1, 5, false);
  }
}

//main loop function 
void loop() {
    //cycle through button states
  while (buttonTest() == 2) {
    lc.setIntensity(0, 4);
    turnOffLED();
    pattern();
    lc.setIntensity(0, 2);
  }
  while (buttonTest() == 1 || buttonTest() == 4) {
    lc.setIntensity(0, 1);
    catTail();
    buttonTest();
    lc.setIntensity(0, 2);
  }
  while (buttonTest() == 3) {
    temp();
  }
}