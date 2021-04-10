#include "alpaca_devices.h"

#include "alpaca_response.h"
#include "ascom_error_codes.h"
#include "json_response.h"
#include "literals.h"
#include "utils/any_printable.h"
#include "utils/array_view.h"
#include "utils/json_encoder.h"
#include "utils/logging.h"
#include "utils/platform_ethernet.h"
#include "utils/string_view.h"

namespace alpaca {

AlpacaDevices::AlpacaDevices(ArrayView<DeviceInterface::ConstPtr> devices)
    : devices_(devices) {}

bool AlpacaDevices::Initialize() {
  for (DeviceInterface::ConstPtr handler : devices_) {
    handler->Initialize();
  }
  return true;
}

void AlpacaDevices::MaintainDevices() {
  // Give devices a chance to perform work.
  for (DeviceInterface::ConstPtr handler : devices_) {
    handler->Update();
  }
}

bool AlpacaDevices::HandleManagementConfiguredDevices(AlpacaRequest& request,
                                                      Print& out) {
  TAS_VLOG(3) << TASLIT("HandleManagementConfiguredDevices");
  ConfiguredDevicesResponse response(request, devices_);
  return WriteResponse::OkResponse(request, response, out);
}

bool AlpacaDevices::DispatchDeviceRequest(AlpacaRequest& request, Print& out) {
  TAS_VLOG(3) << TASLIT("AlpacaDevices::OnRequestDecoded: device_type=")
              << request.device_type << TASLIT(", device_number=")
              << request.device_number;
  TAS_DCHECK(request.api == EAlpacaApi::kDeviceApi ||
             request.api == EAlpacaApi::kDeviceSetup);

  for (DeviceInterface::ConstPtr handler : devices_) {
    if (request.device_type == handler->device_type() &&
        request.device_number == handler->device_number()) {
      return DispatchDeviceRequest(request, *handler, out);
    }
  }
  TAS_VLOG(3) << TASLIT("Found no Device API Handler");

  return WriteResponse::AscomErrorResponse(request, ErrorCodes::kInvalidValue,
                                           TASLIT("Unknown device"), out);
}

bool AlpacaDevices::DispatchDeviceRequest(AlpacaRequest& request,
                                          DeviceInterface& handler,
                                          Print& out) {
  if (request.api == EAlpacaApi::kDeviceApi) {
    TAS_VLOG(3) << TASLIT("DispatchDeviceRequest: device_method=")
                << request.device_method;
    return handler.HandleDeviceApiRequest(request, out);
  } else if (request.api == EAlpacaApi::kDeviceSetup) {
    return handler.HandleDeviceApiRequest(request, out);
  } else {
    return WriteResponse::HttpErrorResponse(
        EHttpStatusCode::kHttpInternalServerError,
        Literals::HttpMethodNotImplemented(), out);
  }
}

}  // namespace alpaca