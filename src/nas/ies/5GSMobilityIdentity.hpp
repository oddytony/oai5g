#ifndef _5GSMobilityIdentity_H_
#define _5GSMobilityIdentity_H_

#include <string>
#include <stdint.h>
using namespace std;

namespace nas{

typedef struct _5G_GUTI_s{
  string mcc;
  string mnc;
  uint8_t  amf_region_id;
  uint8_t amf_set_id;
  uint8_t  amf_pointer;
  string   _5g_tmsi;
}_5G_GUTI_t;

typedef struct IMEI_or_IMEISV_s{
  uint8_t typeOfIdentity:3;
  bool    odd_even_indic;// for imei, even means bits 5 to 8 of last octet is "1111", for imeisv, bits 5 to 8 of last octet is "1111"
  string  identity;// "46011000001"
}IMEI_IMEISV_t;

typedef struct SUCI_imsi_s{
  uint8_t supi_format:3;
  string  mcc;
  string  mnc;
  string  routingIndicator; //"1234"
  uint8_t protectionSchemeId:4;// 0000
  uint8_t homeNetworkPKI;// 00000000
  string  msin; // two types of coding; BCD & hexadecimal
}SUCI_imsi_t;// SUPI format "IMSI"

//don't define suci and supi format "Network specific identifier"

typedef struct _5G_S_TMSI_s{
  uint16_t amf_set_id;
  uint8_t  amf_pointer;
  string   _5g_tmsi;
}_5G_S_TMSI_t;

class _5GSMobilityIdentity{
public:
  _5GSMobilityIdentity(const string mcc, const string mnc, const string routingInd, uint8_t protection_sch_id, const string msin);
  _5GSMobilityIdentity();
  ~_5GSMobilityIdentity();
  void setIEI(uint8_t _iei);
  int encode2buffer(uint8_t *buf, int len);
  int suci_encode2buffer(uint8_t *buf, int len);
  int _5g_guti_encode2buffer(uint8_t *buf, int len);
  int encodeMssMnc2buffer(string mcc, string mnc, uint8_t *buf);
  int encodeRoutid2buffer(string routid, uint8_t *buf);
  int encodeMSIN2buffer(string msinstr, uint8_t *buf);

  int decodefrombuffer(uint8_t *buf, int len, bool is_option);
  int suci_decodefrombuffer(uint8_t *buf, int len);
  int _5g_guti_decodefrombuffer(uint8_t *buf, int len);
  void set5GGUTI(const string mcc, const string mnc, uint8_t amf_region_id, uint8_t amf_set_id, uint8_t amf_pointer, const string _5g_tmsi);
  void setSuciWithSupiImsi(const string &mcc, const string &mnc, const string &routingInd, uint8_t protecSchId ,uint8_t home_pki, const string &msin_digits);
  void setSuciWithSupiImsi(const string &mcc, const string &mnc, const string &routingInd, uint8_t protecSchId ,const string &msin_digits);
  void getSuciWithSupiImsi(SUCI_imsi_t &);
  void get5GGUTI(_5G_GUTI_t &);
  uint8_t gettypeOfIdentity() { return typeOfIdentity; };
private:
  uint8_t         iei;
  _5G_GUTI_t     *_5g_guti;
  IMEI_IMEISV_t  *imei_imeisv;
  SUCI_imsi_t    *supi_format_imsi;
  _5G_S_TMSI_t   *_5g_s_tmsi;
  bool            is_no_identity;
  uint16_t        length;
  uint8_t         typeOfIdentity:3;
};



}



#endif
