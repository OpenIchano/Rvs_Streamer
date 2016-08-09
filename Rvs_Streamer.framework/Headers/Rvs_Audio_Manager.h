//
//  AvsAudioManager.h
//  AvsServeriOS
//
//  Created by Lvyi on 5/30/14.
//  Copyright (c) 2014 guojing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Rvs_Streamer_Media.h"

@class Rvs_Audio_Streamer;
@interface Rvs_Audio_Manager : NSObject <Rvs_Streamer_Media_RevStream_Delegate>

/// 是否播放声音，默认为YES
@property (nonatomic, assign) BOOL isPlayVoice;

+ (Rvs_Audio_Manager *)shareManager;

// 启动音频模块
- (void)start;

// 停止音频模块
- (void)stop;

// 获取AudioStreamer
- (Rvs_Audio_Streamer *)getAudioStreamer;

// 接受音频流通知
- (void)onAudioCollectFlagNotify:(int)flag
                          ForMic:(NSUInteger)micId;

/// 设置每个音频流通道到的音频流参数
- (NSInteger)setAudioProperty:(const ST_RVS_STREAMER_MIC_INFO *)audioFormat
                       forMic:(NSUInteger)micId;


@end
