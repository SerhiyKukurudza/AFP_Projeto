# TAIPS - Aircraft Fleet Management

TAIPS is a console-based C application designed to manage a small fleet of aircraft. It features a custom, interactive graphical user interface built directly into the Windows command prompt, allowing users to navigate through menus using arrow keys.

## Overview

The system allows administrators to manage aircraft, handle flight authorizations, register passengers, and track flight histories. Data persistence is ensured by saving the fleet's state into a binary file (`Aeronaves.bin`), meaning data is not lost between sessions.

## Features

The application is divided into several core functionalities accessible via an interactive menu:

### Fleet Management

* **Add Aircraft:** Register a new aircraft to the fleet (up to a maximum of 10). You can define its capacity (2 to 4 passengers) and its initial location (Vila Real, Tires, or Portimão).
* **Remove Aircraft:** Delete an aircraft from the system.
* **Edit Aircraft:**
  * Modify passenger capacity and number of flights (for aircraft in the "Ready" state).
  * Add, edit, or remove passengers and change the destination (for aircraft "Waiting for Authorization").

### Flight Operations

* **Initiate Flight Request:** Select a ready aircraft, input passenger details (NIF and Name), choose a destination, and place the aircraft in a "Waiting for Authorization" state.
* **Authorize Flight:** Approve a pending flight. This updates the aircraft's current location, adds the route to its flight history (keeping track of the last 3 flights), clears the passenger manifest, and sets the state back to "Ready".
* **Cancel Flight:** Reject a pending flight, clearing the destination and passenger list, and reverting the aircraft's state to "Ready".

### Listing and Consultation

* **Ranked List:** Display all aircraft ordered by the number of flights performed (descending order).
* **State-based Filtering:** List aircraft that are either "Ready" or "Waiting for Authorization" (can be filtered globally or by a specific location).
* **Specific Consultation:** Search for an aircraft by its ID to view its full details, including current passengers and its history of the last 3 flights.

### Data Persistence

* **Auto-Save:** The system automatically loads data from `Aeronaves.bin` on startup and saves any changes when exiting the application safely (via the Exit option or pressing ESC).
* **Manual Save:** Option to manually force a data save to the binary file from the main menu.

## Tech Stack & Requirements

* **Language:** C
* **Platform:** Windows (Strictly requires a Windows environment due to the use of `windows.h` for console window sizing/colors and `conio.h` for capturing arrow key inputs).
* **Data Storage:** Binary File Handling (`fread`, `fwrite`).
