// -*- C++ -*-
// $Id: qdp_xmlio.h,v 1.16 2003-07-06 19:04:26 edwards Exp $

/*! @file
 * @brief XML IO support
 */

#include <string>
#include <sstream>
#include <stack>

#include "xml_simplewriter.h"
#include "basic_xpath_reader.h"

QDP_BEGIN_NAMESPACE(QDP);

// Forward declarations
class XMLReader;
class XMLWriter;
class XMLBufferWriter;
class XMLFileWriter;
class XMLArrayWriter;


/*! @addtogroup io
 *
 * XML File input and output operations on QDP types
 *
 * @{
 */

//--------------------------------------------------------------------------------
//! XML reader class
class XMLReader : protected XMLXPathReader::BasicXPathReader
{
public:
  //! Empty constructor
  XMLReader();

  //! Construct from contents of file
  XMLReader(const std::string& filename);

  //! Construct from contents of stream
  XMLReader(std::istream& is);

  //! Construct from contents of a XMLBufferWriter
  XMLReader(const XMLBufferWriter& mw);

  ~XMLReader();

  /* The meaning of these should be clear to you */
  void open(const std::string& filename);
  void open(std::istream& is);
  void open(const XMLBufferWriter& mw);
  bool is_open();
  void close();
    
  /* So should these, there is just a lot of overloading */
  void get(const std::string& xpath, std::string& result);
  void get(const std::string& xpath, int& result);
  void get(const std::string& xpath, unsigned int& result);
  void get(const std::string& xpath, short int& result);
  void get(const std::string& xpath, unsigned short int& result);
  void get(const std::string& xpath, long int& result);
  void get(const std::string& xpath, unsigned long int& result);
  void get(const std::string& xpath, float& result);
  void get(const std::string& xpath, double& result);
  void get(const std::string& xpath, bool& result);

  //! Return the entire contents of the Reader as a stream
  void print(ostream& is);
        
  //! Return the root element of the Reader as a stream
  void printRoot(ostream& is);
        
  //! Count the number of occurances from the xpath query
  int count(const std::string& xpath);

protected:
  // The universal data-reader. All the read functions call this
  template<typename T>
  void
  readPrimitive(const std::string& xpath, T& output);

private:
  bool  iop;  //file open or closed?
};


// Time to build a telephone book of basic primitives
void read(XMLReader& xml, const std::string& s, std::string& input);
void read(XMLReader& xml, const std::string& s, int& input);
void read(XMLReader& xml, const std::string& s, unsigned int& input);
void read(XMLReader& xml, const std::string& s, short int& input);
void read(XMLReader& xml, const std::string& s, unsigned short int& input);
void read(XMLReader& xml, const std::string& s, long int& input);
void read(XMLReader& xml, const std::string& s, unsigned long int& input);
void read(XMLReader& xml, const std::string& s, float& input);
void read(XMLReader& xml, const std::string& s, double& input);
void read(XMLReader& xml, const std::string& s, bool& input);


//! Read a XML multi1d element
template<class T>
inline
void read(XMLReader& xml, const std::string& s, multi1d<T>& input)
{
  std::ostringstream error_message;
  std::string elemName = "elem";
  
  // Count the number of elements
  std::string elem_base_query = s + "/" + elemName;
	
  int array_size;
  try {
    array_size = xml.count(elem_base_query);
  }
  catch( const std::string& e) { 
    error_message << "Exception occurred while counting " << elem_base_query 
		  << " during array read " << endl;
  }
      
  // Now resize the array to hold the no of elements.
  input.resize(array_size);

  // Get the elements one by one
  for(int i=0; i < input.size(); i++) 
  {
    std::ostringstream element_xpath;

    // Create the query for the element 
    element_xpath << elem_base_query << "[" << (i+1) << "]";

    // recursively try and read the element.
    try 
    {
      read(xml, element_xpath.str(), input[i]);
    } 
    catch (const std::string& e) 
    {
      error_message << "Failed to match element " << i
		    << " of array with query " << element_xpath.str()
		    << endl
		    << "Query returned error: " << e;
      throw error_message.str();
    }
  }
}


// Specialized versions for basic types
void read(XMLReader& xml, const std::string& s, multi1d<int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<unsigned int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<short int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<unsigned short int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<long int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<unsigned long int>& input);
void read(XMLReader& xml, const std::string& s, multi1d<float>& input);
void read(XMLReader& xml, const std::string& s, multi1d<double>& input);
void read(XMLReader& xml, const std::string& s, multi1d<bool>& input);


#define ReadPath(xml,path,a) read(xml,path+"/"+#a,a)


