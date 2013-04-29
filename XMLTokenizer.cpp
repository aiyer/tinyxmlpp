#include "XMLTokenizer.h"
#include "XMLException.h"

namespace tinyXMLpp{

  /**
   * Function which peeks the next character from the input stream without removing it.
   *
   *@return The next character from the input stream.
   */
  int XMLTokenizer::peekChar()
  {
    return inputStream.good()?inputStream.peek():-1;
  }


  /**
   * Function which removes 'space' and 'newline' characters from the stream.
   *	
   */
  void XMLTokenizer::skipUnimpChars()
  {
    int c;
    while( ( (c = inputStream.get()) == '\n' || c == ' ' || c == '\t' ) && inputStream.good() );

    pushBack(c);		
  }

  /**
   * Function which reads the next character from the input stream and removes it from the stream.
   *
   *@param specifies whether to skip whitespace characters while reading the next character.
   *@return The next character from the input stream.
   */
  int XMLTokenizer::readChar(bool skipWS)
  {
    if(skipWS){			
      skipUnimpChars();
    }

    return inputStream.good()?inputStream.get():-1;
  }

  /**
   * Function which returns the comment text
   *
   *@return The comment Text
   */
  std::string XMLTokenizer::getComment()
  {
    return this->text;
  }

  /**
   * Function which returns the tag name of the element
   *
   *@return The tag name of the XML element
   */
  std::string XMLTokenizer::getTagName()
  {
    return this->tagName;
  }

  /**
   * Function which returns the XML text
   *
   *@return The XML text
   */
  std::string XMLTokenizer::getText()
  {
    return this->text;
  }

  /**
   * Function which returns the XML CDATA
   *
   *@return The XML CDATA
   */
  std::string XMLTokenizer::getCDATA()
  {
    return this->text;
  }

  /**
   * Function which returns the Attribute Value for the given attribute name
   *
   *@param The attribute name whose value is returned
   *@return The attribute value whose name was given
   */
  std::string XMLTokenizer::getAttributeValue(const std::string& attrName)
  {

    for(int i=0; i < this->attrVals.size() ; ++i){
      if(attrNames[i] == attrName){
	return attrVals[i];
	break;
      }
    }

    return nullptr;
  }

  /**
   * Function which returns the Attribute Name for the given attribute index
   *
   *@param The attribute index whose name is returned
   *@return The attribute name whose index was given
   */
  std::string XMLTokenizer::getAttributeName(int idx)
  {
    return (attrNames.size() > idx) ? attrNames[idx]:nullptr;
  }

  /**
   * Function which returns the Attribute Value for the given attribute index
   *
   *@param The attribute index whose value is returned
   *@return The attribute value whose index was given
   */
  std::string XMLTokenizer::getAttributeValue(int idx)
  {
    return (attrVals.size() > idx) ? attrVals[idx]:nullptr;
  }


  /**
   * Function which resets the state() (member variables).
   * This function should be called before processing a new state.
   *	
   */
  void XMLTokenizer::reset()
  {
    this->hasEndTag = false;
    this->text = "";
    this->attrNames.clear();
    this->attrVals.clear();		
  }

  /**
   * Function which returns the Attribute count for the current XML tag.
   *	
   *@return The number of attributes.
   */
  int XMLTokenizer::getAttributeCount()
  {
    return attrNames.size();
  }

  /**
   * Function which parses XML Text from the input stream. Modifies the current state appropriately.	
   *	
   */
  void XMLTokenizer::parseText()
  {
    reset();

    /*read all chars till '<' or EOF*/
    int c;
    while( ((c = peekChar()) != -1) && c != '<' ){
      if(c == '<' || c== '&')
	throw XMLException("Invalid Characters found in XML " + c);
      this->text += (char)c;
      readChar(false);
    }

    if(c == -1 && this->text.length() == 0)
      this->tokenType = ENDOFFILE;
    else
      this->tokenType = TEXT;
  }

