#pragma once

#include "vector2.hpp"
#include <utility>
#include <functional>
#include <vector>

namespace ge {
class ScreenCollider {
public:
  ScreenCollider(const vector2& minPos, const vector2& maxPos);
  ~ScreenCollider();
  void cleanUp();

  void setEnabled(const bool& value);

public:
  void onMouseDown(int key);
  void onMouseUp(int key);
  void onMouseHover();
  void resetHover();

private:
  std::vector<std::function<void(int)>> onMouseDownCallbacks;
  std::vector<std::function<void(int)>> onMouseUpCallbacks;
  std::vector<std::function<void()>> onMouseHoverEnterCallbacks;
  std::vector<std::function<void()>> onMouseHoverExitCallbacks;

public:
  // Mouse Down
  void addMouseDownCallback(std::function<void(int)> callback);
  void removeMouseDownCallback(std::function<void(int)> callback);

  // Mouse Up
  void addMouseUpCallback(std::function<void(int)> callback);
  void removeMouseUpCallback(std::function<void(int)> callback);

  // Mouse hover enter
  void addMouseHoverEnterCallback(std::function<void()> callback);
  void removeMouseHoverEnterCallback(std::function<void()> callback);

  // Mouse hover exit
  void addMouseHoverExitCallback(std::function<void()> callback);
  void removeMouseHoverExitCallback(std::function<void()> callback);
  
public:
  bool isWithinBounds(const vector2& pos);
  std::pair<vector2, vector2> getBounds();
protected:
  vector2 minPos;
  vector2 maxPos;

  bool isEnabled = false;
  bool isClean = false;

private:
  bool bIsHovering = false;
};
} // namespace ge
