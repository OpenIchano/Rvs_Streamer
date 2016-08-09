//
//  RVS_Streamer_Media.h
//  RVS_Stream
//
//  Created by Lvyi on 4/21/15.
//  Copyright (c) 2015 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "Rvs_Streamer_Sys.h"

typedef enum enum_RVS_STREAMER_MEDIASTREAM_STATE{
    EN_RVS_STREAMER_MEDIASTREAM_STATE_CREATED        = 0,
    EN_RVS_STREAMER_MEDIASTREAM_STATE_CLOSED,
}EN_RVS_STREAMER_MEDIASTREAM_STATE;

typedef enum enum_RVS_STREAMER_VIDEO_TYPE
{
    E_RVS_STREAMER_VIDEO_TYPE_NOVIDEO            = 0,
    E_RVS_STREAMER_VIDEO_TYPE_JPEG               = 1,
    E_RVS_STREAMER_VIDEO_TYPE_H264               = 2,
}EN_RVS_STREAMER_VIDEO_TYPE;

typedef enum enum_RVS_STREAMER_AUDIO_TYPE
{
    E_RVS_STREAMER_AUDIO_TYPE_NOAUDIO           = 0,
    E_RVS_STREAMER_AUDIO_TYPE_AAC               = 1,
    E_RVS_STREAMER_AUDIO_TYPE_G711A             = 2,
    E_RVS_STREAMER_AUDIO_TYPE_G711U             = 3,
    E_RVS_STREAMER_AUDIO_TYPE_PCM16             = 4,//”√ªß¥´¥À∏Ò Ωµƒª∞£¨”…SDK«ø÷∆—πÀı≥…AAC∏Ò Ω¥´µ›∏¯CLIENT
}EN_RVS_STREAMER_AUDIO_TYPE;

typedef enum enum_RVS_STREAMER_PTZMOVE_MODE{
    EN_RVS_STREAMER_PTZMOVE_MODE_NOMODE        = 0,
    EN_RVS_STREAMER_PTZMOVE_MODE_PCTRL         = 0x01,
    EN_RVS_STREAMER_PTZMOVE_MODE_TCTRL         = 0x02,
    EN_RVS_STREAMER_PTZMOVE_MODE_ZCTRL         = 0x04,
    EN_RVS_STREAMER_PTZMOVE_MODE_XMOVE         = 0x08,
    EN_RVS_STREAMER_PTZMOVE_MODE_YMOVE         = 0x10,
    EN_RVS_STREAMER_PTZMOVE_MODE_ZMOVE         = 0x20
}EN_RVS_STREAMER_PTZMOVE_MODE;

typedef enum enum_RVS_STREAMER_STREAM_MODE{
    EN_RVS_STREAMER_STREAM_MODE_USESINGLE     = 0x00,
    EN_RVS_STREAMER_STREAM_MODE_USEMULTI      = 0x01
}EN_RVS_STREAMER_STREAM_MODE;

typedef struct {
    NSUInteger        PTZMoveMode;
    NSUInteger        torchMode;
    NSUInteger        rotateMode;
    NSUInteger        streamMode;
}ST_RVS_CAMERA_CAPACITY;

@interface RvsScheduleSetting : NSObject

@property (nonatomic, assign) NSUInteger  seq;
@property (nonatomic, assign) BOOL enable;
@property (nonatomic, assign) NSUInteger  startPoint;
@property (nonatomic, assign) NSUInteger  endPoint;
@property (nonatomic, assign) NSUInteger  weekFlag;

@end

@interface RvsTimeRecordSetting : NSObject

@property (nonatomic, retain) RvsScheduleSetting* schedule;
@property (nonatomic, assign) NSUInteger  param;

@end

@interface RvsMotionDetectSetting : NSObject

@property (nonatomic, retain) RvsScheduleSetting* schedule;
@property (nonatomic, assign) NSUInteger  sensitive;

