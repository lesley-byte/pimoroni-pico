#pragma once
#include <stdint.h>
#include <climits>
#include "pico/stdlib.h"

#define PIMORONI_I2C_DEFAULT_INSTANCE i2c0
#define PIMORONI_SPI_DEFAULT_INSTANCE spi0

// Macro to return a value clamped between a minimum and maximum
#ifndef CLAMP
#define CLAMP(a, mn, mx) ((a)<(mx)?((a)>(mn)?(a):(mn)):(mx))
#endif


namespace pimoroni {
    static const unsigned int PIN_UNUSED = INT_MAX; // Intentionally INT_MAX to avoid overflowing MicroPython's int type

    // I2C
    static const unsigned int I2C_DEFAULT_BAUDRATE = 400000;
    static const unsigned int I2C_DEFAULT_SDA = 20;
    static const unsigned int I2C_DEFAULT_SCL = 21;
    static const unsigned int I2C_DEFAULT_INT = 22;

    static const unsigned int I2C_BG_SDA = 4;
    static const unsigned int I2C_BG_SCL = 5;
    static const unsigned int I2C_BG_INT = 3;

    static const unsigned int I2C_HEADER_SDA = 20;
    static const unsigned int I2C_HEADER_SCL = 21;
    static const unsigned int I2C_HEADER_INT = 19;

    // SPI
    static const unsigned int SPI_DEFAULT_MOSI = 19;
    static const unsigned int SPI_DEFAULT_MISO = 16;
    static const unsigned int SPI_DEFAULT_DC = 16;
    static const unsigned int SPI_DEFAULT_SCK = 18;

    static const unsigned int SPI_BG_FRONT_PWM = 20;
    static const unsigned int SPI_BG_FRONT_CS = 17;

    static const unsigned int SPI_BG_BACK_PWM = 21;
    static const unsigned int SPI_BG_BACK_CS = 22;

    enum BG_SPI_SLOT {
      BG_SPI_FRONT,
      BG_SPI_BACK,
      PICO_EXPLORER_ONBOARD
    };

    enum BOARD {
      BREAKOUT_GARDEN,
      PICO_EXPLORER,
      PLASMA_2040,
      INTERSTATE_75,
      SERVO_2040
    };
  
    enum Rotation {
      ROTATE_0 = 0,
      ROTATE_90 = 90,
      ROTATE_180 = 180,
      ROTATE_270 = 270
    };

    enum Polarity {
      ACTIVE_LOW = 0,
      ACTIVE_HIGH = 1
    };

    enum Direction {
      NORMAL_DIR    = 0,
      REVERSED_DIR  = 1,
    };

    inline uint32_t millis() {
      return to_ms_since_boot(get_absolute_time());
    }

    // (uint16_t)(powf((float)(n) / 255.0f, 2.8f) * 65535.0f + 0.5f);
    constexpr uint16_t GAMMA[256] = {
      0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 8, 10, 13, 16, 19, 24, 
      28, 33, 39, 46, 53, 60, 69, 78, 88, 98, 110, 122, 135, 149, 164, 179, 
      196, 214, 232, 252, 273, 295, 317, 341, 366, 393, 420, 449, 478, 510, 542, 575, 
      610, 647, 684, 723, 764, 806, 849, 894, 940, 988, 1037, 1088, 1140, 1194, 1250, 1307, 
      1366, 1427, 1489, 1553, 1619, 1686, 1756, 1827, 1900, 1975, 2051, 2130, 2210, 2293, 2377, 2463, 
      2552, 2642, 2734, 2829, 2925, 3024, 3124, 3227, 3332, 3439, 3548, 3660, 3774, 3890, 4008, 4128, 
      4251, 4376, 4504, 4634, 4766, 4901, 5038, 5177, 5319, 5464, 5611, 5760, 5912, 6067, 6224, 6384, 
      6546, 6711, 6879, 7049, 7222, 7397, 7576, 7757, 7941, 8128, 8317, 8509, 8704, 8902, 9103, 9307, 
      9514, 9723, 9936, 10151, 10370, 10591, 10816, 11043, 11274, 11507, 11744, 11984, 12227, 12473, 12722, 12975, 
      13230, 13489, 13751, 14017, 14285, 14557, 14833, 15111, 15393, 15678, 15967, 16259, 16554, 16853, 17155, 17461, 
      17770, 18083, 18399, 18719, 19042, 19369, 19700, 20034, 20372, 20713, 21058, 21407, 21759, 22115, 22475, 22838, 
      23206, 23577, 23952, 24330, 24713, 25099, 25489, 25884, 26282, 26683, 27089, 27499, 27913, 28330, 28752, 29178, 
      29608, 30041, 30479, 30921, 31367, 31818, 32272, 32730, 33193, 33660, 34131, 34606, 35085, 35569, 36057, 36549, 
      37046, 37547, 38052, 38561, 39075, 39593, 40116, 40643, 41175, 41711, 42251, 42796, 43346, 43899, 44458, 45021, 
      45588, 46161, 46737, 47319, 47905, 48495, 49091, 49691, 50295, 50905, 51519, 52138, 52761, 53390, 54023, 54661, 
      55303, 55951, 56604, 57261, 57923, 58590, 59262, 59939, 60621, 61308, 62000, 62697, 63399, 64106, 64818, 65535
    };

  struct pin_pair {
    union {
      uint8_t first;
      uint8_t a;
      uint8_t positive;
      uint8_t phase;
    };
    union {
      uint8_t second;
      uint8_t b;
      uint8_t negative;
      uint8_t enable;
    };

    constexpr pin_pair() : first(0), second(0) {}
    constexpr pin_pair(uint8_t first, uint8_t second) : first(first), second(second) {}
  };

  struct bool_pair {
    union {
      bool first;
      bool a;
    };
    union {
      bool second;
      bool b;
    };

    bool_pair() : first(false), second(false) {}
    bool_pair(bool first, bool second) : first(first), second(second) {}
  };
}