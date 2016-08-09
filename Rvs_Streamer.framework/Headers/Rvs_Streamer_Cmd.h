//
//  Rvs_Streamer_Command.h
//  Rvs_Stream
//
//  Created by Lvyi on 4/21/15.
//  Copyright (c) 2015 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Rvs_Streamer/Rvs_Streamer_Sys.h>

typedef void (^recvDataBlock)(int cmdId, unsigned char *data, NSInteger dataLenth, unsigned long long peerCID);


//PTZ 枚举
typedef enum enum_Rvs_STREAMER_PTZMoveCtrl{
    EN_RVS_STREAMER_PTZMOVE_CTRL_PTZ  = 0,
    EN_RVS_STREAMER_PTZMOVE_CTRL_MOVE = 1
}EN_RVS_STREAMER_PTZMOVE_CTRL;

typedef enum enum_Rvs_STREAMER_RotateType{
    EN_RVS_STREAMER_ROTATE_TYPE_VERTICAL   = 0x01,
    EN_RVS_STREAMER_ROTATE_TYPE_HORIZONTAL = 0x02
}EN_RVS_STREAMER_ROTATE_TYPE;

typedef enum enum_RVS_STREAMER_CMD_ERROR_CODE{
    EN_RVS_STREAMER_CMD_ERROR_CODE_NOERR = 0, // No Error, SUCCESS;
    EN_RVS_STREAMER_CMD_ERROR_CODE_NOTSUPPORT, // Error, This cmd process function not implement;
    EN_RVS_STREAMER_CMD_ERROR_CODE_PROCESSERR, // Error, This cmd process error.
    EN_RVS_STREAMER_CMD_ERROR_CODE_TIMEOUT, // Error, This cmd process timeout.
    EN_RVS_STREAMER_CMD_ERROR_CODE_INVALIDPARAM, // Error, This cmd Param invalid.
    EN_RVS_STREAMER_CMD_ERROR_CODE_BREAKERR // Error, This cmd process break.
}EN_RVS_STREAMER_CMD_ERROR_CODE;

//处理命令通道来的事件
@protocol Rvs_Streamer_Cmd_Delegate <NSObject>

//云台控制接口
- (void)onPtzMoveCtrlWithPeerCID:(unsigned long long)peerCID
                        CameraId:(NSUInteger)camId
                        CtrlType:(EN_RVS_STREAMER_PTZMOVE_CTRL)PTZMoveCtrlType
                        PRDirect:(NSInteger)pRDirect
                        TVDirect:(NSInteger)tVDirect
                        ZFDirect:(NSInteger)zFDirect;


//报警信息参数变化时通知
- (void)onEmailSettingsWithPeerCID:(unsigned long long)peerCID
                        EmailAlert:(BOOL) enableEmail
                      EmailAddress:(NSString*) emailAddr;

//Push参数变化时通知
- (void)onPushSettingWithPeerCID:(unsigned long long)peerCID
                       PushAlert:(BOOL)enablePush;

//当切换前后摄像头请求到来时触发
- (void)onSwitchCameraStreamWithPeerCID:(unsigned long long)peerCID
                               CameraId:(NSUInteger)camId;

//当切换手电筒请求到来时触发
- (void)onSwitchTorchWithPeerCID:(unsigned long long)peerCID
                        CameraId:(NSUInteger)camId;

//收到自定义的控制指令
- (void)onRecvData:(unsigned char*)data
        DataLength:(NSUInteger)dataLength
          FromPeer:(unsigned long long)peerCID;


/**
 *  收到自定义的控制命令
 *
 *  @param cmdId     命令id,当cmdId = -1即未定义id
 *  @param command   command命令
 *  @param peerCID   观看端CID
 */
- (void)onRecvCustomCmdWithId:(int)cmdId
                   command:(NSString *)command
               fromPeer:(unsigned long long)peerCID;

/**
 *  收到采集端位置回调
 *
 *  @param isSuccess 是否正确获取地理位置
 *  @param longitude 经度
 *  @param latitude  纬度
 *  @param peerCID   采集端CID
 */
- (void)onRecvStreamerRequestLocationFormPeer:(unsigned long long)peerCID;

/**
 *  收到文件回调
 *
 *  @param data     数据data
 *  @param dataDesc 数据描述（用于唯一标识数据，长度不能超过128个字节）
 *  @param peerCID  发送端CID
 */
- (void)onRecvCustomData:(NSData *)fileData
              fileDesc:(NSString *)fileDesc
              formPeer:(unsigned long long)peerCID;



@end

@interface Rvs_Streamer_Cmd : NSObject

/// 回调block存储字典
@property (nonatomic, strong, readonly) NSMutableDictionary *blockDict;

@property (nonatomic, assign) id<Rvs_Streamer_Cmd_Delegate> delegate;

//发送自定义控制指令
- (NSInteger)sendData:(unsigned char*)data
           DataLength:(NSUInteger)dataLength
               ToPeer:(unsigned long long)peerCID;


/**
 *  根据自定义id发送控制命令
 *
 *  @param cmdId   自定义命令id，取值范围应大于1000，小于1000为内部保留id
 *  @param command 命令字符串
 *  @param peerCID 观看端CID
 */
- (NSInteger)sendCustomCommandWithId:(int)cmdId
                       command:(NSString *)command
                        toPeer:(unsigned long long)peerCID;

/**
 *  根据自定义id发送控制命令
 *
 *  @param cmdId           自定义命令id，取值范围应大于1000，小于1000为内部保留id
 *  @param command         命令字符串
 *  @param peerCID         观看端CID
 *  @param complementBlock 完成时回调block
 */
- (NSInteger)sendCustomCommandWithId:(int)cmdId
                       command:(NSString *)command
                        toPeer:(unsigned long long)peerCID
               complementBlock:(recvDataBlock)complementBlock;


/**
 *  发送采集端的位置
 *
 *  @param longitude 经度
 *  @param latitude  唯独
 *  @param peerCID   接收端CID
 */
- (NSInteger)sendStreamerLocationWithLongitude:(double)longitude
                                      latitude:(double)latitude
                                        toPeer:(unsigned long long)peerCID;

/**
 *  发送文件
 *
 *  @param data     数据data
 *  @param dataDesc 数据描述（用于唯一标识数据，长度不能超过128个字节）
 *  @param peerCID  接收端CID
 */
- (NSInteger)sendCustomData:(NSData *)data
                     dataDesc:(NSString *)dataDesc
                       toPeer:(unsigned long long)peerCID;

@end