  /**
   * Function which parses the attributes from the input stream. Modifies the current state appropriately.
   *	
   *@return Value indicating whether the current XML tag has a closing tag in itself.
   */
  bool XMLTokenizer::parseAttributes()
  {

    int c;
    std::string attrName;
    std::string attrValue;

    while(true){

      attrName = "";
      attrValue = "";

      /*eat whitespace characters before attrName*/
      c = readChar(true);				

      /*check for end of tag*/
      if(c == '>')
	return false;
      else if( c == '/' && readChar(false) == '>')
	return true;
      else if( !isalnum(c) ) 
	throw XMLException("Non alpha-numeric characters found in attribute name" + attrName);

      while( isalnum(c) ){						
	attrName += c;
	c = readChar(false);
      }			

      if(attrName.length() == 0)
	throw XMLException("Attribute name missing for tag" + this->tagName);

      /*eat whitespace*/
      if( c != '='){				
	c = readChar(true);
      }

      if(c == '='){

	/*eat whitespace before attrValue*/
	c = readChar(true);

	if( c != '"' && c != '\'') 
	  throw XMLException("Unexpected character found while looking for attribute value for " + attrName);
	while(  ( c = readChar(false) ) != '\'' && c != '"' ){
	  attrValue += c;
	}

      }else
	throw XMLException("Expected '=' after" + attrName +".But found illegal character");

      this->attrNames.push_back(attrName);
      this->attrVals.push_back(attrValue);

    }

  }


  /**
   * Function which parses the XML Start Tag. Modifies the current state appropriately.
   *			
   */
  void XMLTokenizer::parseStartTag()
  {	
    reset();

    /*TODO: check for invalid chars at the start of the state*/	
    int c = readChar(false);	
    if(c == -1){
      this->tokenType = ENDOFFILE;
      return;
    }

    if(c != '<') 
      throw XMLException("Unexpected character while parsing start tag.");

    this->tagName = "";
    while(	(c = peekChar() ) != ' ' && 
	c != '\t' &&
	c != '>'  && 
	c != '/'  &&
	c != -1   &&
	c != '\n'
	){
      if(isalnum(c))
	this->tagName += c;
      else
	throw XMLException("Non alpha-numeric characters found in the tagname:" + this->tagName);

      readChar(false);
    }

    if(this->tagName.length() == 0)
      throw XMLException("Tag name missing while parsing");
    else if(c == -1)
      throw XMLException("Unexpected EOF while parsing start tag " + this->tagName + ".");

    /*skip unimportant characters after the tag name*/
    c = readChar(true);

    if(c == '>'){
      this->tokenType = START_TAG;
    }else if(c == '/'){
      if((c = readChar(false)) == '>'){
	this->hasEndTag = true;
	this->tokenType = START_TAG;
      }else
	throw XMLException("Tag" + this->tagName + "has invalid characters");
    }else{		
      pushBack(c);
      this->hasEndTag = parseAttributes();
      this->tokenType = START_TAG;
    }

  }

  /**
   * Function which pushes back a character to the input stream.
   *		
   * @param The character which has to be pushed back.
   */
  void XMLTokenizer::pushBack(int c)
  {
    inputStream.putback(c);
  }

  /**
   * Function which parses the XML end tag. Modifies the current state appropriately.
   *			
   */
  void XMLTokenizer::parseEndTag()
  {	
    reset();

    int c = readChar(false);	
    if(c == -1){
      this->tokenType = ENDOFFILE;
      return;
    }

    if(c != '<' || (c=readChar(false) != '/')) 
      throw XMLException("XML malformed. Invalid characters while parsing the end tag");

    this->tagName = "";
    while(true){

      c = readChar(false);
      if(isalnum(c))				
	this->tagName += c;			
      else if (c == '>')
	break;
      else{
	c = readChar(true);
	if(c == '>') 
	  break;
	else
	  throw XMLException("XML malformed. Tag " + this->tagName + "not closed");
      }
    }

    this->tokenType = END_TAG;
  }

