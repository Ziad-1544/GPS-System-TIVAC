🛰️ Real-Time GPS Tracking System on Tiva C (TM4C123GH6PM) 📍
---
📌 Project Overview:
---
This project implements a real-time GPS tracking system using the Tiva C (TM4C123GXL) microcontroller. It processes live GPS data, displays location information, and interacts with peripherals like LCDs, LEDs, and EEPROM through custom-built drivers. The system simulates a compact and reliable embedded navigation solution.

🎯 Features:
---
📡 Real-time GPS Data Parsing – Receives and decodes NMEA sentences from a GPS module.

🧭 Live Location Tracking – Displays coordinates on a character LCD.

🔘 User Interaction – Reads input from physical switches to navigate or trigger actions.

💾 Data Storage – Saves location data to EEPROM for persistent memory.

🔄 Custom Driver Development – Includes low-level drivers for UART, GPIO, Systick, EEPROM, CLCD, LEDs, and Switches.

🧠 Interrupt Handling – Responds to asynchronous external events using GPIO interrupts.

⏱️ Precise Timing Control – Utilizes Systick timer for accurate delays and task scheduling.

🔍 Modular and Scalable – Organized in milestones for easy expansion and maintenance.

📁 Well-Documented – Each module includes clear README files and usage examples.

---

📂 File Structure:
---
| 🧩 Component         | 📂 Description                              | 🔗 Link |
|----------------------|---------------------------------------------|--------|
| GPIO Driver          | 🛠️ Handles digital I/O                      | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/1-GPIO) |
| Systick Timer        | ⏱️ Precise delay and task scheduling        | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/2-SYSTICK) |
| UART Driver          | 📡 Serial communication                     | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/hussien/UART) |
| EEPROM Driver        | 💾 Non-volatile data storage                | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/mustafa/EEPROM) |
| GPIO Interrupt       | 🚨 External interrupt handling              | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/mustafa/GPIO_INT) |
| CLCD Driver          | 📟 Character LCD display                    | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/randa/CLCD) |
| LED Driver           | 💡 Output indicators                        | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/randa/LED) |
| Switch Driver        | 🔘 User input controls                      | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/randa/SW) |
| GPS Driver           | 🌐 GPS module parsing and extraction        | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/3-GPS) |
| Main Code            | 🧠 Core logic for full GPS functionality    | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/blob/master/main.c) |
| Phase 1 Fixes        | 🔧 Compilation error resolution             | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/mustafa/Phase_1_Compilation_errors) |
| Milestone 1 (MCAL)   | 🧭 Testing GPIO,SYSTICK,SW,LEDS,CLCD        | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/Our_Milestone_1) |
| Milestone 2 (UART)   | 📍 Integrating UART with other peripherals  | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/Our_Milestone_2) |
| Milestone 3 (EEPROM) | 📦 Location saving feature                  | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/mustafa/Milestone_4_EEPROM) |
| Milestone 4 (INT)    | 🚦 Interrupt-driven location actions        | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/mustafa/Milestone_5_Interrupt) |
| Coordinates DataBase | 📌 Parsing and managing coordinate data     | [Open](https://github.com/Ziad-1544/GPS-System-TIVAC/tree/ziad/Coordinates) |
| Documentation        | 📚 Project documentation and README formats | [Open](#) <!-- Add your documentation link here -->

---
🛠️ Implementation Details:
---
🚀 Phase 1 – Initial Setup & Driver Validation:

In the first phase of implementation, the team focused on setting up the foundational drivers and validating them through practical testing. The following steps were accomplished:

1. 🛠️ Driver Development:

Systick Driver: Implemented to provide accurate time delays and periodic actions.

GPIO Driver: Created to handle input/output operations with the Tiva C’s digital pins.

2. 🧪 Testing via Milestone 1:

A basic milestone project was developed to test and validate the functionality of both the Systick and GPIO drivers.

This served as a proof-of-concept and verified that the microcontroller could interact reliably with LEDs, switches, and timing routines.

---
🚀 Phase 2 – Serial Communication & Peripheral Integration:

This phase focused on enabling communication and integrating multiple user-interaction modules:

1.🔌 UART Driver Implementation:

Developed a UART (Universal Asynchronous Receiver/Transmitter) driver to enable serial communication between the Tiva C microcontroller and external systems .

2.🧩 Peripheral Driver Integration:

Integrated and tested additional drivers including:

CLCD (Character LCD).

LEDs.

Switches.

3.🧪 Testing via Milestone 2:

Created Milestone 2 to test communication between UART and the above drivers.

Verified correct data display on CLCD and interaction through switches and LED indicators.

---
🚀Phase 3 – EEPROM Implementation & Validation:

In this stage, the focus shifted to implementing non-volatile memory functionality using the EEPROM:

1.📦 EEPROM Driver Development:

Developed a driver to interface with EEPROM, enabling data storage across power cycles.

Ensured support for read/write operations with address-level control.

2.🧪 Testing via Milestone 3

Designed Milestone 3 specifically to test EEPROM functionality.

Validated correct saving and retrieval of data through various system states.

---
🚀Phase 4 – Interrupt Handling via GPIO:

This phase introduced interrupt-driven functionality, allowing the system to respond to asynchronous external events:

1.🧠 GPIO Interrupt Driver Development:

Implemented GPIO interrupt support for edge-triggered external inputs.

Enabled the microcontroller to react immediately to user actions (e.g., button presses) without constant polling.

2.🧪 Testing via Milestone 4:

Created Milestone 4 to validate the interrupt mechanism.

Confirmed stable operation of event-driven logic and responsiveness of the system.

---

⚙️ How to Use?
---
1.📦 Prepare the System

Connect the GPS module and ensure the location database is loaded.

2.📍 Real-Time Location Matching

The system continuously compares live GPS coordinates with predefined database entries.

3.✅ Activate Location Detection

Press the green switch to trigger location analysis.

4.📊 Display of Information

Upon detecting a match, the system shows:

a) Place name.

b) Distance from current position.

