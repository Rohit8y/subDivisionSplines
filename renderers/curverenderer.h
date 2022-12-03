#ifndef CURVE_RENDERER_H
#define CURVE_RENDERER_H

#include <QOpenGLShaderProgram>

#include "../shadertypes.h"
#include "../subdivisioncurve.h"
#include "renderer.h"

/**
 * @brief Renderer responsible for rendering the curve resulting from the
 * control net.
 */
class CurveRenderer : public Renderer {
 public:
  ~CurveRenderer() override;
  void updateBuffers(SubdivisionCurve& sc);
  void draw();

 protected:
  void initShaders() override;
  void initBuffers() override;

 private:
  GLuint vao, vbo;
  int vboSize;
};

#endif  // CURVE_RENDERER_H
