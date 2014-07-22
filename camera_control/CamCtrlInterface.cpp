#include "StdAfx.h"
#include "CamCtrlInterface.h"


CamCtrlInterface::CamCtrlInterface(void)
{
	m_PanSpeed = 0;
	m_TiltSpeed = 0;
	m_address = 1;
	if(!m_CameraCom.Open())
	{
		MessageBox(NULL,TEXT("串口不存在或已被占用"),TEXT("串口打开失败"), MB_OK | MB_ICONERROR);
	}
}


CamCtrlInterface::~CamCtrlInterface(void)
{
	m_CameraCom.Close();
}

void CamCtrlInterface::SetAllInstructionsOfPELCOD( void )
{
	BYTE instruct[7];
	checksum = 0;

	instruct[0]= 0xFF;
	instruct[1]= m_address;
	instruct[2]= 0x00;
	instruct[3]= 0x04;
	instruct[4]= 0;
	instruct[5]= 0;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	PanLeftInstruction(instruct, 7);

	checksum = 0;
	instruct[3]= 0x02;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	PanRightInstruction(instruct, 7);

	checksum = 0;
	instruct[3]= 0x08;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	TiltUpInstruction(instruct, 7);

	checksum = 0;
	instruct[3]= 0x10;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	TiltDownInstruction(instruct, 7);

	instruct[3]= 0x03;
	instruct[5]= 0x01;
	checksum = 0;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	SetPresetInstruction(instruct, 7);

	instruct[3]= 0x07;
	instruct[5]= 0x01;
	checksum = 0;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	GotoPresetInstruction(instruct, 7);

	instruct[3]= 0x05;
	instruct[5]= 0x01;
	checksum = 0;
	for(int i = 1; i < 6; i++)
	{
		checksum += instruct[i];
	}
	instruct[6]= static_cast<BYTE>(checksum % 256);
	ClearPresetInstruction(instruct, 7);

	instruct[2]= 0x02;
	instruct[3]= 0x00;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x03;
	OpenIrisInstruction(instruct, 7);

	instruct[2]= 0x04;
	instruct[3]= 0x00;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x05;
	CloseIrisInstruction(instruct, 7);

	instruct[2]= 0x01;
	instruct[3]= 0x00;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x02;
	FocusNearInstruction(instruct, 7);

	instruct[2]= 0x00;
	instruct[3]= 0x80;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x81;
	FocusFarInstruction(instruct, 7);

	instruct[2]= 0x00;
	instruct[3]= 0x40;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x41;
	ZoomWideInstruction(instruct, 7);

	instruct[2]= 0x00;
	instruct[3]= 0x20;
	instruct[4]= 0;
	instruct[5]= 0;
	instruct[6]= 0x21;
	ZoomTeleInstruction(instruct, 7);
}

void CamCtrlInterface::PanSpeed( BYTE speed )
{
	if(speed <= 0x40)
	{
		m_PanSpeed = speed;
	}
}

BYTE CamCtrlInterface::PanSpeed( void )
{
	return m_PanSpeed;
}

void CamCtrlInterface::TiltSpeed( BYTE speed )
{
	if(speed <= 0x3F)
	{
		m_TiltSpeed = speed;
	}
}

BYTE CamCtrlInterface::TiltSpeed( void )
{
	return m_TiltSpeed;
}

BOOL CamCtrlInterface::PanLeft( void )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_PanLeftInstruction[4] = m_PanSpeed;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_PanLeftInstruction[i];
		}
		m_PanLeftInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_PanLeftInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::PanRight( void )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_PanRightInstruction[4] = m_PanSpeed;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_PanRightInstruction[i];
		}
		m_PanRightInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_PanRightInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::TiltUp( void )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_TiltUpInstruction[5] = m_TiltSpeed;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_TiltUpInstruction[i];
		}
		m_TiltUpInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_TiltUpInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::TiltDown( void )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_TiltDownInstruction[5] = m_TiltSpeed;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_TiltDownInstruction[i];
		}
		m_TiltDownInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_TiltDownInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::SetPreset( BYTE preset )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_SetPresetInstruction[5] = preset;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_SetPresetInstruction[i];
		}
		m_SetPresetInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_SetPresetInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::GotoPreset( BYTE preset )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_GotoPresetInstruction[5] = preset;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_GotoPresetInstruction[i];
		}
		m_GotoPresetInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_GotoPresetInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::ClearPreset( BYTE preset )
{
	if(m_CameraCom.IsOpened())
	{
		checksum = 0;
		m_ClearPresetInstruction[5] = preset;
		for(int i = 1; i < 6; i++)
		{
			checksum += m_ClearPresetInstruction[i];
		}
		m_ClearPresetInstruction[6]= static_cast<BYTE>(checksum % 256);
		char *p = static_cast<char *>(static_cast<void *>(m_ClearPresetInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::OpenIris( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_OpenIrisInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::CloseIris( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_CloseIrisInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::FocusNear( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_FocusNearInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::FocusFar( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_FocusFarInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::ZoomWide( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_ZoomWideInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

BOOL CamCtrlInterface::ZoomTele( void )
{
	if(m_CameraCom.IsOpened())
	{
		char *p = static_cast<char *>(static_cast<void *>(m_ZoomTeleInstruction));
		m_CameraCom.SendData(p, 7);
		return TRUE;
	}
	return FALSE;
}

void CamCtrlInterface::PanLeftInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_PanLeftInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::PanRightInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_PanRightInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::TiltUpInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_TiltUpInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::TiltDownInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_TiltDownInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::SetPresetInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_SetPresetInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::GotoPresetInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_GotoPresetInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::ClearPresetInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_ClearPresetInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::OpenIrisInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_OpenIrisInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::CloseIrisInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_CloseIrisInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::FocusNearInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_FocusNearInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::FocusFarInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_FocusFarInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::ZoomWideInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_ZoomWideInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::ZoomTeleInstruction( BYTE *instruct, BYTE length )
{
	for(int i = 0; i < length; i++)
	{
		m_ZoomTeleInstruction[i] = instruct[i];
	}
}

void CamCtrlInterface::StopMov( void )
{
	char stopInstruct[7] = {0xFF,m_address,0,0,0,0,m_address};
	m_CameraCom.SendData(stopInstruct, 7);
}

void CamCtrlInterface::SetAddrOfInstruction( BYTE addr )
{
	m_address = addr;
	SetAllInstructionsOfPELCOD();
}

BOOL CamCtrlInterface::GetComState( void )
{
	return m_CameraCom.IsOpened();
}

BOOL CamCtrlInterface::OpenCam( int nPort, int nBaud )
{
	if(!m_CameraCom.IsOpened())
	{
		return m_CameraCom.Open(nPort, nBaud);
	}
	return FALSE;
}

BOOL CamCtrlInterface::CloseCam( void )
{
	return m_CameraCom.Close();
}

void CamCtrlInterface::SetComProtocol( BYTE iProtocol )
{
	switch(iProtocol)
	{
	case PELCOD:
		SetAllInstructionsOfPELCOD();
	}
}

