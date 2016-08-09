//
//  Rvs_Streamer.h
//  Rvs_Stream
//
//  Created by Lvyi on 4/21/15.
//  Copyright (c) 2015 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Rvs_Streamer/Rvs_Streamer_Capacity.h>
#import <Rvs_Streamer/Rvs_Streamer_Media.h>
#import <Rvs_Streamer/Rvs_Streamer_Cmd.h>
#import <Rvs_Streamer/Rvs_Video_Manager.h>
#import <Rvs_Streamer/Rvs_Audio_Manager.h>


typedef enum enum_RVS_STREAMER_LOGIN_STATE
{
    E_RVS_STREAMER_LOGIN_STATE_IDLE      = 0,
    E_RVS_STREAMER_LOGIN_STATE_CONNING   = 1,
    E_RVS_STREAMER_LOGIN_STATE_CONNED    = 2,
    E_RVS_STREAMER_LOGIN_STATE_DISCONNED = 3
}EN_RVS_STREAMER_LOGIN_STATE;

typedef enum enum_RVS_STREAMER_LOGIN_ERR
{
    E_RVS_STREAMER_LOGIN_ERR_NOERR      = 0,
    
    E_RVS_STREAMER_LOGIN_ERR_SERVICEGETERR,
    E_RVS_STREAMER_LOGIN_ERR_AUTH_ERRCOMPANYINFO,
    E_RVS_STREAMER_LOGIN_ERR_AUTH_ERRAPPID,
    E_RVS_STREAMER_LOGIN_ERR_AUTH_ERRLICENSE,
    E_RVS_STREAMER_LOGIN_ERR_AUTH_FULLLICENSE,
    E_RVS_STREAMER_LOGIN_ERR_AUTH_TIMEOUT,
    E_RVS_STREAMER_LOGIN_ERR_CONNECT_ERR,
    E_RVS_STREAMER_LOGIN_ERR_REGISTER_ERR,
    E_RVS_STREAMER_LOGIN_ERR_ALLOCATE_ERR,
    E_RVS_STREAMER_LOGIN_ERR_GETSYSCONFIG_ERR,
    E_RVS_STREAMER_LOGIN_ERR_UPLOADINFO_ERR,
    E_RVS_STREAMER_LOGIN_ERR_CONNECT_INTERUPT,
    E_RVS_STREAMER_LOGIN_ERR_DEFAULT
}EN_RVS_LOGIN_ERR;

typedef enum enum_RVS_STREAMER_LOGIN_PROGRESS{
    E_RVS_STREAMER_LOGIN_PROGRESS_INIT     = 0,
    E_RVS_STREAMER_LOGIN_PROGRESS_SERVICEGET,
    E_RVS_STREAMER_LOGIN_PROGRESS_SERVICEGETTED,
    E_RVS_STREAMER_LOGIN_PROGRESS_AUTHING,
    E_RVS_STREAMER_LOGIN_PROGRESS_AUTHED,
    E_RVS_STREAMER_LOGIN_PROGRESS_CONNECTING,
    E_RVS_STREAMER_LOGIN_PROGRESS_CONNECTED,
    E_RVS_STREAMER_LOGIN_PROGRESS_REGISTING,
    E_RVS_STREAMER_LOGIN_PROGRESS_REGISTED,
    E_RVS_STREAMER_LOGIN_PROGRESS_ALLOCATING,
    E_RVS_STREAMER_LOGIN_PROGRESS_ALLOCATED,
    E_RVS_STREAMER_LOGIN_PROGRESS_GETSYSCONFIG,
    E_RVS_STREAMER_LOGIN_PROGRESS_UPLOADINFO,
    E_RVS_STREAMER_LOGIN_PROGRESS_STARTSERVICES,
    E_RVS_STREAMER_LOGIN_PROGRESS_STARTED
}EN_RVS_STREAMER_LOGIN_PROGRESS;

typedef enum enum_RVS_STREAMER_SESSION_STATE{
    E_RVS_STREAMER_SESSION_STATE_INIT = 0,
    E_RVS_STREAMER_SESSION_STATE_CONNECTING,
    E_RVS_STREAMER_SESSION_STATE_CONNECTED,
    E_RVS_STREAMER_SESSION_STATE_CONNECT_ERROR
}EN_RVS_STREAMER_SESSION_STATE;



@protocol Rvs_Streamer_Delegate <NSObject>

//连接状态通知
- (void)onLoginResultWithLoginState:(EN_RVS_STREAMER_LOGIN_STATE)loginState
                       ProgressRate:(EN_RVS_STREAMER_LOGIN_PROGRESS)progressRate
                            errCode:(EN_RVS_LOGIN_ERR)errCode;

//CID变化通知
- (void)onUpdateCID:(unsigned long long)localCID;

//设备名称有变化时通知
- (void)onDeviceNameChange:(NSString*)deviceName;

//用户名与密码更新
- (void)onUpdateUserName:(NSString*)userName andPwd:(NSString*)pwd;

- (void)onSession:(unsigned long long)remoteCID StateChange:(EN_RVS_STREAMER_SESSION_STATE)state;

- (void)onUpdateSymbol:(NSString*)symbol;


@end


@interface Rvs_Streamer : NSObject


@property (nonatomic, copy) NSString* deviceName;//采集端名称
@property (nonatomic, copy, readonly) NSString* userName;//用户名
@property (nonatomic, copy, readonly) NSString* pwd;//密码

@property (nonatomic, assign, readonly) unsigned long long CID;
@property (nonatomic, assign, readonly) NSUInteger sessionCurNum;

@property (nonatomic, assign) id<Rvs_Streamer_Delegate> delegate;


@property (nonatomic, strong, readonly) Rvs_Streamer_Capacity* streamerCapacity;
@property (nonatomic, strong, readonly) Rvs_Streamer_Media* streamerMedia;
@property (nonatomic, strong, readonly) Rvs_Streamer_Cmd* streamerCmd;
@property (nonatomic, strong, readonly) Rvs_Video_Manager *videoManager;
@property (nonatomic, strong, readonly) Rvs_Audio_Manager *audioManager;


+ (Rvs_Streamer*)defaultStreamer;

+ (void)destroy;

- (NSInteger)initStreamerWithWorkPath:(NSString*)workPath
                                  CachePath:(NSString*)cachePath
                                 AppVersion:(NSString*)appVersion;

//设置授权信息
- (NSInteger)setLoginInfoWithCompanyID:(NSString*)companyID
                        CompanyKey:(unsigned long long)companyKey
                             AppID:(NSString*)appID
                           License:(NSString*)license
                            Symbol:(NSString*)symbol;

- (NSInteger)setUserName:(NSString*)userName andPwd:(NSString*)pwd;

- (NSInteger)setSessionMaxNum:(NSUInteger)sessionMaxNum;

- (NSInteger)login;

- (NSInteger)logout;

- (NSString*)getRvsVersion;

- (void)setLogEnabled:(BOOL)enable;

@end
