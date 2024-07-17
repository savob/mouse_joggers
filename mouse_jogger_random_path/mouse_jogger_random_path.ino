#include "Mouse.h"

const int JOG_PERIOD_MS = 45E3;     // Period between each burst of motions (ms)
const int NUM_MOTIONS = 3;          // Number of pseudo random motions to perform
const int MOVEMENT_SPACING_MS = 10; // Delay between each motion (ms)

void setup() {
  Mouse.begin();
}

int generate_random_movement() {
  const int MAX_MAGNITUDE = 20;

  int random_val = rand(); 

  bool negative = (random_val & 1) == 0; // Should the number be negative?
  random_val = random_val >> 1; // Disregard bit used for directionality

  random_val = (random_val % MAX_MAGNITUDE) + 1;
  if (negative) random_val = -random_val;
  return random_val;
}

void loop() {
  int x[NUM_MOTIONS];
  int y[NUM_MOTIONS];

  // Generate and perform random motions
  for (int i = 0; i < NUM_MOTIONS; i++) {
    x[i] = generate_random_movement();
    y[i] = generate_random_movement();
    Mouse.move(x[i], y[i], 0);
    delay(MOVEMENT_SPACING_MS);
  }

  // Reverse motions
  for (int i = 0; i < NUM_MOTIONS; i++) {
    Mouse.move(-x[i], -y[i], 0);
    delay(MOVEMENT_SPACING_MS);
  }

  delay(JOG_PERIOD_MS);
}
