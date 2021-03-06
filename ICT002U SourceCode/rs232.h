
class Rs232
{
private:
  unsigned char TxBuff[1];
public:
  int SetComPort(HANDLE &hComm,COMMTIMEOUTS toComm,char *Comm,char *baud);
  //return(0)  COMPort open success
  //return(1)  COMPort open fail
  //return(2)  HANDLE already exist
  void TransferComm(HANDLE &hComm,unsigned char SendData);
  void Exit(HANDLE &hComm);
};

int Rs232::SetComPort(HANDLE &hComm,COMMTIMEOUTS toComm,char *Comm,char *baud)
{
  if(hComm==NULL||hComm==INVALID_HANDLE_VALUE)
  {
    DCB dcbComPort;
    hComm=CreateFile(Comm,
                     GENERIC_READ|GENERIC_WRITE,
                     0,
                     0,
                     OPEN_EXISTING,
                     0,
                     0);
    if(hComm==INVALID_HANDLE_VALUE)
      return(0);
    else
    {
      GetCommTimeouts(hComm,&toComm);
      toComm.ReadIntervalTimeout=50;
      SetCommTimeouts(hComm,&toComm);
      dcbComPort.DCBlength=sizeof(DCB);
      GetCommState(hComm,&dcbComPort);
      BuildCommDCB(baud,&dcbComPort);
      SetCommState(hComm,&dcbComPort);
      return(1);
    }
  }
  else
    return(2);
}

void Rs232::TransferComm(HANDLE &hComm,unsigned char SendData)
{
  TxBuff[0]=SendData;
  WriteFile(hComm,TxBuff,1,&dwAct,NULL);
}

void Rs232::Exit(HANDLE &hComm)
{
  SetCommMask(hComm,0);
  PurgeComm(hComm,PURGE_RXABORT);
  CloseHandle(hComm);
}

