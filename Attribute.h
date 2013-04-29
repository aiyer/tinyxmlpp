#ifndef __ATTRB_H__
#define __ATTRB_H__

#include <string>
#include "Node.h"

namespace tinyXMLpp{

  class Attribute
  {
    std::string name;
    std::string value;
    public:
    Attribute(const std::string& name, const std::string& value);
    std::string getName();
    std::string getValue();
    void setName(std::string);
    void setValue(std::string);
  };

}
#endif
