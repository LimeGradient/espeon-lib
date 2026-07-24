#pragma once

namespace espeon::util {
    template <class T>
    class Singleton {
    public:
        static T* get() {
            static T instance;
            return &instance;
        }
    };
}