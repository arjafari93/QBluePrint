# QBlueprint

[![QBlueprint Overview](https://github.com/arjafari93/QBluePrint/blob/master/ScreenShots/screenshot1Youtube.jpg)](https://www.youtube.com/playlist?list=PLWlFycMes7_7DIiUJyj-BgJh1ARTclklZ)  


**See Demo Videos at my [YouTube Channel](https://www.youtube.com/playlist?list=PLWlFycMes7_7DIiUJyj-BgJh1ARTclklZ)**


QBlueprint is a **visual programming tool** built with **Qt C++ and QML**. It is inspired by Unreal Engine’s Blueprint system but is much simpler and designed for general-purpose use. Users can create logic visually by **dragging and dropping boxes** onto a workspace, connecting their input and output terminals, and allowing data to flow between them.

The project currently uses **Qt 5.15** and **qmake**, with plans to support **CMake and Qt 6** in future updates.

Tested on **Windows and Linux**.

![License: BSD 3-Clause](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)
![Build Status](https://github.com/arjafari93/QBluePrint/actions/workflows/main.yml/badge.svg)
![GitHub release](https://img.shields.io/github/v/release/arjafari93/QBluePrint)
![GitHub stars](https://img.shields.io/github/stars/arjafari93/QBluePrint?style=social)
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen)
![GitHub all releases](https://img.shields.io/github/downloads/yourusername/yourrepository/total)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-blue)


## Key Features

### 🔹 Visual Logic Creation
<p align="center">
    <img src="https://github.com/arjafari93/QBluePrint/blob/master/ScreenShots/screenshot2.JPG" alt="Feature 1" width="45% style="margin-right: 10%;"">
    <img src="https://github.com/arjafari93/QBluePrint/blob/master/ScreenShots/screenshot3.JPG" alt="Feature 2" width="45%">
</p>
  
- Drag and drop functional boxes onto the workspace.
- Connect input and output terminals to establish structured data flow.
- No programming knowledge required—construct logic visually.

### 🔹 Comprehensive Box Library
QBlueprint includes various **box types**, categorized by function:
<img src="https://github.com/arjafari93/QBluePrint/blob/master/ScreenShots/screenshot4.JPG" alt="Dark/Light Theme" width="25%" align="right">
- **Logical Operations:** AND, OR, NOT, etc.
- **Bitwise Operations:** AND, OR, XOR, Left SHIFT, Right SHIFT, etc.
- **Mathematical Operations:** Multiplication, Division, Modulus, Absolute, Power, etc.
- **Comparative Operators:** Equal (`==`), Less than (`<`), Greater than (`>`), etc.
- **Conditional Branching** to control execution flow.
- **Input Sources:** TCP/UDP servers, Timer-based triggers.
- **Output Sinks:** TCP/UDP clients, Line-series chart visualization, String View Sink.

### 🔹 Enhanced User Experience
- **Dark/Light mode** for better readability.
- **Zoom In/Out** functionality for easier navigation.
- **Blueprint Persistence:**
  - Save and load blueprints as JSON files.
  - Stores box positions, input data, connections, and other details.

## 🚀 Roadmap and Future Enhancements
QBlueprint is still in its early stages, with many planned improvements:
- Expanding the **box library** with more logic and computational tools.
- Improving the **user interface and usability**.
- Enhancing **performance** for smoother operation.
- Adding options for **custom boxes** and user-defined behaviors.
- Implementing **CMake and Qt 6 support**.

## 🛠️ Installation Guide
To build and run QBlueprint:

1. **Install Qt** (Recommended: Qt 5.15; Qt 6 support coming soon).
2. Clone the repository:
   ```sh
   git clone https://github.com/arjafari93/QBlueprint.git
   cd QBlueprint
   ```
3. Open the project in **Qt Creator** or compile manually with **qmake**:
   ```sh
   qmake QBlueprint.pro
   make -j$(nproc)
   ./QBlueprint
   ```
   _(CMake-based builds will be introduced in future updates.)_


## 💡 Usage Instructions
1. Launch the application.
2. Drag and drop boxes from the sidebar into the workspace.
3. Connect input and output terminals.
4. your blueprint will Run and visualize in real time.
5. Save and load blueprints as **JSON files**.

## 🤝 Contributions
Contributions are welcome! Feel free to fork the repository and submit pull requests with improvements or new features.

## 📜 License
Licensed under the BSD 3-Clause License

Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)

This software is provided "as is", without warranty of any kind. You may use, modify, and distribute this software, but you MUST keep the copyright notice and credit the original author.

## 📬 Contact and Support
For suggestions, feature requests, or collaboration inquiries, contact **[alirezajafari28@gmail.com]** or visit **[https://alirezajafari.ir/]**.

## ⚠️ Disclaimer
This software is a **personal project** and is provided **as-is**, without any guarantees of stability, security, or ongoing support. Use at your own risk.

