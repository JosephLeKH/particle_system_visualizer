#include "Color.h"
#include "error.h"
#include "gcanvas.h"
#include "TextUtils.h"
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

/* Random color. */
MiniGUI::Color MiniGUI::Color::RANDOM() {
    return MiniGUI::Color(randomInteger(0, 255),
                          randomInteger(0, 255),
                          randomInteger(0, 255));
}

/* To HTML string. */
std::string MiniGUI::Color::toHTML() const {
    ostringstream builder;
    builder << setfill('0') << hex << '#'
            << setw(2) << GCanvas::getRed(color)
            << setw(2) << GCanvas::getGreen(color)
            << setw(2) << GCanvas::getBlue(color);
    return builder.str();
}

/* Stream insertion. */
ostream& MiniGUI::operator<< (ostream& out, const MiniGUI::Color& color) {
    /* Is it a named color? */
    if (color == MiniGUI::Color::BLACK()) {
        return out << "Color::BLACK()";
    } else if (color == MiniGUI::Color::BLUE()) {
        return out << "Color::BLUE()";
    } else if (color == MiniGUI::Color::CYAN()) {
        return out << "Color::CYAN()";
    } else if (color == MiniGUI::Color::GRAY()) {
        return out << "Color::GRAY()";
    } else if (color == MiniGUI::Color::GREEN()) {
        return out << "Color::GREEN()";
    } else if (color == MiniGUI::Color::MAGENTA()) {
        return out << "Color::MAGENTA()";
    } else if (color == MiniGUI::Color::RED()) {
        return out << "Color::RED()";
    } else if (color == MiniGUI::Color::WHITE()) {
        return out << "Color::WHITE()";
    } else if (color == MiniGUI::Color::YELLOW()) {
        return out << "Color::YELLOW()";
    }

    return out << color.toHTML();
}

bool MiniGUI::operator== (const MiniGUI::Color& lhs, const MiniGUI::Color& rhs) {
    return lhs.toRGB() == rhs.toRGB();
}
bool MiniGUI::operator!= (const MiniGUI::Color& lhs, const MiniGUI::Color& rhs) {
    return !(lhs == rhs);
}
bool MiniGUI::operator<  (const MiniGUI::Color& lhs, const MiniGUI::Color& rhs) {
    return lhs.toRGB() < rhs.toRGB();
}
