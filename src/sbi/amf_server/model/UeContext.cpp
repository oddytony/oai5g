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


#include "UeContext.h"

namespace oai {
namespace amf {
namespace model {

UeContext::UeContext()
{
    m_Supi = "";
    m_SupiIsSet = false;
    m_SupiUnauthInd = false;
    m_SupiUnauthIndIsSet = false;
    m_GpsiListIsSet = false;
    m_Pei = "";
    m_PeiIsSet = false;
    m_UdmGroupId = "";
    m_UdmGroupIdIsSet = false;
    m_AusfGroupId = "";
    m_AusfGroupIdIsSet = false;
    m_RoutingIndicator = "";
    m_RoutingIndicatorIsSet = false;
    m_GroupListIsSet = false;
    m_DrxParameterIsSet = false;
    m_SubRfsp = 0;
    m_SubRfspIsSet = false;
    m_UsedRfsp = 0;
    m_UsedRfspIsSet = false;
    m_SubUeAmbrIsSet = false;
    m_SmsSupportIsSet = false;
    m_SmsfId = "";
    m_SmsfIdIsSet = false;
    m_SeafDataIsSet = false;
    m__5gMmCapabilityIsSet = false;
    m_PcfId = "";
    m_PcfIdIsSet = false;
    m_PcfAmPolicyUri = "";
    m_PcfAmPolicyUriIsSet = false;
    m_AmPolicyReqTriggerListIsSet = false;
    m_PcfUePolicyUri = "";
    m_PcfUePolicyUriIsSet = false;
    m_UePolicyReqTriggerListIsSet = false;
    m_HpcfId = "";
    m_HpcfIdIsSet = false;
    m_RestrictedRatListIsSet = false;
    m_ForbiddenAreaListIsSet = false;
    m_ServiceAreaRestrictionIsSet = false;
    m_RestrictedCoreNwTypeListIsSet = false;
    m_EventSubscriptionListIsSet = false;
    m_MmContextListIsSet = false;
    m_SessionContextListIsSet = false;
    m_TraceDataIsSet = false;
    m_RemainingServiceGapTimer = 0;
    m_RemainingServiceGapTimerIsSet = false;
    
}

UeContext::~UeContext()
{
}

void UeContext::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const UeContext& o)
{
    j = nlohmann::json();
    if(o.supiIsSet())
        j["supi"] = o.m_Supi;
    if(o.supiUnauthIndIsSet())
        j["supiUnauthInd"] = o.m_SupiUnauthInd;
    if(o.gpsiListIsSet())
        j["gpsiList"] = o.m_GpsiList;
    if(o.peiIsSet())
        j["pei"] = o.m_Pei;
    if(o.udmGroupIdIsSet())
        j["udmGroupId"] = o.m_UdmGroupId;
    if(o.ausfGroupIdIsSet())
        j["ausfGroupId"] = o.m_AusfGroupId;
    if(o.routingIndicatorIsSet())
        j["routingIndicator"] = o.m_RoutingIndicator;
    if(o.groupListIsSet())
        j["groupList"] = o.m_GroupList;
    if(o.drxParameterIsSet())
        j["drxParameter"] = o.m_DrxParameter;
    if(o.subRfspIsSet())
        j["subRfsp"] = o.m_SubRfsp;
    if(o.usedRfspIsSet())
        j["usedRfsp"] = o.m_UsedRfsp;
    if(o.subUeAmbrIsSet())
        j["subUeAmbr"] = o.m_SubUeAmbr;
    if(o.smsSupportIsSet())
        j["smsSupport"] = o.m_SmsSupport;
    if(o.smsfIdIsSet())
        j["smsfId"] = o.m_SmsfId;
    if(o.seafDataIsSet())
        j["seafData"] = o.m_SeafData;
    if(o._5gMmCapabilityIsSet())
        j["5gMmCapability"] = o.m__5gMmCapability;
    if(o.pcfIdIsSet())
        j["pcfId"] = o.m_PcfId;
    if(o.pcfAmPolicyUriIsSet())
        j["pcfAmPolicyUri"] = o.m_PcfAmPolicyUri;
    if(o.amPolicyReqTriggerListIsSet())
        j["amPolicyReqTriggerList"] = o.m_AmPolicyReqTriggerList;
    if(o.pcfUePolicyUriIsSet())
        j["pcfUePolicyUri"] = o.m_PcfUePolicyUri;
    if(o.uePolicyReqTriggerListIsSet())
        j["uePolicyReqTriggerList"] = o.m_UePolicyReqTriggerList;
    if(o.hpcfIdIsSet())
        j["hpcfId"] = o.m_HpcfId;
    if(o.restrictedRatListIsSet())
        j["restrictedRatList"] = o.m_RestrictedRatList;
    if(o.forbiddenAreaListIsSet())
        j["forbiddenAreaList"] = o.m_ForbiddenAreaList;
    if(o.serviceAreaRestrictionIsSet())
        j["serviceAreaRestriction"] = o.m_ServiceAreaRestriction;
    if(o.restrictedCoreNwTypeListIsSet())
        j["restrictedCoreNwTypeList"] = o.m_RestrictedCoreNwTypeList;
    if(o.eventSubscriptionListIsSet())
        j["eventSubscriptionList"] = o.m_EventSubscriptionList;
    if(o.mmContextListIsSet())
        j["mmContextList"] = o.m_MmContextList;
    if(o.sessionContextListIsSet())
        j["sessionContextList"] = o.m_SessionContextList;
    if(o.traceDataIsSet())
        j["traceData"] = o.m_TraceData;
    if(o.remainingServiceGapTimerIsSet())
        j["remainingServiceGapTimer"] = o.m_RemainingServiceGapTimer;
}

void from_json(const nlohmann::json& j, UeContext& o)
{
    if(j.find("supi") != j.end())
    {
        j.at("supi").get_to(o.m_Supi);
        o.m_SupiIsSet = true;
    } 
    if(j.find("supiUnauthInd") != j.end())
    {
        j.at("supiUnauthInd").get_to(o.m_SupiUnauthInd);
        o.m_SupiUnauthIndIsSet = true;
    } 
    if(j.find("gpsiList") != j.end())
    {
        j.at("gpsiList").get_to(o.m_GpsiList);
        o.m_GpsiListIsSet = true;
    } 
    if(j.find("pei") != j.end())
    {
        j.at("pei").get_to(o.m_Pei);
        o.m_PeiIsSet = true;
    } 
    if(j.find("udmGroupId") != j.end())
    {
        j.at("udmGroupId").get_to(o.m_UdmGroupId);
        o.m_UdmGroupIdIsSet = true;
    } 
    if(j.find("ausfGroupId") != j.end())
    {
        j.at("ausfGroupId").get_to(o.m_AusfGroupId);
        o.m_AusfGroupIdIsSet = true;
    } 
    if(j.find("routingIndicator") != j.end())
    {
        j.at("routingIndicator").get_to(o.m_RoutingIndicator);
        o.m_RoutingIndicatorIsSet = true;
    } 
    if(j.find("groupList") != j.end())
    {
        j.at("groupList").get_to(o.m_GroupList);
        o.m_GroupListIsSet = true;
    } 
    if(j.find("drxParameter") != j.end())
    {
        j.at("drxParameter").get_to(o.m_DrxParameter);
        o.m_DrxParameterIsSet = true;
    } 
    if(j.find("subRfsp") != j.end())
    {
        j.at("subRfsp").get_to(o.m_SubRfsp);
        o.m_SubRfspIsSet = true;
    } 
    if(j.find("usedRfsp") != j.end())
    {
        j.at("usedRfsp").get_to(o.m_UsedRfsp);
        o.m_UsedRfspIsSet = true;
    } 
    if(j.find("subUeAmbr") != j.end())
    {
        j.at("subUeAmbr").get_to(o.m_SubUeAmbr);
        o.m_SubUeAmbrIsSet = true;
    } 
    if(j.find("smsSupport") != j.end())
    {
        j.at("smsSupport").get_to(o.m_SmsSupport);
        o.m_SmsSupportIsSet = true;
    } 
    if(j.find("smsfId") != j.end())
    {
        j.at("smsfId").get_to(o.m_SmsfId);
        o.m_SmsfIdIsSet = true;
    } 
    if(j.find("seafData") != j.end())
    {
        j.at("seafData").get_to(o.m_SeafData);
        o.m_SeafDataIsSet = true;
    } 
    if(j.find("5gMmCapability") != j.end())
    {
        j.at("5gMmCapability").get_to(o.m__5gMmCapability);
        o.m__5gMmCapabilityIsSet = true;
    } 
    if(j.find("pcfId") != j.end())
    {
        j.at("pcfId").get_to(o.m_PcfId);
        o.m_PcfIdIsSet = true;
    } 
    if(j.find("pcfAmPolicyUri") != j.end())
    {
        j.at("pcfAmPolicyUri").get_to(o.m_PcfAmPolicyUri);
        o.m_PcfAmPolicyUriIsSet = true;
    } 
    if(j.find("amPolicyReqTriggerList") != j.end())
    {
        j.at("amPolicyReqTriggerList").get_to(o.m_AmPolicyReqTriggerList);
        o.m_AmPolicyReqTriggerListIsSet = true;
    } 
    if(j.find("pcfUePolicyUri") != j.end())
    {
        j.at("pcfUePolicyUri").get_to(o.m_PcfUePolicyUri);
        o.m_PcfUePolicyUriIsSet = true;
    } 
    if(j.find("uePolicyReqTriggerList") != j.end())
    {
        j.at("uePolicyReqTriggerList").get_to(o.m_UePolicyReqTriggerList);
        o.m_UePolicyReqTriggerListIsSet = true;
    } 
    if(j.find("hpcfId") != j.end())
    {
        j.at("hpcfId").get_to(o.m_HpcfId);
        o.m_HpcfIdIsSet = true;
    } 
    if(j.find("restrictedRatList") != j.end())
    {
        j.at("restrictedRatList").get_to(o.m_RestrictedRatList);
        o.m_RestrictedRatListIsSet = true;
    } 
    if(j.find("forbiddenAreaList") != j.end())
    {
        j.at("forbiddenAreaList").get_to(o.m_ForbiddenAreaList);
        o.m_ForbiddenAreaListIsSet = true;
    } 
    if(j.find("serviceAreaRestriction") != j.end())
    {
        j.at("serviceAreaRestriction").get_to(o.m_ServiceAreaRestriction);
        o.m_ServiceAreaRestrictionIsSet = true;
    } 
    if(j.find("restrictedCoreNwTypeList") != j.end())
    {
        j.at("restrictedCoreNwTypeList").get_to(o.m_RestrictedCoreNwTypeList);
        o.m_RestrictedCoreNwTypeListIsSet = true;
    } 
    if(j.find("eventSubscriptionList") != j.end())
    {
        j.at("eventSubscriptionList").get_to(o.m_EventSubscriptionList);
        o.m_EventSubscriptionListIsSet = true;
    } 
    if(j.find("mmContextList") != j.end())
    {
        j.at("mmContextList").get_to(o.m_MmContextList);
        o.m_MmContextListIsSet = true;
    } 
    if(j.find("sessionContextList") != j.end())
    {
        j.at("sessionContextList").get_to(o.m_SessionContextList);
        o.m_SessionContextListIsSet = true;
    } 
    if(j.find("traceData") != j.end())
    {
        j.at("traceData").get_to(o.m_TraceData);
        o.m_TraceDataIsSet = true;
    } 
    if(j.find("remainingServiceGapTimer") != j.end())
    {
        j.at("remainingServiceGapTimer").get_to(o.m_RemainingServiceGapTimer);
        o.m_RemainingServiceGapTimerIsSet = true;
    } 
}

std::string UeContext::getSupi() const
{
    return m_Supi;
}
void UeContext::setSupi(std::string const& value)
{
    m_Supi = value;
    m_SupiIsSet = true;
}
bool UeContext::supiIsSet() const
{
    return m_SupiIsSet;
}
void UeContext::unsetSupi()
{
    m_SupiIsSet = false;
}
bool UeContext::isSupiUnauthInd() const
{
    return m_SupiUnauthInd;
}
void UeContext::setSupiUnauthInd(bool const value)
{
    m_SupiUnauthInd = value;
    m_SupiUnauthIndIsSet = true;
}
bool UeContext::supiUnauthIndIsSet() const
{
    return m_SupiUnauthIndIsSet;
}
void UeContext::unsetSupiUnauthInd()
{
    m_SupiUnauthIndIsSet = false;
}
std::vector<std::string>& UeContext::getGpsiList()
{
    return m_GpsiList;
}
bool UeContext::gpsiListIsSet() const
{
    return m_GpsiListIsSet;
}
void UeContext::unsetGpsiList()
{
    m_GpsiListIsSet = false;
}
std::string UeContext::getPei() const
{
    return m_Pei;
}
void UeContext::setPei(std::string const& value)
{
    m_Pei = value;
    m_PeiIsSet = true;
}
bool UeContext::peiIsSet() const
{
    return m_PeiIsSet;
}
void UeContext::unsetPei()
{
    m_PeiIsSet = false;
}
std::string UeContext::getUdmGroupId() const
{
    return m_UdmGroupId;
}
void UeContext::setUdmGroupId(std::string const& value)
{
    m_UdmGroupId = value;
    m_UdmGroupIdIsSet = true;
}
bool UeContext::udmGroupIdIsSet() const
{
    return m_UdmGroupIdIsSet;
}
void UeContext::unsetUdmGroupId()
{
    m_UdmGroupIdIsSet = false;
}
std::string UeContext::getAusfGroupId() const
{
    return m_AusfGroupId;
}
void UeContext::setAusfGroupId(std::string const& value)
{
    m_AusfGroupId = value;
    m_AusfGroupIdIsSet = true;
}
bool UeContext::ausfGroupIdIsSet() const
{
    return m_AusfGroupIdIsSet;
}
void UeContext::unsetAusfGroupId()
{
    m_AusfGroupIdIsSet = false;
}
std::string UeContext::getRoutingIndicator() const
{
    return m_RoutingIndicator;
}
void UeContext::setRoutingIndicator(std::string const& value)
{
    m_RoutingIndicator = value;
    m_RoutingIndicatorIsSet = true;
}
bool UeContext::routingIndicatorIsSet() const
{
    return m_RoutingIndicatorIsSet;
}
void UeContext::unsetRoutingIndicator()
{
    m_RoutingIndicatorIsSet = false;
}
std::vector<std::string>& UeContext::getGroupList()
{
    return m_GroupList;
}
bool UeContext::groupListIsSet() const
{
    return m_GroupListIsSet;
}
void UeContext::unsetGroupList()
{
    m_GroupListIsSet = false;
}
std::string UeContext::getDrxParameter() const
{
    return m_DrxParameter;
}
void UeContext::setDrxParameter(std::string const& value)
{
    m_DrxParameter = value;
    m_DrxParameterIsSet = true;
}
bool UeContext::drxParameterIsSet() const
{
    return m_DrxParameterIsSet;
}
void UeContext::unsetDrxParameter()
{
    m_DrxParameterIsSet = false;
}
int32_t UeContext::getSubRfsp() const
{
    return m_SubRfsp;
}
void UeContext::setSubRfsp(int32_t const value)
{
    m_SubRfsp = value;
    m_SubRfspIsSet = true;
}
bool UeContext::subRfspIsSet() const
{
    return m_SubRfspIsSet;
}
void UeContext::unsetSubRfsp()
{
    m_SubRfspIsSet = false;
}
int32_t UeContext::getUsedRfsp() const
{
    return m_UsedRfsp;
}
void UeContext::setUsedRfsp(int32_t const value)
{
    m_UsedRfsp = value;
    m_UsedRfspIsSet = true;
}
bool UeContext::usedRfspIsSet() const
{
    return m_UsedRfspIsSet;
}
void UeContext::unsetUsedRfsp()
{
    m_UsedRfspIsSet = false;
}
Ambr UeContext::getSubUeAmbr() const
{
    return m_SubUeAmbr;
}
void UeContext::setSubUeAmbr(Ambr const& value)
{
    m_SubUeAmbr = value;
    m_SubUeAmbrIsSet = true;
}
bool UeContext::subUeAmbrIsSet() const
{
    return m_SubUeAmbrIsSet;
}
void UeContext::unsetSubUeAmbr()
{
    m_SubUeAmbrIsSet = false;
}
SmsSupport UeContext::getSmsSupport() const
{
    return m_SmsSupport;
}
void UeContext::setSmsSupport(SmsSupport const& value)
{
    m_SmsSupport = value;
    m_SmsSupportIsSet = true;
}
bool UeContext::smsSupportIsSet() const
{
    return m_SmsSupportIsSet;
}
void UeContext::unsetSmsSupport()
{
    m_SmsSupportIsSet = false;
}
std::string UeContext::getSmsfId() const
{
    return m_SmsfId;
}
void UeContext::setSmsfId(std::string const& value)
{
    m_SmsfId = value;
    m_SmsfIdIsSet = true;
}
bool UeContext::smsfIdIsSet() const
{
    return m_SmsfIdIsSet;
}
void UeContext::unsetSmsfId()
{
    m_SmsfIdIsSet = false;
}
SeafData UeContext::getSeafData() const
{
    return m_SeafData;
}
void UeContext::setSeafData(SeafData const& value)
{
    m_SeafData = value;
    m_SeafDataIsSet = true;
}
bool UeContext::seafDataIsSet() const
{
    return m_SeafDataIsSet;
}
void UeContext::unsetSeafData()
{
    m_SeafDataIsSet = false;
}
std::string UeContext::get5gMmCapability() const
{
    return m__5gMmCapability;
}
void UeContext::set5gMmCapability(std::string const& value)
{
    m__5gMmCapability = value;
    m__5gMmCapabilityIsSet = true;
}
bool UeContext::_5gMmCapabilityIsSet() const
{
    return m__5gMmCapabilityIsSet;
}
void UeContext::unset_5gMmCapability()
{
    m__5gMmCapabilityIsSet = false;
}
std::string UeContext::getPcfId() const
{
    return m_PcfId;
}
void UeContext::setPcfId(std::string const& value)
{
    m_PcfId = value;
    m_PcfIdIsSet = true;
}
bool UeContext::pcfIdIsSet() const
{
    return m_PcfIdIsSet;
}
void UeContext::unsetPcfId()
{
    m_PcfIdIsSet = false;
}
std::string UeContext::getPcfAmPolicyUri() const
{
    return m_PcfAmPolicyUri;
}
void UeContext::setPcfAmPolicyUri(std::string const& value)
{
    m_PcfAmPolicyUri = value;
    m_PcfAmPolicyUriIsSet = true;
}
bool UeContext::pcfAmPolicyUriIsSet() const
{
    return m_PcfAmPolicyUriIsSet;
}
void UeContext::unsetPcfAmPolicyUri()
{
    m_PcfAmPolicyUriIsSet = false;
}
std::vector<PolicyReqTrigger>& UeContext::getAmPolicyReqTriggerList()
{
    return m_AmPolicyReqTriggerList;
}
bool UeContext::amPolicyReqTriggerListIsSet() const
{
    return m_AmPolicyReqTriggerListIsSet;
}
void UeContext::unsetAmPolicyReqTriggerList()
{
    m_AmPolicyReqTriggerListIsSet = false;
}
std::string UeContext::getPcfUePolicyUri() const
{
    return m_PcfUePolicyUri;
}
void UeContext::setPcfUePolicyUri(std::string const& value)
{
    m_PcfUePolicyUri = value;
    m_PcfUePolicyUriIsSet = true;
}
bool UeContext::pcfUePolicyUriIsSet() const
{
    return m_PcfUePolicyUriIsSet;
}
void UeContext::unsetPcfUePolicyUri()
{
    m_PcfUePolicyUriIsSet = false;
}
std::vector<PolicyReqTrigger>& UeContext::getUePolicyReqTriggerList()
{
    return m_UePolicyReqTriggerList;
}
bool UeContext::uePolicyReqTriggerListIsSet() const
{
    return m_UePolicyReqTriggerListIsSet;
}
void UeContext::unsetUePolicyReqTriggerList()
{
    m_UePolicyReqTriggerListIsSet = false;
}
std::string UeContext::getHpcfId() const
{
    return m_HpcfId;
}
void UeContext::setHpcfId(std::string const& value)
{
    m_HpcfId = value;
    m_HpcfIdIsSet = true;
}
bool UeContext::hpcfIdIsSet() const
{
    return m_HpcfIdIsSet;
}
void UeContext::unsetHpcfId()
{
    m_HpcfIdIsSet = false;
}
std::vector<RatType>& UeContext::getRestrictedRatList()
{
    return m_RestrictedRatList;
}
bool UeContext::restrictedRatListIsSet() const
{
    return m_RestrictedRatListIsSet;
}
void UeContext::unsetRestrictedRatList()
{
    m_RestrictedRatListIsSet = false;
}
std::vector<Area>& UeContext::getForbiddenAreaList()
{
    return m_ForbiddenAreaList;
}
bool UeContext::forbiddenAreaListIsSet() const
{
    return m_ForbiddenAreaListIsSet;
}
void UeContext::unsetForbiddenAreaList()
{
    m_ForbiddenAreaListIsSet = false;
}
ServiceAreaRestriction UeContext::getServiceAreaRestriction() const
{
    return m_ServiceAreaRestriction;
}
void UeContext::setServiceAreaRestriction(ServiceAreaRestriction const& value)
{
    m_ServiceAreaRestriction = value;
    m_ServiceAreaRestrictionIsSet = true;
}
bool UeContext::serviceAreaRestrictionIsSet() const
{
    return m_ServiceAreaRestrictionIsSet;
}
void UeContext::unsetServiceAreaRestriction()
{
    m_ServiceAreaRestrictionIsSet = false;
}
std::vector<CoreNetworkType>& UeContext::getRestrictedCoreNwTypeList()
{
    return m_RestrictedCoreNwTypeList;
}
bool UeContext::restrictedCoreNwTypeListIsSet() const
{
    return m_RestrictedCoreNwTypeListIsSet;
}
void UeContext::unsetRestrictedCoreNwTypeList()
{
    m_RestrictedCoreNwTypeListIsSet = false;
}
std::vector<AmfEventSubscription>& UeContext::getEventSubscriptionList()
{
    return m_EventSubscriptionList;
}
bool UeContext::eventSubscriptionListIsSet() const
{
    return m_EventSubscriptionListIsSet;
}
void UeContext::unsetEventSubscriptionList()
{
    m_EventSubscriptionListIsSet = false;
}
std::vector<MmContext>& UeContext::getMmContextList()
{
    return m_MmContextList;
}
bool UeContext::mmContextListIsSet() const
{
    return m_MmContextListIsSet;
}
void UeContext::unsetMmContextList()
{
    m_MmContextListIsSet = false;
}
std::vector<PduSessionContext>& UeContext::getSessionContextList()
{
    return m_SessionContextList;
}
bool UeContext::sessionContextListIsSet() const
{
    return m_SessionContextListIsSet;
}
void UeContext::unsetSessionContextList()
{
    m_SessionContextListIsSet = false;
}
TraceData UeContext::getTraceData() const
{
    return m_TraceData;
}
void UeContext::setTraceData(TraceData const& value)
{
    m_TraceData = value;
    m_TraceDataIsSet = true;
}
bool UeContext::traceDataIsSet() const
{
    return m_TraceDataIsSet;
}
void UeContext::unsetTraceData()
{
    m_TraceDataIsSet = false;
}
int32_t UeContext::getRemainingServiceGapTimer() const
{
    return m_RemainingServiceGapTimer;
}
void UeContext::setRemainingServiceGapTimer(int32_t const value)
{
    m_RemainingServiceGapTimer = value;
    m_RemainingServiceGapTimerIsSet = true;
}
bool UeContext::remainingServiceGapTimerIsSet() const
{
    return m_RemainingServiceGapTimerIsSet;
}
void UeContext::unsetRemainingServiceGapTimer()
{
    m_RemainingServiceGapTimerIsSet = false;
}

}
}
}

