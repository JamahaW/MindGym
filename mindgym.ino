struct LedButton {
  const uint8_t PIN_LED, PIN_BUTTON;
  mutable bool state = false;

  LedButton(uint8_t led, uint8_t button) : PIN_LED(led), PIN_BUTTON(button) {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
  }

  void set(bool state) const {digitalWrite(PIN_LED, state);}

  bool read() const { return !digitalRead(PIN_BUTTON);}

  void toggle() const { set(state ^= 1); }
};


LedButton buttons[] {
  LedButton(3, 2),
  LedButton(5, 4),
  LedButton(8, 9),
  LedButton(6, 7),
};

void setup() {
  Serial.begin(9600);
  Serial.println(F("hello world"));
}

void loop() {
  static uint8_t i;

  i = 0;

  for (const LedButton& b : buttons) {
    b.toggle();

    if (b.read()) {
      Serial.print(F("Press: "));
      Serial.println(i);
    }

    i++;
    delay(50);
  }
}
