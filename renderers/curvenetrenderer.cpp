#include "curvenetrenderer.h"

/**
 * @brief CurveNetRenderer::~CurveNetRenderer Destructor of the control curve
 * net renderer.
 */
CurveNetRenderer::~CurveNetRenderer() {
  gl->glDeleteVertexArrays(1, &vao);
  gl->glDeleteBuffers(1, &vbo);
}

/**
 * @brief CurveNetRenderer::initShaders Initialises the different shaders used
 * in the control curve net renderer. The control net only supports
 * the flat shader.
 */
void CurveNetRenderer::initShaders() {
  shaders.insert(ShaderType::FLAT, constructDefaultShader("flat"));
}

/**
 * @brief CurveNetRenderer::initBuffers Initialises the buffers
 */
void CurveNetRenderer::initBuffers() {
  // Pure OpenGL functions used here

  // create vao
  gl->glGenVertexArrays(1, &vao);
  // bind vao
  gl->glBindVertexArray(vao);
  // generate single buffer object
  gl->glGenBuffers(1, &vbo);
  // bind it
  gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // enable vertex attribute array with index 0 in the currently bound vao
  gl->glEnableVertexAttribArray(0);
  // tell the currently bound vao what the layout is of the vbo
  gl->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  // unbind
  gl->glBindVertexArray(0);
}

/**
 * @brief CurveNetRenderer::updateBuffers Updates the contents of the buffers.
 * @param sc The subdivision curve containing the information to update the
 * buffer(s) with.
 */
void CurveNetRenderer::updateBuffers(SubdivisionCurve& sc) {
  QVector<QVector2D> netCoords = sc.getNetCoords();

  vboSize = netCoords.size();
  gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
  gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vboSize,
                   netCoords.data(), GL_DYNAMIC_DRAW);
}

/**
 * @brief CurveNetRenderer::draw Draw call. Draws the control net on the screen.
 * Uses the contents of the vertex array buffer for drawing. The size of the
 * draw array is expected to be stored in vboSize.
 */
void CurveNetRenderer::draw() {
  // Always renders the control net using the flat shader.
  shaders[ShaderType::FLAT]->bind();

  gl->glBindVertexArray(vao);

  // Draw control net
  gl->glDrawArrays(GL_LINE_STRIP, 0, vboSize);
  gl->glPointSize(8.0);
  gl->glDrawArrays(GL_POINTS, 0, vboSize);

  // Highlight selected control point
  if (settings->selectedPoint > -1) {
    gl->glPointSize(12.0);
    gl->glDrawArrays(GL_POINTS, settings->selectedPoint, 1);
   // gl->glDrawArrays(GL_LINE_STRIP, settings->selectedPoint, vboSize);

  }

  gl->glBindVertexArray(0);

  shaders[ShaderType::FLAT]->release();
}
