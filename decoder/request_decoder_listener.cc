#include "tiny-alpaca-server/decoder/request_decoder_listener.h"

#include "tiny-alpaca-server/common/logging.h"
#include "tiny-alpaca-server/common/string_view.h"
#include "tiny-alpaca-server/decoder/constants.h"

namespace alpaca {

RequestDecoderListener::~RequestDecoderListener() {}

EDecodeStatus RequestDecoderListener::OnExtraParameter(
    EParameter param, const StringView& value) {
  DVLOG(1) << "OnExtraParameter(" << param << ", " << value.ToHexEscapedString()
           << ")";
  return EDecodeStatus::kContinueDecoding;
}

EDecodeStatus RequestDecoderListener::OnExtraHeader(EHttpHeader header,
                                                    const StringView& value) {
  DVLOG(1) << "OnExtraHeader(" << header << ", " << value.ToHexEscapedString()
           << ")";
  return EDecodeStatus::kContinueDecoding;
}

EDecodeStatus RequestDecoderListener::OnUnknownParameterName(
    const StringView& name) {
  DVLOG(1) << "OnUnknownParameterName(" << name.ToHexEscapedString() << ")";
  return EDecodeStatus::kContinueDecoding;
}

EDecodeStatus RequestDecoderListener::OnUnknownParameterValue(
    const StringView& value) {
  DVLOG(1) << "OnUnknownParameterValue(" << value.ToHexEscapedString() << ")";
  return EDecodeStatus::kContinueDecoding;
}

EDecodeStatus RequestDecoderListener::OnUnknownHeaderName(
    const StringView& name) {
  DVLOG(1) << "OnUnknownHeaderName(" << name.ToHexEscapedString() << ")";
  return EDecodeStatus::kContinueDecoding;
}

EDecodeStatus RequestDecoderListener::OnUnknownHeaderValue(
    const StringView& value) {
  DVLOG(1) << "OnUnknownHeaderValue(" << value.ToHexEscapedString() << ")";
  return EDecodeStatus::kContinueDecoding;
}

}  // namespace alpaca
