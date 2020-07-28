
#include "IndividualPDUSessionHSMFApi.h"
#include "IndividualSMContextApi.h"
#include "PDUSessionsCollectionApi.h"
#include "SMContextsCollectionApi.h"
#include "ApiConfiguration.h"
#include "ApiClient.h"
#include "nlohmann/json.hpp"

#include "logger.hpp"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#define DEFAULT_JSON_FILE  "/home/oai/oai-5g-amf/src/sbi/smf_client/inputs/SmContextCreateData.json"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams                            // JSON library
using namespace oai::smf::api;
using namespace oai::smf::model;
//using json = nlohmann::json;


int smf_client_test();