  /**
   * Function which tries to match a string pattern , from the input stream. Throws no exception.
   *
   *@param The pattern to be matched.
   *@return Value indicating whether pattern was matched or not.
   */
  bool XMLTokenizer::tryMatch(const std::string& str)
  {			
    bool flag = true;		
    int i = 0;
    int c;
    for(; i< str.length(); ++i){
      if( (c = readChar(false)) != str[i]){

	if(c == -1)
	  break;

	pushBack(c);
	flag = false;
	break;
      }
    }

    if(c == -1){
      //this->tokenType = ENDOFFILE;
      flag = false;
      //	throw XMLException("Unexpected EOF while reading from input stream.");
    }

    if(!flag){
      --i;
      for(;i>=0;--i)
	pushBack(str[i]);
    }

    return flag;
  }

  /**
   * Function which parses the XML CDATA. Modifies the current state appropriately.
   *			
   */
  void XMLTokenizer::parseCDATA()
  {
    reset();

    /*read until ]]>*/
    int c;
    while( (c = peekChar()) != -1)
    {
      if(tryMatch("]]>")){
	break;
      }

      this->text += c;
      readChar(false);
    }


    if( c != -1)
      this->tokenType = CDATA;
    else
      throw XMLException("Unexpected EOF while parsing CDATA " + this->text);
  }

  /**
   * Function which parses the XML COMMENT. Modifies the current state appropriately.
   *			
   */
  void XMLTokenizer::parseComment()
  {
    reset();

    /*read until -->*/
    int c;
    while( (c = peekChar()) != -1)
    {
      if(tryMatch("--")){
	if(peekChar() == '>'){
	  //this->text += c;
	  readChar(false);
	  break;
	}else
	  throw XMLException(" '--' found in XML Comment ");
      }

      this->text += c;
      readChar(false);
    }

    if( c != -1)
      this->tokenType = COMMENT;
    else
      throw XMLException("Unexpected EOF while parsing comment " + this->text);
  }

  /**
   * Function which returns the next token type from the input stream. Simulates a state machine.
   * The value of the token is exposed through the various member functions.
   */
  TokenType XMLTokenizer::getToken() 
  {
    /*Comment can be 'next state' of any state*/
    if(tryMatch("<!--"))
    {
      parseComment();
      return this->tokenType;
    }

    /*switch on the current state (token type)*/
    switch(this->tokenType)
    {

      /*To Ignore whitespaces at the top of the document*/
      case BOF:			
	parseText();	
	break;

	/*Next token  = tag */
      case TEXT:								
	if( readChar(false) == '<' && peekChar() == '/' ){
	  pushBack('<');
	  parseEndTag();
	}else{
	  pushBack('<');
	  if(tryMatch("<![CDATA["))
	    parseCDATA();
	  else				
	    //Parses tag name and its attributes.
	    parseStartTag();					

	}
	break;

      case START_TAG:							
	//Next Token = END_TAG or TEXT
	if(this->hasEndTag){								
	  this->hasEndTag = false;
	  this->tokenType = END_TAG;
	}else{	

	  /*Parse CDATA or Text*/
	  if(tryMatch("<![CDATA["))
	    parseCDATA();
	  else
	    parseText();								
	}
	break;

      case END_TAG:				
	//Next Token = TEXT
	parseText();
	break;

      case COMMENT:		
      case CDATA:					
	//Next Token = TEXT or CDATA or start tag or end tag
	if(tryMatch("<![CDATA["))
	  parseCDATA();
	else if( tryMatch("</") ){
	  pushBack('/');
	  pushBack('<');
	  parseEndTag();
	}else if( peekChar() == '<' )
	  parseStartTag();			
	else 
	  parseText();	

	break;

      case ENDOFFILE:				
	//Do Nothing.
	break;

      default:	
	throw XMLException("Unrecognized token(s) in the XML");

    }

    /*return the token type.*/
    return this->tokenType;
  }

}
