#include "TextUtils.h"
#include <sstream>
#include <iomanip>
using namespace std;

namespace {
    /* Quotes the given object with the specified escape characters. */
    string quotedVersionOf(const string& str, char quoteChar) {
        ostringstream result;
        result << quoteChar;

        for (char ch: str) {
            /* Escape close quotes. */
            if (ch == '\"') result << "\\\"";
            if (ch == '\'') result << "\\\'";

            /* Escape slashes. */
            else if (ch == '\\') result << "\\\\";

            /* Print out any other printable characters. */
            else if (isgraph(ch) || ch == ' ') result << ch;

            /* Otherwise, escape it. */
            else {
                result << "\\x" << hex << setfill('0') << setw(2) << +static_cast<unsigned char>(ch);
            }
        }

        result << quoteChar;
        return result.str();
    }
}


/* TODO: Once C++14 support is more widespread, replace with std::quoted. */
string quotedVersionOf(const string& source) {
    return quotedVersionOf(source, '"');
}
string quotedVersionOf(char source) {
    return quotedVersionOf(string(1, source), '\'');
}

string readQuotedVersionOf(istream& in) {
    /* Get a character; it must be a quote. */
    if (in.get() != '"') {
        in.setstate(ios::failbit);
        return "";
    }

    string result;

    /* Keep reading until we get to the end. */
    while (true) {
        /* Get the next character. */
        char next;
        if (!in.get(next)) return "";

        /* If it's a close-quote, we're done. */
        if (next == '"') return result;

        /* If it's an escape, see what we're escaping. */
        else if (next == '\\') {
            /* Four options: could be \, ', ", or xHH. */
            char escapeType;
            if (!in.get(escapeType)) return "";

            switch (escapeType) {
                case '\\':
                case '\'':
                case '\"':
                    result += escapeType;
                    break;
                case 'x': {
                    /* Read two hex digits. */
                    char hexDigits[3] = { 0, 0, 0 };
                    for (int i = 0; i < 2; i++) {
                        if (!in.get(hexDigits[i])) return "";
                        if (!isxdigit(hexDigits[i])) {
                            in.setstate(ios::failbit);
                            return "";
                        }
                    }

                    /* We now have a hex string. Decode it. */
                    errno = 0;
                    int value = strtol(hexDigits, nullptr, 16);
                    if (errno != 0) {
                        in.setstate(ios::failbit);
                        return "";
                    }

                    /* Convert that value to a character. */
                    result += value;
                    break;
                }
                default:
                    in.setstate(ios::failbit);
                    return "";
                }
        } else {
            /* Otherwise it's a standard character. */
            result += next;
        }
    }
}

/* Recursive base case. */
string format(const string& pattern) {
    /* If there's a replacement site, something is wrong. */
    if (pattern.find("%s") != string::npos) {
        error("Unmatched pattern string?");
    }
    return pattern;
}
