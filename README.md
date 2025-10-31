# 🪟 Smart Ventilation System

An Arduino-based automatic ventilation system that opens or closes a window based on gas concentration and ambient temperature. Ideal for enclosed spaces where air quality and heat buildup are concerns.

## 📁 Repository Contents

- `Smart_vent.ino` — Main Arduino sketch
- `ckt.png` — Circuit diagram for hardware connections
- `LiquidCrystal-1.0.7.zip` — LCD library (if not already available via Library Manager)
- `Servo-1.2.2.zip` — Servo motor library (if not already available via Library Manager)

## 🧠 Features

- Monitors gas levels using an MQ-series sensor
- Reads temperature using an LM35 sensor
- Displays real-time data on a 16x2 LCD
- Automatically opens/closes a window using a servo motor based on:
  - Gas concentration threshold
  - Temperature range

## 🔧 Hardware Requirements

| Component         | Description                          |
|------------------|--------------------------------------|
| Arduino board     | Uno/Nano/Mega                        |
| MQ Gas Sensor     | Analog output connected to A0        |
| LM35 Temperature Sensor | Analog output connected to A1 |
| Servo Motor       | Connected to digital pin 10          |
| 16x2 LCD Display  | Connected via digital pins 12, 11, 5, 4, 3, 2 |
| Jumper wires      | For connections                      |
| Power supply      | USB or external                      |

## 📐 Circuit Diagram

Refer to `ckt.png` for wiring instructions.

## 📦 Library Installation

If not using the Arduino Library Manager, install manually:

1. Go to **Arduino IDE → Sketch → Include Library → Add .ZIP Library**
2. Select:
   - `LiquidCrystal-1.0.7.zip`
   - `Servo-1.2.2.zip`

## 🚀 How It Works

1. **Startup**: LCD displays system name, servo starts in closed position.
2. **Monitoring**:
   - Gas sensor reads analog value.
   - LM35 converts voltage to temperature.
3. **Control Logic**:
   - If gas level > 400 → window opens.
   - If temperature > 60°C → window opens.
   - If temperature ≤ 40°C → window closes.
4. **Display**:
   - LCD shows gas value, temperature, and window status.
   - Serial monitor logs actions.

## 📈 Sensor Thresholds

| Parameter     | Threshold |
|---------------|-----------|
| Gas Level     | > 400     |
| Temperature   | > 60°C (open), ≤ 40°C (close) |

## 🛠️ Customization

You can adjust the following constants in the code:

```cpp
const int gasThreshold = 400;
const int tempHigh = 60;
const int tempLow = 40;