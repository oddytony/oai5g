#include "PDUSessionResourceItemHORqd.hpp"

#include <iostream>
using namespace std;

namespace ngap{
	PDUSessionResourceItemHORqd::PDUSessionResourceItemHORqd()
	{
		pDUSessionID = NULL;
	}
	PDUSessionResourceItemHORqd::~PDUSessionResourceItemHORqd(){}
	
	void PDUSessionResourceItemHORqd::setPDUSessionResourceItemHORqd(PDUSessionID *m_pDUSessionID, OCTET_STRING_t m_handoverrequiredtransfer)
	{
		pDUSessionID = m_pDUSessionID;
		handoverrequiredtransfer = m_handoverrequiredtransfer;
	}
	bool PDUSessionResourceItemHORqd::encode2PDUSessionResourceItemHORqd(Ngap_PDUSessionResourceItemHORqd_t *pdUSessionResourceItemHORqd)
	{
		if(!pDUSessionID) return false;
		if(!pDUSessionID->encode2PDUSessionID(pdUSessionResourceItemHORqd->pDUSessionID)) return false;
		pdUSessionResourceItemHORqd->handoverRequiredTransfer = handoverrequiredtransfer;
		
		return true; 
	}
	bool PDUSessionResourceItemHORqd::decodefromPDUSessionResourceItemHORqd(Ngap_PDUSessionResourceItemHORqd_t *pdUSessionResourceItemHORqd)
	{
		pDUSessionID = new PDUSessionID();
		if(!pDUSessionID->decodefromPDUSessionID(pdUSessionResourceItemHORqd->pDUSessionID)) return false;
		handoverrequiredtransfer = pdUSessionResourceItemHORqd->handoverRequiredTransfer;
			
		return true;
	}
	void PDUSessionResourceItemHORqd::getPDUSessionResourceItemHORqd(PDUSessionID *&m_pDUSessionID, OCTET_STRING_t &m_handoverrequiredtransfer)
	{
		m_pDUSessionID = pDUSessionID;
		m_handoverrequiredtransfer = handoverrequiredtransfer;
	}

}




