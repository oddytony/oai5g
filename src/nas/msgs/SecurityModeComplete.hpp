#ifndef _SecurityModeComplete_H_
#define _SecurityModeComplete_H_

#include "nas_ie_header.hpp"

namespace nas {

	class SecurityModeComplete {
	public:
		SecurityModeComplete();
		~SecurityModeComplete();
		int encode2buffer(uint8_t *buf, int len);
		int decodefrombuffer(NasMmPlainHeader * header, uint8_t *buf, int len);
		void setHeader(uint8_t security_header_type);
		/*** belongs to _5GSMobilityIdentity**/
		void set_IMEISV_SUCI_SUPI_format_IMSI(const string mcc, const string mnc, const string routingInd, uint8_t protection_sch_id, const string msin);
		void set_NON_IMEISV_SUCI_SUPI_format_IMSI(const string mcc, const string mnc, const string routingInd, uint8_t protection_sch_id, const string msin);
		void setSUCI_SUPI_format_IMSI(const string mcc, const string mnc, const string routingInd, uint8_t protection_sch_id, uint8_t hnpki, const string msin);
		void set5G_GUTI();
		void setIMEI_IMEISV();
		void set5G_S_TMSI();
	  /*** belongs to _5GSMobilityIdentity**/
		void setNAS_Message_Container(bstring value);
	public:
		NasMmPlainHeader       *plain_header;
		_5GSMobilityIdentity   *ie_imeisv;
		NAS_Message_Container  *ie_nas_message_container;
		_5GSMobilityIdentity   *ie_non_imeisvpei;
	};













}



















#endif