//--------------------------------------------------------------------------------
//! Metadata output class
class XMLWriter : protected XMLWriterAPI::XMLSimpleWriter
{
public:
  XMLWriter();
  ~XMLWriter();

  virtual void openSimple(const std::string& tagname);
  virtual void closeSimple();

  virtual void openStruct(const std::string& tagname);
  virtual void closeStruct();

  void openTag(const std::string& tagname);
  void openTag(const std::string& nsprefix, const std::string& tagname);
  void openTag(const std::string& tagname, XMLWriterAPI::AttributeList& al);

  void openTag(const std::string& nsprefix,
	       const std::string& tagname, 
	       XMLWriterAPI::AttributeList& al);

  void closeTag();

  void emptyTag(const std::string& tagname);
  void emptyTag(const std::string& nsprefix, const std::string& tagname);
  void emptyTag(const std::string& tagname, XMLWriterAPI::AttributeList& al);

  void emptyTag(const std::string& nsprefix,
		const std::string& tagname, 
		XMLWriterAPI::AttributeList& al);
    

  // Overloaded Writer Functions
  void write(const std::string& output);
  void write(const int& output);
  void write(const unsigned int& output);
  void write(const short int& output);
  void write(const unsigned short int& output);
  void write(const long int& output);
  void write(const unsigned long int& output);
  void write(const float& output);
  void write(const double& output);
  void write(const bool& output);

  // Write XML std::string
  void writeXML(const std::string& output);

  friend class XMLArrayWriter;
};


//! Push a group name
void push(XMLWriter& xml, const std::string& s);

//! Pop a group name
void pop(XMLWriter& xml);

//! Write something from a reader
void write(XMLWriter& xml, const std::string& s, const XMLReader& d);
XMLWriter& operator<<(XMLWriter& xml, const XMLReader& d);

//! Write something from a XMLBufferWriter
void write(XMLWriter& xml, const std::string& s, const XMLBufferWriter& d);
XMLWriter& operator<<(XMLWriter& xml, const XMLBufferWriter& d);

// Time to build a telephone book of basic primitives
void write(XMLWriter& xml, const std::string& s, const std::string& output);
void write(XMLWriter& xml, const std::string& s, const char* output);
void write(XMLWriter& xml, const std::string& s, const char& output);
void write(XMLWriter& xml, const std::string& s, const int& output);
void write(XMLWriter& xml, const std::string& s, const unsigned int& output);
void write(XMLWriter& xml, const std::string& s, const short int& output);
void write(XMLWriter& xml, const std::string& s, const unsigned short int& output);
void write(XMLWriter& xml, const std::string& s, const long int& output);
void write(XMLWriter& xml, const std::string& s, const unsigned long int& output);
void write(XMLWriter& xml, const std::string& s, const float& output);
void write(XMLWriter& xml, const std::string& s, const double& output);
void write(XMLWriter& xml, const std::string& s, const bool& output);

// Versions that do not print a name
XMLWriter& operator<<(XMLWriter& xml, const std::string& output);
XMLWriter& operator<<(XMLWriter& xml, const char* output);
XMLWriter& operator<<(XMLWriter& xml, const char& output);
XMLWriter& operator<<(XMLWriter& xml, const int& output);
XMLWriter& operator<<(XMLWriter& xml, const unsigned int& output);
XMLWriter& operator<<(XMLWriter& xml, const short int& output);
XMLWriter& operator<<(XMLWriter& xml, const unsigned short int& output);
XMLWriter& operator<<(XMLWriter& xml, const long int& output);
XMLWriter& operator<<(XMLWriter& xml, const unsigned long int& output);
XMLWriter& operator<<(XMLWriter& xml, const float& output);
XMLWriter& operator<<(XMLWriter& xml, const double& output);
XMLWriter& operator<<(XMLWriter& xml, const bool& output);

//! Write a XML multi1d element
template<class T>
inline
void write(XMLWriter& xml, const std::string& s, const multi1d<T>& s1)
{
  // Write the array name
  xml.openTag(s);

#if 0
  // This stuff is for schemas
  XMLWriterAPI::AttributeList alist;
  alist.push_back(XMLWriterAPI::Attribute("minOccurs", s1.size()));
  alist.push_back(XMLWriterAPI::Attribute("maxOccurs", s1.size()));
      
  xml.openTag("complexType");
  xml.openTag("sequence", alist);
#endif

  for(unsigned index=0; index < s1.size(); index++) 
  {
    write(xml, "elem", s1[index]);  // Possibly grab user defines here
  }

#if 0
  // This stuff is for schemas
  xml.closeTag(); // sequence
  xml.closeTag(); // complexType
#endif
  xml.closeTag(); // Array name
}


