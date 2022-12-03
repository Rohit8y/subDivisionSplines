#ifndef SETTINGS_H
#define SETTINGS_H

#include "shadertypes.h"

/**
 * Struct that contains all the settings of the program. Initialised with a
 * number of default values.
 */
typedef struct Settings {
  bool showNet = true;
  bool showSubdivisionCurve = false;
  bool showCombCurve = false;
  bool showTessellation = false;
  bool showInfluence = false;

  int selectedPoint = -1;
  int selectedPointSub = -1;
  float no_Isolines = -1.0;
  float no_Split = -1.0;

  ShaderType currentShader = ShaderType::FLAT;
  ShaderType geometryShader = ShaderType::GEOMETRY;
  ShaderType tessellationShader = ShaderType::TESSELLATION;
  ShaderType advanceShader = ShaderType::ADVANCE;




} Settings;

#endif  // SETTINGS_H
