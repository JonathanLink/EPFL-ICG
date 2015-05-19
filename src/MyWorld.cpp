#include "MyWorld.h"
#include "glm/gtc/matrix_transform.hpp"

MyWorld::MyWorld() : terrainReflectFB(800, 600) {
        
}

void MyWorld::init() {
    _skybox.setScene(this);
    _perlin.setScene(this);
    _terrain.setScene(this);
    _water.setScene(this);
    //_fishEye.setScene(this);

    // Draw perlin noise in framebuffer we've just created
    FrameBuffer perlinFrameBuffer = FrameBuffer(512, 512);
    GLuint perlinTextureId = perlinFrameBuffer.initTextureId(GL_R32F); 
    perlinFrameBuffer.bind();
        _perlin.render(view, projection);
    perlinFrameBuffer.unbind();

    _water.setTexturePerlin(perlinTextureId);
    _terrain.setTexture(perlinTextureId);

    // set camera bezier
    std::vector<Hull> cameraHulls;
    cameraHulls.push_back(Hull(glm::vec3(0,23,-1), glm::vec3(0,20,-2), glm::vec3(0,20,-2), glm::vec3(0,20,-2)));

    std::vector<Hull> lookHulls;
    lookHulls.push_back(Hull(glm::vec3(4,22,-1), glm::vec3(0,21,-2), glm::vec3(-5,24,-2), glm::vec3(-9,10,2)));

    CameraBezier cameraBezier;
    cameraBezier.setHulls(cameraHulls, lookHulls);
    setCameraBezier(cameraBezier);
}

int i;
void MyWorld::render() {
    i++;
    //FrameBuffer fishEyeFrameBuffer = FrameBuffer(800, 600);
    //GLuint fishEyeTextureId = fishEyeFrameBuffer.initTextureId(GL_RGB);
    //fishEyeFrameBuffer.bind();
    //    _skybox.render(view, projection);
    //    _terrain.render(view, projection); 
    //fishEyeFrameBuffer.unbind();

    //_fishEye.setTexture(fishEyeTextureId);
    //_fishEye.render(view, projection);

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // wireframe 
    if (i % 2 == 0) {
        //Draw terrain in framebuffer for water reflection
        GLuint terrainReflectTextureId = terrainReflectFB.initTextureId(GL_RGBA);
        terrainReflectFB.bind();
            _terrain.render(glm::scale(view, glm::vec3(1, -1, 1)), projection);
        terrainReflectFB.unbind();
   _water.setTextureMirror(terrainReflectTextureId);
    } 
    _skybox.render(view, projection);
    _terrain.render(view, projection);
    _water.render(view, projection);

}

void MyWorld::cleanUp() {
    _skybox.cleanUp();
    _terrain.cleanUp();
    _perlin.cleanUp();
    _fishEye.cleanUp();
    terrainReflectFB.cleanUp();
}

