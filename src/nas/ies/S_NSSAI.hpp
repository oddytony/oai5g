#ifndef __S_NSSAI_H_
#define __S_NSSAI_H_

#include <stdint.h>

namespace nas {

        class S_NSSAI {
        public:
			S_NSSAI();
			S_NSSAI(uint8_t iei);
			S_NSSAI(const uint8_t iei, uint8_t SST);
                ~S_NSSAI();
                void setS_NSSAI(uint8_t SST);
                int encode2buffer(uint8_t *buf, int len);
                int decodefrombuffer(uint8_t *buf, int len, bool is_option);
                uint8_t getValue();
        private:
                uint8_t _iei;
                uint8_t length;
                uint8_t _SST;

        };

}












#endif


