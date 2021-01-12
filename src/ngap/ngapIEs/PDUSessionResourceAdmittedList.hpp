#ifndef _PDUSESSIONRESOURCEADMITTEDLIST_H_
#define _PDUSESSIONRESOURCEADMITTEDLIST_H_

#include "PDUSessionResourceAdmittedItem.hpp"

extern "C"{
  #include "Ngap_PDUSessionResourceAdmittedList.h"
}

namespace ngap{

	class PDUSessionResourceAdmittedList {
	public:
		PDUSessionResourceAdmittedList();
		virtual ~PDUSessionResourceAdmittedList();
		
		void setPDUSessionResourceAdmittedList(PDUSessionResourceAdmittedItem *m_pduSessionResourceAdmittedItem,int num);
		void getPDUSessionResourceAdmittedList(PDUSessionResourceAdmittedItem *&m_pduSessionResourceAdmittedItem,int &num);
		
		bool encode2PDUSessionResourceAdmittedList(Ngap_PDUSessionResourceAdmittedList_t *pduSessionResourceAdmittedList);
		bool decodefromPDUSessionResourceAdmittedList(Ngap_PDUSessionResourceAdmittedList_t *pduSessionResourceAdmittedList);
	private:
		PDUSessionResourceAdmittedItem *pduSessionResourceAdmittedItem;
		int numofSessionResourceAdmittedItem;
	};

}

#endif

