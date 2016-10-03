#ifndef OSMIUM_AREA_DETAIL_VECTOR_HPP
#define OSMIUM_AREA_DETAIL_VECTOR_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013-2016 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <cstdint>
#include <iosfwd>

#include <osmium/osm/location.hpp>
#include <osmium/osm/node_ref.hpp>

namespace osmium {

    namespace area {

        namespace detail {

            /**
             * This helper class models a 2D vector in the mathematical sense.
             * It uses 64 bit integers internally which has enough precision
             * for most operations with inputs based on 32 bit locations.
             */
            struct vec {

                int64_t x;
                int64_t y;

                constexpr vec(int64_t a, int64_t b) noexcept :
                    x(a),
                    y(b) {
                }

                constexpr explicit vec(const osmium::Location& l) noexcept :
                    x(l.x()),
                    y(l.y()) {
                }

                constexpr explicit vec(const osmium::NodeRef& nr) noexcept :
                    x(nr.x()),
                    y(nr.y()) {
                }

            }; // struct vec

            // addition
            constexpr inline vec operator+(const vec& a, const vec& b) noexcept {
                return vec{a.x + b.x, a.y + b.y};
            }

            // subtraction
            constexpr inline vec operator-(const vec& a, const vec& b) noexcept {
                return vec{a.x - b.x, a.y - b.y};
            }

            // cross product
            constexpr inline int64_t operator*(const vec& a, const vec& b) noexcept {
                return a.x * b.y - a.y * b.x;
            }

            // scale vector
            constexpr inline vec operator*(double s, const vec& v) noexcept {
                return vec{int64_t(s * v.x), int64_t(s * v.y)};
            }

            // scale vector
            constexpr inline vec operator*(const vec& v, double s) noexcept {
                return vec{int64_t(s * v.x), int64_t(s * v.y)};
            }

            // equality
            constexpr inline bool operator==(const vec& a, const vec& b) noexcept {
                return a.x == b.x && a.y == b.y;
            }

            // inequality
            constexpr inline bool operator!=(const vec& a, const vec& b) noexcept {
                return !(a == b);
            }

            template <typename TChar, typename TTraits>
            inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const vec& v) {
                return out << '(' << v.x << ',' << v.y << ')';
            }

        } // namespace detail

    } // namespace area

} // namespace osmium

#endif //  OSMIUM_AREA_DETAIL_VECTOR_HPP
