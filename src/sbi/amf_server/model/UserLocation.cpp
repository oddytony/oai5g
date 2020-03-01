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


#include "UserLocation.h"

namespace oai {
namespace amf {
namespace model {

UserLocation::UserLocation()
{
    m_EutraLocationIsSet = false;
    m_NrLocationIsSet = false;
    m_N3gaLocationIsSet = false;
    
}

UserLocation::~UserLocation()
{
}

void UserLocation::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const UserLocation& o)
{
    j = nlohmann::json();
    if(o.eutraLocationIsSet())
        j["eutraLocation"] = o.m_EutraLocation;
    if(o.nrLocationIsSet())
        j["nrLocation"] = o.m_NrLocation;
    if(o.n3gaLocationIsSet())
        j["n3gaLocation"] = o.m_N3gaLocation;
}

void from_json(const nlohmann::json& j, UserLocation& o)
{
    if(j.find("eutraLocation") != j.end())
    {
        j.at("eutraLocation").get_to(o.m_EutraLocation);
        o.m_EutraLocationIsSet = true;
    } 
    if(j.find("nrLocation") != j.end())
    {
        j.at("nrLocation").get_to(o.m_NrLocation);
        o.m_NrLocationIsSet = true;
    } 
    if(j.find("n3gaLocation") != j.end())
    {
        j.at("n3gaLocation").get_to(o.m_N3gaLocation);
        o.m_N3gaLocationIsSet = true;
    } 
}

EutraLocation UserLocation::getEutraLocation() const
{
    return m_EutraLocation;
}
void UserLocation::setEutraLocation(EutraLocation const& value)
{
    m_EutraLocation = value;
    m_EutraLocationIsSet = true;
}
bool UserLocation::eutraLocationIsSet() const
{
    return m_EutraLocationIsSet;
}
void UserLocation::unsetEutraLocation()
{
    m_EutraLocationIsSet = false;
}
NrLocation UserLocation::getNrLocation() const
{
    return m_NrLocation;
}
void UserLocation::setNrLocation(NrLocation const& value)
{
    m_NrLocation = value;
    m_NrLocationIsSet = true;
}
bool UserLocation::nrLocationIsSet() const
{
    return m_NrLocationIsSet;
}
void UserLocation::unsetNrLocation()
{
    m_NrLocationIsSet = false;
}
N3gaLocation UserLocation::getN3gaLocation() const
{
    return m_N3gaLocation;
}
void UserLocation::setN3gaLocation(N3gaLocation const& value)
{
    m_N3gaLocation = value;
    m_N3gaLocationIsSet = true;
}
bool UserLocation::n3gaLocationIsSet() const
{
    return m_N3gaLocationIsSet;
}
void UserLocation::unsetN3gaLocation()
{
    m_N3gaLocationIsSet = false;
}

}
}
}

