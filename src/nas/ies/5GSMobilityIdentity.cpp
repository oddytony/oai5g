#include "5GSMobilityIdentity.hpp"
#include "3gpp_ts24501.hpp"
#include "String2Value.hpp"
#include <math.h>
#include "logger.hpp"

using namespace nas;
void _5GSMobilityIdentity::setIEI(uint8_t _iei) {
	iei = _iei;

}
_5GSMobilityIdentity::_5GSMobilityIdentity(const string mcc, const string mnc, const string routingInd, uint8_t protection_sch_id, const string msin){
  iei = 0;
  typeOfIdentity = SUCI;
  supi_format_imsi = (SUCI_imsi_t*)calloc(1,sizeof(SUCI_imsi_t));
  supi_format_imsi->supi_format = SUPI_FORMAT_IMSI;
  supi_format_imsi->mcc = mcc;
  supi_format_imsi->mnc = mnc;
  supi_format_imsi->routingIndicator = routingInd;
  supi_format_imsi->protectionSchemeId = protection_sch_id;
  supi_format_imsi->homeNetworkPKI = HOME_NETWORK_PKI_0_WHEN_PSI_0;
  supi_format_imsi->msin = msin;
  length = 10+ceil(msin.length()/2);
}

_5GSMobilityIdentity::_5GSMobilityIdentity(){
  iei = 0;
  _5g_guti = NULL;
  imei_imeisv = NULL;
  supi_format_imsi = NULL;
  _5g_s_tmsi = NULL;
}

_5GSMobilityIdentity::~_5GSMobilityIdentity(){}

void _5GSMobilityIdentity::set5GGUTI(const string mcc, const string mnc, uint8_t amf_region_id, uint8_t amf_set_id, uint8_t amf_pointer, const string _5g_tmsi){
  typeOfIdentity = _5G_GUTI;
  _5g_guti = (_5G_GUTI_t*)calloc(1, sizeof(_5G_GUTI_t));
  _5g_guti->mcc = mcc;
  _5g_guti->mnc = mnc;
  _5g_guti->amf_region_id = amf_region_id;
  _5g_guti->amf_set_id = amf_set_id;
  _5g_guti->amf_pointer = amf_pointer;
  _5g_guti->_5g_tmsi = _5g_tmsi;
  length = 14;
}

void _5GSMobilityIdentity::setSuciWithSupiImsi(const string &mcc, const string &mnc, const string &routingInd, uint8_t protecSchId, const string &msin_digits){
  supi_format_imsi = (SUCI_imsi_t*)calloc(1,sizeof(SUCI_imsi_t));
  supi_format_imsi->supi_format = SUPI_FORMAT_IMSI;
  supi_format_imsi->mcc = mcc;
  supi_format_imsi->mnc = mnc;
  supi_format_imsi->routingIndicator = routingInd;
  supi_format_imsi->protectionSchemeId = protecSchId;
  supi_format_imsi->homeNetworkPKI = HOME_NETWORK_PKI_0_WHEN_PSI_0;
  supi_format_imsi->msin = msin_digits;
}

void _5GSMobilityIdentity::setSuciWithSupiImsi(const string &mcc, const string &mnc, const string &routingInd, uint8_t protecSchId ,uint8_t home_pki, const string &msin_digits){
  supi_format_imsi = (SUCI_imsi_t*)calloc(1,sizeof(SUCI_imsi_t));
  supi_format_imsi->supi_format = SUPI_FORMAT_IMSI;
  supi_format_imsi->mcc = mcc;
  supi_format_imsi->mnc = mnc;
}

void _5GSMobilityIdentity::getSuciWithSupiImsi(SUCI_imsi_t & ptr){
  ptr = *supi_format_imsi;
}
void _5GSMobilityIdentity::get5GGUTI(_5G_GUTI_t &ptr){
	ptr =* _5g_guti;
}

int _5GSMobilityIdentity::encode2buffer(uint8_t *buf, int len){
  switch(typeOfIdentity){
    case SUCI:{
      suci_encode2buffer(buf, len);
    }break;
    case _5G_GUTI: {
      _5g_guti_encode2buffer(buf, len);
    }break;
  }
}

