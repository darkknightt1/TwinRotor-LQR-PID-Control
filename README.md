# 🚁 Twin Rotor Pitch Control System

This project implements **pitch angle control** for a **twin rotor system** using both **PID** and **State-Space** methods. The system was modeled and tested using MATLAB/Simulink, with real-time control deployed on an **ESP32 microcontroller** via the Arduino IDE.

---

## 🧠 Project Overview

- **Controlled Axis**: Pitch angle  
- **Potential Extension**: Yaw angle control (not completed due to time constraints)

- **Hardware**:
  - Twin rotor setup with BLDC motors
  - Encoder for pitch angle measurement
  - Potentiometer to vary input signal
  - ESP32 for real-time control

---

## 🛠️ System Identification

- **Input**: Potentiometer-mapped control signal to BLDC motor  
- **Output**: Measured pitch angle from encoder  
- Used **MATLAB System Identification Toolbox** to model the system  
- Identified as a **3rd-order system**

---

## 🎯 Control Strategies

### ✅ PID Control
- PID parameters tuned using **Root Locus** technique on the identified model
- Simulated and validated in **MATLAB/Simulink**

### ✅ State-Space Control
- Designed using both:
  - **LQR (Linear Quadratic Regulator)**
  - **Pole Placement with Integral Action** for minimal steady-state error

---

## ⚙️ Implementation

- Control algorithm coded on **ESP32** using **Arduino IDE**
- Real-time feedback from encoder
- Actuation via BLDC motor driver

---

## 🔧 Features & Improvements

-  Stable pitch control
-  Yaw control system modeling in progress (implementation halted due to time constraints)
-  Easy extension to full MIMO control in future iterations

---

## 📚 Tools & Technologies

- MATLAB / Simulink  
- System Identification Toolbox  
- Control System Toolbox  
- Arduino IDE (ESP32 support)

---


## 🧩 Future Work

- Complete yaw axis modeling and control
- Full dual-axis control using LQR or MPC
- Sensor fusion and disturbance rejection enhancements
