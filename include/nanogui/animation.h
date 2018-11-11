#pragma once

#include <nanogui/object.h>

#include <chrono>
#include <iostream>

NAMESPACE_BEGIN(nanogui)

class Widget;

class NANOGUI_EXPORT Animation {
public:
  Animation(double start, double end, float duration)
  : mStart(start)
  , mEnd(end)
  , mDuration(duration)
  , mBegin(std::chrono::steady_clock::now())
  {
  }

  Animation(const Animation& a)
  : mStart(a.mStart)
  , mEnd(a.mEnd)
  , mDuration(a.mDuration)
  , mBegin(a.mBegin)
  {
  }

  inline bool finished() const {
    return t() >= 1.0f;
  }

  // t goes from 0 to 1 over the course of the animation
  inline float t() const {
    auto now = std::chrono::steady_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now - mBegin);
    float passed = ((float)millis.count()) / 1000.0f;
    return passed / mDuration;
  }

  inline float curve(float value) const {
    return 1 - (1 - value) * (1 - value);
  }

  inline double currentValue() const {
    auto tValue = t();
    if (tValue >= 1) {
      return mEnd;
    }

    return (mEnd - mStart) * curve(tValue) + mStart;
  }

  virtual void apply(Widget *target);

protected:
  const double mStart, mEnd;
  const float mDuration;
  const std::chrono::steady_clock::time_point mBegin;
};

NAMESPACE_END(nanogui)
