//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
extern HANDLE hCom1;
extern DWORD dwAct;
#include "rs232.h"
extern Rs232 rs232;
extern TCheckBox *check[16];
extern fg_wait_escrow;
extern receive_money;
extern Accept_ON;
extern STACK_MONEY_COUNT;
extern InIdiling;
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall RS232::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall RS232::RS232(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void ReadPortCom1()
{
  unsigned char InBuff[5000];
  DWORD dwBytesRead;
  AnsiString str;

  ReadFile(hCom1,InBuff,4999,&dwBytesRead,NULL);
  if(dwBytesRead==0)
    return;



  for(unsigned int n=0;n<dwBytesRead;n++)
  {
   Application->ProcessMessages();
   switch(InBuff[n])
   {
    case 0x80:
    //case 0x8F:
         if (InBuff[n+1]==0x8F)
         {
           rs232.TransferComm(hCom1,0x02);
           Form1->Label2->Color=clGreen;
           Form1->Label2->Caption="Ready";
           Form1->StatusBar1->Panels->Items[2]->Text="Ready";
         }
    break;
    case 0x3e:
    case 0x5e:
    break;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x27:
    case 0x28:
         Form1->Label2->Color=clRed;
         Form1->Label2->Caption="Error";
         Form1->StatusBar1->Panels->Items[2]->Text="Error";
    break;
    case 0x29:
         InIdiling=1;
         if(Accept_ON==1)
         {
           //Form1->Edit1->Text=0;
           Accept_ON=0;
           Form1->BitBtn6->Enabled=false;
           Form1->BitBtn7->Enabled=false;
         }
    break;
    case 0x2F:
           InIdiling=1;
           Form1->Label2->Color=clGreen;
           Form1->Label2->Caption="Ready";
           Form1->StatusBar1->Panels->Items[2]->Text="Ready";
    break;
    case 0x10:
         Form1->BitBtn6->Enabled=false;
         Form1->BitBtn7->Enabled=false;
         STACK_MONEY_COUNT++;
         //Form1->Edit1->Text=0;
         Form1->Edit2->Text=Form1->Edit2->Text.ToInt()+receive_money;
         Form1->Edit3->Text=STACK_MONEY_COUNT;
         InIdiling=1;
    break;
    case 0x11:
         Form1->BitBtn6->Enabled=false;
         Form1->BitBtn7->Enabled=false;
         //Form1->Edit1->Text=0;
         InIdiling=1;
    break;
    case 0x81:
         Accept_ON=1;
         InIdiling=0;

         int tttt;
         tttt=(InBuff[n+1]&0x0F)+1;
         switch(tttt)
         {
            case 1:
                 if(Form1->CheckBox1->Checked==true)
                 {
                    receive_money=Form1->CheckBox1->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                      rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                      fg_wait_escrow=1;
                      Form1->BitBtn6->Enabled=true;
                      Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                   rs232.TransferComm(hCom1,0x0F);
                 }
            break;
            case 2: 
            	 if(Form1->CheckBox2->Checked==true)
                 {
                    receive_money=Form1->CheckBox2->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                       rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                       fg_wait_escrow=1;
                       Form1->BitBtn6->Enabled=true;
                       Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                    rs232.TransferComm(hCom1,0x0F);
                 }
            break;
            case 3:
            	 if(Form1->CheckBox3->Checked==true)
                 {
                    receive_money=Form1->CheckBox3->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                       rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                       fg_wait_escrow=1;
                       Form1->BitBtn6->Enabled=true;
                       Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                    rs232.TransferComm(hCom1,0x0F);
                 }
            break;
            case 4:
            	 if(Form1->CheckBox4->Checked==true)
                 {
                    receive_money=Form1->CheckBox4->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                       rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                       fg_wait_escrow=1;
                       Form1->BitBtn6->Enabled=true;
                       Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                    rs232.TransferComm(hCom1,0x0F);
                 }
            break;
            case 5: 
            	 if(Form1->CheckBox5->Checked==true)
                 {
                    receive_money=Form1->CheckBox5->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                       rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                       fg_wait_escrow=1;
                       Form1->BitBtn6->Enabled=true;
                       Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                    rs232.TransferComm(hCom1,0x0F);
                 }
            break;
            case 6: 
            	 if(Form1->CheckBox6->Checked==true)
                 {
                    receive_money=Form1->CheckBox6->Caption.ToInt();
                    Form1->Edit1->Text=receive_money;
                    if(Form1->RadioGroup1->ItemIndex==1)
                    {
                       rs232.TransferComm(hCom1,0x02);
                    }
                    else
                    {
                      fg_wait_escrow=1;
                      Form1->BitBtn6->Enabled=true;
                      Form1->BitBtn7->Enabled=true;
                    }
                 }
                 else
                 {
                    rs232.TransferComm(hCom1,0x0F);
                 }
            break;
         }
         break;
    default:
    break;
   }
  }
}

void __fastcall RS232::Execute()
{
        //---- Place thread code here ----
  DWORD dwErrorCom1;
  COMSTAT  csCom1;

  FreeOnTerminate=true;
  SetCommMask(hCom1,EV_RXCHAR);
  while(1)
  {
    if(Terminated)           
      return;
    ClearCommError(hCom1,&dwErrorCom1,&csCom1);
    if(csCom1.cbInQue)
      ReadPortCom1();
  }
}
//---------------------------------------------------------------------------
