#ifndef __NB_USONICECHO
#define __NB_USONICECHO

#include "mbed.h"
#include "nworkbench.h"

#define IDLE           0x00
#define WAITINGECHO    0x01
#define ECHOSTARTED    0x03
#define ECHOCOMPLETE   0x02


class nBlock_USonicEcho: public nBlockSimpleNode<1> {

public:
    uint_8 _state = IDLE;
    nBlock_USonicEcho(PinName pinSDA);
    void triggerInput(nBlocks_Message message);
    void endFrame(void);
	void echostart(void);
	void echoend(void);	
	
private:

	DigitalInOut _inout;
	InterruptIn  _int;

};

#endif
