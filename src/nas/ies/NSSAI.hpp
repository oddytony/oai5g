#ifndef __NSSAI_H_
#define __NSSAI_H_
#include <vector>

#include <stdint.h>
namespace nas {

typedef struct SNSSAI_s {
	uint8_t sst;
	int8_t sd;//若sd不存在，则sd设置为-1
}SNSSAI_t;
        class NSSAI{
        public:
                NSSAI();
                NSSAI(uint8_t iei);
                NSSAI(const uint8_t iei, std::vector<struct SNSSAI_s> nssai);
                ~NSSAI();
                void setS_NAASI(uint8_t SST);
                int encode2buffer(uint8_t *buf, int len);
                int decodefrombuffer(uint8_t *buf, int len, bool is_option);
                bool getValue(std::vector<struct SNSSAI_s> &nssai);
        private:
                uint8_t _iei;
                uint8_t length;
				std::vector<struct SNSSAI_s> S_NSSAI;

        };

}












#endif


