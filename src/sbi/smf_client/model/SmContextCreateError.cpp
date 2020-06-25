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



#include "SmContextCreateError.h"

namespace oai {
namespace smf {
namespace model {




SmContextCreateError::SmContextCreateError()
{
    m_N1SmMsgIsSet = false;
    m_RecoveryTime = utility::datetime();
    m_RecoveryTimeIsSet = false;
}

SmContextCreateError::~SmContextCreateError()
{
}

void SmContextCreateError::validate()
{
    // TODO: implement validation
}

web::json::value SmContextCreateError::toJson() const
{
    web::json::value val = web::json::value::object();

    val[utility::conversions::to_string_t("error")] = ModelBase::toJson(m_Error);
    if(m_N1SmMsgIsSet)
    {
        val[utility::conversions::to_string_t("n1SmMsg")] = ModelBase::toJson(m_N1SmMsg);
    }
    if(m_RecoveryTimeIsSet)
    {
        val[utility::conversions::to_string_t("recoveryTime")] = ModelBase::toJson(m_RecoveryTime);
    }

    return val;
}

void SmContextCreateError::fromJson(const web::json::value& val)
{
    std::shared_ptr<ProblemDetails_2> newError(new ProblemDetails_2());
    newError->fromJson(val.at(utility::conversions::to_string_t("error")));
    setError( newError );
    if(val.has_field(utility::conversions::to_string_t("n1SmMsg")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("n1SmMsg"));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<RefToBinaryData> newItem(new RefToBinaryData());
            newItem->fromJson(fieldValue);
            setN1SmMsg( newItem );
        }
    }
    if(val.has_field(utility::conversions::to_string_t("recoveryTime")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("recoveryTime"));
        if(!fieldValue.is_null())
        {
            setRecoveryTime(ModelBase::dateFromJson(fieldValue));
        }
    }
}

void SmContextCreateError::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    m_Error->toMultipart(multipart, utility::conversions::to_string_t("error."));
    if(m_N1SmMsgIsSet)
    {
        if (m_N1SmMsg.get())
        {
            m_N1SmMsg->toMultipart(multipart, utility::conversions::to_string_t("n1SmMsg."));
        }
    }
    if(m_RecoveryTimeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("recoveryTime"), m_RecoveryTime));
    }
}

void SmContextCreateError::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    std::shared_ptr<ProblemDetails_2> newError(new ProblemDetails_2());
    newError->fromMultiPart(multipart, utility::conversions::to_string_t("error."));
    setError( newError );
    if(multipart->hasContent(utility::conversions::to_string_t("n1SmMsg")))
    {
        if(multipart->hasContent(utility::conversions::to_string_t("n1SmMsg")))
        {
            std::shared_ptr<RefToBinaryData> newItem(new RefToBinaryData());
            newItem->fromMultiPart(multipart, utility::conversions::to_string_t("n1SmMsg."));
            setN1SmMsg( newItem );
        }
    }
    if(multipart->hasContent(utility::conversions::to_string_t("recoveryTime")))
    {
        setRecoveryTime(ModelBase::dateFromHttpContent(multipart->getContent(utility::conversions::to_string_t("recoveryTime"))));
    }
}

std::shared_ptr<ProblemDetails_2> SmContextCreateError::getError() const
{
    return m_Error;
}

void SmContextCreateError::setError(const std::shared_ptr<ProblemDetails_2>& value)
{
    m_Error = value;
    
}

std::shared_ptr<RefToBinaryData> SmContextCreateError::getN1SmMsg() const
{
    return m_N1SmMsg;
}

void SmContextCreateError::setN1SmMsg(const std::shared_ptr<RefToBinaryData>& value)
{
    m_N1SmMsg = value;
    m_N1SmMsgIsSet = true;
}

bool SmContextCreateError::n1SmMsgIsSet() const
{
    return m_N1SmMsgIsSet;
}

void SmContextCreateError::unsetN1SmMsg()
{
    m_N1SmMsgIsSet = false;
}

utility::datetime SmContextCreateError::getRecoveryTime() const
{
    return m_RecoveryTime;
}

void SmContextCreateError::setRecoveryTime(const utility::datetime& value)
{
    m_RecoveryTime = value;
    m_RecoveryTimeIsSet = true;
}

bool SmContextCreateError::recoveryTimeIsSet() const
{
    return m_RecoveryTimeIsSet;
}

void SmContextCreateError::unsetRecoveryTime()
{
    m_RecoveryTimeIsSet = false;
}

}
}
}