// Writers for arrays of basic types
void write(XMLWriter& xml, const std::string& s, const multi1d<int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<unsigned int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<short int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<unsigned short int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<long int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<unsigned long int>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<float>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<double>& output);
void write(XMLWriter& xml, const std::string& s, const multi1d<bool>& output);


//! XML OScalar output
template<class T>
inline
void write(XMLWriter& xml, const std::string& s, const OScalar<T>& d)
{
  xml.openTag(s);
  xml << d;
  xml.closeTag();
}

//! XML OLattice output
template<class T>
inline
void write(XMLWriter& xml, const std::string& s, const OLattice<T>& d)
{
  xml.openTag(s);
  xml << d;
  xml.closeTag();
}


#if 0
// NEED TO FIX THIS
//! Write a XML multi2d element
template<class T> 
inline
void write(XMLWriter& xml, const std::string& s, const multi2d<T>& s1)
{
  for(int j=0; j < s1.size1(); ++j)
    for(int i=0; i < s1.size2(); ++i)
    {
      std::ostringstream ost;
      if (Layout::primaryNode()) 
	ost << s << "[ " << i << " ][ " << j << " ]";
      write(xml, ost.str(), s1[i][j]);
    }
}

#endif



//--------------------------------------------------------------------------------
//! Write metadata to a buffer
class XMLBufferWriter : public XMLWriter
{
public:
  //! Constructor
  /*! No prologue written */
  XMLBufferWriter();
  
  //! Destructor
  ~XMLBufferWriter();

  // Return entire stream as a string
  std::string str();
        
  // Return root element as a string
  std::string printRoot();
        
private:
  // The output stream...
  ostringstream output_stream;

  // The function that supplies the stream to the parent...
  ostream& getOstream(void) {return output_stream;}
};


//--------------------------------------------------------------------------------
//! Write data to a file
class XMLFileWriter : public XMLWriter
{
public:
  //! Empty constructor
  XMLFileWriter();

  //! Constructor from a filename
  explicit XMLFileWriter(const std::string& filename, bool write_prologue=true)
    {
      open(filename, write_prologue);
    }

  //! Destructor
  ~XMLFileWriter();

  bool is_open();
  void open(const std::string& filename, bool write_prologue=true)
    {
      if (Layout::primaryNode())
      {
	output_stream.open(filename.c_str(), ofstream::out);
	if (write_prologue)
	  writePrologue(output_stream);
      }

      indent_level=0;
    }

  //! Flush the buffer
  void flush();

  //! Return true if some failure occurred in previous IO operation
  bool fail();

  //! Close the file
  void close();
        
private:
  QDPUtil::RemoteOutputFileStream output_stream;
//  ofstream output_stream;
  ostream& getOstream(void) {return output_stream;}
};



//--------------------------------------------------------------------------------
//! Write metadata to an array which serves as a handle for another XML object
class XMLArrayWriter : public XMLWriter
{
public:
  //! Constructor
  /*! No prologue written
   * @param xml_out  previous XMLWriter object - used for handle source
   * @param size     size of array - default unbounded
   */
  explicit XMLArrayWriter(XMLWriter& xml_out, int size = -1) : 
    output_xml(xml_out), array_size(size)
    {
      initP = arrayTag = false;
      elements_written = 0;
      indent_level = xml_out.indent_level;
      simpleElements = false; // do not know this yet
    }
  
  //! Destructor
  ~XMLArrayWriter();

  //! Flush the buffer
//  void flush();

  //! Close the array writer
  /*! It is an error to close before all data is written, unless unbounded */
  void close();
       
  //! Size of array
  int size() const {return array_size;}

  void openArray(const std::string& tagname);
  void closeArray();

//  virtual void openSimple(const std::string& tagname);
//  virtual void closeSimple();

  void openStruct(const std::string& tagname);
  void closeStruct();

private:
  std::string qname;
  std::string elem_qname;

  bool arrayTag;         // set once array tag is written
  bool initP;            // set once we know how the array is composed
  bool simpleElements;   // true if elements will all be simple types
  int array_size;        // total array element size
  int elements_written;  // elements written so far

  // A stack to hold context.
  enum ElementType {SIMPLE, STRUCT};
  std::stack<ElementType> contextStack;

  // output stream is actually the original stream
  XMLWriter& output_xml;
  ostream& getOstream(void) {return output_xml.getOstream();}
};

//! Push a group name
void push(XMLArrayWriter& xml);

//! Pop a group name
void pop(XMLArrayWriter& xml);


/*! @} */   // end of group io
QDP_END_NAMESPACE();
