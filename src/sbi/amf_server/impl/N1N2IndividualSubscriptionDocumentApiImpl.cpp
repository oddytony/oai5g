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

#include "N1N2IndividualSubscriptionDocumentApiImpl.h"

namespace oai {
namespace amf {
namespace api {

N1N2IndividualSubscriptionDocumentApiImpl::N1N2IndividualSubscriptionDocumentApiImpl(std::shared_ptr<Pistache::Rest::Router> rtr)
    : N1N2IndividualSubscriptionDocumentApi(rtr)
    { }

void N1N2IndividualSubscriptionDocumentApiImpl::n1_n2_message_un_subscribe(const std::string &ueContextId, const std::string &subscriptionId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}

}
}
}

