/**
  ****************************************************************************************************
  * @file       mwcc68_cfg.h
  * @author     正点原子团队(ALIENTEK)
  * @version    V1.0
  * @date       2022-2-15
  * @brief      mwcc68模块参数定义
  * @license   	Copyright (c) 2022-2032, 广州市星翼电子科技有限公司
  ****************************************************************************************************
  * @attention
  *
  * 实验平台:正点原子 STM32开发板
  * 在线视频:www.yuanzige.com
  * 技术论坛:www.openedv.com
  * 公司网址:www.alientek.com
  * 购买地址:openedv.taobao.com
  *
  * 修改说明
  * V1.0 2022-2-15
  * 第一次发布
  *
  ****************************************************************************************************
  */

#ifndef _MWCC68_CFG_H
#define _MWCC68_CFG_H

#include "stm32f4xx.h"

typedef enum
{
    ATK_IDM750C_LINK1MODE_TCP = 0,
    ATK_IDM750C_LINK1MODE_UDP,
} atk_idm750c_link1mode_t;

typedef enum
{
    ATK_IDM750C_LINK2MODE_TCP = 0,
    ATK_IDM750C_LINK2MODE_UDP,
} atk_idm750c_link2mode_t;

typedef enum
{
    ATK_IDM750C_LINK3MODE_TCP = 0,
    ATK_IDM750C_LINK3MODE_UDP,
} atk_idm750c_link3mode_t;

typedef enum
{
    ATK_IDM750C_LINK4MODE_TCP = 0,
    ATK_IDM750C_LINK4MODE_UDP,
} atk_idm750c_link4mode_t;

typedef enum
{
    ATK_IDM750C_LINK1EN_ON = 0,
    ATK_IDM750C_LINK1EN_OFF,
} atk_idm750c_link1en_t;

typedef enum
{
    ATK_IDM750C_LINK2EN_ON = 0,
    ATK_IDM750C_LINK2EN_OFF,
} atk_idm750c_link2en_t;

typedef enum
{
    ATK_IDM750C_LINK3EN_ON = 0,
    ATK_IDM750C_LINK3EN_OFF,
} atk_idm750c_link3en_t;

typedef enum
{
    ATK_IDM750C_LINK4EN_ON = 0,
    ATK_IDM750C_LINK4EN_OFF,
} atk_idm750c_link4en_t;

typedef enum
{
    ATK_IDM750C_LINK1MD_LONG = 0,
    ATK_IDM750C_LINK1MD_SHORT,
} atk_idm750c_link1md_t;

typedef enum
{
    ATK_IDM750C_LINK2MD_LONG = 0,
    ATK_IDM750C_LINK2MD_SHORT,
} atk_idm750c_link2md_t;

typedef enum
{
    ATK_IDM750C_LINK3MD_LONG = 0,
    ATK_IDM750C_LINK3MD_SHORT,
} atk_idm750c_link3md_t;

typedef enum
{
    ATK_IDM750C_LINK4MD_LONG = 0,
    ATK_IDM750C_LINK4MD_SHORT,
} atk_idm750c_link4md_t;

typedef enum
{
    ATK_IDM750C_SENDFAST_ON = 0,
    ATK_IDM750C_SENDFAST_OFF,
} atk_idm750c_sendfast_t;

typedef enum
{
    ATK_IDM750C_SET_YUANZIYUN_ON = 0,
    ATK_IDM750C_SET_YUANZIYUN_OFF,
} atk_idm750c_set_yuanziyun_t;

typedef enum
{
    ATK_IDM750C_SET_REGEN_ON = 0,
    ATK_IDM750C_SET_REGEN_OFF,
} atk_idm750c_regen_t;

typedef enum
{
    ATK_IDM750C_HRTEN_ON = 0,
    ATK_IDM750C_HRTEN_OFF,
} atk_idm750c_hrten_t;

typedef enum
{
    ATK_IDM750C_HTTP_REQUEST_GET = 0,
    ATK_IDM750C_HTTP_REQUEST_POST,
} atk_idm750c_http_request_mode_t;

