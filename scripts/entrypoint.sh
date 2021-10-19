#!/bin/bash

set -euo pipefail

CONFIG_DIR="/openair-amf/etc"

# Default values
EXTERNAL_AUSF=${EXTERNAL_AUSF:-no}
EXTERNAL_UDM=${EXTERNAL_UDM:-no}
NRF_SELECTION=${NRF_SELECTION:-no}
NSSF_IPV4_ADDRESS=${NSSF_IPV4_ADDRESS:-0.0.0.0}
NSSF_PORT=${NSSF_PORT:-80}
NSSF_API_VERSION=${NSSF_API_VERSION:-v2}
NSSF_FQDN=${NSSF_FQDN:-oai-nssf}

if [[ ${USE_FQDN_DNS} == "yes" ]];then
    NSSF_IPV4_ADDR=${NSSF_IPV4_ADDR_0:-0.0.0.0}
    SMF_IPV4_ADDR_0=${SMF_IPV4_ADDR_0:-0.0.0.0}
    SMF_IPV4_ADDR_1=${SMF_IPV4_ADDR_1:-0.0.0.0}
    NRF_IPV4_ADDRESS=${NRF_IPV4_ADDRESS:-0.0.0.0}
    AUSF_IPV4_ADDRESS=${AUSF_IPV4_ADDRESS:-0.0.0.0}
fi

for c in ${CONFIG_DIR}/*.conf; do
    # grep variable names (format: ${VAR}) from template to be rendered
    VARS=$(grep -oP '@[a-zA-Z0-9_]+@' ${c} | sort | uniq | xargs)
    echo "Now setting these variables '${VARS}'"

    # create sed expressions for substituting each occurrence of ${VAR}
    # with the value of the environment variable "VAR"
    EXPRESSIONS=""
    for v in ${VARS}; do
        NEW_VAR=`echo $v | sed -e "s#@##g"`
        if [[ -z ${!NEW_VAR+x} ]]; then
            echo "Error: Environment variable '${NEW_VAR}' is not set." \
                "Config file '$(basename $c)' requires all of $VARS."
            exit 1
        fi
        EXPRESSIONS="${EXPRESSIONS};s|${v}|${!NEW_VAR}|g"
    done
    EXPRESSIONS="${EXPRESSIONS#';'}"

    # render template and inline replace config file
    sed -i "${EXPRESSIONS}" ${c}
done
echo "Done setting the configuration"
exec "$@"
