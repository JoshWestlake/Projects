# Project Documentation: Design Round 1

## Overview

This document summarizes activities, deliverables, and milestones for Round 1 of the **MREN 303 Mechatronics and Robotics Design III** course.


## Activities and Deliverables

Over the course of round 1 the team has met a variety of milestones and predefined goals which are highlighted throughout the following documentation.

### Workshop 1.2: Kit Introduction, Team Formation, and Brainstorming
---
During the very first work period the team was formed, kit was recieved and the group ensured that all components had been provided within the kit - initially we were missing a motor driver.

The team name was selected and the gitlab was created

Basic brainstorming took place to explore a variety of different designs for the robotic mobility system and gripper/actuator design.


### Workshop 2.1: Raspberry Pi Pico W, Remote Control, and Battery Monitoring
- **Installation**:
The team focussed much of the second work period on establishing which tools will be used for the project in order to ensure all members have access - minimizing an integration issues later down the line. 
  - Tools to be used: Arduino IDE, VSCode, Python, SolidWorks
  - Scripts: `PicoUDPGamepadRead_BatteryRead.ino`, `MREN_303_Pico_W_Wifi_Gamepad_Input.py`, and `GetMACIP.ino`.
- **Status Update**:
  1. Verify MAC/IP address configuration.
  The group was able to succesfully verify the mac address and IP configuration  of the pico and has decided that the networking from this point on will be built on the basis of a personnel hotspot.
    
    The Pico W's device attributes are as follows:
    MAC:_____________
    IP: 172.20.10.10

  2. Establish communication between gamepad and Raspberry Pi Pico W. The team was succesfully able to connect the LED control using gamepad buttons and Implement and verify a battery monitoring system using a voltage divider.

    __insert image__

---
### Workshop 2.2: Design on Paper, Safety, and Risk Mitigation
- **Scrum Planning**:
  - Specific goals, task assignments, and resource requirements.
- **Health and Safety**:
  - Identification of safety risks and mitigation strategies.
- **Risk Management**:
  - A risk assessment matrix documenting likelihood, impact, and response plans.
- **Design Sketches**:
  - Back-of-the-envelope calculations for key design parameters.

---

### Workshop 3.1: Cardboard Prototyping and Team Assessment
**Prototype Module**:

The team decided to focus it's resources on the design of the arm and gripper mechanisms that will be used to manipulate each of the objects in play
  The team will attempt to produce a variance of the below arm mechanisms which allows for a greater degree of freedom than that of a single jointed robot (as seen below): 
  ![signle jointed arm](https://cdn.numerade.com/ask_images/bb75a4997d7d477c8ea338751b5d9520.jpg)

The below robot featurs 2 major joints allowing for a greater degree of freedom, however, exponenetially greater compexity for designing the mechanism.

In order ensure that the robotic arm will be a feasible option the team has turned its focus to designing a carboard prototype which will serve as a proof of concept before further time and resources are reserved for the componenets

![Concept Robotic Arm](https://i.etsystatic.com/18279136/r/il/e8f6a8/4705720755/il_1588xN.4705720755_m8mh.jpg)

The resulting card-board prototpye can be seen below...

**insert image of protoype**

---

### Workshop 3.2: Design Review 1 and Work Plan
- **Functional Design Table**:
  - Complete FRDPARRC table with functional requirements, design parameters, and risks.
- **Work Plan**:
  - SMART goals, project milestones, task assignments, and timelines.

---

## Deliverables and Deadlines

### Key Submissions:
- [x] Markdown documentation (e.g., `README.md`)..
- [x] Updated scripts in the team repository.
- [ ] Risk assessment and health/safety plans.

### Milestone Demonstrations:
- [x] Communication between Raspberry Pi Pico W and gamepad.
- [x] Battery monitoring functionality.
- [ ] Cardboard prototype explanation and demonstration.




## Peer and Self-Assessments
- Complete ITP Metrics **Team Health and Peer Feedback Assessment** by January 26, 2025.


