//---------------------------------------------------------------------------

#define SetPortA SetPort

#include <vcl.h>
#include <Clipbrd.hpp>
#include <IniFiles.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>

#include <cstdio>
#include <ctime>

#pragma hdrstop

#include "main.h"
#include "formload.h"
#include "strutils.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "CPort"
#pragma link "CPortCtl"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
   CaptureCountEdit->Text = captureCount = 0;
   timeCount = 0;

   InMemo->DoubleBuffered = true;
   OutMemo->DoubleBuffered = true;

   connectedCount = false;
   endpoint = NULL;

   connecting = false;

   inifile = ChangeFileExt(Application->ExeName, ".ini");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OutMemoKeyPress(TObject *Sender, char &Key)
{
   sendOutData(Key);
}
//---------------------------------------------------------------------------

int TMainForm::getCaptureChar()
{
   CaptureEdit->Text = CaptureEdit->Text.Trim();
   AnsiString capture = CaptureEdit->Text;

   if (capture == '*')
      return -1;

   if (capture.Length() >= 3 && capture[1] == '\'' && capture == '\'')
      return CaptureEdit->Text[2];

   int result;

   if (capture.Length() >= 3 && capture.SubString(1, 2) == "0x")
      if (std::sscanf(capture.c_str(), "%x", &result) == 1)
         return result;

   if (std::sscanf(capture.c_str(), "%d", &result) == 1)
      return result;

   CaptureEdit->Text = '*';
   return -1;
}
//---------------------------------------------------------------------------

void TMainForm::putMemoChar(TMemo* memo, int ch)
{
   if (!CrSpeedButton->Down && ch == '\r' && memo == InMemo)
      return;

   if (!LfSpeedButton->Down && ch == '\n' && memo == InMemo)
      return;

   if (ch == '\n' || ch == '\r')
      memo->Lines->Add("");
   else {
      if (memo->Lines->Count == 0)
         memo->Lines->Add("");

      AnsiString current = memo->Lines->Strings[ memo->Lines->Count - 1 ];
      memo->Lines->Strings[ memo->Lines->Count - 1 ] = current + (char)ch;
   }

   memo->Perform(EM_LINESCROLL, 0, memo->Lines->Count);
}
//---------------------------------------------------------------------------

