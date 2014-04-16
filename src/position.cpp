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
/// %Position class and helper functions (implementation).

#include <cmath> // for atan2(), sqrt()
#include <ostream>

#include "position.h"
#include "orientation.h"
#include "apf/math.h"

Position::Position(const float x, const float y, const float z) :
  x(x),
  y(y),
  z(z)
{}

Position Position::operator-()
{
  return Position(-this->x, -this->y, -this->z);
}

Position& Position::operator+=(const Position& other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Position& Position::operator-=(const Position& other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

bool Position::operator==(const Position& other) const
{
  return x == other.x && y == other.y && z == other.z;
}

bool Position::operator!=(const Position& other) const
{
  return !this->operator==(other);
}

/** convert the orientation given by the position vector (x,y,z) to an
 * Orientation.
 * @return Orientation with the corresponding azimuth value
 **/
Orientation Position::orientation() const
{
  return Orientation(apf::math::rad2deg(atan2(y, x)), apf::math::rad2deg(atan2(z,sqrt(apf::math::square(x) + apf::math::square(y)))));
}

float Position::length() const
{
  return sqrt(apf::math::square(x) + apf::math::square(y) + apf::math::square(z));
}

/** ._
 * @param yaw yaw rotation angle in degrees.
 * @param pitch pitch rotation angle in degrees.
 * @return the resulting position
 **/
Position& Position::rotate(float yaw, float pitch)
{
  // angles phi and theta in radians!
  float phi = apf::math::deg2rad(this->orientation().azimuth + yaw);
  float theta = apf::math::deg2rad(this->orientation().elevation + pitch);
  float radius = this->length();
  return *this = Position(radius * cos(theta) * cos(phi), radius * cos(theta) * sin(phi));
}

Position& Position::rotate(const Orientation& rotation)
{
  return this->rotate(rotation.azimuth, rotation.elevation);
}

Position operator-(const Position& a, const Position& b)
{
  Position temp(a);
  return temp -= b;
}

Position operator+(const Position& a, const Position& b)
{
  Position temp(a);
  return temp += b;
}

/** _.
 * @param point
 * @param orientation
 * @return Angle in radians.
 **/
float angle(const Position& point, const Orientation& orientation)
{
  return angle(point, orientation.look_vector());
}

/** _.
 * @param a
 * @param b
 * @return Angle in radians.
 **/
float angle(const Position& a, const Position& b)
{
  float inner_product = a.x * b.x + a.y * b.y + a.z * b.z;
  return acos(inner_product / (a.length() * b.length()));
}

std::ostream& operator<<(std::ostream& stream, const Position& position)
{
  stream << "x = " << position.x << ", y = " << position.y << ", z = " << position.z;
  return stream;
}

// Settings for Vim (http://www.vim.org/), please do not remove:
// vim:softtabstop=2:shiftwidth=2:expandtab:textwidth=80:cindent
// vim:fdm=expr:foldexpr=getline(v\:lnum)=~'/\\*\\*'&&getline(v\:lnum)!~'\\*\\*/'?'a1'\:getline(v\:lnum)=~'\\*\\*/'&&getline(v\:lnum)!~'/\\*\\*'?'s1'\:'='