int _5GSMobilityIdentity::suci_encode2buffer(uint8_t *buf, int len){
  Logger::nas_mm().debug("encoding SUCI IE iei(0x%x)",iei);
  if(len < length)
    Logger::nas_mm().debug("error: len is less than %d",length);
  int encoded_size = 0;
  if(iei){
	 Logger::nas_mm().debug("decoding 5GSMobilityIdentity iei0x%x",typeOfIdentity);
    *(buf) = iei;
    encoded_size++;
    encoded_size += 2;
	*(buf + encoded_size) = 0x00 | (SUPI_FORMAT_IMSI << 4) | SUCI;
	encoded_size += 1;
	encoded_size += encodeMssMnc2buffer(supi_format_imsi->mcc, supi_format_imsi->mnc, buf + encoded_size);
	encoded_size += encodeRoutid2buffer(supi_format_imsi->routingIndicator, buf + encoded_size);
	*(buf + encoded_size) = 0x00 | supi_format_imsi->protectionSchemeId;
	encoded_size += 1;
	*(buf + encoded_size) = 0x00 | supi_format_imsi->homeNetworkPKI;
	encoded_size += 1;
  }else{
    encoded_size +=2;
    *(buf+encoded_size) = 0x00 | (SUPI_FORMAT_IMSI<<4) | SUCI;
    encoded_size += 1;
    encoded_size += encodeMssMnc2buffer(supi_format_imsi->mcc, supi_format_imsi->mnc, buf+encoded_size);
    encoded_size += encodeRoutid2buffer(supi_format_imsi->routingIndicator, buf+encoded_size);
    *(buf+encoded_size) = 0x00 | supi_format_imsi->protectionSchemeId;
    encoded_size += 1;
    *(buf+encoded_size) = 0x00 | supi_format_imsi->homeNetworkPKI;
    encoded_size += 1;
    //encoded_size += encodeMSIN2buffer(supi_format_imsi->msin, buf+encoded_size);
  }
  if(!iei){
    *(uint16_t *)buf = encoded_size - 2;
  }else{
    *(uint16_t *)(buf+1) = encoded_size -3;
  }
  Logger::nas_mm().debug("encoded SUCI IE len(%d octets)", encoded_size);
  return encoded_size;  
}
int _5GSMobilityIdentity::_5g_guti_encode2buffer(uint8_t *buf, int len) {
	Logger::nas_mm().debug("encoding 5G-GUTI IE iei(0x%x)", iei);
	if (len < length)
		Logger::nas_mm().debug("error: len is less than %d", length);
	int encoded_size = 0;
	if (iei) {
		Logger::nas_mm().debug("decoding 5GSMobilityIdentity iei0x%x", typeOfIdentity);
		*(buf) = iei;
		encoded_size++;
		encoded_size += 2;
		*(buf + encoded_size) = 0xf0 | _5G_GUTI;
		encoded_size += 1;
		encoded_size += encodeMssMnc2buffer(_5g_guti->mcc, _5g_guti->mnc, buf + encoded_size);
		*(buf + encoded_size) = _5g_guti->amf_region_id; encoded_size += 1;
		*(buf + encoded_size) = _5g_guti->amf_set_id; encoded_size += 1;
		*(buf + encoded_size) = _5g_guti->amf_pointer; encoded_size += 1;
		int tmsi=fromString<int>(_5g_guti->_5g_tmsi);
		*(buf + encoded_size) = tmsi & 0x000000ff; encoded_size += 1;
		*(buf + encoded_size) = (tmsi & 0x0000ff00)>>8; encoded_size += 1;
		*(buf + encoded_size) = (tmsi & 0x00ff0000)>>16; encoded_size += 1;
		*(buf + encoded_size) = (tmsi & 0xff000000)>>24; encoded_size += 1;
	}
	else {
		encoded_size += 2;
		*(buf + encoded_size) = 0x00 | (SUPI_FORMAT_IMSI << 4) | SUCI;
		encoded_size += 1;
		encoded_size += encodeMssMnc2buffer(supi_format_imsi->mcc, supi_format_imsi->mnc, buf + encoded_size);
		encoded_size += encodeRoutid2buffer(supi_format_imsi->routingIndicator, buf + encoded_size);
		*(buf + encoded_size) = 0x00 | supi_format_imsi->protectionSchemeId;
		encoded_size += 1;
		*(buf + encoded_size) = 0x00 | supi_format_imsi->homeNetworkPKI;
		encoded_size += 1;
		//encoded_size += encodeMSIN2buffer(supi_format_imsi->msin, buf+encoded_size);
	}
	if (!iei) {
		*(uint16_t *)buf = encoded_size - 2;
	}
	else {
		*(uint16_t *)(buf + 1) = encoded_size - 3;
	}
	Logger::nas_mm().debug("encoded 5G-GUTI IE len(%d octets)", encoded_size);
	return encoded_size;
}
int _5GSMobilityIdentity::encodeMssMnc2buffer(string mccstr, string mncstr, uint8_t *buf){
  int encoded_size = 0;
  int mcc = fromString<int>(mccstr);
  int mnc = fromString<int>(mncstr); 
  *(buf+encoded_size) = (0x0f & (mcc/100)) | ((0x0f & ((mcc%100)/10))<<4);
  encoded_size += 1;
  Logger::nas_mm().debug("mnc digit 1 (%d)", mnc/100);
  if(!(mnc/100)){
    Logger::nas_mm().debug("encoding mnc 2 digits");
    *(buf+encoded_size) = (0x0f & (mcc%10)) | 0xf0;
    Logger::nas_mm().debug("buffer(0x%x)",*(buf+encoded_size));
    encoded_size += 1;
    *(buf+encoded_size) = (0x0f & ((mnc%100)/10)) | ((0x0f & (mnc%10))<<4);
    encoded_size += 1;
  }else{
    Logger::nas_mm().debug("encoding mnc 3 digits");
    *(buf+encoded_size) = (0x0f & (mcc%10)) | ((0x0f & (mnc%10))<<4);
    Logger::nas_mm().debug("buffer(0x%x)",*(buf+encoded_size));
    encoded_size += 1;
    *(buf+encoded_size) = ((0x0f & ((mnc%100)/10))<<4) | (0x0f & (mnc/100));
    Logger::nas_mm().debug("buffer(0x%x)",*(buf+encoded_size));
    encoded_size += 1;
  }
  Logger::nas_mm().debug("mcc(%s) mnc(%s)",mccstr.c_str(),mncstr.c_str());
  return encoded_size;
}

