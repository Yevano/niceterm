#include <cstdio>
#include <string>
#include <utility>
#include <tuple>
#include <type_traits>

using namespace std;

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;

struct console {
    
};

template<typename... arg_types>
string formatv(string const& fstr, arg_types... args) {
    string result;
    size_t arg_index = 0;
    string converted[] = { to_string(args)... };
    
    for(char const& c : fstr) {
        if(c == '%') {
            result += converted[arg_index++];
        } else {
            result += c;
        }
    }

    return move(result);
}

template<typename... arg_type>
void printv(string const& fstr, arg_type... args) {
    string str = formatv(fstr, args...);
    auto cstr = str.c_str();
    puts(cstr);
}

string set_color(uint32_t r, uint32_t g, uint32_t b) {
    return move(formatv("\x1b[48;2;%;%;%m", r, g, b));
}

string reset() {
    return move("\x1b[0m");
}

void new_line() {
    printf("\n");
}

string test_square(auto length) {
    string out;
    int w = (float) length * 8 / 21;
    
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < length; j++) {
            int r = (float) i / w * 255;
            int g = 0;
            int b = (float) j / length * 255;
            out += set_color(r, g, b);
            out += " ";
            out += reset();
        }

        out += "\n";
    }

    return move(out);
}

int main() {
    string out;
    out += test_square(100);
    
    auto s = out.c_str();
    puts(s);
    return 0;
}
