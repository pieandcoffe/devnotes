//
// Created by Kyrylo Pylinskyi on 10/08/2026.
//

#ifndef ASSIGNMENT_01_GUARD_HPP
#define ASSIGNMENT_01_GUARD_HPP

template<typename T>
struct ArrayGuard {
    T* data;
    ~ArrayGuard() { delete[] data; }
};

#endif //ASSIGNMENT_01_GUARD_HPP
