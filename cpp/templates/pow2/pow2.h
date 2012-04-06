#ifndef STH_TMATHPOWER_H
#define STH_TMATHPOWER_H
#include<stdexcept>


/**
  @author Steven T. Hatton
 */
template <size_t Exponent_S, typename T>
class PowerOf
{
  public:
    static T eval(const T& base)
    {
      return base * PowerOf<Exponent_S - 1, T>::eval(base);
    }
};

template <typename T>
class PowerOf<1, T>
{
  public:
    static T eval(const T& base)
    {
      return base;
    }
};

template <typename T>
class PowerOf<0, T>
{
  public:
    static T eval(const T& base)
    {
      if(!base)
      {
        throw std::logic_error(
            "sth::tmath::PowerOf<0>(0) is an indeterminate form.");
      }
      return 1;
    }
};

  template <size_t Exponent_S, typename T>
T power(const T& base)
{
  return PowerOf<Exponent_S, T>::eval(base);
}

#endif
