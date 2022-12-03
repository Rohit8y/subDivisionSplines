#ifndef ADVANCERENDERER_H
#define ADVANCERENDERER_H

#include <QOpenGLShaderProgram>

#include "renderer.h"
#include "shadertypes.h"
#include "subdivisioncurve.h"

/**
 * @brief Renderer responsible for rendering the control net.
 */
class AdvanceRenderer : public Renderer {
 public:
  AdvanceRenderer() {}
  ~AdvanceRenderer() override;
  void updateBuffers(SubdivisionCurve& sc);
  void draw();

 protected:
  void initShaders() override;
  void initBuffers() override;

 private:
  GLuint vao, vbo;
  int vboSize;
};


#endif // ADVANCERENDERER_H



