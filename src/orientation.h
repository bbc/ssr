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
/// %Orientation class and helper function(s) (definition).

#ifndef SSR_ORIENTATION_H
#define SSR_ORIENTATION_H

#include <iosfwd>

class Position; // forward declaration

/** Geometric representation of a orientation.
 * For now, only azimuth value is handled.
 **/
struct Orientation
{
  // the default orientation is in negative y-direction (facing the listener)
  explicit Orientation(const float azimuth = 0.f, const float elevation = 0.f);

  float azimuth; ///< (=yaw) azimuth (in degrees)
  float elevation; ///< (=pitch) elevation (in degrees)

  friend Orientation operator-(const Orientation& lhs, const Orientation& rhs);
  friend Orientation operator+(const Orientation& lhs, const Orientation& rhs);

  Orientation& operator+=(const Orientation& other);
  Orientation& operator-=(const Orientation& other);

  Position look_vector() const;

  /// turn
  Orientation& rotate(float yaw, float pitch = 0.f);
  Orientation& rotate(const Orientation& rotation);

  friend std::ostream& operator<<(std::ostream& stream,
      const Orientation& orientation);

  /** division (/) operator.
   * @param a dividend, a DirectionalPoint.
   * @param b divisor, any numeric Type..
   * @return quotient.
   **/
  template <typename T>
  friend Orientation operator/(const Orientation& a, const T& b)
  {
    return Orientation(a.azimuth / b, a.elevation / b);
  }
};

/// Angle (in radians) between two orientations.
float angle(const Orientation& a, const Orientation& b);

#endif

// Settings for Vim (http://www.vim.org/), please do not remove:
// vim:softtabstop=2:shiftwidth=2:expandtab:textwidth=80:cindent
// vim:fdm=expr:foldexpr=getline(v\:lnum)=~'/\\*\\*'&&getline(v\:lnum)!~'\\*\\*/'?'a1'\:getline(v\:lnum)=~'\\*\\*/'&&getline(v\:lnum)!~'/\\*\\*'?'s1'\:'='
