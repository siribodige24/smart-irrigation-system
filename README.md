# Smart Irrigation & Intrusion Detection System

## Project Overview

An Arduino-based system designed to automate irrigation based on soil moisture and rainfall conditions while detecting animal intrusion.

## Components Used

- Arduino Uno
- Soil Moisture Sensor
- Rain Sensor
- IR/Obstacle Sensor
- Relay Module
- Water Pump
- Buzzer
- 16x2 I2C LCD

## Technologies Used

- Arduino
- Embedded C
- Sensor Interfacing
- Automation

## Key Features

- Automatic irrigation based on soil moisture
- Rain detection
- Animal intrusion detection
- Automatic water pump control
- Buzzer alert for intrusion
- Real-time status display using 16x2 I2C LCD

## Working

The soil moisture sensor monitors the moisture level of the soil. When the soil becomes dry and there is no rain, the Arduino activates the water pump through the relay.

The rain sensor detects rainfall conditions and prevents unnecessary irrigation.

The IR/obstacle sensor detects possible animal intrusion. When an obstacle is detected, the buzzer is activated as an alert.

The LCD displays the soil condition, rain status, pump status, and obstacle detection status.

## Libraries Used

- Wire.h
- LiquidCrystal_I2C.h

## Hardware Platform

Arduino Uno

## Project Type

Embedded Systems / Arduino Project
