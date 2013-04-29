#ifndef __COMMENTNODE_H__
#define __COMMENTNODE_H__

#include "Node.h"
#include <iostream>

namespace tinyXMLpp{

  class CommentNode : public Node {
    std::string content;

    CommentNode();
    CommentNode(const std::string& content);

    public:
    ~CommentNode();

    static CommentNode* createCommentNode();

    static CommentNode* createCommentNode(const std::string& content);

    /*Methods to get and set content*/
    void setContent(const std::string& content);

    std::string getContent() const;

    void addChildNode (Node* child);

    void addChildNode (Node* child, int index);

    void removeChildNode (Node* child);

    void removeChildNode (int index);

    void write(std::ostream& os) const;
  };

}

#endif
