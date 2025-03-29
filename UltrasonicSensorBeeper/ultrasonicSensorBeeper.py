import serial
import time
import numpy as np
import sounddevice as sd
import platform

# Set correct port name (check Arduino IDE for correct port)
# port_name = "COM3"  # For Windows (e.g., COM3)
# port_name = "/dev/ttyUSB0"  # For Linux
port_name = "/dev/tty.usbserial-1140"  # For Mac

# Set up serial communication
ser = serial.Serial(port_name, 9600, timeout=1)
time.sleep(2)  # Allow time for connection

# Function to generate and play a beep sound
def beep(frequency=1000, duration=0.2, sample_rate=44100):
    # Create the sine wave
    t = np.linspace(0, duration, int(sample_rate * duration), False)
    audio_wave = 0.5 * np.sin(2 * np.pi * frequency * t)
    
    try:
        # Play the sound with error handling
        sd.play(audio_wave, sample_rate)
        sd.wait()  # This blocks until sound finishes playing
    except Exception as e:
        print(f"Audio error: {e}")

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(line)

            # Define different beeping patterns
            if line == "BEEP_SLOW":
                beep(800, 0.5)  # Slow beep (800 Hz, 500 ms)
            elif line == "BEEP_MEDIUM":
                beep(1000, 0.3)  # Medium beep (1000 Hz, 300 ms)
            elif line == "BEEP_FAST":
                beep(1200, 0.1)  # Fast beep (1200 Hz, 100 ms)
            elif line == "CONTINUOUS_BEEP":
                beep(1500, 0.05)  # Continuous beep at higher frequency

except KeyboardInterrupt:
    print("Stopping...")
    ser.close()
