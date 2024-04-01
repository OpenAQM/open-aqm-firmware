#pragma once

// NOTE This file will slowly be migrated into the platform header files.

// pin mapping

//Button
#define FLASH 0

//MP503
#define MP503_1 2
#define MP503_2 34

// DHT22
#define DHT22 4

// MQ131
#define MQ131_1 5
#define MQ131_2 35

//LORA
#define LORA_CS 12
#define LORA_IO0 26
#define LORA_RST 27

//SPI
#define MOSI 23
#define MISO 19
#define SCK 18

// I2C
#define I2C_SDA 21
#define I2C_SCL 22

// RTC
#define RTC_INT 32

// BATTERY
#define STAT_PWR 33
#define B_MON 25
#define PWR2_EN 10

//LED
#define LED_DPIN 17

//PMS5003 PM2.5
#define PM_TX2 16
#define PM_RX2 15

//MH-Z19B C02
#define MH_TX1 14
#define MH_RX1 13



#define BTN_STATE_ARRAY {LOW, HIGH, HIGH}

// button order is: select, up, down
#define BTN_NUMBER 3
#define BTN_POSX_ARRAY {24, 208, 208}
#define BTN_POSY_ARRAY {190, 44, 190}
#define BTN_POS_ISTOP_ARRAY {false, true, false}
#define BTN_POS_ISLEFT_ARRAY {true, false, false}
#define BTN_NAME_ARRAY {"SELECT", "UP", "DOWN"}
#define BTN_PIN_ARRAY {BTN_1, BTN_2, BTN_3}