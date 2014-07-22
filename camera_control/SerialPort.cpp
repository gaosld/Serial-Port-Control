#include "StdAfx.h"
#include "SerialPort.h"


SerialPort::SerialPort(void)
{
	m_hCom = NULL;
	m_bOpen = FALSE;
}

SerialPort::~SerialPort(void)
{
	Close();
}

BOOL SerialPort::Open( int nPort /*= 4*/, int nBaud /*= 2400*/ )
{
	if(m_bOpen)
		return TRUE;

	TCHAR szPort[10];
	DCB dcb;

	wsprintf(szPort,TEXT("COM%d"),nPort);
	//�򿪴���
	m_hCom = CreateFile(
		szPort,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	// �첽��д
		NULL
		);

	if (NULL == m_hCom) return FALSE;

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED ));
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));

	// ���ó�ʱ,��ʹ�ö���ʱ
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout		= MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant	= 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier= 0;
	CommTimeOuts.WriteTotalTimeoutConstant	= 5000;
	SetCommTimeouts(m_hCom, &CommTimeOuts);

	// �����첽��ȡ/д������¼�
	m_OverlappedRead.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	m_OverlappedWrite.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

	// ��ȡ/���ô����豸����
	dcb.DCBlength = sizeof ( DCB );
	GetCommState ( m_hCom, &dcb );
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;

	if (!SetupComm(m_hCom, 1024, 1024) ||
		!SetCommState(m_hCom, &dcb) ||
		m_OverlappedRead.hEvent == NULL ||
		m_OverlappedWrite.hEvent == NULL )
	{
			DWORD dwError = GetLastError();

			if ( m_OverlappedRead.hEvent != NULL ) CloseHandle ( m_OverlappedRead.hEvent );

			if ( m_OverlappedWrite.hEvent != NULL ) CloseHandle ( m_OverlappedWrite.hEvent );

			CloseHandle(m_hCom);
			return FALSE;
	}

	m_bOpen = TRUE;

	return m_bOpen;
}

BOOL SerialPort::Close( void )
{
	if (!m_bOpen || m_hCom == NULL) return TRUE;

	if (m_OverlappedRead.hEvent != NULL) CloseHandle(m_OverlappedRead.hEvent);

	if (m_OverlappedWrite.hEvent != NULL) CloseHandle(m_OverlappedWrite.hEvent);

	CloseHandle(m_hCom);
	m_bOpen = FALSE;
	m_hCom = NULL;

	return TRUE;
}

int SerialPort::ReadData( void *buffer, int limit)
{
	if ( !m_bOpen || m_hCom == NULL ) return ( 0 );

	BOOL bReadStatus;
	DWORD dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	// ��ȡ֮ǰ�����������Ϣ
	ClearCommError ( m_hCom, &dwErrorFlags, &ComStat );

	if ( !ComStat.cbInQue ) return ( 0 );

	dwBytesRead = ( DWORD ) ComStat.cbInQue;

	if ( limit < ( int ) dwBytesRead ) dwBytesRead = ( DWORD ) limit;

	bReadStatus = ReadFile ( m_hCom, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead );

	// ��ѯ�첽��ȡ�Ƿ���ɣ�δ��������ȴ�
	if ( !bReadStatus ) {
		if ( GetLastError() == ERROR_IO_PENDING ) {
			WaitForSingleObject ( m_OverlappedRead.hEvent, 4000 );
			return ( ( int ) dwBytesRead );
		}

		return ( 0 );
	}

	return ( ( int ) dwBytesRead );
}

int SerialPort::SendData( const char *buffer, int size)
{
	if ( !m_bOpen || m_hCom == NULL ) return ( 0 );

	DWORD dwBytesWritten = 0;
	int i;

	for ( i=0; i<size; i++ ) {
		WriteCommByte ( buffer[i] );
		dwBytesWritten++;
	}

	return ( ( int ) dwBytesWritten );
}

int SerialPort::ReadDataWaiting( void )
{
	if ( !m_bOpen || m_hCom == NULL ) return ( 0 );

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError ( m_hCom, &dwErrorFlags, &ComStat );

	return ( ( int ) ComStat.cbInQue );
}

BOOL SerialPort::WriteCommByte(unsigned char ucByte)
{
	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile(m_hCom, (LPSTR)&ucByte, 1, &dwBytesWritten, &m_OverlappedWrite);

	// ��ѯ�첽д���Ƿ���ɣ�δ��������ȴ�
	if ( !bWriteStat && ( GetLastError() == ERROR_IO_PENDING ) ) {
		if ( WaitForSingleObject ( m_OverlappedWrite.hEvent, 2000 ) )
			dwBytesWritten = 0;
		else {
			GetOverlappedResult ( m_hCom, &m_OverlappedWrite, &dwBytesWritten, FALSE );
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}

	return ( TRUE );
}
