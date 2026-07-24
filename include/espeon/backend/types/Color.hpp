#pragma once

namespace espeon {
    struct Color {
        int r;
        int g;
        int b;
        int a;

        Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
    };
}