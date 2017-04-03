#ifndef HTTP_MIME_TYPES_HPP
#define HTTP_MIME_TYPES_HPP

#include <string>

namespace mime_types {

  /// Convert a file extension into a MIME type.
  std::string ExtensionToType(const std::string& extension);

} // namespace mime_types

#endif // HTTP_MIME_TYPES_HPP
