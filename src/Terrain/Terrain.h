#ifndef TERRAIN_H
#define TERRAIN_H

#include "pgl/RenderObject.h"

class Terrain: public RenderObject {
public:
    Terrain();
    void init() override;
    void render(const glm::mat4 &view, const glm::mat4 &projection) override;
    void cleanUp() override;
    void setTexture(GLuint textureId);

private:
    GLuint _vertexArrayId;
    GLuint _vertexBufferId;
    GLuint _elementBufferId;
    GLuint _textureId;
    std::vector<GLfloat> _vertices;
    std::vector<GLuint> _indices;

    struct Triangle {
        double x;
        double y;
        double z;
    };
    struct Point {
        double x;
        double y;
        double indice;
    };

    void constructGrid();
};

#endif