#ifndef __PARSER_H__
#define __PARSER_H__

#include "Node.h"
#include "Document.h"

namespace tinyXMLpp {

  class Document;

  class Parser {

    public:
      Parser(){};

      bool isEmptyText (const std::string& input);

      bool isInvalidText (const std::string& input);

      std::unique_ptr<Document> parse(const std::string& filePath);

      std::unique_ptr<Document> parse(std::istream& is);
  };
}

#endif
