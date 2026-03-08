#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <Adafruit_NeoPixel.h>

#define LED 13
#define TIRA_PIN 6
#define NUM_LEDS 8

Adafruit_NeoPixel strip(NUM_LEDS, TIRA_PIN, NEO_GRB + NEO_KHZ800);

void tiraTask(void *pvParameters);
bool led = false; 

void setup() {
  pinMode(LED, OUTPUT);  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  printf("Tira LED example started\n");
  xTaskCreate(tiraTask, "Tira Task", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  digitalWrite(LED, led ? HIGH : LOW);
  led = !led; 
  delay(1000);
 // printf("LED is now %s\n", led ? "ON" : "OFF");
}

void tiraTask(void *pvParameters) {
  int ciclo = 0;
  while (1) {
   
    switch (ciclo)
    {
    case 0:
      printf("Ciclo %d\n", ciclo);
      for (int i = 0; i < NUM_LEDS; i++) {
          strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red
          strip.show();
          vTaskDelay(100 / portTICK_PERIOD_MS);
          }
          
          ciclo = 1;
      break;
    case 1:
      printf("Ciclo %d\n", ciclo);
      for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green
      strip.show();
      vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      ciclo = 2;
      break;      
    case 2:
      printf("Ciclo %d\n", ciclo);
      for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 255)); // Blue
      strip.show();
      vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      
      ciclo = 3;
      break;
    case 3:
      // Efecto de onda sinusoidal en cada color    
      printf("Ciclo %d\n", ciclo);
      for (uint n = 0; n < 3; n++) {
        for (int k = 0; k < 256; k++) {   
          for (int i = 0; i < NUM_LEDS; i++) {
            uint8_t r = (n == 0) ? k : 0;  // Red wave
            uint8_t g = (n == 1) ? k : 0;  // Green wave
            uint8_t b = (n == 2) ? k : 0;  // Blue wave
            strip.setPixelColor(i, strip.Color(_NeoPixelSineTable[r], _NeoPixelSineTable[g], _NeoPixelSineTable[b]));
            strip.show();
            vTaskDelay(5 / portTICK_PERIOD_MS);
          }
        }
      }
      ciclo = 0;
      break;
      default:
      ciclo = 0;
      break;
    }
    
      
    }
}


