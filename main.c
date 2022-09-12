/*
 *
 *
Communication Command Frame Format:
Header	Header 2	Address		Data 	Length	Command	Data	Checksum
0x55	0xAA		1 byte		1 byte	1 byte	Data 1～Data n	1 byt

hosts	HUSKYLENS
COMMAND_REQUEST_KNOCK===>
<===COMMAND_RETURN_OK
COMMAND_REQUEST===>
<=== COMMAND_RETURN_INFO
<=== COMMAND_RETURN_BLOCK
<=== COMMAND_RETURN_BLOCK
<=== COMMAND_RETURN_ARROW
COMMAND_REQUEST_BLOCKS====>
<=== COMMAND_RETURN_INFO
<=== COMMAND_RETURN_BLOCK
<=== COMMAND_RETURN_BLOCK
COMMAND_REQUEST_ARROWS====>
<=== COMMAND_RETURN_INFO
<=== COMMAND_RETURN_ARROW
COMMAND_REQUEST_ALGORITHM===>
<===COMMAND_RETURN_OK
COMMAND_REQUEST_ALGORITHM===>
COMMAND_REQUEST_ALGORITHM===>
<===COMMAND_RETURN_BUSY
<===COMMAND_RETURN_OK

 */
 
#include "debug.h"
#include "ch32v307_config_all.h"
#include "HUSKYLENS.h"

/* Global typedef */
typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

HUSKYLENS huskylens;
int left = 0, right = 0;
 
int main(void)
{
	Config_all();
	Delay_Init();
	USART_Printf_Init(115200);
	printf("LINE FOLLOWER USING CH32V307 & HUSKYLENS\r\n")
	huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.
	while(1){
	HUSKYLENSResult result = huskylens.read();
        printResult(result);
 
        error = (int32_t)result.xTarget - (int32_t)160;
        headingLoop.update(error);
        left = headingLoop.m_command;
        right = -headingLoop.m_command;
        left += speed;
        right += speed;
		printf("%d \t %d\r\n",left,right);
		setspeed(left,right);
	}
}
 