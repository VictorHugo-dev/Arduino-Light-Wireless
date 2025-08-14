# ESP32 Wireless Lamp Control

A simple school project that demonstrates how to control a **lamp wirelessly** using an **ESP32**.

---

## Project Overview

* The **ESP32** hosts a web page with a **button**.
* Clicking the button turns the **lamp** ON or OFF.
* A **transistor** acts as a electronic switch.
* The project demonstrates how **transistors allow small control signals to manage larger loads**, a principle used in CPUs, amplifiers, and motor drivers.

---

## Components

* ESP32 DevKit
* NPN transistor
* 12V lamp
* 1 kΩ resistor
* Breadboard and jumper wires
* 12 V battery

---

## Circuit Overview

* **ESP32 GPIO → 1 kΩ resistor → transistor base**
* **Transistor emitter → GND**
* **Transistor collector → lamp negative**
* **Lamp positive → 12V battery positive**
* **ESP32 GND → common GND with transistor and battery**

---

## How to Use

1. Change to yours Wi-Fi credentials in the code:
   const char* ssid = "ssid";
   const char* password = "password";
2. Upload the code to the ESP32.
3. Open Serial Monitor at 115200 baud to find the ESP32 IP.
4. Open a browser and go to the ESP32 IP.
5. Click the switch to turn the lamp ON or OFF.

---

## Learning Outcomes

* Using a **transistor as an electronic switch**.
* Creating a **web interface with ESP32**.

---

> This project was created as part of a **school assignment** about transistors, and I came up with the idea to use a ESP32.
