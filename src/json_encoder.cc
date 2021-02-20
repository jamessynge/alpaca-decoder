#include "json_encoder.h"

#include "host_printable.h"
#include "string_view.h"

namespace alpaca {
namespace internal {

void PrintBoolean(Print& out, const bool value) {
  if (value) {
    PrintStringLiteral(out, "true");
  } else {
    PrintStringLiteral(out, "false");
  }
}

}  // namespace internal

JsonArrayEncoder AbstractJsonEncoder::MakeChildArrayEncoder() {
  return JsonArrayEncoder(out_, this);
}

JsonObjectEncoder AbstractJsonEncoder::MakeChildObjectEncoder() {
  return JsonObjectEncoder(out_, this);
}

JsonArrayEncoder JsonObjectEncoder::StartArrayProperty(const StringView& name) {
  StartProperty(name);
  return MakeChildArrayEncoder();
}

JsonObjectEncoder JsonObjectEncoder::StartObjectProperty(
    const StringView& name) {
  StartProperty(name);
  return MakeChildObjectEncoder();
}

JsonArrayEncoder JsonArrayEncoder::StartArrayElement() {
  StartItem();
  return MakeChildArrayEncoder();
}

JsonObjectEncoder JsonArrayEncoder::StartObjectElement() {
  StartItem();
  return MakeChildObjectEncoder();
}

}  // namespace alpaca
