
---

# Electronics & Hardware Projects

Welcome to the hardware section of my portfolio. This directory contains the schematics, PCB designs, and firmware source code for my custom embedded systems.

As a Computer Engineer, I focus on building robust hardware architectures that tightly integrate with embedded C/C++ firmware. The projects below demonstrate a range of skills, from high-current motor control and real-time kinematics to low-power audio processing and sensor integration.

---

## Project Directory

### 1. HARM - Delta X Basketball Robot Mainboard

**HARM** is a high-performance motor control and sensor interface motherboard designed for a basketball-playing robot used in the **Delta X** robotics competition. It acts as the "lower-level brain" of the robot, translating high-level commands into precise physical movements.

* **Microcontroller:** STM32G441KB (170 MHz ARM Cortex-M4 with FPU)
* **Core Function:** Computes kinematics ($V_x, V_y, \omega$) and executes strict PID control loops for a multi-wheel omnidirectional chassis.
* **Hardware Highlights:**
* Custom TI DRV8243 H-Bridge implementations for 3x brushed DC motors.
* Robust power architecture with massive bulk capacitance to prevent brownouts during high-current motor stalls.
* Digital isolation (MAX1493x) separating the noisy 16V/5V motor environments from the sensitive 3.3V MCU logic.


* **Interface:** Communicates with an overarching Intel NUC via USB 2.0 (Virtual COM Port).

### 2. CoolFridgeGuard - Smart Refrigerator Door Alarm

**CoolFridgeGuard** is a low-power, custom PCB designed to monitor a refrigerator door and play a custom audio alert from an SD card if left open. It focuses on battery efficiency, custom audio amplification, and sensor integration.

* **Microcontroller:** STM32F411RET6 (ARM Cortex-M4)
* **Core Function:** Uses a phototransistor to detect light changes, triggering a PAM8403 3W Class-D amplifier to play .WAV files read via SPI from a MicroSD card.
* **Hardware Highlights:**
* Optimized for 3x AA alkaline batteries (3.0V - 4.5V input).
* PAM2401 5.1V Boost Converter ensures loud, distortion-free audio even as battery voltage drops.
* Full ESD protection on user-facing interfaces (USB-C and SD Card).

---

## Hardware & Firmware Skills Demonstrated

| Skill Area | Application in Projects |
| --- | --- |
| **MCU Architecture** | STMicroelectronics STM32 (Cortex-M4), clock configuration, hardware timers, ADC/SPI peripherals. |
| **Power Supply Design** | Boost converters, LDO regulators, active reverse polarity protection, inductive kickback mitigation. |
| **Motor Control** | H-Bridge integration, quadrature encoder feedback, PID loop tuning, logic-level PWM. |
| **Signal Integrity** | Digital galvanic isolation (MAX14930), ESD protection (USBLC6-4SC6), noise filtering. |
| **Firmware Design** | Real-time kinematics math, USB CDC serial communication, FATFS middleware for SD cards. |
