#include <nanogui/animation.h>
#include <nanogui/widget.h>

NAMESPACE_BEGIN(nanogui)

void Animation::apply(Widget *target) {
  target->mPosAnimated.y() = currentValue();
}

NAMESPACE_END(nanogui)
