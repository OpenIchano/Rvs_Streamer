//
//  RvsStreamerInitHelper.h
//  Rvs_Streamer
//
//  Created by GYJ on 16/6/13.
//  Copyright © 2016年 ifziv. All rights reserved.
//

/**
 * 初始化AVS SDK使用，并接收登陆信息等。
 * 生命周期 初始化 --- login --- logout;
 * @author KindDeath
 */

#import <Foundation/Foundation.h>
#import "Rvs_Streamer.h"

@protocol RvsStreamerInitHelperDelegate;

@interface RvsStreamerInitHelper : NSObject

@property (nonatomic, assign) NSInteger sessionMaxNum;

@property (nonatomic, weak) id<RvsStreamerInitHelperDelegate> delegate;

/**
 *  快速获取初始化单例对象
 *
 *  @return 单例对象
 */
+ (RvsStreamerInitHelper *)streamerInitHelper;

/**
 *  设置配置及缓存路径
 *
 *  @param workPath     配置路径    如果为nil则采用默认
 *  @param cachePath    缓存路径    如果为nil则采用默认
 *  @param appVersion   APP版本号   如果为nil则采用默认
 *
 *  @return 设置结果
 */
- (NSInteger)setStreamerWithWorkPath:(NSString *)workPath cachePath:(NSString *)cachePath appVersion:(NSString *)appVersion;

/**
 *  设置授权信息
 *
 *  @param companyID  公司ID，申请开发者时会提供给开发者
 *  @param companyKey 公司Key，申请开发者时会提供给开发者
 *  @param appID      应用ID，申请开发者时会提供给开发者
 *  @param license    软件许可证，申请开发者时会提供给开发者
 *
 *  @return 设置结果
 */
- (NSInteger)setLoginInfoWithCompanyID:(NSString *)companyID companyKey:(unsigned long long)companyKey appID:(NSString *)appID license:(NSString *)license;

/**
 *  登陆到IChano云视频平台
 */
- (void)login;

/**
 * 退出应用时，请调用以释放资源
 */
- (void)logout;

/**
 *  是否输出log 默认是NO
 */
- (void)setLogEnabled:(BOOL)enable;

@end



@protocol RvsStreamerInitHelperDelegate <NSObject>

@optional
//连接状态通知
- (void)onLoginResultWithLoginState:(EN_RVS_STREAMER_LOGIN_STATE)loginState
                       ProgressRate:(EN_RVS_STREAMER_LOGIN_PROGRESS)progressRate
                            errCode:(EN_RVS_LOGIN_ERR)errCode;

//CID变化通知
- (void)onUpdateCID:(unsigned long long)localCID;

//设备名称有变化时通知
- (void)onDeviceNameChange:(NSString *)deviceName;

//用户名与密码更新
- (void)onUpdateUserName:(NSString *)userName pwd:(NSString*)pwd;

- (void)onSession:(unsigned long long)remoteCID StateChange:(EN_RVS_STREAMER_SESSION_STATE)state;


@end
