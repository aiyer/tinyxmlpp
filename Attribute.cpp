#include "Attribute.h"

namespace tinyXMLpp {
  /**
   *Sets the 'name' of the name-value pair of an Attribute
   *
   *@param name 'name' in the name-value pair
   */
  void Attribute::setName (std::string name) {
    this->name = name;
  }

  /**
   *Sets the 'value' of the name-value pair of an Attribute
   *
   *@param value 'value' in the name-value pair
   */
  void Attribute::setValue (std::string value) {
    this->value = value;
  }

  /**
   *Gets the 'name' of the name-value pair of an Attribute
   */
  std::string Attribute::getName () {
    return this->name;
  }

  /**
   *Gets the 'value' of the name-value pair of an Attribute
   */
  std::string Attribute::getValue () {
    return this->value;
  }

  /**
   *Constructor that takes in name and value as parameters
   *
   *@param name 'name' in the name-value pair
   *@param value 'value' in the name-value pair
   */
  Attribute::Attribute (const std::string& name, const std::string& value) {
    this->name = name;
    this->value = value;
  }
}
