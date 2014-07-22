#pragma once

#include "SerialPort.h"

//Э�鶨��
#define PELCOD 0

class CamCtrlInterface
{
public:
	CamCtrlInterface(void);
	~CamCtrlInterface(void);

	//����Э��
	void SetComProtocol(BYTE iProtocol);

	//�����豸����ָ��,������豸Э���ڴ�����µ�ָ���
	void SetAllInstructionsOfPELCOD(void);	//����PELCO(D)Э��

	//����ˮƽ�ƶ��ٶ�
	//speed: 0x0:ֹͣ-0x3F:����,0xFF�����
	void PanSpeed(BYTE speed);
	BYTE PanSpeed(void);

	//���ô�ֱ�ƶ��ٶ�
	//speed: 0x0:ֹͣ-0x3F:����
	void TiltSpeed(BYTE speed);
	BYTE TiltSpeed(void);

	//����
	BOOL PanLeft(void);

	//����
	BOOL PanRight(void);

	//����
	BOOL TiltUp(void);

	//����
	BOOL TiltDown(void);

	//����Ԥ��λ
	//preset: 0x01-0x20
	BOOL SetPreset(BYTE preset);

	//����Ԥ��λ
	BOOL GotoPreset(BYTE preset);

	//���Ԥ��λ
	BOOL ClearPreset(BYTE preset);

	//�򿪹�Ȧ
	BOOL OpenIris(void);

	//�رչ�Ȧ
	BOOL CloseIris(void);

	//��������
	BOOL FocusNear(void);

	//��Զ����
	BOOL FocusFar(void);

	//���,��Сͼ��,�Ŵ���Ұ
	BOOL ZoomWide(void);

	//խ��,�Ŵ�ͼ��,��С��Ұ
	BOOL ZoomTele(void);

	void StopMov(void);

	//����ָ���ַ
	void SetAddrOfInstruction(BYTE addr);
	//���ÿ���ָ��
	//����
	void PanLeftInstruction(BYTE *instruct, BYTE length);
	//����
	void PanRightInstruction(BYTE *instruct, BYTE length);
	//����
	void TiltUpInstruction(BYTE *instruct, BYTE length);
	//����
	void TiltDownInstruction(BYTE *instruct, BYTE length);
	//����Ԥ��λ
	//preset: 0x01-0x20
	void SetPresetInstruction(BYTE *instruct, BYTE length);
	//����Ԥ��λ
	void GotoPresetInstruction(BYTE *instruct, BYTE length);
	//���Ԥ��λ
	void ClearPresetInstruction(BYTE *instruct, BYTE length);
	//�򿪹�Ȧ
	void OpenIrisInstruction(BYTE *instruct, BYTE length);
	//�رչ�Ȧ
	void CloseIrisInstruction(BYTE *instruct, BYTE length);
	//��������
	void FocusNearInstruction(BYTE *instruct, BYTE length);
	//��Զ����
	void FocusFarInstruction(BYTE *instruct, BYTE length);
	//���,��Сͼ��,�Ŵ���Ұ
	void ZoomWideInstruction(BYTE *instruct, BYTE length);
	//խ��,�Ŵ�ͼ��,��С��Ұ
	void ZoomTeleInstruction(BYTE *instruct, BYTE length);

	//�жϴ����Ƿ��
	BOOL GetComState(void);
	//�򿪴���
	BOOL OpenCam(int nPort, int nBaud);
	//�رմ���
	BOOL CloseCam(void);


private:
	SerialPort m_CameraCom;	//ͨ�Ŵ���

	BYTE m_PanSpeed;	//ˮƽ�ƶ��ٶ�
	BYTE m_TiltSpeed;	//��ֱ�ƶ��ٶ�
	BYTE m_address;		//ָ���ַ

	unsigned short checksum; //ָ��У��

	BYTE m_PanLeftInstruction[7];	//����
	BYTE m_PanRightInstruction[7];	//����
	BYTE m_TiltUpInstruction[7];		//����
	BYTE m_TiltDownInstruction[7];	//����
	BYTE m_SetPresetInstruction[7];	//����Ԥ��λ
	BYTE m_GotoPresetInstruction[7];	//����Ԥ��λ
	BYTE m_ClearPresetInstruction[7];	//���Ԥ��λ
	BYTE m_OpenIrisInstruction[7];	//�򿪹�Ȧ
	BYTE m_CloseIrisInstruction[7];	//�رչ�Ȧ
	BYTE m_FocusNearInstruction[7];	//��������
	BYTE m_FocusFarInstruction[7];	//��Զ����
	BYTE m_ZoomWideInstruction[7];	//���,��Сͼ��,�Ŵ���Ұ
	BYTE m_ZoomTeleInstruction[7];	//խ��,�Ŵ�ͼ��,��С��Ұ
};

