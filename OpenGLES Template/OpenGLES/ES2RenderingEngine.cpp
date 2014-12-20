//
//  ES2RenderingEngine.cpp
//  OpenGLES Template
//
//  Created by innerpeacer on 14/12/20.
//  Copyright (c) 2014年 palmap+. All rights reserved.
//

#include "ES2RenderingEngine.h"

#include <iostream>

using namespace Innerpeacer::ES2;


ES2RenderingEngine::ES2RenderingEngine()
{
    glGenRenderbuffers(1, &m_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
}

void ES2RenderingEngine::Render(const Vertex *vertices) const
{
#ifdef ES_ENGINE_FLOW_DEBUG
    printf("ES2RenderingEnging::Render()\n");
#endif
    
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLuint positionSlot = glGetAttribLocation(m_shaderProgram, "Position");
    glEnableVertexAttribArray(positionSlot);
    
    GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &vertices[0].Position[0];
    
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, stride, pCoords);
    
    
    GLsizei vertexCount = sizeof(vertices)/sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableVertexAttribArray(positionSlot);
    
}

void ES2RenderingEngine::Initialize(int width, int height, const char *vertexShaderSource, const char *fragmentShaderSource)
{
#ifdef ES_ENGINE_FLOW_DEBUG
    printf("ES2RenderingEngine::Initialize()\n");
#endif
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBuffer);
    
    glViewport(0, 0, width, height);
    
    m_shaderProgram = BuildProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(m_shaderProgram);
}

GLuint ES2RenderingEngine::BuildShader(const char *shaderSrc, GLenum shaderType) const
{
    
#ifdef ES_ENGINE_FLOW_DEBUG
    printf("ES2RenderingEngine::BuildShader()\n");
    printf("%s\n", shaderSrc);
#endif
    
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &shaderSrc, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        
        glDeleteShader(shaderHandle);
        exit(1);
    }
    
    return shaderHandle;
}

GLuint ES2RenderingEngine::BuildProgram(const char *vertexShaderSource, const char *fragmentShaderSource) const
{
#ifdef ES_ENGINE_FLOW_DEBUG
    printf("ES2RenderingEngine::BuildProgram()\n");
#endif
    
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSucess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSucess);
    
    if (linkSucess == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(programHandle, sizeof(message), 0, &message[0]);
        std::cout << message;
        
        glDeleteProgram(programHandle);
        exit(1);
    }
    
    return programHandle;
}