@end


typedef struct
{
    NSUInteger          videoType;
    NSUInteger          width;
    NSUInteger          height;
    NSUInteger          bitRate;
    NSUInteger          frameRate;
    NSUInteger          iFrameInterval;
    NSUInteger          imageQuality;
   
    
}ST_RVS_STREAMER_CAMERASTREAM_INFO;

typedef struct
{
    NSUInteger              audioType;
    NSUInteger              sampleRate;
    NSUInteger              channel;
    NSUInteger              depth;
}ST_RVS_STREAMER_MIC_INFO;

typedef struct stRVS_STREAMER_MEDIA_AVDESC
{
    EN_RVS_STREAMER_VIDEO_TYPE         videoType;
    NSUInteger                         width;
    NSUInteger                         height;
    
    EN_RVS_STREAMER_AUDIO_TYPE          audioType;
    NSUInteger                          sampleRate;
    NSUInteger                          channel;
    NSUInteger                          depth;
}ST_RVS_STREAMER_MEDIA_AVDESC;

typedef enum enum_RVS_STREAMER_MEDIA_REVDATATYPE{
    E_RVS_STREAMER_MEDIA_REVDATATYPE_AUDIO = 1,
    E_RVS_STREAMER_MEDIA_REVDATATYPE_VIDEO = 2
}EN_RVS_STREAMER_MEDIA_REVDATATYPE;

typedef enum enum_RVS_STREAMER_MEDIA_COLLECT_FLAG{
    E_RVS_STREAMER_MEDIA_COLLECT_CLOSE                    = 0x00,
    E_RVS_STREAMER_MEDIA_COLLECT_OPEN                     = 0x01,
}EN_RVS_STREAMER_MEDIA_COLLECT_FLAG;

typedef enum enum_RVS_STREAMER_JPEG_TYPE
{
    EN_RVS_STREAMER_JPEG_TYPE_HD           = 0,
    EN_RVS_STREAMER_JPEG_TYPE_NORMAL       = 1,
    EN_RVS_STREAMER_JPEG_TYPE_ICON         = 2,
}EN_RVS_STREAMER_JPEG_TYPE;

@protocol Rvs_Streamer_Media_AV_Delegate <NSObject>

- (void)onMediaChannelState:(unsigned long long)peerCid
           MediaStreamState:(EN_RVS_STREAMER_MEDIASTREAM_STATE)state
               ChannelCount:(NSUInteger)channelCount;

//需要一个IDR帧
- (void)onKeyFrameRequiredForCamera:(NSUInteger) cameraId
                             Stream:(NSUInteger) streamId;

- (void)onGetYUV420Frame:(unsigned char**)ppFrameBuf
            ForCamera:(NSUInteger) cameraId
               Stream:(NSUInteger) streamId;

- (void)onGetJpegFrame:(unsigned char**)ppFrameBuf
           FrameLength:(NSUInteger*) pFrameBufLength
              JpegType:(EN_RVS_STREAMER_JPEG_TYPE)jpegType
             ForCamera:(NSUInteger) cameraId
                Stream:(NSUInteger) streamId;


- (void)onAdjustVideoBitrate:(NSUInteger)bitRate
                   Framerate:(NSUInteger)frameRate
                ImageQuality:(NSUInteger)imageQuality
              IFrameInterval:(NSUInteger)iFrameInterval
                   ForCamera:(NSUInteger) cameraId
                      Stream:(NSUInteger) streamId;


- (void)onVideoCollectFlagNotify:(EN_RVS_STREAMER_MEDIA_COLLECT_FLAG)flag
                       ForCamera:(NSUInteger) cameraId
                          Stream:(NSUInteger) streamId;

- (void)onAudioCollectFlagNotify:(EN_RVS_STREAMER_MEDIA_COLLECT_FLAG)flag
                          ForMic:(NSUInteger)micId;


