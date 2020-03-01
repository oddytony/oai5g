#include "NSSAI.hpp"
#include <vector>
#include "logger.hpp"
using namespace nas;
using namespace std;

NSSAI::NSSAI(uint8_t iei) {
        _iei = iei;
}
NSSAI::NSSAI(const uint8_t iei, std::vector<struct SNSSAI_s> nssai) {
        _iei = iei;
        length = 2;
		S_NSSAI.assign(nssai.begin(), nssai.end());
		for(int i =0;i< nssai.size(); i++){
			length = length + 1 + 1;
			if (nssai.at(i).sd != -1)
			{
				length++;
			}
		}
}
NSSAI::NSSAI() {}
NSSAI::~NSSAI() {}

void NSSAI::setS_NAASI(uint8_t SST) {
}
bool NSSAI::getValue(std::vector<struct SNSSAI_s> &nssai) 
{
	nssai.assign(S_NSSAI.begin(), S_NSSAI.end());
}

int NSSAI::encode2buffer(uint8_t *buf, int len) {
        Logger::nas_mm().debug("encoding NSSAI iei(0x%x)", _iei);
        if (len < length) {
                Logger::nas_mm().error("len is less than %d", length);
                return 0;
        }
        int encoded_size = 0;
        if (_iei) {
                *(buf + encoded_size) = _iei; encoded_size++;
                *(buf + encoded_size) = length - 2; encoded_size++;

				
				for(int i =0;i< S_NSSAI.size(); i++){
					if (S_NSSAI.at(i).sd != -1)
					{
						*(buf + encoded_size) = 2; encoded_size++;
					}
					else { *(buf + encoded_size) = 1; encoded_size++; }

					*(buf + encoded_size) = S_NSSAI.at(i).sst;    encoded_size++;
					if (S_NSSAI.at(i).sd != -1)
					{
						*(buf + encoded_size) = S_NSSAI.at(i).sd;    encoded_size++;
					}	
				}
        }
        else {
           //     *(buf + encoded_size) = length - 1; encoded_size++;
             //   *(buf + encoded_size) = _value; encoded_size++; encoded_size++;
 }
        Logger::nas_mm().debug("encoded NSSAI len(%d)", encoded_size);
        return encoded_size;
}

int NSSAI::decodefrombuffer(uint8_t *buf, int len, bool is_option) {
        Logger::nas_mm().debug("decoding NSSAI iei(0x%x)", *buf);
        int decoded_size = 0;
		SNSSAI_s a;
        if (is_option) {
                decoded_size++;
		}
        length = *(buf + decoded_size); decoded_size++;
		int LEAGTH = length;
		while (LEAGTH) {
			if (*(buf + decoded_size) == 1)  //通过snssai的length检测有无sd
			{
				decoded_size++;//snssai—leagth
				LEAGTH--;
				a.sst = *(buf + decoded_size); decoded_size++;//无 sd
				LEAGTH--;
				a.sd = -1;
			}
			else
			{
				decoded_size++;
				LEAGTH--;
				a.sst = *(buf + decoded_size); decoded_size++;
				LEAGTH--;
				a.sd = *(buf + decoded_size); decoded_size++;//有 sd
				LEAGTH--;
			}
			S_NSSAI.insert(S_NSSAI.end(),a);
		}
		
		for(int i =0;i< S_NSSAI.size(); i++){
		Logger::nas_mm().debug("decoded NSSAI SST(0x%x) SD(%d) ",S_NSSAI.at(i).sst,S_NSSAI.at(i).sd); }
        Logger::nas_mm().debug("decoded NSSAI len(%d)", decoded_size);
        return decoded_size;
}


