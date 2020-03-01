#include "Payload_Container.hpp"
#include "logger.hpp"
using namespace nas;

Payload_Container::Payload_Container(uint8_t iei) {
	_iei = iei;
}
Payload_Container::Payload_Container(const uint8_t iei, std::vector<PayloadContainerEntry> content) {
	_iei = iei;
	length = 4 + content.size() * 2;  
	CONTENT.assign(content.begin(), content.end());
	for (int i = 0; i < content.size(); i++) {
		length = length + content.at(i).optionalIE.size() * 2;
		for (int j = 0; j < content.at(i).optionalIE.size(); j++) {
			length+= blength(content.at(i).optionalIE.at(j).ie_value);
		}
	}
}
Payload_Container::Payload_Container() {}
Payload_Container::~Payload_Container() {}

void Payload_Container::setValue(uint8_t iei, uint8_t value) {
	_iei = iei;
	//_value = value;
}
void Payload_Container::getValue(std::vector<PayloadContainerEntry> &content) {
	content.assign(CONTENT.begin(), CONTENT.end());
}

int Payload_Container::encode2buffer(uint8_t *buf, int len) {
	Logger::nas_mm().debug("encoding Payload_Container iei(0x%x)", _iei);
	if (len < length) {
		Logger::nas_mm().error("len is less than %d", length);
		return 0;
	}
	int encoded_size = 0;
	if (_iei) {
		*(buf + encoded_size) = _iei; encoded_size++;
		*(buf + encoded_size) = (length - 2)&0x00ff; encoded_size++;
		*(buf + encoded_size) = (length - 2) & 0xff00; encoded_size++;
		*(buf + encoded_size) = CONTENT.size(); encoded_size++;
		for (int i = 0; i < CONTENT.size(); i++) {
			/*Length of Payload container entry*/
			*(buf + encoded_size) = CONTENT.at(i).optionalIE.size() * 2 + 1;
				for (int j = 0; j < CONTENT.at(i).optionalIE.size(); j++) {
					*(buf + encoded_size) += blength(CONTENT.at(i).optionalIE.at(j).ie_value);
				}
			encoded_size++;
			/*Length of Payload container entry*/
			*(buf + encoded_size) = ((CONTENT.at(i).optionalIE.size()&0x0f)<<4)| CONTENT.at(i).payloadContainerType;
			encoded_size++;
			for (int j = 0; j < CONTENT.at(i).optionalIE.size(); j++) {
				*(buf + encoded_size) += CONTENT.at(i).optionalIE.at(j).ie_type; encoded_size++;
				*(buf + encoded_size) += CONTENT.at(i).optionalIE.at(j).ie_len; encoded_size++;
				int size = encode_bstring(CONTENT.at(i).optionalIE.at(j).ie_value, (buf + encoded_size), len - encoded_size);
				encoded_size += size;
			}
		}
	}
	else {
		*(buf + encoded_size) = (length - 2) & 0x00ff; encoded_size++;
		*(buf + encoded_size) = (length - 2) & 0xff00; encoded_size++;
		//*(buf + encoded_size) = _value; encoded_size++;
	}
	Logger::nas_mm().debug("encoded Payload_Container len(%d)", encoded_size);
	return encoded_size;
}

int Payload_Container::decodefrombuffer(uint8_t *buf, int len, bool is_option) {
	Logger::nas_mm().debug("decoding Payload_Container iei(0x%x)", *buf);
	int decoded_size = 0;
	uint8_t num_entries;
	uint8_t num_optional;
	IE_t value;
	PayloadContainerEntry payloadcontainerentry;
	if (is_option) {
		decoded_size++;
	}
	length = 0x00;
	length |= *(buf + decoded_size); decoded_size++;
	length |= (*(buf + decoded_size)) << 8; decoded_size++;
	num_entries = *(buf + decoded_size); decoded_size++;
	while (num_entries) {
		uint8_t Length_entry = *(buf + decoded_size); decoded_size++;
		payloadcontainerentry.payloadContainerType = *(buf + decoded_size) & 0x0f;
		num_optional = (*(buf + decoded_size) & 0xf0) >> 4; decoded_size++;
		while (num_optional) {
			value.ie_type = *(buf + decoded_size); decoded_size++;
			value.ie_len = *(buf + decoded_size); decoded_size++;
			decode_bstring(&value.ie_value, value.ie_len, (buf + decoded_size), len - decoded_size);
			decoded_size += value.ie_len;
			payloadcontainerentry.optionalIE.insert(payloadcontainerentry.optionalIE.end(), value);
			num_optional--;
		}
		CONTENT.insert(CONTENT.end(), payloadcontainerentry);
		num_entries--;
	}
	//Logger::nas_mm().debug("decoded Payload_Container value(0x%x)", _value);
	Logger::nas_mm().debug("decoded Payload_Container len(%d)", decoded_size);
	return decoded_size;
}



