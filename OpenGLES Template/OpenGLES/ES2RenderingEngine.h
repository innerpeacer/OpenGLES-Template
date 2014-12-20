//
//  ES2RenderingEngine.h
//  OpenGLES Template
//
//  Created by innerpeacer on 14/12/20.
//  Copyright (c) 2014年 palmap+. All rights reserved.
//

#ifndef __OpenGLES_Template__ES2RenderingEngine__
#define __OpenGLES_Template__ES2RenderingEngine__

//#include <stdlib.h>
//#include <stdio.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "Vertex.h"

namespace Innerpeacer {
namespace ES2 {
        
    class ES2RenderingEngine {
    public:
        
        ES2RenderingEngine();
        
        void Initialize(int width, int height, const char *vertexShaderSource, const char *fragmentShaderSource);
        
        void Render(const Vertex *vertices) const;
        
        ~ES2RenderingEngine() {}
        
    private:
        GLuint BuildShader(const char *shaderSrc, GLenum shaderType) const;
        GLuint BuildProgram(const char *vertexShaderSource, const char *fragmentShaderSource) const;
        
        GLuint m_renderBuffer;
        GLuint m_frameBuffer;
        GLuint m_shaderProgram;
    };

}
}




#endif /* defined(__OpenGLES_Template__ES2RenderingEngine__) */
