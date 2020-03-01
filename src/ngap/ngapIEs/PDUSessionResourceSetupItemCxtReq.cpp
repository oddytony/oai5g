#include "PDUSessionResourceSetupItemCxtReq.hpp"

#include <iostream>
using namespace std;

namespace ngap{
	PDUSessionResourceSetupItemCxtReq::PDUSessionResourceSetupItemCxtReq()
	{
		pDUSessionID = NULL;
		nAS_PDU = NULL;
		s_NSSAI = NULL;
	}
	PDUSessionResourceSetupItemCxtReq::~PDUSessionResourceSetupItemCxtReq(){}
	
	void PDUSessionResourceSetupItemCxtReq::setPDUSessionResourceSetupItemCxtReq(PDUSessionID *m_pDUSessionID, NAS_PDU	*m_nAS_PDU, S_NSSAI	*m_s_NSSAI,OCTET_STRING_t m_pDUSessionResourceSetupRequestTransfer)
	{
		pDUSessionID = m_pDUSessionID;
		nAS_PDU = m_nAS_PDU;
		s_NSSAI = m_s_NSSAI;
		pDUSessionResourceSetupRequestTransfer = m_pDUSessionResourceSetupRequestTransfer;
	}
	bool PDUSessionResourceSetupItemCxtReq::encode2PDUSessionResourceSetupItemCxtReq(Ngap_PDUSessionResourceSetupItemCxtReq_t *pduSessionResourceSetupItemCxtReq)
	{
		if(!pDUSessionID->encode2PDUSessionID(pduSessionResourceSetupItemCxtReq->pDUSessionID)) return false;
		if(nAS_PDU)
		{
			Ngap_NAS_PDU_t	*naspdu = (Ngap_NAS_PDU_t *)calloc(1,sizeof(Ngap_NAS_PDU_t));
			if(!naspdu) return false;
			if(!nAS_PDU->encode2octetstring(*naspdu)) return false;
			pduSessionResourceSetupItemCxtReq->nAS_PDU = naspdu;
		}
		if(!s_NSSAI->encode2S_NSSAI(&pduSessionResourceSetupItemCxtReq->s_NSSAI)) return false;
		pduSessionResourceSetupItemCxtReq->pDUSessionResourceSetupRequestTransfer = pDUSessionResourceSetupRequestTransfer;
		
		return true; 
	}
	bool PDUSessionResourceSetupItemCxtReq::decodefromPDUSessionResourceSetupItemCxtReq(Ngap_PDUSessionResourceSetupItemCxtReq_t *pduSessionResourceSetupItemCxtReq)
	{
		pDUSessionID = new PDUSessionID();
		s_NSSAI = new S_NSSAI();
		if(!pDUSessionID->decodefromPDUSessionID(pduSessionResourceSetupItemCxtReq->pDUSessionID)) return false;
		if(!s_NSSAI->decodefromS_NSSAI(&(pduSessionResourceSetupItemCxtReq->s_NSSAI))) return false;
		
		if(pduSessionResourceSetupItemCxtReq->nAS_PDU)
		{
			nAS_PDU = new NAS_PDU();
			if(!nAS_PDU->decodefromoctetstring(*pduSessionResourceSetupItemCxtReq->nAS_PDU)) return false;
		}

		pDUSessionResourceSetupRequestTransfer = pduSessionResourceSetupItemCxtReq->pDUSessionResourceSetupRequestTransfer;
			
		return true;
	}
	void PDUSessionResourceSetupItemCxtReq::getPDUSessionResourceSetupItemCxtReq(PDUSessionID *&m_pDUSessionID, NAS_PDU	*&m_nAS_PDU, S_NSSAI *&m_s_NSSAI,OCTET_STRING_t &m_pDUSessionResourceSetupRequestTransfer)
	{
		m_pDUSessionID = pDUSessionID;
		m_nAS_PDU = nAS_PDU;
		m_s_NSSAI = s_NSSAI;
		m_pDUSessionResourceSetupRequestTransfer = pDUSessionResourceSetupRequestTransfer;
	}

}




