// -*- C++ -*-
// $Id: qdp_traits.h,v 1.3 2003-07-31 01:07:11 edwards Exp $

/*! @file
 * @brief Traits classes
 * 
 * Traits classes needed internally
 */

QDP_BEGIN_NAMESPACE(QDP);


//-----------------------------------------------------------------------------
// Traits class for returning the subset-ted class name of a outer grid class
//-----------------------------------------------------------------------------

template<class T, class S>
struct QDPSubTypeTrait {};

//-----------------------------------------------------------------------------
// Traits classes to support operations of simple scalars (floating constants, 
// etc.) on QDPTypes
//-----------------------------------------------------------------------------

//! Find the underlying word type of a field
template<class T>
struct WordType
{
  typedef T  Type_t;
};


//-----------------------------------------------------------------------------
// Constructors for simple word types
//-----------------------------------------------------------------------------

//! Construct simple word type. Default behavior is empty
template<class T>
struct SimpleScalar {};


//! Construct simple word type used at some level within primitives
template<class T>
struct InternalScalar {};


//! Construct simple word type used at some level within primitives
template<class T>
struct RealScalar {};


//! Construct primitive type of input but always RScalar complex type
template<class T>
struct NoComplex {};


//! Simple zero tag
struct Zero {};

//! Put zero in some unnamed space
namespace {
Zero zero;
}

QDP_END_NAMESPACE();

