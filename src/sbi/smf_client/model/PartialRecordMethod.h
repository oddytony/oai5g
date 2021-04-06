/**
 * Nsmf_PDUSession
 * SMF PDU Session Service. © 2019, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.1.0.alpha-1
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 4.1.1-SNAPSHOT.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

/*
 * PartialRecordMethod.h
 *
 *
 */

#ifndef OAI_SMF_MODEL_PartialRecordMethod_H_
#define OAI_SMF_MODEL_PartialRecordMethod_H_

#include "../ModelBase.h"

namespace oai {
namespace smf {
namespace model {

/// <summary>
///
/// </summary>
class PartialRecordMethod : public ModelBase {
 public:
  PartialRecordMethod();
  virtual ~PartialRecordMethod();

  /////////////////////////////////////////////
  /// ModelBase overrides

  void validate() override;

  web::json::value toJson() const override;
  void fromJson(const web::json::value& json) override;

  void toMultipart(
      std::shared_ptr<MultipartFormData> multipart,
      const utility::string_t& namePrefix) const override;
  void fromMultiPart(
      std::shared_ptr<MultipartFormData> multipart,
      const utility::string_t& namePrefix) override;

  /////////////////////////////////////////////
  /// PartialRecordMethod members

 protected:
};

}  // namespace model
}  // namespace smf
}  // namespace oai

#endif /* OAI_SMF_MODEL_PartialRecordMethod_H_ */
