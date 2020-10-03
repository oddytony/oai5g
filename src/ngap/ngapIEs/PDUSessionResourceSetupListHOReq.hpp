#ifndef _PDUSESSIONRESOURCESETUPLISTHOREQ_H_
#define _PDUSESSIONRESOURCESETUPLISTHOREQ_H_

#include "PDUSessionResourceSetupItemHOReq.hpp"

extern "C"{
  #include "Ngap_PDUSessionResourceSetupListHOReq.h"

}

namespace ngap{

	class PDUSessionResourceSetupListHOReq{
	public:
		PDUSessionResourceSetupListHOReq();
		virtual ~PDUSessionResourceSetupListHOReq();
		
		void setPDUSessionResourceSetupListHOReq(PDUSessionResourceSetupItemHOReq *m_pduSessionResourceSetupItemHOReq,int num);
		void getPDUSessionResourceSetupListHOReq(PDUSessionResourceSetupItemHOReq *&m_pduSessionResourceSetupItemHOReq,int &num);
		
		bool encode2PDUSessionResourceSetupListHOReq(Ngap_PDUSessionResourceSetupListHOReq_t *pduSessionResourceSetupListHOReq);
		bool decodefromPDUSessionResourceSetupListHOReq(Ngap_PDUSessionResourceSetupListHOReq_t *pduSessionResourceSetupListHOReq);
	private:
		PDUSessionResourceSetupItemHOReq *pduSessionResourceSetupItemHOReq;
		int numofpduSessionResourceSetupItemHOReq;
	};

}

#endif
