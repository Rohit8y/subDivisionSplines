#include "curverenderer.h"

/**
 * @brief CurveRenderer::~CurveNetRenderer Destructor of the subdivision curve
 * renderer.
 */
CurveRenderer::~CurveRenderer() {
  gl->glDeleteVertexArrays(1, &vao);
  gl->glDeleteBuffers(1, &vbo);
}

/**
 * @brief CurveRenderer::initShaders Initialises the different shaders used
 * in the subdivision curve renderer.
 */
void CurveRenderer::initShaders() {

  // Initialize default shader
  shaders.insert(ShaderType::FLAT, constructDefaultShader("flat"));

  // Initialize geometry shader
  shaders.insert(ShaderType::GEOMETRY, constructGeometryShader("flat"));


  // Initialize tessellation shader
  shaders.insert(ShaderType::TESSELLATION, constructTessellationShader("flat"));

}

/**
 * @brief CurveRenderer::initBuffers Initialises the buffers.
 */
void CurveRenderer::initBuffers() {

    // created vertex array object of size 1
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
 * @brief CurveRenderer::updateBuffers Updates the contents of the buffers.
 * @param sc The subdivision curve containing the information to update the
 * buffer(s) with.
 */
void CurveRenderer::updateBuffers(SubdivisionCurve& curve) {
    // Get curveCoords and update the buffers
    QVector<QVector2D> curveCoords = curve.getCurveCoords();
    if (curveCoords.size()>1)
    vboSize = curveCoords.size();
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vboSize,
                     curveCoords.data(), GL_DYNAMIC_DRAW);
}

/**
 * @brief CurveRenderer::draw Draws the subdivision curve on the screen.
 * Uses the contents of the vertex array buffer for drawing. The size of the
 * draw array is expected to be stored in vboSize.
 */
void CurveRenderer::draw() {

  // Draw subdivision curve
  if (settings->showSubdivisionCurve){

    // Binding the current shader
    shaders[settings->currentShader]->bind();
    gl->glBindVertexArray(vao);
    gl->glDrawArrays(GL_LINE_STRIP, 0, vboSize);
    gl->glPointSize(8.0);
    gl->glDrawArrays(GL_POINTS, 0, vboSize);

    if (settings->selectedPointSub > -1) {
    gl->glPointSize(16.0);
    gl->glDrawArrays(GL_POINTS, settings->selectedPointSub, 1);
    }
    gl->glBindVertexArray(0);
    shaders[settings->currentShader]->release();
   }

  // Draw geometry shader
  if (settings->showCombCurve){

    // Binding geometry shader
    shaders[settings->geometryShader]->bind();
    gl->glBindVertexArray(vao);
    // Add primitive type here GL_LINE_STRIP_ADJACENCY for geometry shader
    gl->glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, vboSize);
    gl->glBindVertexArray(0);
    shaders[settings->geometryShader]->release();
  }

  // Draw Tessellation shader
  if (settings->showTessellation){

      // Binding Tessellation shader
    shaders[settings->tessellationShader]->bind();

    // Setting tessellation level
     int NoLines_location = shaders[settings->tessellationShader]->uniformLocation("noIsolines");
     int NoSplits_location = shaders[settings->tessellationShader]->uniformLocation("noSplit");

     GLfloat a = settings->no_Isolines;
     GLfloat b = settings->no_Split;
     shaders[settings->tessellationShader]->setUniformValue(NoLines_location, a);
     shaders[settings->tessellationShader]->setUniformValue(NoSplits_location, b);

     gl->glBindVertexArray(vao);

    // Set GL_PATCH_VERTICES value to 5 for cubic b-spline, and to 4 for quadratic b-spline.
    gl->glPatchParameteri(GL_PATCH_VERTICES, 4);
    gl->glDrawArrays(GL_PATCHES, 0, vboSize);
    gl->glBindVertexArray(0);
    shaders[settings->tessellationShader]->release();
  }
}
