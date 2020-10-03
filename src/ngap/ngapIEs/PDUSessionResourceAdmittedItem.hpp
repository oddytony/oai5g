#ifndef _PDUSESSIONRESOURCEADMITTEDITEM_H_
#define _PDUSESSIONRESOURCEADMITTEDITEM_H_

#include "PDUSessionID.hpp"

extern "C"{
  #include "Ngap_PDUSessionResourceAdmittedItem.h"
}

namespace ngap{

	class PDUSessionResourceAdmittedItem {
	public:
		PDUSessionResourceAdmittedItem();
		virtual ~PDUSessionResourceAdmittedItem();
		
		void setPDUSessionResourceAdmittedItem(PDUSessionID *m_pDUSessionID, OCTET_STRING_t m_handoverrequestAcktransfer);
		void getPDUSessionResourceAdmittedItem(PDUSessionID *&m_pDUSessionID, OCTET_STRING_t &m_handoverrequestAcktransfer);
		
		bool encode2PDUSessionResourceAdmittedItem(Ngap_PDUSessionResourceAdmittedItem_t *pdUSessionResourceAdmittedItem);
		bool decodefromPDUSessionResourceAdmittedItem(Ngap_PDUSessionResourceAdmittedItem_t *pdUSessionResourceAdmittedItem);
	private:
		PDUSessionID *pDUSessionID;
		OCTET_STRING_t handoverrequestAcktransfer;
	};

}

#endif





