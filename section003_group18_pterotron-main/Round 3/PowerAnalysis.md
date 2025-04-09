# Power Analysis of Motor System

## Given Information
- **Power Supply:**  
  - 4 × AA NiMH Batteries (1.2V each)  
  - **Total Voltage:** 4.8V  
  - **Capacity:** 2500mAh (2.5Ah)  

- **Servo Motors:** (Hitec HS-422 ×3)  
  - **Operating Voltage:** 4.8V – 6.0V  
  - **No-load Current:** ~150mA  
  - **Stall Current:** ~800mA  

- **DC Motors:** (DFRobot 6V 160RPM Gear Motor ×2)  
  - **Operating Voltage:** 3-6V  
  - **Rated Current (at 6V):** ~250mA  
  - **Stall Current (at 6V):** ~1.6A  

Since the battery pack operates at **4.8V**, the motors will run slightly below their rated 6V values. For this analysis, we assume current scales proportionally with voltage.

---

## Nominal Case (Typical Operation)
Under normal operation, each servo motor draws **150mA**, and each DC motor draws **250mA**.

### **Total Current Draw:**

(3 x 150mA) + (2 x times 250mA) = 450mA + 500mA = 950mA


### **Total Power Consumption:**

P = V x I = 4.8V x 0.95A = 4.56W


This means that under normal conditions, the system consumes approximately **4.56W of power**.

---

## Worst-Case Scenario (All Motors Stalling)
If all motors stall, they draw their maximum current. The servo motors each consume **800mA**, while the DC motors each consume **1.6A**.

### **Total Current Draw:**

(3 x 800mA) + (2 x 1.6A) = 2.4A + 3.2A = 5.6A


### **Total Power Consumption:**

P = 4.8V x 5.6A = 26.88W

In this worst-case scenario, the power consumption jumps to **26.88W**, which is significantly higher than the nominal case.

---

## Battery Life Estimation
Given the battery's **capacity of 2500mAh (2.5Ah)**:

- **Nominal Case:**
  
  2.5Ah/0.95A = approx 2.63 hrs
  
  Under normal conditions, the batteries could last **about 2.6 hours**.

- **Worst Case (Stall):**
  
  2.5Ah/5.6A = approx 0.45 hours (27 minutes)}
  
  If the motors stall continuously, the batteries would drain in **about 27 minutes**.

---

## Key Takeaways
1. **Under normal conditions**, power consumption is **4.56W**, and the batteries could last **around 2.6 hours**.
2. **In a worst-case stall scenario**, power demand surges to **26.88W**, draining the batteries in **27 minutes**.
3. **Battery Current Limits:**  
   - AA NiMH batteries may struggle to supply **5.6A of current**, likely causing a **voltage drop** and potentially **cutting power** to the motors.  
4. **Potential Solution:**  
   - If your system frequently encounters high current spikes, consider using a **higher-capacity battery pack** (e.g., a larger NiMH pack or LiPo battery) to ensure stable performance.
