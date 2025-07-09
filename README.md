#  Indoor Air Quality Monitoring System (IoT + Cloud + Web)

This project is a complete IoT-based **Indoor Air Quality Monitoring System** that monitors **temperature, humidity**, and **air quality**, with real-time cloud updates, a custom login system, and an interactive web dashboard.

---

##  Features

-  Real-time sensor data collection using ESP32
-  Data transmission to **ThingSpeak** cloud platform
-  **Automatic & Remote Buzzer Control** based on air quality
-  **Login and Signup System** using **Google Sheets** and Apps Script
-  Clean and responsive **web interface using HTML/CSS**
-  Data visualization on ThingSpeak + logs in Google Sheets

---

##  Technologies Used

| Layer         | Tools/Technologies               |
|---------------|----------------------------------|
| Microcontroller | ESP32                         |
| Cloud Logging   | ThingSpeak, Google Sheets     |
| Web Frontend    | HTML, CSS                     |
| Backend Logic   | Google Apps Script (for auth) |
| Programming     | Arduino C++, JavaScript       |

---

##  How It Works

1. **ESP32** reads temperature, humidity, and gas levels from sensors.
2. Data is sent every 10 seconds to **ThingSpeak**.
3. A buzzer is triggered automatically if air quality is poor.
4. Users can remotely turn the buzzer ON/OFF by updating a ThingSpeak field.
5. Sensor data is also logged in **Google Sheets** using a connected Web App.
6. Users must **sign up or log in** to view the dashboard.
7. The frontend fetches and displays data from ThingSpeak or Google Sheets.

---

##  Google Sheets Login System

- Login and signup forms are handled by **Google Apps Script**.
- User credentials (email/password) are stored securely in a Google Sheet.
- Scripts validate user input and grant or deny access accordingly.

---

##  ThingSpeak URL

https://thingspeak.mathworks.com/login?skipSSOCheck=true


