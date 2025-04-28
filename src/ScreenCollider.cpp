#include "ScreenCollider.hpp"

namespace ge {
// Constructor
ScreenCollider::ScreenCollider(const vector2 &_minPos, const vector2 &_maxPos) {
  minPos = _minPos;
  maxPos = _maxPos;
  isEnabled = true;
  isClean = false;

  bIsHovering = false;
}

// Destructor
ScreenCollider::~ScreenCollider() {
  if (!isClean)
    cleanUp();
}

void ScreenCollider::cleanUp() {}

// Mouse events
void ScreenCollider::onMouseDown(int key) {
  for (auto it = onMouseDownCallbacks.begin(); it != onMouseDownCallbacks.end();
       ++it) {
    (*it)(key);
  }
}
void ScreenCollider::onMouseUp(int key) {
  for (auto it = onMouseUpCallbacks.begin(); it != onMouseUpCallbacks.end();
       ++it) {
    (*it)(key);
  }
}
void ScreenCollider::onMouseHover() {
  if (!bIsHovering) {
    bIsHovering = true;
    for (auto it = onMouseHoverEnterCallbacks.begin();
         it != onMouseHoverEnterCallbacks.end(); ++it) {
      (*it)();
    }
  }
}
void ScreenCollider::resetHover() {
  if (bIsHovering) {
    bIsHovering = false;
    for (auto it = onMouseHoverExitCallbacks.begin();
         it != onMouseHoverExitCallbacks.end(); ++it) {
      (*it)();
    }
  }
}

// Adding and removing callbacks
void ScreenCollider::addMouseDownCallback(std::function<void(int)> callback) {
  for (auto it = onMouseDownCallbacks.begin(); it != onMouseDownCallbacks.end();
       ++it) {
    if (it->target<void(int)>() == callback.target<void(int)>()) {
      return;
    }
  }
  onMouseDownCallbacks.push_back(callback);
}
void ScreenCollider::removeMouseDownCallback(
    std::function<void(int)> callback) {
  for (auto it = onMouseDownCallbacks.begin(); it != onMouseDownCallbacks.end();
       ++it) {
    if (it->target<void(int)>() == callback.target<void(int)>()) {
      onMouseDownCallbacks.erase(it);
      break;
    }
  }
}

void ScreenCollider::addMouseUpCallback(std::function<void(int)> callback) {
  for (auto it = onMouseUpCallbacks.begin(); it != onMouseUpCallbacks.end();
       ++it) {
    if (it->target<void(int)>() == callback.target<void(int)>()) {
      return;
    }
  }
  onMouseUpCallbacks.push_back(callback);
}
void ScreenCollider::removeMouseUpCallback(std::function<void(int)> callback) {
  for (auto it = onMouseUpCallbacks.begin(); it != onMouseUpCallbacks.end();
       ++it) {
    if (it->target<void(int)>() == callback.target<void(int)>()) {
      onMouseUpCallbacks.erase(it);
      break;
    }
  }
}

void ScreenCollider::addMouseHoverEnterCallback(
    std::function<void()> callback) {
  for (auto it = onMouseHoverEnterCallbacks.begin();
       it != onMouseHoverEnterCallbacks.end(); ++it) {
    if (it->target<void()>() == callback.target<void()>()) {
      return;
    }
  }
  onMouseHoverEnterCallbacks.push_back(callback);
}
void ScreenCollider::removeMouseHoverEnterCallback(
    std::function<void()> callback) {
  for (auto it = onMouseHoverEnterCallbacks.begin();
       it != onMouseHoverEnterCallbacks.end(); ++it) {
    if (it->target<void()>() == callback.target<void()>()) {
      onMouseHoverEnterCallbacks.erase(it);
      break;
    }
  }
}

void ScreenCollider::addMouseHoverExitCallback(std::function<void()> callback) {
  for (auto it = onMouseHoverExitCallbacks.begin();
       it != onMouseHoverExitCallbacks.end(); ++it) {
    if (it->target<void()>() == callback.target<void()>()) {
      return;
    }
  }
  onMouseHoverExitCallbacks.push_back(callback);
}
void ScreenCollider::removeMouseHoverExitCallback(
    std::function<void()> callback) {
  for (auto it = onMouseHoverExitCallbacks.begin();
       it != onMouseHoverExitCallbacks.end(); ++it) {
    if (it->target<void()>() == callback.target<void()>()) {
      onMouseHoverExitCallbacks.erase(it);
      break;
    }
  }
}

// check bounds
bool ScreenCollider::isWithinBounds(const vector2 &pos) {
  return pos.x >= minPos.x && pos.y >= minPos.y && pos.x < maxPos.x &&
         pos.y < maxPos.y;
}

std::pair<vector2, vector2> ScreenCollider::getBounds() {
  return std::make_pair(minPos, maxPos);
}

} // namespace ge