void TMainForm::putMemoStr(TMemo* memo, const AnsiString& str)
{
   if (str.Length() == 0)
      return;

   memo->Lines->BeginUpdate();
   for (int i = 1; i < str.Length(); i++)
      putMemoChar(memo, str[ i ]);
   memo->Lines->EndUpdate();
   putMemoChar(memo, str[ str.Length() ]);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComPortRxChar(TObject *Sender, int Count)
{
   if (HoldSpeedButton->Down)
      return;

   AnsiString data;

   ComPort->ReadStr(data, Count);

   processIncomingData(data);
}
//---------------------------------------------------------------------------

void TMainForm::processIncomingData(const AnsiString& data)
{
   timeCount += data.Length();

   int captureChar = getCaptureChar();

   if (captureChar == -1)
      captureCount += data.Length();
   else
      for (int i = 1; i <= data.Length(); i++)
         if (data[ i ] == captureChar)
            captureCount += 1;

   CaptureCountEdit->Text = captureCount;

   AnsiString prepared = "?";

   if (InCharSpeedButton->Down)
      prepared = data;

   if (InHexSpeedButton->Down)
      prepared = hexDump(data, " ");

   if (InSmartSpeedButton->Down)
      prepared = smartHexDump(data);

   if (TimeSpeedButton->Down) {
      prepared = AnsiString().sprintf(
         "[%s,%d]> ", 
         Date().CurrentTime().FormatString("hh:nn:ss").c_str(), 
         timeCount
     ) + prepared;
      timeCount = 0;
   }

   putMemoStr(InMemo, prepared);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CtrlVOutPopupMenuItemClick(TObject *Sender)
{
   if (Clipboard()->HasFormat(CF_TEXT))
      sendOutData(Clipboard()->AsText);
}
//---------------------------------------------------------------------------

void TMainForm::sendOutData(const AnsiString& data)
{
   if (ModeEdit->Text == "Serial") {
      if (!ComPort->Connected) return;
      ComPort->WriteStr(data);
   } else {
      if (!endpoint) return;
      endpoint->SendText(data);
   }

   AnsiString prepared = "?";

   if (OutCharSpeedButton->Down)
      prepared = data;

   if (OutHexSpeedButton->Down)
      prepared = hexDump(data, " ");

   if (OutSmartSpeedButton->Down)
      prepared = smartHexDump(data);

   putMemoStr(OutMemo, prepared);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DtrSpeedButtonClick(TObject *Sender)
{
   dtr(DtrSpeedButton->Down);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RtsSpeedButtonClick(TObject *Sender)
{
   rts(RtsSpeedButton->Down);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearOutButtonClick(TObject *Sender)
{
   OutMemo->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == 0x04 && ActiveControl != OutMemo)
      DelimiterInPopupMenuItemClick(Sender);

   if (ActiveControl == InMemo) {
      ActiveControl = OutMemo;
      OutMemoKeyPress(Sender, Key);
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OutClearPopupMenuItemClick(TObject *Sender)
{
   OutMemo->Clear();   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InClearPopupMenuItemClick(TObject *Sender)
{
   InMemo->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InSavePopupMenuItemClick(TObject *Sender)
{
   if (OpenDialog->Execute())
      InMemo->Lines->SaveToFile(OpenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OutSavePopupMenuItemClick(TObject *Sender)
{
   if (OpenDialog->Execute())
      OutMemo->Lines->SaveToFile(OpenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SendOutDataEditPopupMenuItemClick(
      TObject *Sender)
{
   sendOutData(OutDataEditMemo->Lines->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SerialOpenedSpeedButtonClick(TObject *Sender)
{
   InvalidateMode();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SerialSettingsSpeedButtonClick(TObject *Sender)
{
   SerialSettingsSpeedButton->Down = true;
   try {
      if (ManualSerialPortLabeledEdit->Text.Length())
         ComPort->Port = ManualSerialPortLabeledEdit->Text;
      ComPort->ShowSetupDialog();
      if (ComPort->Port.Length())
         ManualSerialPortLabeledEdit->Text = ComPort->Port;
   } __finally {
      SerialSettingsSpeedButton->Down = false;
   }
   if (ComPort->Connected) {
      ComPort->SetDTR(DtrSpeedButton->Down);
      ComPort->SetRTS(RtsSpeedButton->Down);
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   storeSettings();
   ComPort->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HoldSpeedButtonClick(TObject *Sender)
{
   if (ModeEdit->Text == "Serial") {
      if (!HoldSpeedButton->Down && ComPort->Connected && ComPort->InputCount())
         ComPortRxChar(Sender, ComPort->InputCount());
   } else {
      if (!HoldSpeedButton->Down && endpoint && endpoint->ReceiveLength()) {
         char buf[ 10240 ];
         endpoint->ReceiveBuf(buf, endpoint->ReceiveLength());
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CtrlCOutPopupMenuItemClick(TObject *Sender)
{
   OutMemo->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CtrlCInPopupMenuItemClick(
      TObject *Sender)
{
   InMemo->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CtrlVOutDataEditPopupMenuItemClick(
      TObject *Sender)
{
   if (Clipboard()->HasFormat(CF_TEXT))
      putMemoStr(OutDataEditMemo, Clipboard()->AsText);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimeSpeedButtonClick(TObject *Sender)
{
   if (TimeSpeedButton->Down)
      timeCount = 0;   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DelimiterInPopupMenuItemClick(TObject *Sender)
{
   AnsiString delimiter = 
      Date().CurrentTime().FormatString(
         "-------------- hh:nn:ss --------------");

   if (InMemo->Lines->Strings[ InMemo->Lines->Count - 1 ].Length())
      InMemo->Lines->Add(delimiter);
   else
      InMemo->Lines->Strings[ InMemo->Lines->Count - 1 ] = delimiter;

   InMemo->Lines->Add("");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SendFileSpeedButtonClick(TObject *Sender)
{
    if (!OpenDialog->Execute())
       return;

    std::ifstream is(OpenDialog->FileName.c_str());

    char buf[ 1024 ];

    while (is) {
       int sz = is.readsome(buf, sizeof buf);
       if (!sz)
          break;
       sendOutData(AnsiString(buf, sz));
       Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void TMainForm::storeSettings()
{
   ComPort->StoreSettings(stIniFile, inifile);

   FormLoader::store(this, inifile);
}
//---------------------------------------------------------------------------

void TMainForm::loadSettings()
{
   ComPort->LoadSettings(stIniFile, inifile);

   FormLoader::restore(this, inifile);

   InvalidateMode();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   loadSettings();
}
//---------------------------------------------------------------------------

void TMainForm::dtr(bool state)
{
   DtrSpeedButton->Down = state;
   DtrSpeedButton->Font->Color = state ? clRed : clWindowText;

   if (ComPort->Connected)
      ComPort->SetDTR(state);
}
//---------------------------------------------------------------------------

void TMainForm::rts(bool state)
{
   RtsSpeedButton->Down = state;
   RtsSpeedButton->Font->Color = state ? clRed : clWindowText;

   if (ComPort->Connected)
      ComPort->SetRTS(state);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutMenuItemClick(TObject *Sender)
{
   AnsiString revision = "3.0";
   Application->MessageBox(
      AnsiString(
         AnsiString("Smart communication terminal debugger\n\n") +
         AnsiString("Copyright (C) 2004-2009 by Alexander Demin\n\n") +
         AnsiString("Version ") +
         AnsiString(revision)
     ).c_str(),
      "About", MB_OK
  );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OutDataEditSendSpeedButtonClick(TObject *Sender)
{
   AnsiString data = OutDataEditMemo->Lines->Text;

   AnsiString prepared = "?";

   if (OutDataEditCharSpeedButton->Down)
      prepared = data;

   if (OutDataEditHexSpeedButton->Down)
      prepared = hexPack(data);

   if (OutDataEditSmartSpeedButton->Down)
      prepared = smartHexPack(data);

   sendOutData(prepared);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CaptureResetSpeedButtonClick(TObject *Sender)
{
   CaptureCountEdit->Text = captureCount = 0;
}
//---------------------------------------------------------------------------

void TMainForm::updateStatusBar()
{
   if (ModeEdit->Text == "Serial") {
   
      AnsiString rates[] = {
         "?",
         "110", "300", "600", "1200", "2400", "4800", "9600",
         "14400", "19200", "38400", "56000", "57600", "115200",
         "128000", "256000"
      };
      AnsiString bits[] = { "5", "6", "7", "8" };
      AnsiString parity[] = { "N", "O", "E", "M", "S" };
      AnsiString stopbits[] = { "1", "1.5", "2" };

      StatusBar->SimpleText =
         ComPort->Port + ":" +
         rates[ ComPort->BaudRate ] + ":" +
         bits[ ComPort->DataBits ] +
         parity[ ComPort->Parity->Bits ] +
         stopbits[ ComPort->StopBits ] +
         (ComPort->Connected ? ", opened" : "");

   } else {

      AnsiString base;
      
      if (ServerSocket->Active) {

         base = AnsiString().sprintf("Server mode, listen at port: %d", 
                                     ServerSocket->Port);

         if (endpoint)
            base += AnsiString().sprintf(", connected from %s:%d", 
                                         endpoint->RemoteAddress.c_str(), 
                                         endpoint->RemotePort);
         else
            base += ", not connected";

      } else if (connecting) {

         base = "Connecting...";

      } else if (ClientSocket->Active) {

         base = AnsiString().sprintf("Client mode");

         if (endpoint)
            base += AnsiString().sprintf(", connected to %s:%d", 
                                         ClientSocket->Address.c_str(), 
                                         ClientSocket->Port);
         else
            base += ", not connected";
      } else
         base = "Idle";

      StatusBar->SimpleText = base;
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FontMenuItemClick(TObject *Sender)
{
   if (FontDialog->Execute()) {
      InMemo->Font = FontDialog->Font;
      OutMemo->Font = FontDialog->Font;
      OutDataEditMemo->Font = FontDialog->Font;
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SerialMenuItemClick(TObject *Sender)
{
   ServerSocket->Close();
   ClientSocket->Close();

   InvalidateMode();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TcpServerMenuItemClick(TObject *Sender)
{
   ComPort->Close();
   ClientSocket->Close();

   InvalidateMode();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TcpClientMenuItemClick(TObject *Sender)
{
   ComPort->Close();
   ServerSocket->Close();

   InvalidateMode();
}
//---------------------------------------------------------------------------

void TMainForm::InvalidateMode()
{
   if (SerialMenuItem->Checked) ModeEdit->Text = "Serial";
   if (TcpServerMenuItem->Checked) ModeEdit->Text = "Server";
   if (TcpClientMenuItem->Checked) ModeEdit->Text = "Client";

   SerialControlPanel->Visible = ModeEdit->Text == "Serial";
   OutLedslPanel->Visible = SerialControlPanel->Visible;
   InLedsPanel->Visible = SerialControlPanel->Visible;

   TcpServerControlPanel->Visible = ModeEdit->Text == "Server";
   TcpClientControlPanel->Visible = ModeEdit->Text == "Client";

   Caption = AnsiString("Smart terminal :: ") + ModeEdit->Text + " mode";

   if (ManualSerialPortLabeledEdit->Text.Length())
      ComPort->Port = ManualSerialPortLabeledEdit->Text;

   if (ModeEdit->Text == "Serial") {

      if (SerialOpenedSpeedButton->Down) {

         try {
            try {
               ComPort->Open();
               ConnectingPanel->Show();

               std::time_t started = std::time(NULL);
               while (!ComPort->Connected && std::time(NULL) - started < 5)
                  Application->ProcessMessages();
            } __finally {
               ConnectingPanel->Hide();
            }
         } catch(EComPort& e) {
            SerialOpenedSpeedButton->Down = false;
            Application->MessageBox((AnsiString("Unable to open port ") + ComPort->Port).c_str(), "Error", MB_OK);
            return;
         }

         if (!ComPort->Connected) {
            SerialOpenedSpeedButton->Down = false;
            Application->MessageBox((AnsiString("Unable to open port ") + ComPort->Port).c_str(), "Error", MB_OK);
            return;
         }

         ComPort->SetDTR(DtrSpeedButton->Down);
         ComPort->SetRTS(RtsSpeedButton->Down);

      } else
         ComPort->Close();

   } if (ModeEdit->Text == "Server") {

      ServerSocket->Port = ServerPortLabeledEdit->Text.ToInt();

      if (ServerOpenedSpeedButton->Down)
         ServerSocket->Open();
      else
         ServerSocket->Close();

   } if (ModeEdit->Text == "Client") {

      if (ClientOpenedSpeedButton->Down) {

         ClientSocket->Address = ClientAddressLabeledEdit->Text;
         ClientSocket->Port = ClientPortLabeledEdit->Text.ToInt();
         ClientSocket->Open();

         ConnectingPanel->Show();

         std::time_t started = std::time(NULL);
         while (!ClientSocket->Active && std::time(NULL) - started < 5)
            Application->ProcessMessages();

         ConnectingPanel->Hide();

         if (!ClientSocket->Active) {
            ClientOpenedSpeedButton->Down = true;
            Application->MessageBox("Unable to connect", "Error", MB_OK);
         }

      } else
         ClientSocket->Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApplicationEventsException(TObject *Sender,
      Exception *E)
{
   //   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   connectedCount += 1;

   if (connectedCount > 1) {
      Socket->SendText("Already connected\n");
      Socket->Close();
      return;
   }

   endpoint = Socket;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   connectedCount -= 1;

   if (!connectedCount) endpoint = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
   if (HoldSpeedButton->Down)
      return;

   AnsiString data;

   int sz;
   char buf[ 10240 ];

   while ((sz = Socket->ReceiveBuf(buf, sizeof buf)) > 0)
      data += AnsiString(buf, sz);

   processIncomingData(data);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   endpoint = Socket;   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   endpoint = NULL;
   ClientOpenedSpeedButton->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerOpenedSpeedButtonClick(TObject *Sender)
{
   InvalidateMode();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientOpenedSpeedButtonClick(TObject *Sender)
{
   InvalidateMode();   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimerTimer(TObject *Sender)
{
   updateStatusBar();
}
//---------------------------------------------------------------------------
