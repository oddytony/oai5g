#include "PDUSessionResourceSetupItemHOReq.hpp"

#include <iostream>
using namespace std;

namespace ngap{
	PDUSessionResourceSetupItemHOReq::PDUSessionResourceSetupItemHOReq()
	{
		pDUSessionID = NULL;
		s_NSSAI = NULL;
	}
	PDUSessionResourceSetupItemHOReq::~PDUSessionResourceSetupItemHOReq(){}
	
	void PDUSessionResourceSetupItemHOReq::setPDUSessionResourceSetupItemHOReq(PDUSessionID *m_pDUSessionID,S_NSSAI	*m_s_NSSAI,OCTET_STRING_t m_pDUSessionResourceSetupRequestTransfer)
	{
		pDUSessionID = m_pDUSessionID;
		s_NSSAI = m_s_NSSAI;
		pDUSessionResourceSetupRequestTransfer = m_pDUSessionResourceSetupRequestTransfer;
	}
	bool PDUSessionResourceSetupItemHOReq::encode2PDUSessionResourceSetupItemHOReq(Ngap_PDUSessionResourceSetupItemHOReq_t *pduSessionResourceSetupItemHOReq)
	{
		if(!pDUSessionID->encode2PDUSessionID(pduSessionResourceSetupItemHOReq->pDUSessionID)) return false;
		if(!s_NSSAI->encode2S_NSSAI(&pduSessionResourceSetupItemHOReq->s_NSSAI)) return false;
		pduSessionResourceSetupItemHOReq->handoverRequestTransfer = pDUSessionResourceSetupRequestTransfer;
		
		return true; 
	}
	bool PDUSessionResourceSetupItemHOReq::decodefromPDUSessionResourceSetupItemHOReq(Ngap_PDUSessionResourceSetupItemHOReq_t *pduSessionResourceSetupItemHOReq)
	{
		pDUSessionID = new PDUSessionID();
		s_NSSAI = new S_NSSAI();
		if(!pDUSessionID->decodefromPDUSessionID(pduSessionResourceSetupItemHOReq->pDUSessionID)) return false;
		if(!s_NSSAI->decodefromS_NSSAI(&pduSessionResourceSetupItemHOReq->s_NSSAI)) return false;
		pDUSessionResourceSetupRequestTransfer = pduSessionResourceSetupItemHOReq->handoverRequestTransfer;
			
		return true;
	}
	void PDUSessionResourceSetupItemHOReq::getPDUSessionResourceSetupItemHOReq(PDUSessionID *&m_pDUSessionID, S_NSSAI *&m_s_NSSAI,OCTET_STRING_t &m_pDUSessionResourceSetupRequestTransfer)
	{
		m_pDUSessionID = pDUSessionID;
		m_s_NSSAI = s_NSSAI;
		m_pDUSessionResourceSetupRequestTransfer = pDUSessionResourceSetupRequestTransfer;
	}

}




