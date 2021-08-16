/**
 * Namf_EventExposure
 * AMF Event Exposure Service © 2019, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.1.0.alpha-1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * IndividualSubscriptionDocumentApiEventExposure.h
 *
 *
 */

#ifndef IndividualSubscriptionDocumentApiEventExposure_H_
#define IndividualSubscriptionDocumentApiEventExposure_H_

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/http_headers.h>
#include <pistache/optional.h>

#include <utility>

#include "AmfUpdatedEventSubscription.h"
//#include "OneOfarrayAmfUpdateEventOptionItem.h"
#include "ProblemDetails.h"
//#include "SubscriptionData.h"
#include "AmfUpdateEventOptionItem.h"
#include <string>

namespace oai {
namespace amf {
namespace api {

using namespace oai::amf::model;

class IndividualSubscriptionDocumentApiEventExposure {
 public:
  explicit IndividualSubscriptionDocumentApiEventExposure(
      const std::shared_ptr<Pistache::Rest::Router>& rtr);
  virtual ~IndividualSubscriptionDocumentApiEventExposure() = default;
  void init();

  const std::string base = "/namf-comm/";

 private:
  void setupRoutes();

  void delete_subscription_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);
  void modify_subscription_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);
  void individual_subscription_document_api_default_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);

  const std::shared_ptr<Pistache::Rest::Router> router;

  /// <summary>
  /// Helper function to handle unexpected Exceptions during Parameter parsing
  /// and validation. May be overriden to return custom error formats.
  /// </summary>
  virtual std::pair<Pistache::Http::Code, std::string> handleParsingException(
      const std::exception& ex) const noexcept;

  /// <summary>
  /// Helper function to handle unexpected Exceptions during processing of the
  /// request in handler functions. May be overriden to return custom error
  /// formats.
  /// </summary>
  virtual std::pair<Pistache::Http::Code, std::string> handleOperationException(
      const std::exception& ex) const noexcept;

  /// <summary>
  /// Namf_EventExposure Unsubscribe service Operation
  /// </summary>
  /// <remarks>
  ///
  /// </remarks>
  /// <param name="subscriptionId">Unique ID of the subscription to be
  /// deleted</param>
  virtual void delete_subscription(
      const std::string& subscriptionId,
      Pistache::Http::ResponseWriter& response) = 0;
  /// <summary>
  /// Namf_EventExposure Subscribe Modify service Operation
  /// </summary>
  /// <remarks>
  ///
  /// </remarks>
  /// <param name="subscriptionId">Unique ID of the subscription to be
  /// modified</param> <param name="AmfUpdateEventOptionItem"></param>
  virtual void modify_subscription(
      const std::string& subscriptionId,
      const oai::amf::model::AmfUpdateEventOptionItem& amfUpdateEventOptionItem,
      Pistache::Http::ResponseWriter& response) = 0;
};

}  // namespace api
}  // namespace amf
}  // namespace oai

#endif /* IndividualSubscriptionDocumentApiEventExposure_H_ */
