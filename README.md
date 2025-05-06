<h1 align="center">Simon Says - STM32 Embedded Game</h1>


<p align="center">
  <img src="banner.png" alt="Simon Says STM32 Banner" />
</p>

A real-time memory game implemented on the STM32F103RB microcontroller using C and GPIO interrupts.  
Designed as a course project for ENSE 352, this system challenges users to mimic LED patterns through timed button presses, with difficulty increasing after each correct round.

---

## 🎮 Game Overview

- The game begins with a **Knight Rider-style LED animation**.
- A random LED sequence is generated and shown to the user.
- The user must replicate the sequence by pressing corresponding buttons.
- Each level adds one more step to the sequence.
- On success: the game progresses with a longer sequence.
- On failure: a unique **error animation** is played and the game ends.
- On completion: a **winning animation** sequence is triggered.

---

## 🔌 Hardware Overview

- **Microcontroller**: STM32F103RB  
- **IDE**: Keil uVision (C programming)  
- **Inputs**: 4 Buttons (using external interrupts)  
- **Outputs**: 4 LEDs (via GPIO)  
- **Timing**: SysTick timer used for delays and animation pacing

---

## 📍 GPIO Pin Configuration

| Function       | Pin     | Description            |
|----------------|---------|------------------------|
| LED 1          | PA0     | First color LED        |
| LED 2          | PA1     | Second color LED       |
| LED 3          | PA2     | Third color LED        |
| LED 4          | PA3     | Fourth color LED       |
| Button 1       | PB0     | Corresponds to LED 1   |
| Button 2       | PB1     | Corresponds to LED 2   |
| Button 3       | PB10    | Corresponds to LED 3   |
| Button 4       | PB11    | Corresponds to LED 4   |

> *(Pins can be adjusted based on user wiring — document reflects default setup)*

---

## 🧠 Technical Highlights

- Uses **EXTI (External Interrupts)** for responsive button detection  
- **SysTick timer** handles precise delays between LED flashes and input reading  
- Implements state machine logic to track game phase and level  
- Includes modular functions for LED control, sequence generation, and input checking

---

## 📚 Course Context

- **Course**: ENSE 352 — Digital Systems Design  
- **Semester**: Winter 2025  
- **Project Type**: Embedded Game (Individual or Group)

---

## 🎓 Key Learning Outcomes

- Mastery of GPIO interrupts on STM32  
- Embedded logic structuring using C  
- Real-time input/output timing and feedback systems  
- Enhanced understanding of microcontroller-based game design

---

## 📁 Repository Structure

