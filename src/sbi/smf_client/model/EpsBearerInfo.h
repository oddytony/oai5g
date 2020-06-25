/**
 * Nsmf_PDUSession
 * SMF PDU Session Service. © 2019, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved. 
 *
 * The version of the OpenAPI document: 1.1.0.alpha-1
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 4.1.1-SNAPSHOT.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

/*
 * EpsBearerInfo.h
 *
 * 
 */

#ifndef OAI_SMF_MODEL_EpsBearerInfo_H_
#define OAI_SMF_MODEL_EpsBearerInfo_H_


#include "../ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace oai {
namespace smf {
namespace model {


/// <summary>
/// 
/// </summary>
class  EpsBearerInfo
    : public ModelBase
{
public:
    EpsBearerInfo();
    virtual ~EpsBearerInfo();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// EpsBearerInfo members

    /// <summary>
    /// 
    /// </summary>
    int32_t getEbi() const;
    
    void setEbi(int32_t value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getPgwS8uFteid() const;
    
    void setPgwS8uFteid(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getBearerLevelQoS() const;
    
    void setBearerLevelQoS(const utility::string_t& value);


protected:
    int32_t m_Ebi;
        utility::string_t m_PgwS8uFteid;
        utility::string_t m_BearerLevelQoS;
    };


}
}
}

#endif /* OAI_SMF_MODEL_EpsBearerInfo_H_ */