- (void)onRawVideoCollectFlagNotify:(EN_RVS_STREAMER_MEDIA_COLLECT_FLAG)flag
                          forCamera:(NSUInteger)cameraId
                             stream:(NSUInteger)streamId;


@end

@protocol Rvs_Streamer_Media_RevStream_Delegate <NSObject>

- (void)onRevStreamDataToPlay:(unsigned char*)pRevData
                   DataLength:(NSUInteger) length
                     DataType:(EN_RVS_STREAMER_MEDIA_REVDATATYPE) dataType
                  FromPeerCID:(unsigned long long)peerCID;

- (NSInteger)onRevStreamStatus:(unsigned long long)peerCid
                           Url:(NSString*)url
                        Status:(NSUInteger)status;


@end

@protocol Rvs_Streamer_Media_Record_Delegate <NSObject>

- (void)onRecordStart;

- (void)onRecordStop;

- (void)onScheduledRecordSettingUpdate:(NSArray*)recordSettings ForCameraID:(NSUInteger)cameraId;


@end


@protocol Rvs_Streamer_Media_MotionDetect_Delegate <NSObject>

- (void)onMotionDetectStart;

- (void)onMotionDetectStop;

- (void)onMotionDetectSettingUpdate:(NSArray*)motionSettings ForCameraID:(NSUInteger)cameraId;
- (void)onMotionDetectAlarmOut:(NSUInteger)cameraId;

@end


@protocol Rvs_Streamer_Media_H264Encoder_Delegate <NSObject>

- (RVS_HANDLE)onVideoEncoderCreateWithWidth:(NSUInteger)width
                                     Height:(NSUInteger)height;

- (NSInteger)onVideoEncodeFrameWithHandle:(RVS_HANDLE)handle
                          NeedIFrame:(BOOL)needIFrame
                         YUV420Frame:(unsigned char*)yuv420Frame
                           TimeStamp:(NSUInteger)timeStamp
                           H264Frame:(unsigned char**)h264Frame
                        H264FrameLen:(NSUInteger*)h264FrameLen;


- (NSInteger)onVideoEncoderCloseWithHandle:(RVS_HANDLE)handle;

- (NSInteger)onVideoEncoderAdjustWithHandle:(RVS_HANDLE)handle AdjustType:(NSUInteger)adjustType;

@end


@interface Rvs_Streamer_Media : NSObject

@property (nonatomic, assign) id<Rvs_Streamer_Media_AV_Delegate> mediaDelegate;
@property (nonatomic, assign) id<Rvs_Streamer_Media_RevStream_Delegate> revStreamDelegate;
@property (nonatomic, assign) id<Rvs_Streamer_Media_Record_Delegate> recordDelegate;
@property (nonatomic, assign) id<Rvs_Streamer_Media_MotionDetect_Delegate> motionDetectDelegate;
@property (nonatomic, assign) id<Rvs_Streamer_Media_H264Encoder_Delegate> h264EncoderDelegate;

- (void)addMediaObserver:(id<Rvs_Streamer_Media_AV_Delegate>)observer;
- (void)removeMediaObserver:(id<Rvs_Streamer_Media_AV_Delegate>)observer;
- (void)addRvsStreamObserver:(id<Rvs_Streamer_Media_RevStream_Delegate>)observer;
- (void)removeRvsStreamObserver:(id<Rvs_Streamer_Media_RevStream_Delegate>)observer;
- (void)addRecordObserver:(id<Rvs_Streamer_Media_Record_Delegate>)observer;
- (void)removeRecordObserver:(id<Rvs_Streamer_Media_Record_Delegate>)observer;
- (void)addMotionDetectObserver:(id<Rvs_Streamer_Media_MotionDetect_Delegate>)observer;
- (void)removeMotionDetectObserver:(id<Rvs_Streamer_Media_MotionDetect_Delegate>)observer;
- (void)addH264EncoderObserver:(id<Rvs_Streamer_Media_H264Encoder_Delegate>)observer;
- (void)removeH264EncoderObserver:(id<Rvs_Streamer_Media_H264Encoder_Delegate>)observer;

