#pragma once

#include <ostream>
#include <cmath>
#include <algorithm>
#include "error.h"

namespace MiniGUI {
    class Color {
    public:
        /* Defaults to black. */
        constexpr Color() = default;

        /* You can create a color by specifying its red, green, and blue color
         * components. Each value runs from 0 (none of this color) to 255
         * (as much of this color as possible.)
         */
        constexpr Color(int red, int green, int blue) {
            if (red < 0 || green < 0 || blue < 0 || red >= 256 || green >= 256 || blue >= 256) {
                error("Color values out of range.");
            }
            color = (red << 16) + (green << 8) + blue;
        }

        /* How much red, green, and blue are used. */
        constexpr int red() const {
            return (color >> 16) & 0xFF;
        }
        constexpr int green() const {
            return (color >> 8) & 0xFF;
        }
        constexpr int blue() const {
            return color & 0xFF;
        }

        /* A composed color value represented as a 24-bit integer used by the
         * graphics system. If you know what 0xRRGGBB means, great! That's what
         * this does. If not, no worries! You aren't expected to know or use
         * this function.
         */
        constexpr int toRGB() const {
            return color;
        }

        /* Returns an HTML-friendly string representation of the color. */
        std::string toHTML() const;

        /* Helpful preset colors. You can access them as Color::WHITE(),
         * Color::BLACK(), etc.
         */
        static constexpr Color WHITE() {
            return fromHex(0xFFFFFF);
        }
        static constexpr Color BLACK() {
            return fromHex(0x000000);
        }
        static constexpr Color RED() {
            return fromHex(0xFF0000);
        }
        static constexpr Color GREEN() {
            return fromHex(0x00FF00);
        }
        static constexpr Color BLUE() {
            return fromHex(0x0000FF);
        }
        static constexpr Color YELLOW() {
            return fromHex(0xFFFF00);
        }
        static constexpr Color CYAN() {
            return fromHex(0x00FFFF);
        }
        static constexpr Color MAGENTA() {
            return fromHex(0xFF00FF);
        }
        static constexpr Color GRAY() {
            return fromHex(0x808080);
        }

        /* A randomly-chosen color. Call this function as Color::RANDOM(). */
        static Color RANDOM();

        /* Creates a color given its hue, saturation, and value, each of which
         * ranges from 0 to 1, inclusive.
         */
        constexpr static Color fromHSV(double h, double s, double v) {
            if (h < 0 || h > 1 || s < 0 || s > 1 || v < 0 || v > 1) {
                error("Color::fromHSV(): Values out of range.");
            }

            /* From https://en.wikipedia.org/wiki/HSL_and_HSV */
            auto f = [=](int n) {
                double k = std::fmod(n + h * 6, 6);
                return v - v * s * std::max(0.0, std::min({k, 4 - k, 1.0}));
            };

            return Color(255 * f(5), 255 * f(3), 255 * f(1));
        }

        constexpr static Color fromHex(int hexValue) {
            if (hexValue < 0 || hexValue > 0xFFFFFF) {
                error("Color::fromHex(): Value out of range.");
            }

            Color result;
            result.color = hexValue;
            return result;
        }

    private:
        int color = 0;
    };

    /* Utility functions to print / compare colors. */
    std::ostream& operator<< (std::ostream& out, const Color& color);
    bool operator== (const Color& lhs, const Color& rhs);
    bool operator!= (const Color& lhs, const Color& rhs);
    bool operator<  (const Color& lhs, const Color& rhs);
}
