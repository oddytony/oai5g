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



#include "RoamingChargingProfile.h"

namespace oai {
namespace smf {
namespace model {




RoamingChargingProfile::RoamingChargingProfile()
{
    m_TriggersIsSet = false;
    m_PartialRecordMethodIsSet = false;
}

RoamingChargingProfile::~RoamingChargingProfile()
{
}

void RoamingChargingProfile::validate()
{
    // TODO: implement validation
}

web::json::value RoamingChargingProfile::toJson() const
{
    web::json::value val = web::json::value::object();

    {
        std::vector<web::json::value> jsonArray;
        for( auto& item : m_Triggers )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        if(jsonArray.size() > 0)
        {
            val[utility::conversions::to_string_t("triggers")] = web::json::value::array(jsonArray);
        }
    }
    if(m_PartialRecordMethodIsSet)
    {
        val[utility::conversions::to_string_t("partialRecordMethod")] = ModelBase::toJson(m_PartialRecordMethod);
    }

    return val;
}

void RoamingChargingProfile::fromJson(const web::json::value& val)
{
    {
        m_Triggers.clear();
        std::vector<web::json::value> jsonArray;
        if(val.has_field(utility::conversions::to_string_t("triggers")))
        {
        for( auto& item : val.at(utility::conversions::to_string_t("triggers")).as_array() )
        {
            if(item.is_null())
            {
                m_Triggers.push_back( std::shared_ptr<Trigger>(nullptr) );
            }
            else
            {
                std::shared_ptr<Trigger> newItem(new Trigger());
                newItem->fromJson(item);
                m_Triggers.push_back( newItem );
            }
        }
        }
    }
    if(val.has_field(utility::conversions::to_string_t("partialRecordMethod")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("partialRecordMethod"));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<PartialRecordMethod> newItem(new PartialRecordMethod());
            newItem->fromJson(fieldValue);
            setPartialRecordMethod( newItem );
        }
    }
}

void RoamingChargingProfile::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    {
        std::vector<web::json::value> jsonArray;
        for( auto& item : m_Triggers )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        
        if(jsonArray.size() > 0)
        {
            multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("triggers"), web::json::value::array(jsonArray), utility::conversions::to_string_t("application/json")));
        }
    }
    if(m_PartialRecordMethodIsSet)
    {
        if (m_PartialRecordMethod.get())
        {
            m_PartialRecordMethod->toMultipart(multipart, utility::conversions::to_string_t("partialRecordMethod."));
        }
    }
}

void RoamingChargingProfile::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    {
        m_Triggers.clear();
        if(multipart->hasContent(utility::conversions::to_string_t("triggers")))
        {

        web::json::value jsonArray = web::json::value::parse(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("triggers"))));
        for( auto& item : jsonArray.as_array() )
        {
            if(item.is_null())
            {
                m_Triggers.push_back( std::shared_ptr<Trigger>(nullptr) );
            }
            else
            {
                std::shared_ptr<Trigger> newItem(new Trigger());
                newItem->fromJson(item);
                m_Triggers.push_back( newItem );
            }
        }
        }
    }
    if(multipart->hasContent(utility::conversions::to_string_t("partialRecordMethod")))
    {
        if(multipart->hasContent(utility::conversions::to_string_t("partialRecordMethod")))
        {
            std::shared_ptr<PartialRecordMethod> newItem(new PartialRecordMethod());
            newItem->fromMultiPart(multipart, utility::conversions::to_string_t("partialRecordMethod."));
            setPartialRecordMethod( newItem );
        }
    }
}

std::vector<std::shared_ptr<Trigger>>& RoamingChargingProfile::getTriggers()
{
    return m_Triggers;
}

void RoamingChargingProfile::setTriggers(const std::vector<std::shared_ptr<Trigger>>& value)
{
    m_Triggers = value;
    m_TriggersIsSet = true;
}

bool RoamingChargingProfile::triggersIsSet() const
{
    return m_TriggersIsSet;
}

void RoamingChargingProfile::unsetTriggers()
{
    m_TriggersIsSet = false;
}

std::shared_ptr<PartialRecordMethod> RoamingChargingProfile::getPartialRecordMethod() const
{
    return m_PartialRecordMethod;
}

void RoamingChargingProfile::setPartialRecordMethod(const std::shared_ptr<PartialRecordMethod>& value)
{
    m_PartialRecordMethod = value;
    m_PartialRecordMethodIsSet = true;
}

bool RoamingChargingProfile::partialRecordMethodIsSet() const
{
    return m_PartialRecordMethodIsSet;
}

void RoamingChargingProfile::unsetPartialRecordMethod()
{
    m_PartialRecordMethodIsSet = false;
}

}
}
}