int _5GSMobilityIdentity::encodeRoutid2buffer(string routidstr, uint8_t *buf){
  Logger::nas_mm().debug("routid(%s)",routidstr.c_str());
  int encoded_size = 0;
  if(routidstr == (const string)("none")){
    Logger::nas_mm().debug("encoding routid none");
    *buf = 0xf0;
    encoded_size++;
    *(buf+encoded_size) = 0xff;
    encoded_size++;
    return encoded_size;
  }
  int rooutid = fromString<int>(routidstr);
  switch(routidstr.length()){
    case 1:{
      *buf = 0xf0 | (0x0f & rooutid); 
      encoded_size++;
      *(buf+encoded_size) = 0xff;
      encoded_size++;
    }break;
    case 2:{
      *buf = (0x0f & (rooutid/10)) | ((0x0f & (rooutid%10))<<4);
      encoded_size++;
      *(buf+encoded_size) = 0xff;
      encoded_size++;
    }break;
    case 3:{
      *buf = (0x0f & (rooutid/100)) | ((0x0f & ((rooutid%100)/10))<<4);
      encoded_size++;
      *(buf+encoded_size) = 0xf0 | (0x0f & (rooutid%10));
      encoded_size++;
    }break;
    case 4:{
      *buf = (0x0f & (rooutid/1000)) | ((0x0f & ((rooutid%1000)/100))<<4);
      encoded_size++;
      *(buf+encoded_size) = (0x0f & ((rooutid%100)/10)) | ((0x0f & (rooutid%10))<<4);
      encoded_size++;
    }break;
  }
  return encoded_size; 
}

int _5GSMobilityIdentity::encodeMSIN2buffer(string msinstr, uint8_t *buf){
}