//设置总共镜头数目
- (NSInteger)setCameraCount:(NSUInteger) cameraCount;

//设置每个镜头的视频流通道数
- (NSInteger)setStreamCount:(NSUInteger) streamCount
			 ForCamera:(NSUInteger) cameraId;

//设置每个视频流通道到的视频流参数
- (NSInteger)setCameraStreamProperty:(const ST_RVS_STREAMER_CAMERASTREAM_INFO*) videoFormat
			ForCamera:(NSUInteger) cameraId
			   Stream:(NSUInteger) streamId;

- (NSInteger)setCameraCapacity:(const ST_RVS_CAMERA_CAPACITY*)cameraCapacity
                     ForCamera:(NSUInteger) cameraId;

/**
 *  设置视频录制路径
 *
 *  @param recordPath 路径
 *
 *  @return 设置结果
 */
- (NSInteger)setRecordPath:(NSString *)recordPath;


//设置麦克风数，也就是音频流通道数
- (NSInteger)setMicCount:(NSUInteger) micCount;

//设置每个音频流通道到的音频流参数
- (NSInteger)setAudioProperty:(const ST_RVS_STREAMER_MIC_INFO*) audioFormat
			   ForMic:(NSUInteger)micId;


//发送视频流
- (NSInteger)writeVideoData:(unsigned char*) videoData
            DataLength:(NSUInteger) dataLength
             TimeStamp:(NSUInteger) timeStamp
              IsIFrame:(BOOL)isIFrame
			ForCamera:(NSUInteger) cameraId
			   Stream:(NSUInteger) streamId;

- (NSInteger)writeRawVideoData:(unsigned char*) videoData
                    DataLength:(NSUInteger) dataLength
                     TimeStamp:(NSUInteger) timeStamp
                     ForCamera:(NSUInteger) cameraId
                        Stream:(NSUInteger) streamId;

//发送音频流
- (NSInteger)writeAudioData:(unsigned char*)audioData
            DataLength:(NSUInteger) dataLength
             TimeStamp:(NSUInteger) timeStamp
			   ForMic:(NSUInteger)micId;


- (NSInteger)getRevProperty:(ST_RVS_STREAMER_MEDIA_AVDESC*) pMediaDesc FromPeerCID:(unsigned long long)peerCid;


- (NSInteger)setScheduleRecordSettings:(NSArray*)scheduleRecordSettings ForCamera:(NSUInteger)cameraId;

- (NSArray*)getScheduleRecordSettingsForCamera:(NSUInteger)cameraId;

- (NSInteger)setMotionDetectSettings:(NSArray*)motionDetectSettings ForCamera:(NSUInteger)cameraId;

- (NSArray*)getMotionDetectSettingsForCamera:(NSUInteger)cameraId;

- (NSInteger)getWritenChannelForAsync:(RVS_HANDLE)encHandle;

//发送视频流
- (NSInteger)asynWriteVideoData:(unsigned char*) videoData
                     DataLength:(NSUInteger) dataLength
                      TimeStamp:(NSUInteger) timeStamp
                       IsIFrame:(BOOL)isIFrame
                     ForChannel:(NSInteger)channelId;

//发送视频流
- (NSInteger)asynWriteVideoData:(unsigned char*)videoData
                     dataLength:(NSUInteger)dataLength
                      timeStamp:(NSUInteger)timeStamp
                       isIFrame:(BOOL)isIFrame
                      forHandle:(RVS_HANDLE)handle;


- (void)startCustomRecordForCamera:(NSUInteger)cameraId Stream:(NSUInteger)streamId;

- (void)stopCustomRecordForCamera:(NSUInteger)cameraId Stream:(NSUInteger)streamId;


@end