c) Number of visits.

d) Time of current visit.

5.🔴 Switch 1: Select Destination

Use the first red switch to scroll through and choose a location to navigate to.

6.🔴 Switch 2: Confirm Selection

Press the second red switch to confirm (enter) the selected destination.

7.🔴 Switch 3: Exit Point

Press the third red switch to mark that you’ve exited the selected location.

8.🔴 Switch 4: Interrupt - Visit Report

The fourth red switch triggers an interrupt, generating a report of all visited locations.



---

🎯 Conclusion:
---

This GPS System on Tiva C successfully demonstrates real-time location tracking using GPS data, integrated with custom-built drivers for UART, GPIO, EEPROM, interrupts, and peripheral interfaces. Through modular development and milestone-based validation, the system can detect known locations, calculate distances, log visit history, and respond to user input efficiently. The project highlights practical embedded systems design, interrupt-driven control, and structured data handling in a resource-constrained environment.

---
<div style="text-align:center">
👨‍💻 Team members:

| Name           | Member Photo                                                                 |
|----------------|--------------------------------------------------------------------------------|
| Ziad Kassem    | <img src="https://avatars.githubusercontent.com/u/170097123?v=4" width="200"/> |
| Randa Ayman    | <img src="https://avatars.githubusercontent.com/u/177648687?v=4" width="200"/> |
| Hussein Bahaa  | <img src="https://avatars.githubusercontent.com/u/201500976?v=4" width="200"/> |
| Mustafa Tamer  | <img src="https://avatars.githubusercontent.com/u/168356659?v=4" width="200"/> |
| Jessica Samuel | <img src="https://avatars.githubusercontent.com/u/201390497?v=4" width="200"/> |
| Ahmad Ezz-Eldeen | <img src="https://avatars.githubusercontent.com/u/153951438?v=4" width="200"/> |














