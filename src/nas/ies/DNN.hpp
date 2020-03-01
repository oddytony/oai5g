#ifndef __DNN_H_
#define __DNN_H_

#include <stdint.h>

namespace nas {

	class DNN {
	public:
		DNN();
		DNN(uint8_t iei);
		DNN(const uint8_t iei, uint8_t _length, uint8_t value);
		~DNN();
		void setValue(uint8_t iei, uint8_t value);
		int encode2buffer(uint8_t *buf, int len);
		int decodefrombuffer(uint8_t *buf, int len, bool is_option);
		uint8_t getValue();
	private:
		uint8_t _iei;
		uint8_t length;
		uint8_t _value;

	};



}










#endif

