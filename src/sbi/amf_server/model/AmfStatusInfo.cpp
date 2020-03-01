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


#include "AmfStatusInfo.h"

namespace oai {
namespace amf {
namespace model {

AmfStatusInfo::AmfStatusInfo()
{
    m_TargetAmfRemoval = "";
    m_TargetAmfRemovalIsSet = false;
    m_TargetAmfFailure = "";
    m_TargetAmfFailureIsSet = false;
    
}

AmfStatusInfo::~AmfStatusInfo()
{
}

void AmfStatusInfo::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const AmfStatusInfo& o)
{
    j = nlohmann::json();
    j["guamiList"] = o.m_GuamiList;
    j["statusChange"] = o.m_StatusChange;
    if(o.targetAmfRemovalIsSet())
        j["targetAmfRemoval"] = o.m_TargetAmfRemoval;
    if(o.targetAmfFailureIsSet())
        j["targetAmfFailure"] = o.m_TargetAmfFailure;
}

void from_json(const nlohmann::json& j, AmfStatusInfo& o)
{
    j.at("guamiList").get_to(o.m_GuamiList);
    j.at("statusChange").get_to(o.m_StatusChange);
    if(j.find("targetAmfRemoval") != j.end())
    {
        j.at("targetAmfRemoval").get_to(o.m_TargetAmfRemoval);
        o.m_TargetAmfRemovalIsSet = true;
    } 
    if(j.find("targetAmfFailure") != j.end())
    {
        j.at("targetAmfFailure").get_to(o.m_TargetAmfFailure);
        o.m_TargetAmfFailureIsSet = true;
    } 
}

std::vector<Guami>& AmfStatusInfo::getGuamiList()
{
    return m_GuamiList;
}
StatusChange AmfStatusInfo::getStatusChange() const
{
    return m_StatusChange;
}
void AmfStatusInfo::setStatusChange(StatusChange const& value)
{
    m_StatusChange = value;
    
}
std::string AmfStatusInfo::getTargetAmfRemoval() const
{
    return m_TargetAmfRemoval;
}
void AmfStatusInfo::setTargetAmfRemoval(std::string const& value)
{
    m_TargetAmfRemoval = value;
    m_TargetAmfRemovalIsSet = true;
}
bool AmfStatusInfo::targetAmfRemovalIsSet() const
{
    return m_TargetAmfRemovalIsSet;
}
void AmfStatusInfo::unsetTargetAmfRemoval()
{
    m_TargetAmfRemovalIsSet = false;
}
std::string AmfStatusInfo::getTargetAmfFailure() const
{
    return m_TargetAmfFailure;
}
void AmfStatusInfo::setTargetAmfFailure(std::string const& value)
{
    m_TargetAmfFailure = value;
    m_TargetAmfFailureIsSet = true;
}
bool AmfStatusInfo::targetAmfFailureIsSet() const
{
    return m_TargetAmfFailureIsSet;
}
void AmfStatusInfo::unsetTargetAmfFailure()
{
    m_TargetAmfFailureIsSet = false;
}

}
}
}

