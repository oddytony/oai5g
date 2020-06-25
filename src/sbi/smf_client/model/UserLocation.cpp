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



#include "UserLocation.h"

namespace oai {
namespace smf {
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

web::json::value UserLocation::toJson() const
{
    web::json::value val = web::json::value::object();

    if(m_EutraLocationIsSet)
    {
        val[utility::conversions::to_string_t("eutraLocation")] = ModelBase::toJson(m_EutraLocation);
    }
    if(m_NrLocationIsSet)
    {
        val[utility::conversions::to_string_t("nrLocation")] = ModelBase::toJson(m_NrLocation);
    }
    if(m_N3gaLocationIsSet)
    {
        val[utility::conversions::to_string_t("n3gaLocation")] = ModelBase::toJson(m_N3gaLocation);
    }

    return val;
}

void UserLocation::fromJson(const web::json::value& val)
{
    if(val.has_field(utility::conversions::to_string_t("eutraLocation")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("eutraLocation"));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<EutraLocation> newItem(new EutraLocation());
            newItem->fromJson(fieldValue);
            setEutraLocation( newItem );
        }
    }
    if(val.has_field(utility::conversions::to_string_t("nrLocation")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("nrLocation"));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<NrLocation> newItem(new NrLocation());
            newItem->fromJson(fieldValue);
            setNrLocation( newItem );
        }
    }
    if(val.has_field(utility::conversions::to_string_t("n3gaLocation")))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t("n3gaLocation"));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<N3gaLocation> newItem(new N3gaLocation());
            newItem->fromJson(fieldValue);
            setN3gaLocation( newItem );
        }
    }
}

void UserLocation::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    if(m_EutraLocationIsSet)
    {
        if (m_EutraLocation.get())
        {
            m_EutraLocation->toMultipart(multipart, utility::conversions::to_string_t("eutraLocation."));
        }
    }
    if(m_NrLocationIsSet)
    {
        if (m_NrLocation.get())
        {
            m_NrLocation->toMultipart(multipart, utility::conversions::to_string_t("nrLocation."));
        }
    }
    if(m_N3gaLocationIsSet)
    {
        if (m_N3gaLocation.get())
        {
            m_N3gaLocation->toMultipart(multipart, utility::conversions::to_string_t("n3gaLocation."));
        }
    }
}

void UserLocation::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    if(multipart->hasContent(utility::conversions::to_string_t("eutraLocation")))
    {
        if(multipart->hasContent(utility::conversions::to_string_t("eutraLocation")))
        {
            std::shared_ptr<EutraLocation> newItem(new EutraLocation());
            newItem->fromMultiPart(multipart, utility::conversions::to_string_t("eutraLocation."));
            setEutraLocation( newItem );
        }
    }
    if(multipart->hasContent(utility::conversions::to_string_t("nrLocation")))
    {
        if(multipart->hasContent(utility::conversions::to_string_t("nrLocation")))
        {
            std::shared_ptr<NrLocation> newItem(new NrLocation());
            newItem->fromMultiPart(multipart, utility::conversions::to_string_t("nrLocation."));
            setNrLocation( newItem );
        }
    }
    if(multipart->hasContent(utility::conversions::to_string_t("n3gaLocation")))
    {
        if(multipart->hasContent(utility::conversions::to_string_t("n3gaLocation")))
        {
            std::shared_ptr<N3gaLocation> newItem(new N3gaLocation());
            newItem->fromMultiPart(multipart, utility::conversions::to_string_t("n3gaLocation."));
            setN3gaLocation( newItem );
        }
    }
}

std::shared_ptr<EutraLocation> UserLocation::getEutraLocation() const
{
    return m_EutraLocation;
}

void UserLocation::setEutraLocation(const std::shared_ptr<EutraLocation>& value)
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

std::shared_ptr<NrLocation> UserLocation::getNrLocation() const
{
    return m_NrLocation;
}

void UserLocation::setNrLocation(const std::shared_ptr<NrLocation>& value)
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

std::shared_ptr<N3gaLocation> UserLocation::getN3gaLocation() const
{
    return m_N3gaLocation;
}

void UserLocation::setN3gaLocation(const std::shared_ptr<N3gaLocation>& value)
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

