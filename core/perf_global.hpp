#pragma once
#include <stdexcept>

namespace perf
{

template <typename T> void ptr_check(T *t)
  {
  if (!t)
    {
    throw std::runtime_error("");
    }
  }

template <typename T> void check(T *t)
  {
  perf_ptr_check(t);

  if (!T::check(t))
    {
    throw std::runtime_error("");
    }
  }

inline void check(bool b)
  {
  if (!b)
    {
    throw std::runtime_error("");
    }
  }

}
