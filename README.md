# libDynamixel
This is a C++ interface to control [ROBOTIS](http://www.robotis.com) [Dynamixel smart servos](http://www.robotis.com/xe/dynamixel_en). This library provides an API to perform basic low-level functionality of dynamixel servos, plus a higher-level convenience layer on the top of basic API.

# Usage
Each servo type has an abstraction defined in the library. The communication layer is completely isolated and supposed to be managed by libSerial. You will need to pass a reference to a `SerialStream` object for each servo when initializing it.

    #include <SerialStream.h>     /* It's libSerial's business to communicate */
    #include <dynamixel/mx28.hpp> /* We want to control two MX-28 */
    #include <dynamixel/ax12.hpp> /* And a AX-12 */
    using namespace std;
    using namespace Dynamixel;
    using namespace LibSerial;
    
    int main() {
        SerialStream stream{"/dev/ttyUSB0", SerialStreamBuf::BAUD_57600,
			SerialStreamBuf::CHAR_SIZE_8, SerialStreamBuf::PARITY_NONE, 1,
			SerialStreamBuf::FLOW_CONTROL_NONE};
		MX28 m1 { stream, 1 };  /* Initialize a MX-28 with id `2' */
		MX28 m2 { stream, 2 };
		AX12 m3 { stream, 3 }
		// Rotate by 90 degree, and 10 RPM:
		m1.rotate(90.0f,Dynamixel::AngleUnit::Degree,
		          20.0f, Dynamixel::VelocityUnit::RPM);
		// Rotate by 1024 steps, and speed of 500 units:
		m1.rotate(1024.0f, 500.0f);
		// Or:
		m1.rotate(1024.0f,Dynamixel::AngleUnit::Default,
		          500.0f, Dynamixel::VelocityUnit::Default);
		// Sense information:
		while(m1.moving()) {
		    	cout << m1.presentLoad() << endl;
	            cout << m1.presentPosition() << endl;
	            cout << m1.presentSpeed() << endl;
                cout << m1.presentTemperature() << endl;
                cout << m1.presentVoltage() << endl;
		}
		// Set acceleration:
		m1.setGoalAcceleration(100);
		// Set ID:
		m1.setID(4);
		// Do whatever you want (:
		return 0;
    }

# Compile
Please refere to INSTALL.