// -*- C++ -*-
// $Id: map.h,v 1.2 2003-01-17 05:42:06 edwards Exp $

/*! @file
 * @brief Map classes
 *
 * Support classes for maps/shifts
 */

QDP_BEGIN_NAMESPACE(QDP);

/*! @defgroup map Maps and shifts
 *
 * Maps are the mechanism for communications. Under a map,
 * a data-parallel object is mapped uniquely from sites to
 * sites. Nearest neighbor shifts are an example of the more
 * generic map.
 *
 * @{
 */

//! MapFunc 
/*! Abstract base class used as a function object for constructing maps */
class MapFunc
{
public:
  //! Maps a lattice coordinate under a map to a new lattice coordinate
  /*! sign > 0 for map, sign < 0 for the inverse map */
  virtual multi1d<int> operator() (const multi1d<int>& coordinate, int sign) const = 0;
};
    
//! ArrayMapFunc 
/*! Abstract base class used as a function object for constructing maps */
class ArrayMapFunc
{
public:
  //! Maps a lattice coordinate under a map to a new lattice coordinate
  /*! sign > 0 for map, sign < 0 for the inverse map */
  virtual multi1d<int> operator() (const multi1d<int>& coordinate, int sign, int dir) const = 0;

  //! Returns the array size - the number of directions which are to be used
  virtual int numArray() const;
};
    
/** @} */ // end of group map

QDP_END_NAMESPACE();
