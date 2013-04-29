#ifndef __XMLEXCEPTION_H__
#define __XMLEXCEPTION_H__

#include <exception>
#include <string>
#include <stdexcept>

namespace tinyXMLpp{

  class XMLException:public std::runtime_error  {

    int lineNumber;
    //std::string message;

    public:
    //virtual const char* what() const throw();
    //XMLException(){};
    XMLException(std::string message):runtime_error(message) {}
    XMLException(std::string message, int lineNumber):runtime_error(message),lineNumber(lineNumber){}

  };

}
#endif
