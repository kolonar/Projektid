# CoolFridgeGuard - Smart Refrigerator Door Alarm

**CoolFridgeGuard** is a custom PCB designed to detect when a refrigerator door is left open and play a custom audio alert. It features an STM32 microcontroller, SD card support for custom audio files, and a high-efficiency power system running off standard AA batteries.

## Key Features

* **MCU:** STM32F411RET6 (ARM Cortex-M4).
* **Audio:** PAM8403 3W Class-D Amplifier with SD Card support for .WAV playback.
* **Sensors:** Phototransistor (Light detection) to sense door opening.
* **Power:**
    * Powered by **3x AA Batteries** (3.0V - 4.5V input).
    * **5.1V Boost Converter** (PAM2401) ensures loud audio even as batteries drain.
    * **3.3V LDO** (NCP164) for stable logic voltage.
* **Protection:** Full ESD protection on USB and SD Card lines.

---

## Hardware Specifications

| Parameter | Value | Notes |
| :--- | :--- | :--- |
| **Input Voltage** | 3.0-5.0V | optimized for 3x AA Alkaline Batteries |
| **Logic Voltage** | 3.3V | Regulated via U5 (NCP164) |
| **Audio Output** | 3 Watts (4Ω) | Mono output via J2 |
| **Connectors** | USB-C, Molex PicoBlade (Speaker), Molex MicroClasp (Battery) | |
| **Programming** | SWD | Standard ST-Link Interface |

---

## 🔌 Connector Pinouts

### **J1 - USB-C (Power & Data)**
Used for debugging and potential data transfer.
* **VBUS:** 5V Input (Protected by U1)
* **D-/D+:** Data lines
* **GND:** Common Ground

### **J2 - Speaker Output (Molex PicoBlade 1.25mm)**
Connects to the 3W 4Ω Speaker mounted on the case.
* **Pin 1:** Speaker +
* **Pin 2:** Speaker -
* *Note: Uses cable assembly `15134-0202` (Cut in half).*

### **J3 - Battery Input (Molex MicroClasp 2.00mm)**
Connects to the 3xAA Battery Holder.
* **Pin 1:** V_BAT (+)
* **Pin 2:** GND (-)
* *Note: Uses cable assembly `15136-0201` (Cut in half).*

### **J5 - MicroSD Card Slot**
SPI Interface for reading audio files.
* **SPI Mode:** CLK, MOSI, MISO, CS.
* *ESD Protected via U6 (USBLC6-4SC6).*

---

## Bill of Materials (BOM) Highlights

| Component | Description | Part Number |
| :--- | :--- | :--- |
| **MCU** | STM32F411RET6 | `STM32F411RET6` |
| **Amp** | 3W Audio Amp | `PAM8403DR` |
| **Boost** | Step-Up DC-DC | `PAM2401SCADJ` |
| **Speaker** | 40mm 3W 4Ω | `AS04004PO-2-R` |
| **Battery Case** | 3x AA Holder | `Keystone 2479` |

---

## Firmware Setup (STM32CubeIDE)

* **System Core:** 96 MHz Clock (HSI + PLL).
* **Timers:** Enable PWM for Audio generation (if not using I2S/DAC) or simple beep tones.
* **ADC:** Configure for Phototransistor input (detects light level changes).
* **SPI:** Configure for SD Card communication (FATFS middleware required).
