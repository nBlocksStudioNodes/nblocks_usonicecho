#include "USonicEcho.h"

nBlock_USonicEcho::nBlock_USonicEcho(PinName EchoPin) :
			_inout(EchoPin), _int(EchoPin) {
		
	_int.rise(&echostart);
	_int.fall(&echoend);
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
			pingPin.output();	// Trigger the Ultrasonic Tranmission with a LOW-HIGH-LOW
			pingPin = 0;
			wait_us(2);
			pingPin = 1;
			wait_us(4);			// The PING Board is triggered by a HIGH pulse of 2 or more microseconds.
			pingPin = 0;
			pingPin.input(); 	// the echo will rise after 800 us and fall after 200us for 3cm (minimum), and 25ms for 300cm (maximum)
			_state = WAITINGECHO;
		}
	}

	if (_state == ECHOCOMPLETE) {
		duration = tmr.read_us();
		_state = IDLE; 
		output[0] = duration;
		available[0] = 1;
	}

return;
}//endFrame


void nBlock_USonicEcho::echostart() {
	if (_state == WAITINGECHO){
		_tmr.start();
		_state = ECHOSTARTED;
	}
}

void nBlock_USonicEcho::echoend() {
	if (_state == ECHOSTARTED){
		_tmr.stop();
		_state = ECHOCOMPLETE;
	}
}

