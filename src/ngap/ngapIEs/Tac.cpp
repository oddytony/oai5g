#include "Tac.hpp"

namespace ngap{
	TAC::TAC(){}
	TAC::~TAC(){}

	
	void TAC::setTac(uint32_t m_tac)
	{
		tac = m_tac;
	}
	bool TAC::encode2octetstring(Ngap_TAC_t &m_tac)
	{
		m_tac.size = 3;//OCTET_STRING(SIZE(3))
		uint8_t *buffer = (uint8_t*)calloc(1,sizeof(uint8_t)+sizeof(uint16_t));
		if(!buffer) return false;
		
		*(uint32_t *)buffer = tac & 0x00ffffff;
		m_tac.buf = buffer;

		return true;
	}
	bool TAC::decodefromoctetstring(Ngap_TAC_t &m_tac)
	{
		if(!m_tac.buf) return false;
		tac = *(uint32_t *)m_tac.buf & 0x00ffffff;

		return true;
	}

	uint32_t TAC::getTac()
	{
		return tac;
	}


}
