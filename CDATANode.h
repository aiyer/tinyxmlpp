#ifndef __CDATANODE_H__
#define __CDATANODE_H__

#include "Node.h"
#include <iostream>

namespace tinyXMLpp{

  class CDATANode : public Node {
    std::string cdata;

    CDATANode(const std::string &cdata);

    public:

    static CDATANode* createCDATANode(const std::string& cdata);

    ~CDATANode();

    void addChildNode (Node* child);

    void addChildNode (Node* child, int index);

    void removeChildNode (Node* child);

    void removeChildNode (int index);

    std::string getcdata() const;

    void write(std::ostream& os) const;
  };

}
#endif