typedef enum
{
    ATK_IDM750C_MQTT_ZERO_MODE1 = 0,
    ATK_IDM750C_MQTT_ZERO_MODE2,
    ATK_IDM750C_MQTT_ZERO_MODE3,
    ATK_IDM750C_MQTT_ZERO_MODE4,
    ATK_IDM750C_MQTT_ONE_MODE1,
    ATK_IDM750C_MQTT_ONE_MODE2,
    ATK_IDM750C_MQTT_ONE_MODE3,
    ATK_IDM750C_MQTT_ONE_MODE4,
    ATK_IDM750C_MQTT_TWO_MODE1,
    ATK_IDM750C_MQTT_TWO_MODE2,
    ATK_IDM750C_MQTT_TWO_MODE3,
    ATK_IDM750C_MQTT_TWO_MODE4,
} atk_idm750c_mqtt_para_mode_t;

typedef enum
{
    ATK_IDM750C_ALIYUN_ZERO_MODE1 = 0,
    ATK_IDM750C_ALIYUN_ZERO_MODE2,
    ATK_IDM750C_ALIYUN_ZERO_MODE3,
    ATK_IDM750C_ALIYUN_ZERO_MODE4,
    ATK_IDM750C_ALIYUN_ONE_MODE1,
    ATK_IDM750C_ALIYUN_ONE_MODE2,
    ATK_IDM750C_ALIYUN_ONE_MODE3,
    ATK_IDM750C_ALIYUN_ONE_MODE4,
    ATK_IDM750C_ALIYUN_TWO_MODE1,
    ATK_IDM750C_ALIYUN_TWO_MODE2,
    ATK_IDM750C_ALIYUN_TWO_MODE3,
    ATK_IDM750C_ALIYUN_TWO_MODE4,
} atk_idm750c_aliyun_para_mode_t;

typedef enum
{
    ATK_IDM750C_ONENET_ZERO_MODE1 = 0,
    ATK_IDM750C_ONENET_ZERO_MODE2,
    ATK_IDM750C_ONENET_ZERO_MODE3,
    ATK_IDM750C_ONENET_ZERO_MODE4,
    ATK_IDM750C_ONENET_ZERO_MODE5,
    ATK_IDM750C_ONENET_ZERO_MODE6,
    ATK_IDM750C_ONENET_ZERO_MODE7,
    ATK_IDM750C_ONENET_ZERO_MODE8,
    ATK_IDM750C_ONENET_ZERO_MODE9,
    ATK_IDM750C_ONENET_ZERO_MODE10,
    ATK_IDM750C_ONENET_ZERO_MODE11,
    ATK_IDM750C_ONENET_ZERO_MODE12,
    ATK_IDM750C_ONENET_ONE_MODE1,
    ATK_IDM750C_ONENET_ONE_MODE2,
    ATK_IDM750C_ONENET_ONE_MODE3,
    ATK_IDM750C_ONENET_ONE_MODE4,
    ATK_IDM750C_ONENET_ONE_MODE5,
    ATK_IDM750C_ONENET_ONE_MODE6,
    ATK_IDM750C_ONENET_ONE_MODE7,
    ATK_IDM750C_ONENET_ONE_MODE8,
    ATK_IDM750C_ONENET_ONE_MODE9,
    ATK_IDM750C_ONENET_ONE_MODE10,
    ATK_IDM750C_ONENET_ONE_MODE11,
    ATK_IDM750C_ONENET_ONE_MODE12,
    ATK_IDM750C_ONENET_TWO_MODE1,
    ATK_IDM750C_ONENET_TWO_MODE2,
    ATK_IDM750C_ONENET_TWO_MODE3,
    ATK_IDM750C_ONENET_TWO_MODE4,
    ATK_IDM750C_ONENET_TWO_MODE5,
    ATK_IDM750C_ONENET_TWO_MODE6,
    ATK_IDM750C_ONENET_TWO_MODE7,
    ATK_IDM750C_ONENET_TWO_MODE8,
    ATK_IDM750C_ONENET_TWO_MODE9,
    ATK_IDM750C_ONENET_TWO_MODE10,
    ATK_IDM750C_ONENET_TWO_MODE11,
    ATK_IDM750C_ONENET_TWO_MODE12,
} atk_idm750c_onenet_para_mode_t;

