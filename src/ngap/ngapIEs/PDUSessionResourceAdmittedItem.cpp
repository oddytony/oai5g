#include "PDUSessionResourceAdmittedItem.hpp"

#include <iostream>
using namespace std;

namespace ngap{
	PDUSessionResourceAdmittedItem::PDUSessionResourceAdmittedItem()
	{
		pDUSessionID = NULL;
	}
	PDUSessionResourceAdmittedItem::~PDUSessionResourceAdmittedItem(){}
	
	void PDUSessionResourceAdmittedItem::setPDUSessionResourceAdmittedItem(PDUSessionID *m_pDUSessionID, OCTET_STRING_t m_handoverrequestAcktransfer)
	{
		pDUSessionID = m_pDUSessionID;
		handoverrequestAcktransfer = m_handoverrequestAcktransfer;
	}
	bool PDUSessionResourceAdmittedItem::encode2PDUSessionResourceAdmittedItem(Ngap_PDUSessionResourceAdmittedItem_t *pdUSessionResourceAdmittedItem)
	{
		if(!pDUSessionID) return false;
		if(!pDUSessionID->encode2PDUSessionID(pdUSessionResourceAdmittedItem->pDUSessionID)) return false;
		pdUSessionResourceAdmittedItem->handoverRequestAcknowledgeTransfer = handoverrequestAcktransfer;
		
		return true; 
	}
	bool PDUSessionResourceAdmittedItem::decodefromPDUSessionResourceAdmittedItem(Ngap_PDUSessionResourceAdmittedItem_t *pdUSessionResourceAdmittedItem)
	{
		pDUSessionID = new PDUSessionID();
		if(!pDUSessionID->decodefromPDUSessionID(pdUSessionResourceAdmittedItem->pDUSessionID)) return false;
		handoverrequestAcktransfer = pdUSessionResourceAdmittedItem->handoverRequestAcknowledgeTransfer;
			
		return true;
	}
	void PDUSessionResourceAdmittedItem::getPDUSessionResourceAdmittedItem(PDUSessionID *&m_pDUSessionID, OCTET_STRING_t &m_handoverrequestAcktransfer)
	{
		m_pDUSessionID = pDUSessionID;
		m_handoverrequestAcktransfer = handoverrequestAcktransfer;
	}

}




