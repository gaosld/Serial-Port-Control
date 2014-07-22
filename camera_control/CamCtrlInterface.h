#pragma once

#include "SerialPort.h"

//协议定义
#define PELCOD 0

class CamCtrlInterface
{
public:
	CamCtrlInterface(void);
	~CamCtrlInterface(void);

	//设置协议
	void SetComProtocol(BYTE iProtocol);

	//设置设备操作指令,添加新设备协议在此添加新的指令函数
	void SetAllInstructionsOfPELCOD(void);	//设置PELCO(D)协议

	//设置水平移动速度
	//speed: 0x0:停止-0x3F:高速,0xFF最高速
	void PanSpeed(BYTE speed);
	BYTE PanSpeed(void);

	//设置垂直移动速度
	//speed: 0x0:停止-0x3F:高速
	void TiltSpeed(BYTE speed);
	BYTE TiltSpeed(void);

	//左移
	BOOL PanLeft(void);

	//右移
	BOOL PanRight(void);

	//上移
	BOOL TiltUp(void);

	//下移
	BOOL TiltDown(void);

	//设置预置位
	//preset: 0x01-0x20
	BOOL SetPreset(BYTE preset);

	//调用预置位
	BOOL GotoPreset(BYTE preset);

	//清除预置位
	BOOL ClearPreset(BYTE preset);

	//打开光圈
	BOOL OpenIris(void);

	//关闭光圈
	BOOL CloseIris(void);

	//拉近焦距
	BOOL FocusNear(void);

	//拉远焦距
	BOOL FocusFar(void);

	//广角,缩小图像,放大视野
	BOOL ZoomWide(void);

	//窄角,放大图像,缩小视野
	BOOL ZoomTele(void);

	void StopMov(void);

	//设置指令地址
	void SetAddrOfInstruction(BYTE addr);
	//设置控制指令
	//左移
	void PanLeftInstruction(BYTE *instruct, BYTE length);
	//右移
	void PanRightInstruction(BYTE *instruct, BYTE length);
	//上移
	void TiltUpInstruction(BYTE *instruct, BYTE length);
	//下移
	void TiltDownInstruction(BYTE *instruct, BYTE length);
	//设置预置位
	//preset: 0x01-0x20
	void SetPresetInstruction(BYTE *instruct, BYTE length);
	//调用预置位
	void GotoPresetInstruction(BYTE *instruct, BYTE length);
	//清除预置位
	void ClearPresetInstruction(BYTE *instruct, BYTE length);
	//打开光圈
	void OpenIrisInstruction(BYTE *instruct, BYTE length);
	//关闭光圈
	void CloseIrisInstruction(BYTE *instruct, BYTE length);
	//拉近焦距
	void FocusNearInstruction(BYTE *instruct, BYTE length);
	//拉远焦距
	void FocusFarInstruction(BYTE *instruct, BYTE length);
	//广角,缩小图像,放大视野
	void ZoomWideInstruction(BYTE *instruct, BYTE length);
	//窄角,放大图像,缩小视野
	void ZoomTeleInstruction(BYTE *instruct, BYTE length);

	//判断串口是否打开
	BOOL GetComState(void);
	//打开串口
	BOOL OpenCam(int nPort, int nBaud);
	//关闭串口
	BOOL CloseCam(void);


private:
	SerialPort m_CameraCom;	//通信串口

	BYTE m_PanSpeed;	//水平移动速度
	BYTE m_TiltSpeed;	//垂直移动速度
	BYTE m_address;		//指令地址

	unsigned short checksum; //指令校验

	BYTE m_PanLeftInstruction[7];	//左移
	BYTE m_PanRightInstruction[7];	//右移
	BYTE m_TiltUpInstruction[7];		//上移
	BYTE m_TiltDownInstruction[7];	//下移
	BYTE m_SetPresetInstruction[7];	//设置预置位
	BYTE m_GotoPresetInstruction[7];	//调用预置位
	BYTE m_ClearPresetInstruction[7];	//清除预置位
	BYTE m_OpenIrisInstruction[7];	//打开光圈
	BYTE m_CloseIrisInstruction[7];	//关闭光圈
	BYTE m_FocusNearInstruction[7];	//拉近焦距
	BYTE m_FocusFarInstruction[7];	//拉远焦距
	BYTE m_ZoomWideInstruction[7];	//广角,缩小图像,放大视野
	BYTE m_ZoomTeleInstruction[7];	//窄角,放大图像,缩小视野
};

