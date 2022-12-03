#include "renderer.h"

/**
 * @brief Renderer::Renderer Creates a new renderer.
 */
Renderer::Renderer() : gl(nullptr) {}

/**
 * @brief Renderer::~Renderer Deconstructs the renderer by deleting all shaders.
 */
Renderer::~Renderer() { qDeleteAll(shaders); }

/**
 * @brief Renderer::init Initialises the renderer with an OpenGL context and
 * settings. Also initialises the shaders and buffers.
 * @param f OpenGL functions pointer.
 * @param s Settings.
 */
void Renderer::init(QOpenGLFunctions_4_1_Core* f, Settings* s) {

  gl = f;
  settings = s;
  initShaders();
  initBuffers();

}

/**
 * @brief Renderer::constructDefaultShader Constructs a shader consisting of a
 * vertex shader and a fragment shader. The shaders are assumed to follow the
 * naming convention: <name>.vert and <name>.frag. Both of these files have to
 * exist for this function to work successfully.
 * @param name Name of the shader.
 * @return The constructed shader.
 */
QOpenGLShaderProgram* Renderer::constructDefaultShader(
    const QString& name) const {

    QString pathVert = ":/shaders/" + name + ".vert";
    QString pathFrag = ":/shaders/" + name + ".frag";

    // we use the qt wrapper functions for shader objects
    QOpenGLShaderProgram* shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, pathVert);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, pathFrag);
    shader->link();

    return shader;
}


/**
 * @brief Renderer::constructGeometryShader Constructs a geometry shader
 * using the name provided in argument The shaders are assumed to follow the
 * naming convention: <name>.vert and <name>.frag. The files have to exist for
 *  this function in the directory to work successfully.
 * @param name Name of the vertex and fragmant shader.
 * @return The geometry shader.
 */
QOpenGLShaderProgram* Renderer::constructGeometryShader(
        const QString& name) const{

    QString pathVert = ":/shaders/" + name + ".vert";
    QString pathFrag = ":/shaders/" + name + ".frag";
    QString geomVert = ":/shaders/curvature.geom";

    // we use the qt wrapper functions for shader objects
    QOpenGLShaderProgram* shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, pathVert);
    shader->addShaderFromSourceFile(QOpenGLShader::Geometry, geomVert);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, pathFrag);
    shader->link();
    return shader;

}


/**
 * @brief Renderer::constructTessellation: Shader Constructs a Tessellation shader.
 *  The shader has a vertex shader, Tessellatoin control shader, Tessellation
 *  evaluation shader and Fragmant shader. The files have to exist for this function
 * in the directory to work successfully.
 * @param name Name of the vertex shader.
 * @return The Tessellation shader.
 */
QOpenGLShaderProgram* Renderer::constructTessellationShader(
        const QString& name) const{

    QString pathVert = ":/shaders/" + name + ".vert";
    QString pathFrag =":/shaders/tess.frag";
    QString pathtcs = ":/shaders/tcs.glsl";
    QString pathtes = ":/shaders/tes.glsl";

    QOpenGLShaderProgram* tessShader = new QOpenGLShaderProgram();
    tessShader->addShaderFromSourceFile(QOpenGLShader::Vertex, pathVert);
    tessShader->addShaderFromSourceFile(QOpenGLShader::TessellationControl, pathtcs);
    tessShader->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, pathtes);
    tessShader->addShaderFromSourceFile(QOpenGLShader::Fragment, pathFrag);
    tessShader->link();

    tessShader->bind();

    return tessShader;

}

/**
 * @brief Renderer::constructAdvanceShader Constructs a shader consisting of a
 * vertex shader and a fragment shader for highlighting the influence of control points.
 * The shaders are assumed to follow the
 * naming convention: <name>.vert and <name>.frag. Both of these files have to
 * exist for this function to work successfully.
 * @param name Name of the shader.
 * @return The constructed shader.
 */
QOpenGLShaderProgram* Renderer::constructAdvanceShader(
    const QString& name) const {

    QString pathVert = ":/shaders/" + name + ".vert";
    QString pathFrag = ":/shaders/" + name + ".frag";

    // we use the qt wrapper functions for shader objects
    QOpenGLShaderProgram* shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, pathVert);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, pathFrag);
    shader->link();

    return shader;
}

