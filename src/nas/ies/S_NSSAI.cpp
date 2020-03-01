#include "S_NSSAI.hpp"
#include "logger.hpp"
using namespace nas;


S_NSSAI::S_NSSAI(uint8_t iei) {
        _iei = iei;
}
S_NSSAI::S_NSSAI(const uint8_t iei, uint8_t SST) {
        _iei = iei;
        length = 3;
        _SST = SST;
}
S_NSSAI::S_NSSAI() {}
S_NSSAI::~S_NSSAI() {}

void S_NSSAI::setS_NSSAI(uint8_t SST) {
        _SST = SST;
}
uint8_t S_NSSAI::getValue() {
        return _SST;
}

int S_NSSAI::encode2buffer(uint8_t *buf, int len) {
        Logger::nas_mm().debug("encoding S_NSSAI iei(0x%x)", _iei);
        if (len < length) {
                Logger::nas_mm().error("len is less than %d", length);
                return 0;
        }
        int encoded_size = 0;
        if (_iei) {
                *(buf + encoded_size) = _iei; encoded_size++;
                *(buf + encoded_size) = length - 2; encoded_size++;
                *(buf + encoded_size) = _SST;    encoded_size++;
        }
        else {
           //     *(buf + encoded_size) = length - 1; encoded_size++;
             //   *(buf + encoded_size) = _value; encoded_size++; encoded_size++;
 }
        Logger::nas_mm().debug("encoded S_NSSAI len(%d)", encoded_size);
        return encoded_size;
}

int S_NSSAI::decodefrombuffer(uint8_t *buf, int len, bool is_option) {
        Logger::nas_mm().debug("decoding S_NSSAI iei(0x%x)", *buf);
        int decoded_size = 0;
        if (is_option) {
                decoded_size++;
}
        length = *(buf + decoded_size); decoded_size++;
        _SST = *(buf + decoded_size);    decoded_size++;
        Logger::nas_mm().debug("decoded S_NSSAI value_SST(0x%x)",_SST);
        Logger::nas_mm().debug("decoded S_NSSAI len(%d)", decoded_size);
        return decoded_size;
}


