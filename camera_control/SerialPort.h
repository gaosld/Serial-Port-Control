#pragma once

class SerialPort
{
public:
	SerialPort(void);
	~SerialPort(void);

	BOOL Open(int nPort = 4, int nBaud = 2400);
	BOOL Close ( void );

	int ReadData ( void *buffer, int limit);
	int SendData ( const char *buffer, int size);
	int ReadDataWaiting ( void );	// 查询缓冲区内是否有未读取的数据

	BOOL IsOpened ( void ) {
		return ( m_bOpen );
	}

private:
	BOOL WriteCommByte ( unsigned char ucByte);	//内部实现，向串口写数据
	HANDLE m_hCom;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	BOOL m_bOpen;
};

