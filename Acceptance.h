#ifndef __ACCEPTANCE_H__
#define __ACCEPTANCE_H__

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "XMLTokenizer.h"
#include <iostream>
#include <cassert>


namespace tinyXMLtest{

  bool accept_streams(std::istream& is1, std::istream& is2)
  {	 
    using namespace tinyXMLpp;

    XMLTokenizer t1(is1), t2(is2);
    TokenType t_type;
    while(true){

      assert((t_type = t1.getToken()) == t2.getToken() ) ;			

      switch(t_type)
      {
	case START_TAG:
	  assert(t1.getTagName() == t2.getTagName());
	  assert(t1.getAttributeCount() == t2.getAttributeCount());
	  for(int i =0; i< t1.getAttributeCount(); ++i){
	    assert(t1.getAttributeName(i) == t1.getAttributeName(i));
	    assert(t1.getAttributeValue(i) == t2.getAttributeValue(i));
	  }
	  break;

	case COMMENT:
	  assert(t1.getComment() == t2.getComment());
	  break;

	case CDATA:
	  assert(t1.getCDATA() == t2.getCDATA());					
	  break;

	case END_TAG:
	  assert(t1.getTagName() == t2.getTagName());
	  break;

	case TEXT:
	  assert(t1.getText() == t2.getText());
	  break;

	case ENDOFFILE:					
	  return true;

      }

    }

  }

  bool accept_files(const std::string& s1, const std::string& s2)
  {
    std::ifstream ifs1(s1.c_str());
    std::ifstream ifs2(s2.c_str());
    accept_streams(ifs1,ifs2);
    return true;
  }
}

#endif
