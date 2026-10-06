#pragma once
#include <iostream>


template <typename... Ts>
void print(Ts const&... args);

#include "print.tpp"