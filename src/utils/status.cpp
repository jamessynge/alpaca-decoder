#include "utils/status.h"

#include "utils/counting_print.h"
#include "utils/hex_escape.h"
#include "utils/inline_literal.h"
#include "utils/o_print_stream.h"
#include "utils/platform.h"

namespace alpaca {

size_t Status::printTo(Print& out) const {
  CountingPrint counter(out);
  OPrintStream strm(counter);
  if (ok()) {
    strm << FLASHSTR("OK");
  } else {
    strm << FLASHSTR("{.code=}") << code_;
    if (message_.size()) {
      strm << FLASHSTR(", message=\"") << HexEscaped(message_) << '"';
    }
    strm << '}';
  }
  return counter.count();
}

}  // namespace alpaca