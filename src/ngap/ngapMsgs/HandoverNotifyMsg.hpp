#ifndef _HANDOVERNOTIFYMSG_H_
#define _HANDOVERNOTIFYMSG_H_

#include "NgapIEsStruct.hpp"

#include "AMF-UE-NGAP-ID.hpp"
#include "RAN-UE-NGAP-ID.hpp"
#include "MessageType.hpp"
#include "UserLocationInformation.hpp"

extern "C" {
#include "Ngap_NGAP-PDU.h"
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_HandoverNotify.h"
}

namespace ngap {
	class HandoverNotifyMsg{
	public:
		HandoverNotifyMsg();
		virtual ~HandoverNotifyMsg();
		int  encode2buffer(uint8_t* buf, int buf_size);
		bool decodefrompdu(Ngap_NGAP_PDU_t* ngap_msg_pdu);
		void setUserLocationInfoNR(struct NrCgi_s cig, struct Tai_s tai);
		unsigned long getAmfUeNgapId();//return -1;(不存在)
		uint32_t getRanUeNgapId();//return -1;(不存在)
		bool getUserLocationInfoNR(struct NrCgi_s& cig, struct Tai_s& tai);

	private:
		Ngap_NGAP_PDU_t* handoverNotifyPdu;
		Ngap_HandoverNotify_t* handoverNotifyIEs;
		AMF_UE_NGAP_ID* amfUeNgapId;
		RAN_UE_NGAP_ID* ranUeNgapId;
		UserLocationInformation* userLocationInformation;
	};

}
#endif
