#include "USonicEcho.h"

nBlock_USonicEcho::nBlock_USonicEcho(PinName EchoPin) :
			_pingPin(EchoPin), _pingInt(EchoPin) {

    (this->_pingInt).rise(callback(this, &nBlock_USonicEcho::echostart));
    (this->_pingInt).fall(callback(this, &nBlock_USonicEcho::echoend));
	//_pingInt.rise(&nBlock_USonicEcho::echostart);		// RISING EDGE ISR
	//_pingInt.fall(&echoend);		// FALLING EDGE ISR

	_state = IDLE;
	
}

void nBlock_USonicEcho::triggerInput(nBlocks_Message message) {
	// inputNumber is ignored as we only have one input
	// value is ignored as any value is considered a trigger for reading
	// If we received ANY input, means we should activate the sensor
	_flagReadRequested = 1;
}

void nBlock_USonicEcho::endFrame(void) {	
    // If an Echo has been requested
	if (_flagReadRequested) {
		_flagReadRequested = 0;	
		if (_state == IDLE) {
			_pingPin.output();	// Trigger the Ultrasonic Tranmission with a LOW-HIGH-LOW
			_pingPin = 0;
			wait_us(2);
			_pingPin = 1;
			wait_us(4);			// The PING Board is triggered by a HIGH pulse of 2 or more microseconds.
			_pingPin = 0;
			_pingPin.input(); 	// the echo will rise after 800 us and fall after 200us for 3cm (minimum), or 18ms for 300cm (maximum)
			_state = WAITINGECHO;	// The Ultrasonic Sensor is Triggered, ISR will update the _status and duration variables
		}
	}

	// ISR has updated the _status and duration
	if (_state == ECHOCOMPLETE) {
		_state = IDLE; 
		output[0] = duration;	// Update Node Output
		available[0] = 1;		// Update Node Output Availability
		_tmr.reset();
	}

return;
}

// Rising Edge ISR
void nBlock_USonicEcho::echostart() {
	if (_state == WAITINGECHO){
		_tmr.start();
		_state = ECHOSTARTED;
	}
}

// Falling Edge ISR
void nBlock_USonicEcho::echoend() {
	if (_state == ECHOSTARTED){
		duration = _tmr.read_us();
		_tmr.stop();
		_state = ECHOCOMPLETE;
	}
}

