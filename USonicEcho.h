#ifndef __NB_USONICECHO
#define __NB_USONICECHO

#include "mbed.h"
#include "nworkbench.h"

#define IDLE           0x00
#define WAITINGECHO    0x01
#define ECHOSTARTED    0x02
#define ECHOCOMPLETE   0x03


class nBlock_USonicEcho: public nBlockSimpleNode<1> {

public:
    uint8_t _state = IDLE;
    uint32_t duration =0;
    uint8_t _flagReadRequested;
    nBlock_USonicEcho(PinName pinSDA);
    void triggerInput(nBlocks_Message message);
    void endFrame(void);
	void echostart(void);
	void echoend(void);	
    Timer _tmr;

	InterruptIn  _pingInt;

private:

	DigitalInOut _pingPin;

    

};

#endif
