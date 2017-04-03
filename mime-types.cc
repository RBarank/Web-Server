#include "mime-types.hpp"

namespace mime_types {

  struct mapping
  {
    const char* extension;
    const char* mime_type;
  } mappings[] =
    {
      { "gif", "image/gif" },
      { "htm", "text/html" },
      { "html", "text/html" },
      { "jpg", "image/jpeg" },
      { "png", "image/png" },
      { "md", "text/html" }
    };

  std::string ExtensionToType(const std::string& extension)
  {
    for (const mapping mapping: mappings)
      {
	if (mapping.extension == extension)
	  {
	    return mapping.mime_type;
	  }
      }
    return "text/plain"; // if can't find the extension, return a default text/plain
  }

} // namespace mime_types