int _5GSMobilityIdentity::decodefrombuffer(uint8_t *buf, int len, bool is_option){
  Logger::nas_mm().debug("decoding 5GSMobilityIdentity");
  int decoded_size = 0;
  if(is_option){
    iei = *buf;
    decoded_size += 1; 
  }
	 Logger::nas_mm().debug("decoding 5GSMobilityIdentity iei0x%x",typeOfIdentity);
  length = *((uint16_t*)(buf+decoded_size));
  decoded_size += 2; 
  switch(*(buf+decoded_size) & 0x07){
    case SUCI:{
      typeOfIdentity = SUCI;
      decoded_size += suci_decodefrombuffer(buf+decoded_size, len-decoded_size);
      return decoded_size;
    }break;
    case _5G_GUTI: {
		typeOfIdentity = _5G_GUTI;
		decoded_size += _5g_guti_decodefrombuffer(buf + decoded_size, len - decoded_size);
		return decoded_size;
	}break;
  }

}

int _5GSMobilityIdentity::suci_decodefrombuffer(uint8_t *buf, int len){
  Logger::nas_mm().debug("decoding 5GSMobilityIdentity SUCI");
  int decoded_size = 0;
  uint8_t octet = 0;
  octet = *buf;
  decoded_size ++;
  switch((octet & 0x70)>>4){
    case SUPI_FORMAT_IMSI:{
      supi_format_imsi = (SUCI_imsi_t*)calloc(1,sizeof(SUCI_imsi_t));
      supi_format_imsi->supi_format = SUPI_FORMAT_IMSI;
      octet = *(buf+decoded_size);
      decoded_size++;
      int mcc = 0, mnc = 0;
      mcc += ((octet & 0x0f)*100 + ((octet&0xf0)>>4)*10);
      octet = *(buf+decoded_size);
      decoded_size++;
      mcc += (octet & 0x0f); 
      Logger::nas_mm().debug("mcc(%s)",std::to_string(mcc).c_str());
      Logger::nas_mm().debug("buffer(0x%x)",octet);
      if((octet&0xf0) == 0xf0){
        octet = *(buf+decoded_size);
        decoded_size++;
        mnc += ((octet & 0x0f)*10 + ((octet&0xf0)>>4));
        Logger::nas_mm().debug("mnc(2 digits)(%s)",std::to_string(mnc).c_str());
      }else{
        mnc += ((octet&0xf0)>>4);
        octet = *(buf+decoded_size);
        Logger::nas_mm().debug("buffer(0x%x)",octet);
        decoded_size++;
        mnc += ((octet & 0x0f)*100 + ((octet&0xf0)>>4)*10);
        Logger::nas_mm().debug("mnc(3 digits)(%s)",std::to_string(mnc).c_str());
      }
      Logger::nas_mm().debug("mcc(%s) mnc(%s)",std::to_string(mcc).c_str(),std::to_string(mnc).c_str());
      supi_format_imsi->mcc = (const string)(std::to_string(mcc));
      supi_format_imsi->mnc = (const string)(std::to_string(mnc));
      int routid = 0; uint8_t digit[4];
      octet = *(buf+decoded_size); decoded_size++;
      Logger::nas_mm().debug("octet(0x%x)",octet);
      digit[0] = octet & 0x0f;
      digit[1] = (octet & 0xf0)>>4;
      octet = *(buf+decoded_size); decoded_size++;
      Logger::nas_mm().debug("octet(0x%x)",octet);
      digit[2] = octet & 0x0f;
      digit[3] = (octet & 0xf0)>>4;
      if(!digit[0] && digit[1]==0x0f && digit[2]==0x0f && digit[3]==0x0f) {
        supi_format_imsi->routingIndicator = (const string)("none");
        Logger::nas_mm().debug("routing indicator(%s)",supi_format_imsi->routingIndicator.c_str());
      }
      else{
        string result = "";
        for(int i=0;i<4;i++){
          if(digit[i]>=0x00 && digit[i]<=0x09) result += (const string)(std::to_string(digit[i]));
          else if(digit[i] == 0x0f) break;
          else Logger::nas_mm().error("decoded routing indicator is not BCD coding");
        }
        supi_format_imsi->routingIndicator = result;
        Logger::nas_mm().debug("decoded routing indicator(%s)",supi_format_imsi->routingIndicator.c_str());
      }
      octet = *(buf+decoded_size); decoded_size++;
      supi_format_imsi->protectionSchemeId = 0x0f & octet;
      octet = *(buf+decoded_size); decoded_size++;
      supi_format_imsi->homeNetworkPKI = octet; 
      Logger::nas_mm().debug("decoding 5GSMobilityIdentity SUCI SUPI format IMSI");
      return decoded_size;
    }break;
    case SUPI_FORMAT_NETWORK_SPECIFIC_IDENTIFIER:{
    }break;
    default:{
    }break;
  }








}
int _5GSMobilityIdentity::_5g_guti_decodefrombuffer(uint8_t *buf, int len) {
	  Logger::nas_mm().debug("decoding 5GSMobilityIdentity 5G-GUTI");
	  int decoded_size = 0;
	  uint8_t octet = 0;
	  octet = *buf;
	  decoded_size++;

	  _5g_guti = (_5G_GUTI_t*)calloc(1, sizeof(_5G_GUTI_t));
		  octet = *(buf + decoded_size);
		  decoded_size++;
		  int mcc = 0, mnc = 0;
		  mcc += ((octet & 0x0f) * 100 + ((octet & 0xf0) >> 4) * 10);
		  octet = *(buf + decoded_size);
		  decoded_size++;
		  mcc += (octet & 0x0f);
		  Logger::nas_mm().debug("mcc(%s)", std::to_string(mcc).c_str());
		  Logger::nas_mm().debug("buffer(0x%x)", octet);
		  if ((octet & 0xf0) == 0xf0) {
			  octet = *(buf + decoded_size);
			  decoded_size++;
			  mnc += ((octet & 0x0f) * 10 + ((octet & 0xf0) >> 4));
			  Logger::nas_mm().debug("mnc(2 digits)(%s)", std::to_string(mnc).c_str());
		  }
		  else {
			  mnc += ((octet & 0xf0) >> 4);
			  octet = *(buf + decoded_size);
			  Logger::nas_mm().debug("buffer(0x%x)", octet);
			  decoded_size++;
			  mnc += ((octet & 0x0f) * 100 + ((octet & 0xf0) >> 4) * 10);
			  Logger::nas_mm().debug("mnc(3 digits)(%s)", std::to_string(mnc).c_str());
		  }
		  Logger::nas_mm().debug("mcc(%s) mnc(%s)", std::to_string(mcc).c_str(), std::to_string(mnc).c_str());
		  _5g_guti->mcc = (const string)(std::to_string(mcc));
		  _5g_guti->mnc = (const string)(std::to_string(mnc));

		  _5g_guti->amf_region_id = *(buf + decoded_size); decoded_size++;
		  _5g_guti->amf_set_id = *(buf + decoded_size); decoded_size++;
		  _5g_guti->amf_pointer = *(buf + decoded_size); decoded_size++;
		  uint32_t tmsi = 0; uint8_t digit[4];
		  octet = *(buf + decoded_size); decoded_size++;
		  Logger::nas_mm().debug("octet(0x%x)", octet);
		  digit[0] = octet;
		  tmsi |= octet;
		  octet = *(buf + decoded_size); decoded_size++;
		  Logger::nas_mm().debug("octet(0x%x)", octet);
		  digit[1] = octet ;
		  tmsi |= octet<<8;
		  octet = *(buf + decoded_size); decoded_size++;
		  Logger::nas_mm().debug("octet(0x%x)", octet);
		  digit[2] = octet;
		  tmsi |= octet << 16;
		  octet = *(buf + decoded_size); decoded_size++;
		  Logger::nas_mm().debug("octet(0x%x)", octet);
		  digit[3] = octet;
		  tmsi |= octet << 24;
			_5g_guti->_5g_tmsi = (const string)(std::to_string(tmsi));
	      Logger::nas_mm().debug("tmsi (0x%s)", _5g_guti->_5g_tmsi.c_str());
		  Logger::nas_mm().debug("decoding 5GSMobilityIdentity 5G-GUTI");
		  return decoded_size;
}
