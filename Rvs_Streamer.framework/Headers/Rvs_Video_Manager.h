//
//  Rvs_Vedio_Manager.h
//  Rvs_Streamer
//
//  Created by GYJ on 16/4/19.
//  Copyright © 2016年 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "Rvs_Streamer_Sys.h"
#import "Rvs_Streamer_Media.h"

typedef enum : NSUInteger {
    EN_RVS_STREAMER_MEDIA_COLLECTION_CLOSE  = 0x00,
    EN_RVS_STREAMER_MEDIA_COLLECTION_OPEN   = 0x01,
} EN_RVS_STREAMER_MEDIA_COLLECTION_FLAG;

@interface Rvs_Video_Manager : NSObject <Rvs_Streamer_Media_AV_Delegate>

/**
 *  设置是否为后摄像头，默认YES
 */
@property (nonatomic, assign, getter=isBackCamera) BOOL backCamera;

/**
 *  启动视频录制
 *
 *  @param frame 视频显示大小
 *  @param layer 显示layer
 */
- (void)startVideoWithFrame:(CGRect)frame layer:(CALayer *)layer;

/// 启动视频模块
- (void)start;

- (void)startWithWidth:(NSUInteger)width height:(NSUInteger)height bitRate:(NSUInteger)bitRate frameRate:(NSUInteger)frameRate iFrameInterval:(NSUInteger)iFrameInterval imageQuality:(NSUInteger)imageQuality;

/// 停止视频模块
- (void)stop;

- (CALayer *)getCameraView:(CGRect)frame;

/**
 *  切换手电筒
 */
- (void)switchTorch;

/**
 *  切换摄像头
 */
- (void)switchCamera;

/**
 *  获取摄像头数组
 */
- (NSArray *)getCameraArray;

/**
 *  获取视频宽高
 */
- (CGSize)getCameraViewSize;

/**
 *  对焦
 */
- (void)setFocusWithX:(int)pointX Y:(int)pointY;

/**
 *  当观看端链接状态发生变化时调用
 *
 *  @param flag     链接状态
 */
- (void)onVideoCollectFlagNotify:(EN_RVS_STREAMER_MEDIA_COLLECTION_FLAG)flag
                       forCamera:(NSUInteger)cameraId
                          stream:(NSUInteger)streamId;

/**
 *  压缩jepg获取YUV数据，由SDK调用
 */
- (void)getOneFrameToPictureWithFrameData:(unsigned char **)pFrameData width:(int *)width height:(int *)height;

/**
 *  获取一张截图
 */
- (void)onGetJpegFrame:(unsigned char**)ppFrameBuf
           FrameLength:(NSUInteger*) pFrameBufLength
              JpegType:(EN_RVS_STREAMER_JPEG_TYPE)jpegType
             ForCamera:(NSUInteger)cameraId
                Stream:(NSUInteger)streamId;

/**
 *  需要一个IDR帧
 */
- (void)forceEncodeIDRFrame;

/**
 *  根据当前镜头ID获取编码器中一帧YUV数据
 */
- (void)onGetYUV420Frame:(unsigned char**)ppFrameBuf
                   width:(int *)width
                  height:(int *)height;

/// 设置每个视频流通道到的视频流参数
- (NSInteger)setCameraStreamProperty:(const ST_RVS_STREAMER_CAMERASTREAM_INFO *)videoFormat
                           ForCamera:(NSUInteger)cameraId
                              Stream:(NSUInteger)streamId;

@end
