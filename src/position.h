/******************************************************************************
 * Copyright © 2012-2014 Institut für Nachrichtentechnik, Universität Rostock *
 * Copyright © 2006-2012 Quality & Usability Lab,                             *
 *                       Telekom Innovation Laboratories, TU Berlin           *
 * Copyright © 2014 British Broadcasting Corporation                         *
 *                                                                            *
 * This file is part of the SoundScape Renderer (SSR).                        *
 *                                                                            *
 * The SSR is free software:  you can redistribute it and/or modify it  under *
 * the terms of the  GNU  General  Public  License  as published by the  Free *
 * Software Foundation, either version 3 of the License,  or (at your option) *
 * any later version.                                                         *
 *                                                                            *
 * The SSR is distributed in the hope that it will be useful, but WITHOUT ANY *
 * WARRANTY;  without even the implied warranty of MERCHANTABILITY or FITNESS *
 * FOR A PARTICULAR PURPOSE.                                                  *
 * See the GNU General Public License for more details.                       *
 *                                                                            *
 * You should  have received a copy  of the GNU General Public License  along *
 * with this program.  If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                            *
 * The SSR is a tool  for  real-time  spatial audio reproduction  providing a *
 * variety of rendering algorithms.                                           *
 *                                                                            *
 * http://spatialaudio.net/ssr                           ssr@spatialaudio.net *
 ******************************************************************************/

/// @file
/// %Position class and helper functions (definition).

#ifndef SSR_POSITION_H
#define SSR_POSITION_H

#include "orientation.h"

/** Geometric representation of a position.
 * Stores the position of a point in space and provides some helper functions.
 * If you want to speak in design patterns, you could call this a "Messenger"
 * patter. It's the most trivial of all patterns. So maybe it's not even worth
 * mentioning. But I did it anyway ...
 * @warning For now, it only uses 2 dimensions (x,y) but a z coordinate can be 
 * added later, if needed.
 **/
struct Position
{
  /** with no arguments, all member variables are initialized to zero.
   * @param x x coordinate (in meters)
   * @param y y coordinate (in meters)
   **/
  explicit Position(const float x = 0.f, const float y = 0.f, const float z = 0.f);

  float x; ///< x coordinate (in meters)
  float y; ///< y coordinate (in meters)
  float z; ///< z coordinate (in meters)

  /// length of the position vector
  float length() const;

  /// turn around the origin
  Position& rotate(float yaw, float pitch = 0.f);
  Position& rotate(const Orientation& rotation);

  Orientation orientation() const;

  Position operator-();                        ///< unary minus operator
  Position& operator+=(const Position& other); ///< += operator
  Position& operator-=(const Position& other); ///< -= operator
  bool operator==(const Position& other) const;  ///< == operator
  bool operator!=(const Position& other) const;  ///< != operator

  // Declaring the following operators as friend is not really necessary as
  // their fields are public anyway, but it doesn't hurt either.

  /// plus (+) operator
  friend Position operator+(const Position& a, const Position& b);
  /// minus (-) operator
  friend Position operator-(const Position& a, const Position& b);
  /// output stream operator (<<)
  friend std::ostream& operator<<(std::ostream& stream,
      const Position& position);

  /** division (/) operator.
   * @param a dividend, a DirectionalPoint.
   * @param b divisor, any numeric Type..
   * @return quotient.
   **/
  template <typename T>
  friend Position operator/(const Position& a, const T& b)
  {
    return Position(a.x / b, a.y / b, a.z / b);
  }
};

/// Calculate the angle between the position vector of @a point and the
/// orientation @a orientation.
float angle(const Position& point, const Orientation& orientation);
// TODO: declare angle() also as friend of Position?

/// Calculate the angle between the position vector of @a a and the
/// position vector of @a b.
float angle(const Position& a, const Position& b);
// TODO: declare angle() also as friend of Position?

#endif

// Settings for Vim (http://www.vim.org/), please do not remove:
// vim:softtabstop=2:shiftwidth=2:expandtab:textwidth=80:cindent
// vim:fdm=expr:foldexpr=getline(v\:lnum)=~'/\\*\\*'&&getline(v\:lnum)!~'\\*\\*/'?'a1'\:getline(v\:lnum)=~'\\*\\*/'&&getline(v\:lnum)!~'/\\*\\*'?'s1'\:'='
