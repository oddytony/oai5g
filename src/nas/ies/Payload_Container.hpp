#ifndef __Payload_Container_H_
#define __Payload_Container_H_
#include <iostream>
#include <stdint.h>
#include <vector>
extern "C" {
#include "bstrlib.h"
#include "TLVEncoder.h"
#include "TLVDecoder.h"
}
namespace nas {
typedef struct {
	uint8_t ie_type;
	uint8_t ie_len;
	bstring ie_value;
}IE_t;
typedef struct {
	uint8_t ie_type;
	uint16_t ie_len;
	bstring ie_value;
}IE_t_E;
typedef struct {
	uint8_t payloadContainerType : 4;
	std::vector<IE_t> optionalIE;
}PayloadContainerEntry;
	class Payload_Container {
	public:
		Payload_Container();
		Payload_Container(uint8_t iei);
		Payload_Container(const uint8_t iei, std::vector<PayloadContainerEntry> content);
		~Payload_Container();
		void setValue(uint8_t iei, uint8_t value);
		int encode2buffer(uint8_t *buf, int len);
		int decodefrombuffer(uint8_t *buf, int len, bool is_option);
		void getValue(std::vector<PayloadContainerEntry> &content);
	private:
		uint8_t _iei;
		uint16_t length;
		std::vector<PayloadContainerEntry> CONTENT;

	};



}










#endif