typedef enum
{
    ATK_IDM750C_BAIDUYUN_ZERO_MODE1 = 0,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE2,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE3,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE4,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE5,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE6,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE7,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE8,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE9,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE10,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE11,
    ATK_IDM750C_BAIDUYUN_ZERO_MODE12,
    ATK_IDM750C_BAIDUYUN_ONE_MODE1,
    ATK_IDM750C_BAIDUYUN_ONE_MODE2,
    ATK_IDM750C_BAIDUYUN_ONE_MODE3,
    ATK_IDM750C_BAIDUYUN_ONE_MODE4,
    ATK_IDM750C_BAIDUYUN_ONE_MODE5,
    ATK_IDM750C_BAIDUYUN_ONE_MODE6,
    ATK_IDM750C_BAIDUYUN_ONE_MODE7,
    ATK_IDM750C_BAIDUYUN_ONE_MODE8,
    ATK_IDM750C_BAIDUYUN_ONE_MODE9,
    ATK_IDM750C_BAIDUYUN_ONE_MODE10,
    ATK_IDM750C_BAIDUYUN_ONE_MODE11,
    ATK_IDM750C_BAIDUYUN_ONE_MODE12,
} atk_idm750c_baiduyun_para_mode_t;

typedef enum
{
    ATK_IDM750C_WORKMODE_NET = 0,
    ATK_IDM750C_WORKMODE_HTTP,
    ATK_IDM750C_WORKMODE_MQTT,
    ATK_IDM750C_WORKMODE_ALIYUN,
    ATK_IDM750C_WORKMODE_ONENET,
    ATK_IDM750C_WORKMODE_BAUDUYUN,
    ATK_IDM750C_WORKMODE_RNDIS,
} atk_idm750c_workmode_t;

typedef enum
{
    DTU_WORKMODE_NET = 0,  /*网络透传模式*/
    DTU_WORKMODE_HTTP,     /*http透传模式*/
    DTU_WORKMODE_MQTT,     /*mqtt透传模式*/
    DTU_WORKMODE_ALIYUN,   /*阿里云透传模式*/
    DTU_WORKMODE_ONENET,   /*OneNET透传模式*/
    DTU_WORKMODE_BAIDUYUN, /*百度云透传模式*/
} _dtu_work_mode_eu;

typedef struct
{
    uint32_t timeout; /*指令等待超时时间，单位：100ms*/
    char *read_cmd;   /*查询参数指令      请参考DTU AT用户手册说明进行填写*/
    char *write_cmd;  /*配置参数指令      请参考DTU AT用户手册说明进行填写*/
} _dtu_atcmd_st;

typedef struct
{
    const char *urc_info;                         /*DTU自动上报的URC信息*/
    void (*func)(const char *data, uint32_t len); /*回调处理函数*/
} _dtu_urc_st;

typedef enum
{
    ATK_IDM750C_ECHO_ON = 0,
    ATK_IDM750C_ECHO_OFF,
} atk_idm750c_echo_t;

typedef enum
{
    ATK_IDM750C_UARTMODE_FIRST = 0,
    ATK_IDM750C_UARTMODE_SECOND,
    ATK_IDM750C_UARTMODE_THIRD,
    ATK_IDM750C_UARTMODE_FOURTH,
    ATK_IDM750C_UARTMODE_FIFTH,
    ATK_IDM750C_UARTMODE_SIXTH,
    ATK_IDM750C_UARTMODE_SEVENTH,
    ATK_IDM750C_UARTMODE_EIGHTH,
    ATK_IDM750C_UARTMODE_NINTH,
    ATK_IDM750C_UARTMODE_TENTH,
    ATK_IDM750C_UARTMODE_ELEVENTH,
    ATK_IDM750C_UARTMODE_TWELFTH,
    ATK_IDM750C_UARTMODE_THIRTEENTH,
} atk_idm750c_uartmode_t;

typedef enum
{
    ATK_IDM750C_UART_ON = 0,
    ATK_IDM750C_UART_OFF,
} atk_idm750c_urat_t;

typedef enum
{
    ATK_IDM750C_NET_ON = 0,
    ATK_IDM750C_NET_OFF,
} atk_idm750c_net_t;

#endif


