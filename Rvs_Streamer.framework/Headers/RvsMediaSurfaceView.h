//
//  RvsMediaSurfaceView.h
//  Rvs_Streamer
//
//  Created by GYJ on 16/6/13.
//  Copyright © 2016年 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Rvs_Streamer_Media.h"
#import "Rvs_Streamer_Cmd.h"

typedef enum : NSUInteger {
    RvsStreamResolution480p,
    RvsStreamResolution320p,
    RvsStreamResolution720p,
    RvsStreamResolution1080p,
} RvsStreamResolution;

typedef enum : NSUInteger {
    RvsStreamBitrate320p,
    RvsStreamBitrate480p,
    RvsStreamBitrate720p,
    RvsStreamBitrate1080p,
} RvsStreamBitrate;

/**
 * 采集摄像头视频并可发送到观看端供观看端观看。
 * 该类中实现的代理方法都可以继承该类重写代理方法
 *
 * @author KindDeath
 */

@interface RvsMediaSurfaceView : NSObject <Rvs_Streamer_Media_AV_Delegate, Rvs_Streamer_Media_RevStream_Delegate, Rvs_Streamer_Media_Record_Delegate, Rvs_Streamer_Media_MotionDetect_Delegate, Rvs_Streamer_Media_H264Encoder_Delegate, Rvs_Streamer_Cmd_Delegate>

/**
 *  设置打开前置还是后置摄像头，默认打开后置摄像头。 值为YES
 */
@property (nonatomic, assign, getter = isBackCamera) BOOL backCamera;

/**
 *  是否显示水印  （一定要在openCamera之前设置）    默认为YES
 */
@property (nonatomic, assign, getter = isShowWatermark) BOOL showWatermark;

/**
 *  设置采集视频分辨率，默认为480p
 *  该设置应在开始采集前设置
 */
@property (nonatomic, assign) RvsStreamResolution resolution;

/**
 *  是否是竖屏， 默认为NO
 */
@property (nonatomic, assign) BOOL isPortrait;

/**
 *  是否播放声音。默认为YES
 */
@property (nonatomic, assign) BOOL isPlayVoice;

/**
 *  设置视频参数 要求在openCamera前调用
 *
 *  @param bitrate        码率
 *  @param frameRate      帧率    一般采用15左右即可
 *  @param iFrameInterval i帧间隔  一般采用2秒
 */
- (void)setVideoParamWithBitrate:(RvsStreamBitrate)bitrate frameRate:(NSUInteger)frameRate iFrameInterval:(NSUInteger)iFrameInterval;

/**
 *  设置视频展示layer
 *
 *  @param videoView 视频展示view
 */
- (void)videoShowWithView:(UIView *)videoView;

/**
 *  打开摄像头
 */
- (void)openCamera;

- (void)openCameraWithResolution:(RvsStreamResolution)resolution;

/**
 *  关闭摄像头
 */
- (void)closeCamera;

/**
 *  获取视频采集大小
 */
- (CGSize)getVideoSize;

/**
 *  切换摄像头
 */
- (void)switchCamera;

/**
 *  获取当前设备摄像头数组
 */
- (NSArray *)getCameraArray;

/**
 *  获取一样截图
 *
 *  @param type 图片类型
 *
 *  @return 获取的图片
 */
- (UIImage *)getCaptureImageWithType:(EN_RVS_STREAMER_JPEG_TYPE)type;

/**
 *  开关摄像头
 */
- (void)switchTorch;

/**
 *  是否正在录制
 */
@property (nonatomic, assign, readonly) BOOL isRecording;

/**
 *  开启本地视频录制，录制的文件保存在初始化sdk时设置的路径（沙盒中）
 */
- (void)startRecord;

/**
 *  停止本地视频录制，录制的文件保存在初始化sdk时设置的路径（沙盒中）
 */
- (void)stopRecord;


@end
