//
//  OpenGLView.m
//  OpenGLES Template
//
//  Created by innerpeacer on 14/12/20.
//  Copyright (c) 2014年 palmap+. All rights reserved.
//

#import "OpenGLView.h"

#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "ES2RenderingEngine.h"
#include "Vertex.h"


using namespace Innerpeacer::ES2;

@interface OpenGLView()
{
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    
    ES2RenderingEngine *m_renderEngine;

}
@end

//const Vertex Vertices[] = {
//    {{-0.0, 0.5, 0.0}, {1, 1, 0.5f, 1}},
//    {{-0.5, -0.5, 0.0},  {1, 1, 0.5f, 1}},
//    {{0.5, -0.5, 0.0},         {1, 1, 0.5f, 1}},
//};

const Vertex Vertices[] = {
    {{-0.0, 0.5, -1.0}, {1, 1, 0.5f, 1}},
    {{-0.5, -0.5, -1.0},  {1, 1, 0.5f, 1}},
    {{0.5, -0.5, -1.0},         {1, 1, 0.5f, 1}},
};

@implementation OpenGLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _eaglLayer = (CAEAGLLayer *)self.layer;
        _eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        _context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!_context) {
            NSLog(@"Failed to initialize OpenGLES 2.0 context");
            exit(1);
        }
        
        if (![EAGLContext setCurrentContext:_context]) {
            NSLog(@"Failed to set current OpenGL context");
            exit(1);
        }
        
        m_renderEngine = new ES2RenderingEngine();
        [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
        
        m_renderEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame), [self getShaderSoureUTF8String:@"SimpleVertex"], [self getShaderSoureUTF8String:@"SimpleFragment"]);
        
        [self drawView:nil];
        
    }
    
    return self;
}

- (void)drawView:(CADisplayLink *)displayLink
{
    m_renderEngine->Render(Vertices);
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (const char *)getShaderSoureUTF8String:(NSString *)shaderName
{
    NSString *shaderPath = [[NSBundle mainBundle] pathForResource:shaderName ofType:@"glsl"];
    
    NSError *error;
    NSString *shaderString = [NSString stringWithContentsOfFile:shaderPath encoding:NSUTF8StringEncoding error:&error];
    
    if (error) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    return [shaderString UTF8String];
}

- (void)dealloc
{
    delete m_renderEngine;
}

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

@end
