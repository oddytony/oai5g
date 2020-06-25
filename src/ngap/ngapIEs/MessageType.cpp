#include "MessageType.hpp"

#include<iostream>

extern "C"{
  #include "Ngap_Criticality.h"
  #include "Ngap_ProcedureCode.h"
  #include "Ngap_NGAP-PDU.h"
  #include "Ngap_Criticality.h"
  #include "Ngap_InitiatingMessage.h"
  #include "Ngap_SuccessfulOutcome.h"
  #include "Ngap_UnsuccessfulOutcome.h"
}


using namespace std;


namespace ngap{
  
  MessageType::MessageType(){
    criticality = Ngap_Criticality_reject;
  }

  MessageType::~MessageType(){}

  void MessageType::setProcedureCode(Ngap_ProcedureCode_t m_procedureCode){
    procedureCode = m_procedureCode;
  }
  void MessageType::setTypeOfMessage(Ngap_NGAP_PDU_PR m_typeOfMessage){
    typeOfMessage = m_typeOfMessage;
  }
  void MessageType::setCriticality(Ngap_Criticality m_criticality){
	criticality = m_criticality;
  }
  void MessageType::setValuePresent(Ngap_InitiatingMessage__value_PR m_valuePresent){
    initiatingMsgValuePresent = m_valuePresent;
  }
  void MessageType::setValuePresent(Ngap_SuccessfulOutcome__value_PR m_valuePresent){
    successfulOutcomeValuePresent = m_valuePresent;
  }
  void MessageType::setValuePresent(Ngap_UnsuccessfulOutcome__value_PR m_valuePresent){
    unsuccessfulOutcomeValuePresent = m_valuePresent;
  }

  Ngap_ProcedureCode_t MessageType::getProcedureCode(){
    return procedureCode;
  }
  Ngap_NGAP_PDU_PR     MessageType::getTypeOfMessage(){
    return typeOfMessage;
  }
  Ngap_Criticality	   MessageType::getCriticality(){
	return criticality;
  }

  int MessageType::encode2pdu(Ngap_NGAP_PDU_t *&pdu){
    pdu->present = typeOfMessage;
    switch(typeOfMessage){
      case Ngap_NGAP_PDU_PR_initiatingMessage:{
        pdu->choice.initiatingMessage = (Ngap_InitiatingMessage_t*)calloc(1,sizeof(Ngap_InitiatingMessage_t));
        pdu->choice.initiatingMessage->procedureCode = procedureCode; 
        pdu->choice.initiatingMessage->criticality = criticality; 
        pdu->choice.initiatingMessage->value.present = initiatingMsgValuePresent;
        break;}
      case Ngap_NGAP_PDU_PR_successfulOutcome:{
        pdu->choice.successfulOutcome = (Ngap_SuccessfulOutcome_t*)calloc(1,sizeof(Ngap_SuccessfulOutcome_t));
        pdu->choice.successfulOutcome->procedureCode = procedureCode;
        pdu->choice.successfulOutcome->criticality = criticality;
        pdu->choice.successfulOutcome->value.present = successfulOutcomeValuePresent;
        break;}
      case Ngap_NGAP_PDU_PR_unsuccessfulOutcome:{
        pdu->choice.unsuccessfulOutcome = (Ngap_UnsuccessfulOutcome_t*)calloc(1,sizeof(Ngap_UnsuccessfulOutcome_t));
        pdu->choice.unsuccessfulOutcome->procedureCode = procedureCode; 
        pdu->choice.unsuccessfulOutcome->criticality = criticality;
        pdu->choice.unsuccessfulOutcome->value.present = unsuccessfulOutcomeValuePresent;
        break;}
      case Ngap_NGAP_PDU_PR_NOTHING:{
        cout<<"Ngap_NGAP_PDU_PR_NOTHING"<<"(messageType encode error)"<<endl;
        return 0;
      }
    }
  return 1;
  }

}