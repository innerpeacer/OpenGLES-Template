//
//  ViewController.m
//  OpenGLES Template
//
//  Created by innerpeacer on 14/12/20.
//  Copyright (c) 2014年 palmap+. All rights reserved.
//

#import "ViewController.h"
#import "OpenGLView.h"

@interface ViewController ()
{
    OpenGLView *glView;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    glView = [[OpenGLView alloc] initWithFrame:self.view.frame];
    [self.view addSubview:glView];
    
//    [glView setBackgroundColor:[UIColor greenColor]];
}


@end
