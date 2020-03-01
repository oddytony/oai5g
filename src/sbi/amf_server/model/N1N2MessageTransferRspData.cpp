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


#include "N1N2MessageTransferRspData.h"

namespace oai {
namespace amf {
namespace model {

N1N2MessageTransferRspData::N1N2MessageTransferRspData()
{
    m_SupportedFeatures = "";
    m_SupportedFeaturesIsSet = false;
    
}

N1N2MessageTransferRspData::~N1N2MessageTransferRspData()
{
}

void N1N2MessageTransferRspData::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const N1N2MessageTransferRspData& o)
{
    j = nlohmann::json();
    j["cause"] = o.m_Cause;
    if(o.supportedFeaturesIsSet())
        j["supportedFeatures"] = o.m_SupportedFeatures;
}

void from_json(const nlohmann::json& j, N1N2MessageTransferRspData& o)
{
    j.at("cause").get_to(o.m_Cause);
    if(j.find("supportedFeatures") != j.end())
    {
        j.at("supportedFeatures").get_to(o.m_SupportedFeatures);
        o.m_SupportedFeaturesIsSet = true;
    } 
}

N1N2MessageTransferCause N1N2MessageTransferRspData::getCause() const
{
    return m_Cause;
}
void N1N2MessageTransferRspData::setCause(N1N2MessageTransferCause const& value)
{
    m_Cause = value;
    
}
std::string N1N2MessageTransferRspData::getSupportedFeatures() const
{
    return m_SupportedFeatures;
}
void N1N2MessageTransferRspData::setSupportedFeatures(std::string const& value)
{
    m_SupportedFeatures = value;
    m_SupportedFeaturesIsSet = true;
}
bool N1N2MessageTransferRspData::supportedFeaturesIsSet() const
{
    return m_SupportedFeaturesIsSet;
}
void N1N2MessageTransferRspData::unsetSupportedFeatures()
{
    m_SupportedFeaturesIsSet = false;
}

}
}
}

