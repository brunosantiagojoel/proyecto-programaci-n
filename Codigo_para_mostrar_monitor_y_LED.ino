#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define ANCHO 128
#define ALTO 64
#define OLED_SDA 18
#define OLED_SCL 17
#define OLED_RESET -1
#define DIRECCION_OLED 0x3C
#define BOTON_PIN 0 
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, OLED_RESET);


int ultimoEstado = -1;

void setup() {

  Serial.begin(115200);
  pinMode(BOTON_PIN, INPUT_PULLUP);
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_OLED)) {
    Serial.println(F("Error: No se pudo encontrar la pantalla OLED SSD1306"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 5);
  display.print("Estado del Boton:");
  display.display();
}

void loop() {
  int estadoBoton = digitalRead(BOTON_PIN);
  if (estadoBoton != ultimoEstado) {
    display.fillRect(0, 25, ANCHO, 35, SSD1306_BLACK);
    display.setTextSize(2);
    display.setCursor(0, 30);

    if (estadoBoton == LOW) {
      Serial.println("Boton: PULSADO");
      display.setTextColor(SSD1306_WHITE);
      display.print("PULSADO");
    } else {
      Serial.println("Boton: NO PULSADO");
      
      display.setTextColor(SSD1306_WHITE);
      display.print("NO PULSADO");
    }
    display.display();
    ultimoEstado = estadoBoton;
  }

  delay(50);
}