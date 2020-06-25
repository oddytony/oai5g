/**
* Namf_Communication
* AMF Communication Service © 2019, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved. 
*
* The version of the OpenAPI document: 1.1.0.alpha-1
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

/*
* NonUEN2MessageNotificationIndividualSubscriptionDocumentApiImpl.h
*
* 
*/

#ifndef NON_UEN2_MESSAGE_NOTIFICATION_INDIVIDUAL_SUBSCRIPTION_DOCUMENT_API_IMPL_H_
#define NON_UEN2_MESSAGE_NOTIFICATION_INDIVIDUAL_SUBSCRIPTION_DOCUMENT_API_IMPL_H_


#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <memory>

#include <NonUEN2MessageNotificationIndividualSubscriptionDocumentApi.h>

#include <pistache/optional.h>

#include "ProblemDetails.h"
#include <string>

#include "amf_app.hpp"

namespace oai {
namespace amf {
namespace api {

class NonUEN2MessageNotificationIndividualSubscriptionDocumentApiImpl : public oai::amf::api::NonUEN2MessageNotificationIndividualSubscriptionDocumentApi {
public:
    NonUEN2MessageNotificationIndividualSubscriptionDocumentApiImpl(std::shared_ptr<Pistache::Rest::Router>, amf_application::amf_app *amf_app_inst);
    ~NonUEN2MessageNotificationIndividualSubscriptionDocumentApiImpl() {}

    void non_ue_n2_info_un_subscribe(const std::string &n2NotifySubscriptionId, Pistache::Http::ResponseWriter &response);
private:
    amf_application::amf_app *m_amf_app;
};

}
}
}



#endif