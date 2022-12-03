#include "advancerenderer.h"

/**
 * @brief AdvanceRenderer::~AdvanceRenderer Destructor of the advance
 * net renderer.
 */
AdvanceRenderer::~AdvanceRenderer() {
  gl->glDeleteVertexArrays(1, &vao);
  gl->glDeleteBuffers(1, &vbo);
}

/**
 * @brief AdvanceRenderer::initShaders Initialises the different shaders used
 * in the advanceCoords renderer. The advance shader only works in combination
 * with the subdivision shader.
 */
void AdvanceRenderer::initShaders() {
  shaders.insert(ShaderType::ADVANCE, constructAdvanceShader("advance"));
}

/**
 * @brief AdvanceRenderer::initBuffers Initialises the buffers
 */
void AdvanceRenderer::initBuffers() {
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
 * @brief AdvanceRenderer::updateBuffers Updates the contents of the buffers.
 * @param sc The subdivision curve containing the information to update the
 * buffer(s) with.
 */
void AdvanceRenderer::updateBuffers(SubdivisionCurve& sc) {
  QVector<QVector2D> advanceCoords = sc.getAdvanceCoords();

  vboSize = advanceCoords.size();
  gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
  gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vboSize,
                   advanceCoords.data(), GL_DYNAMIC_DRAW);
}

/**
 * @brief AdvanceRenderer::draw Draw call. Draws the control net on the screen.
 * Uses the contents of the vertex array buffer for drawing. The size of the
 * draw array is expected to be stored in vboSize.
 */
void AdvanceRenderer::draw() {

  shaders[ShaderType::ADVANCE]->bind();
  gl->glBindVertexArray(vao);
  // Highlight selected control point
  if (settings->selectedPointSub > -1) {
    gl->glDrawArrays(GL_LINE_STRIP, 0, vboSize);
    gl->glPointSize(12.0);
    gl->glDrawArrays(GL_POINTS, 0, vboSize);
  }
  gl->glBindVertexArray(0);
  shaders[ShaderType::ADVANCE]->release();

}
