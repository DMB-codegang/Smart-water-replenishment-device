//YWROBOT
#ifndef LiquidCrystal_I2C_h
#define LiquidCrystal_I2C_h

#include <inttypes.h>
#include "Arduino.h" 
#include <Wire.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0

class DFRobot_LiquidCrystal_I2C {
public:
  DFRobot_LiquidCrystal_I2C();
  void begin(uint32_t lcd_Addr = 0x20);
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
  void clear();
  void home();
  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void printLeft();
  void printRight();
  void leftToRight();
  void rightToLeft();
  void shiftIncrement();
  void shiftDecrement();
  void noBacklight();
  void backlight();
  void autoscroll();
  void noAutoscroll(); 
  void createChar(uint8_t, uint8_t[]);
  void createChar(uint8_t location, const char *charmap);
  // Example:     const char bell[8] PROGMEM = {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000};

    void print(uint32_t x, uint32_t y, const char *pCh);
    void print(uint32_t x, uint32_t y, uint32_t i);
    void print(uint32_t x, uint32_t y, int32_t i);
#if defined(NRF5) || defined(NRF52833)
    void print(uint32_t x, uint32_t y, int i){print(x, y, (int32_t)i);}
#endif
    void print(uint32_t x, uint32_t y, double f, int precision = 10);
    void print(uint32_t x, uint32_t y, float f){print(x, y, (double)f);}
    void print(uint32_t x, uint32_t y, byte i){print(x, y, (uint32_t)i);}
    void print(uint32_t x, uint32_t y, uint16_t i){print(x, y, (uint32_t)i);}
    void print(uint32_t x, uint32_t y, int16_t i){print(x, y, (int32_t)i);}
    void print(uint32_t x, uint32_t y, uint64_t i){print(x, y, (uint32_t)i);}
    void print(uint32_t x, uint32_t y, int64_t i){print(x, y, (int32_t)i);}
    void print(uint32_t x, uint32_t y, String str){print(x, y, (const char *)str.c_str());}

    void printLine(uint32_t line, const char *pCh);
    void printLine(uint32_t line, uint32_t i);
    void printLine(uint32_t line, int32_t i);
#if defined(NRF5) || defined(NRF52833)
    void printLine(uint32_t line, int i){printLine(line, (int32_t)i);}
#endif
    void printLine(uint32_t line, double f, int precision = 10);
    void printLine(uint32_t line, float f){printLine(line, (double)f);}
    void printLine(uint32_t line, byte i){printLine(line, (uint32_t)i);}
    void printLine(uint32_t line, uint16_t i){printLine(line, (uint32_t)i);}
    void printLine(uint32_t line, int16_t i){printLine(line, (int32_t)i);}
    void printLine(uint32_t line, uint64_t i){printLine(line, (uint32_t)i);}
    void printLine(uint32_t line, int64_t i){printLine(line, (int32_t)i);}
    void printLine(uint32_t line, String str){printLine(line, (const char *)str.c_str());}

  void setCursor(uint8_t, uint8_t); 

  void   write(uint8_t);

  void command(uint8_t);
  void init();

  //compatibility API function aliases
  void blink_on();                        // alias for blink()
  void blink_off();                           // alias for noBlink()
  void cursor_on();                               // alias for cursor()
  void cursor_off();                          // alias for noCursor()
  void setBacklight(uint8_t new_val);                // alias for backlight() and nobacklight()
  void load_custom_character(uint8_t char_num, uint8_t *rows);    // alias for createChar()

  //Unsupported API functions (not implemented in this library)
  uint8_t status();
  void setContrast(uint8_t new_val);
  uint8_t keypad();
  void setDelay(int,int);
  void on();
  void off();
  uint8_t init_bargraph(uint8_t graphtype);
  void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
  void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
  void checkEnable();


private:
  void init_priv();
  void send(uint8_t, uint8_t);
  void send1(uint8_t *data, uint8_t len);
  void setReg(uint8_t addr, uint8_t data);
  void setRGB(uint8_t r, uint8_t g, uint8_t b);               // set rgb
  void write4bits(uint8_t);
  void expanderWrite(uint8_t);
  void pulseEnable(uint8_t);
  uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;
  bool rgbFlag = false;
  bool enable = false;
};

#endif
