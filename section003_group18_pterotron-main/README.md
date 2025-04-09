# PteroTron MREN 303 Team 18
Group Members: Josh Westlake and Paul Booth
![My Image](/Round%205/IMG_5163.jpg)


## Global Index
- [Home](/README.md)   |     [Round 1](/Round%201/README.md)    |    [Round 2](/Round%202/README.md)     |     [Round 3](/Round%203/README.md)  |    [Round 4](/Round%204/README.md)    |   [Round 5](/Round%205/README.md) 

# Main
- [Work Plan](#work-plan)
- [Resource List](#resource-list)
- [Risk Management](#risk-management)

# Design Round 1:

### **Primary Goals**
Over the course of the first round of this design project the team set out to achieve a variety of key goals which will be built upon going forward: 
1. **Achieve the Design Review Deliverables**
   - In order to stay up to date and esnure that all milestones were met the team ensured to produce preliminary designs, functional specifications, health and safety procedures and explored a variety of risk mitigation strategies.
   
2. **Finalize conceptual design features**
   - Brainstorm  and document a variety of possible solutions
   - The team wanted to ensure that all possible solutions were considered before deciding upon a s solutions and selecting a design to begin the prototyping stage going forward.

3. **Understand the resources and technology avalible**
    - The team spend a large portion initializing the various motors and exploring the ins and outs of each of the components
    - The team wanted to gain a good understanding of the components being worked with as well as thier limitations.



## **Goals and Objectives**

### 1. **Achieve the Design Review Deliverables**
   - #### Raspberry Pi Connectivity
        -Establish a reliable sourse of connectivity between the Raspberry Pi Pico W and Personnel computer.
        - Task succesfully completed, allowing communication between the usb connected Logitech Controller and Pico W
        - Task completed by Josh
   - #### Battery Monitoring System
        - Intialize a simple battery monitoring system using a voltage divider circuit and provided code
        - Task completed by Josh
   - #### Brainstorming
        - Hosted team-wide brainstorming sessions in order to explore as many possibilities and begin narrowing down designs
   - #### Prototyping
        - Begin cardboard prototyping stage in order to produce a very rapid prototype of the gripping mechanism that will be used.
        - Cardboard prototype was made to resemble its final design with two connecting pieces to simulate the opening and closing of the gripper.
        - A cardboard base with an arm was also added and attached to the gripper. 
   - #### Identify Key Risks and Mitigation Strategies
        - Create a risk matrix listing all potential risks associated with the design.
        - Develop mitigation strategies for each identified risk (e.g., pinch points, component failure).
        - Assign team members to monitor and address risks throughout the project.
        - One major risk to be aware of is the arm being too heavy to be controlled by the motor. A fix for this would be to use two motors to lift the arm, however that leaves only 1 other motor for other applications.
        - Another risk is component failure which can be mitigated by trying to avoid putting any stress on the components and overloading them.
        

### 2. **Finalize Initial Prototypes**
   - Build and test prototypes for key subsystems (e.g., sensor mounts, motor integration).
   - Further prototyping will be done to create the full arm mechanism using cardboard before final implementation is complete 
   - Record changes made during prototyping for future reference.

### 3. **Complete Detailed Design Documentation**
   - Compile technical documentation, including CAD models, BOM, and functional specifications.
   - Ensure that design decisions (e.g., material choice, component sizing) are clearly explained.
   - Review documentation for clarity, accuracy, and completeness.


### Health and Safety Considerations

After reviewing and reflecting on the plan, please add a statement to indicate that:
1. **your team has reviewed the plan at the beginning of Round 2**
    - The plan has been reviewed again for Round 2 and all the health and safety protocols are still being followed
2. **affirm that your team is meeting or not meeting the plan (all or some aspects), and**
    - The team is still meeting the plan
3. **summarize any changes you have made.**
    - No changes have been made to the plan as nothing new needs to be added because the original plans already took everything into account
4. **If you are not meeting some aspect of the plan, please add why and what you plan to do differently**
    - All aspects are being met

# Design Round 2

1. **What are the specific goals for this round? Aside from meeting this round’s design review deliverables, what are your own goals?**
    - Write the code to control all the sensors and motors specific functions for the robot
    - Become familiar the Autodesk Fusion and begin 3D printing gripper prototypes for the robot

2. **What are the backlog items from last round?**
    - Our team still has to present the cardboard prototype from Round 1 because Paul joined the team late so the due date was extended

3. **What are the tasks needed to achieve each goal, including the backlog items?**
    - The team has to design the gripper for the robot in Autodesk Fusion and 3D print a few test prototypes to make sure the design will work as intended
    - Present the finished cardboard prototype
    - Use the given test sample codes for the sensors and motors and then use and build off of them to create the final code for each part to control the robot

4. **Who is responsible for each task/goal?**
    - Both team members are going to be designing robot parts for printing
    - Josh will write the code for the sensors and motors
    - Paul will complete the documentation
    
---
# Overall Strategy

## Autonomous Mode
- The robot will autonomously navigate using the line following sensor which had been mounted to the bottom of the robot using a custom 3D printed Piece. 
- It will employ a PI controller allowing it to accurately and smoothly follow the line and rapidly travel to the gate with more consistancy then using the button press method

## Manual Mode
- The robot will be focused on:
    1. Collecting Minions (highest priority)
    2. Collecting Dinosours 
    3. Collecting Ken (lowest priority)

# 3D Printing Usage Tracker  

## Print Log  

| **Part Name**       | **Filament Used (g)** | **Quantity** | **Volume (in³)** |  
|---------------------|----------------|----------|----------------|  
| DC Motor Mount     | 1.22           | 2        | 0.060          |  
| Wheels            | 18.75          | 2        | 0.923          |  
| Marble Mount      | 2.28           | 1        | 0.112          |  
| Corner Brackets   | 0.72           | 4        | 0.035          |  
| Lower Arm Piece   | 7.2            | 2        | 0.354          |  
| Upper Arm Piece   | 12.91          | 2        | 0.635          |  
| Upper Arm Piece   | 12.30          | 2        | 0.605          |  
| Gripper Piece     | 134.5          | 1        | 6.619          |  
| **Total**         | **189.88**      | **16**   | **9.344**      |  
