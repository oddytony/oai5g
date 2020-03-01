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
/*
 * N2InformationTransferReqData.h
 *
 * 
 */

#ifndef N2InformationTransferReqData_H_
#define N2InformationTransferReqData_H_


#include "Ecgi.h"
#include "Ncgi.h"
#include "Tai.h"
#include <string>
#include "N2InfoContainer.h"
#include "RatSelector.h"
#include "GlobalRanNodeId.h"
#include <vector>
#include <nlohmann/json.hpp>

namespace oai {
namespace amf {
namespace model {

/// <summary>
/// 
/// </summary>
class  N2InformationTransferReqData
{
public:
    N2InformationTransferReqData();
    virtual ~N2InformationTransferReqData();

    void validate();

    /////////////////////////////////////////////
    /// N2InformationTransferReqData members

    /// <summary>
    /// 
    /// </summary>
    std::vector<Tai>& getTaiList();
    bool taiListIsSet() const;
    void unsetTaiList();
    /// <summary>
    /// 
    /// </summary>
    RatSelector getRatSelector() const;
    void setRatSelector(RatSelector const& value);
    bool ratSelectorIsSet() const;
    void unsetRatSelector();
    /// <summary>
    /// 
    /// </summary>
    std::vector<Ecgi>& getEcgiList();
    bool ecgiListIsSet() const;
    void unsetEcgiList();
    /// <summary>
    /// 
    /// </summary>
    std::vector<Ncgi>& getNcgiList();
    bool ncgiListIsSet() const;
    void unsetNcgiList();
    /// <summary>
    /// 
    /// </summary>
    std::vector<GlobalRanNodeId>& getGlobalRanNodeList();
    bool globalRanNodeListIsSet() const;
    void unsetGlobalRanNodeList();
    /// <summary>
    /// 
    /// </summary>
    N2InfoContainer getN2Information() const;
    void setN2Information(N2InfoContainer const& value);
        /// <summary>
    /// 
    /// </summary>
    std::string getSupportedFeatures() const;
    void setSupportedFeatures(std::string const& value);
    bool supportedFeaturesIsSet() const;
    void unsetSupportedFeatures();

    friend void to_json(nlohmann::json& j, const N2InformationTransferReqData& o);
    friend void from_json(const nlohmann::json& j, N2InformationTransferReqData& o);
protected:
    std::vector<Tai> m_TaiList;
    bool m_TaiListIsSet;
    RatSelector m_RatSelector;
    bool m_RatSelectorIsSet;
    std::vector<Ecgi> m_EcgiList;
    bool m_EcgiListIsSet;
    std::vector<Ncgi> m_NcgiList;
    bool m_NcgiListIsSet;
    std::vector<GlobalRanNodeId> m_GlobalRanNodeList;
    bool m_GlobalRanNodeListIsSet;
    N2InfoContainer m_N2Information;

    std::string m_SupportedFeatures;
    bool m_SupportedFeaturesIsSet;
};

}
}
}

#endif /* N2InformationTransferReqData_H_ */
