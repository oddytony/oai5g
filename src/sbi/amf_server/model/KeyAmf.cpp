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


#include "KeyAmf.h"

namespace oai {
namespace amf {
namespace model {

KeyAmf::KeyAmf()
{
    m_KeyVal = "";
    
}

KeyAmf::~KeyAmf()
{
}

void KeyAmf::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const KeyAmf& o)
{
    j = nlohmann::json();
    j["keyType"] = o.m_KeyType;
    j["keyVal"] = o.m_KeyVal;
}

void from_json(const nlohmann::json& j, KeyAmf& o)
{
    j.at("keyType").get_to(o.m_KeyType);
    j.at("keyVal").get_to(o.m_KeyVal);
}

KeyAmfType KeyAmf::getKeyType() const
{
    return m_KeyType;
}
void KeyAmf::setKeyType(KeyAmfType const& value)
{
    m_KeyType = value;
    
}
std::string KeyAmf::getKeyVal() const
{
    return m_KeyVal;
}
void KeyAmf::setKeyVal(std::string const& value)
{
    m_KeyVal = value;
    
}

}
}
}

