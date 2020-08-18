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

#include "N1N2MessageCollectionDocumentApi.h"
#include "Helpers.h"
#include "mime_parser.hpp"
#include "logger.hpp"

namespace oai {
namespace amf {
namespace api {

using namespace org::openapitools::server::helpers;
using namespace oai::amf::model;

N1N2MessageCollectionDocumentApi::N1N2MessageCollectionDocumentApi(std::shared_ptr<Pistache::Rest::Router> rtr) { 
    router = rtr;
}

void N1N2MessageCollectionDocumentApi::init() {
    setupRoutes();
}

void N1N2MessageCollectionDocumentApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Post(*router, base + "/ue-contexts/:ueContextId/n1-n2-messages", Routes::bind(&N1N2MessageCollectionDocumentApi::n1_n2_message_transfer_handler, this));

    // Default handler, called when a route is not found
    router->addCustomHandler(Routes::bind(&N1N2MessageCollectionDocumentApi::n1_n2_message_collection_document_api_default_handler, this));
}

void N1N2MessageCollectionDocumentApi::n1_n2_message_transfer_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto ueContextId = request.param(":ueContextId").as<std::string>();
    Logger::amf_server().debug("Received a N1N2MessageTrasfer request with ue_ctx_id %s ",ueContextId.c_str());
    // Getting the body param

    //simple parser
    mime_parser sp = { };
    sp.parse(request.body());

    std::vector<mime_part> parts = { };
    sp.get_mime_parts(parts);
    uint8_t size = parts.size();
    Logger::amf_server().debug("Number of MIME parts %d", size);

    //at least 2 parts for Json data and N1 (+ N2)
    if (size < 2) {
      response.send(Pistache::Http::Code::Bad_Request);
      return;
    }

    Logger::amf_server().debug("Request body, part 1: \n%s", parts[0].body.c_str());
    Logger::amf_server().debug("Request body, part 2: \n %s",parts[1].body.c_str());

    bool is_ngap = false;
    if (size > 2) {
      is_ngap = true;
      Logger::amf_server().debug("Request body, part 3: \n %s",parts[2].body.c_str());
    }

    N1N2MessageTransferReqData n1N2MessageTransferReqData = {};
    
    try {
      nlohmann::json::parse(parts[0].body.c_str()).get_to(n1N2MessageTransferReqData);
      if(!is_ngap)
        this->n1_n2_message_transfer(ueContextId, n1N2MessageTransferReqData, parts[1].body, response);
      else
        this->n1_n2_message_transfer(ueContextId, n1N2MessageTransferReqData, parts[1].body, parts[2].body, response);
    } catch (nlohmann::detail::exception &e) {
        //send a 400 error
        Logger::amf_server().error("response 400 error"); 
        response.send(Pistache::Http::Code::Bad_Request, e.what());
        return;
    } catch (std::exception &e) {
        //send a 500 error
        Logger::amf_server().error("response 500 error"); 
        response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
        return;
    }
}

void N1N2MessageCollectionDocumentApi::n1_n2_message_collection_document_api_default_handler(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}
}
}

