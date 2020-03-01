#include "DNN.hpp"
#include "logger.hpp"
using namespace nas;

DNN::DNN(uint8_t iei) {
	_iei = iei;
}
DNN::DNN(const uint8_t iei, uint8_t _length, uint8_t value) {
	_iei = iei;
	_value = value;
	length = _length;
}
DNN::DNN() {}
DNN::~DNN() {}

void DNN::setValue(uint8_t iei, uint8_t value) {
	_iei = iei;
	_value = value;
}
uint8_t DNN::getValue() {
	return _value;
}
int DNN::encode2buffer(uint8_t *buf, int len) {
	Logger::nas_mm().debug("encoding DNN iei(0x%x)", _iei);
	if (len < length) {
		Logger::nas_mm().error("len is less than %d", length);
		return 0;
	}
	int encoded_size = 0;
	if (_iei) {
		*(buf + encoded_size) = _iei; encoded_size++;
		*(buf + encoded_size) = (length - 2); encoded_size++;
		*(buf + encoded_size) = _value; encoded_size++;

	}
	else {
		*(buf + encoded_size) = (length - 1); encoded_size++;
		*(buf + encoded_size) = _value; encoded_size++;
	}
	Logger::nas_mm().debug("encoded DNN len(%d)", encoded_size);
	return encoded_size;
}

int DNN::decodefrombuffer(uint8_t *buf, int len, bool is_option) {
	Logger::nas_mm().debug("decoding DNN iei(0x%x)", *buf);
	int decoded_size = 0;
	if (is_option) {
		decoded_size++;
	}
	_value = 0x00;
	length = *(buf + decoded_size); decoded_size++;
	_value = *(buf + decoded_size); decoded_size++;
	Logger::nas_mm().debug("decoded DNN value(0x%x)", _value);
	Logger::nas_mm().debug("decoded DNN len(%d)", decoded_size);
	return decoded_size;
}

