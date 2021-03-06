#include "protocol.h"
#include "bytebuffer.h"
//设备布防/撤防 反馈
//-------
//标识位 1 byte "0xCE"
//消息长度 2 bytes 标识位(含)字节长度长度
//消息ID 2 bytes 0x00 0x0F
//DeviceID 8 bytes  设备ID
//Result 1 byte 0 fail 1 success
//校验码 (从开头到校验位前一位的^)
//标识位 1 byte
//-------
//
unsigned int protocol_encode_arm_feedback(unsigned char * buf, unsigned long long ieee, unsigned char result){
	unsigned char *p = buf;
	bytebuffer_writebyte(&p,PROTOCOL_START_FLAG);
	bytebuffer_writeword(&p,16);
	bytebuffer_writeword(&p,DEVICE_ARM_FEEDBACK);
	bytebuffer_writequadword(&p,ieee);
	bytebuffer_writebyte(&p, result);

	unsigned char checksum = protocol_checksum(buf,p-buf);
	bytebuffer_writebyte(&p,checksum);
	bytebuffer_writebyte(&p,PROTOCOL_END_FLAG);

	return p-buf;
}
