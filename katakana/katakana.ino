#include <LiquidCrystal.h>

// Connections to the circuit: potentiometer
const int SELECTOR_PIN = A0;

// Connections to the circuit: LCD screen
const int LCD_RS_PIN = 12;
const int LCD_ENABLE_PIN = 11;
const int LCD_DATA_PIN_0 = 5;
const int LCD_DATA_PIN_1 = 4;
const int LCD_DATA_PIN_2 = 3;
const int LCD_DATA_PIN_3 = 2;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_DATA_PIN_0, LCD_DATA_PIN_1, LCD_DATA_PIN_2, LCD_DATA_PIN_3);

const int LCD_ROWS = 2;
const int LCD_COLS = 16;
const int ARRAY_SIZE = 56;
const int KANAS_PER_PAGE = 4;
const int CHARS_PER_KANA = 4;
const int N_PAGES = ARRAY_SIZE/KANAS_PER_PAGE;
const char* translations[ARRAY_SIZE] = {
  "Wo",
  "a", "i", "u", "e", "o",
  "ya", "yu", "yo", "tsu",
  "-",
  "A", "I", "U", "E", "O",
  "Ka", "Ki", "Ku", "Ke", "Ko",
  "Sa", "Shi", "Su", "Se", "So",
  "Ta", "Chi", "Tsu", "Te", "To",
  "Na", "Ni", "Nu", "Ne", "No",
  "Ha", "Hi", "Fu", "He", "Ho",
  "Ma", "Mi", "Mu", "Me", "Mo",
  "Ya", "Yu", "Yo",
  "Ra", "Ri", "Ru", "Re", "Ro",
  "Wa", "N",
};

int lastSelectedPage = -1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SELECTOR_PIN, INPUT);

  lcd.begin(LCD_COLS, LCD_ROWS);
}

void loop() {
  int selectorRawValue = analogRead(SELECTOR_PIN);
  int selectedPage = map(selectorRawValue, 0, 1023, 0, N_PAGES-1);
  if (lastSelectedPage != selectedPage) {
    lastSelectedPage = selectedPage;

    // Switch on internal LED for debug
    digitalWrite(LED_BUILTIN, HIGH);
    
    lcd.clear();

    // Display katakanas and their translation
    for (int i=0; i<KANAS_PER_PAGE; i++) {
      int index = selectedPage*KANAS_PER_PAGE + i;
      lcd.setCursor(i*CHARS_PER_KANA, 0);
      lcd.print(translations[index]);
      lcd.setCursor(i*CHARS_PER_KANA, 1);
      lcd.write(0xA6 + index);
    }

    // Display page number
    int pageNumber = selectedPage + 1;
    lcd.setCursor(LCD_COLS - (pageNumber < 10 ? 1 : 2), 1);
    lcd.print(pageNumber, DEC);

    // Switch off internal LED for debug
    digitalWrite(LED_BUILTIN, LOW);
  }
}
