//---------------------------------------------------------------------------

#ifndef _MAIN_H
#define _MAIN_H
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <ScktComp.hpp>
#include "CPort.hpp"
#include "CPortCtl.hpp"
//---------------------------------------------------------------------------

class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TComPort *ComPort;
   TComLed *OpenComLed;
   TLabel *OpenLabel;
   TPanel *InOutPanel;
   TPanel *InPanel;
   TMemo *InMemo;
   TPanel *InControlPanel;
   TPanel *OutPanel;
   TPanel *OutControlPanel;
   TMemo *OutMemo;
   TSplitter *Splitter;
   TEdit *CaptureEdit;
   TEdit *CaptureCountEdit;
   TPanel *OutDataEditPanel;
   TMemo *OutDataEditMemo;
   TSplitter *OutPanelSplitter;
   TStatusBar *StatusBar;
   TMainMenu *MainMenu;
   TMenuItem *AboutMenuItem;
   TPopupMenu *OutPopupMenu;
   TMenuItem *ShiftInsOutPopupMenuItem;
   TSpeedButton *OutCharSpeedButton;
   TSpeedButton *OutHexSpeedButton;
   TSpeedButton *OutSmartSpeedButton;
   TSpeedButton *InSmartSpeedButton;
   TSpeedButton *InHexSpeedButton;
   TSpeedButton *InCharSpeedButton;
   TPanel *SerialControlPanel;
   TSpeedButton *HoldSpeedButton;
   TMenuItem *OutClearPopupMenuItem;
   TMenuItem *OutSavePopupMenuItem;
   TPopupMenu *InPopupMenu;
   TMenuItem *InClearPopupMenuItem;
   TMenuItem *InSavePopupMenuItem;
   TOpenDialog *OpenDialog;
   TSpeedButton *SerialOpenedSpeedButton;
   TSpeedButton *SerialSettingsSpeedButton;
   TSpeedButton *TimeSpeedButton;
   TSpeedButton *LfSpeedButton;
   TSpeedButton *CrSpeedButton;
   TMenuItem *CtrlInsOutPopupMenuItem;
   TMenuItem *CtrlInsInPopupMenuItem;
   TLabel *CaptureLabel;
   TMenuItem *DelimiterInPopupMenuItem;
   TMenuItem *DelimiterOutPopupMenuItem;
   TSpeedButton *SendFileSpeedButton;
   TPanel *OutDataEditSerivePanel;
   TSpeedButton *OutDataEditHexSpeedButton;
   TSpeedButton *OutDataEditCharSpeedButton;
   TSpeedButton *OutDataEditSmartSpeedButton;
   TSpeedButton *OutDataEditSendSpeedButton;
   TFontDialog *FontDialog;
   TSpeedButton *CaptureResetSpeedButton;
   TMenuItem *SerialMenuItem;
   TMenuItem *TcpServerMenuItem;
   TMenuItem *TcpClientMenuItem;
   TMenuItem *ModeMenuItem;
   TMenuItem *FontMenuItem;
   TPanel *TcpServerControlPanel;
   TPanel *TcpClientControlPanel;
   TEdit *ModeEdit;
   TSpeedButton *ServerOpenedSpeedButton;
   TLabeledEdit *ServerPortLabeledEdit;
   TSpeedButton *ClientOpenedSpeedButton;
   TLabeledEdit *ClientAddressLabeledEdit;
   TLabeledEdit *ClientPortLabeledEdit;
   TMenuItem *N1;
   TMenuItem *N2;
   TMenuItem *N3;
   TMenuItem *N4;
   TMenuItem *N5;
   TPanel *OutLedslPanel;
   TSpeedButton *RtsSpeedButton;
   TSpeedButton *DtrSpeedButton;
   TComLed *TxComLed;
   TLabel *TxLabel;
   TPanel *InLedsPanel;
   TComLed *CtsComLed;
   TLabel *CtsLabel;
   TComLed *DsrComLed;
   TLabel *DsrLabel;
   TComLed *CdComLed;
   TLabel *CdLabel;
   TComLed *RingComLed;
   TLabel *RingLabel;
   TComLed *RxComLed;
   TLabel *RxLabel;
   TApplicationEvents *ApplicationEvents;
   TServerSocket *ServerSocket;
   TClientSocket *ClientSocket;
   TPanel *ConnectingPanel;
   TTimer *Timer;
   TLabeledEdit *ManualSerialPortLabeledEdit;
   void __fastcall OutMemoKeyPress(TObject *Sender, char &Key);
   void __fastcall ComPortRxChar(TObject *Sender, int Count);
   void __fastcall CtrlVOutPopupMenuItemClick(TObject *Sender);
   void __fastcall DtrSpeedButtonClick(TObject *Sender);
   void __fastcall RtsSpeedButtonClick(TObject *Sender);
   void __fastcall ClearOutButtonClick(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall OutClearPopupMenuItemClick(TObject *Sender);
   void __fastcall InClearPopupMenuItemClick(TObject *Sender);
   void __fastcall InSavePopupMenuItemClick(TObject *Sender);
   void __fastcall OutSavePopupMenuItemClick(TObject *Sender);
   void __fastcall SendOutDataEditPopupMenuItemClick(TObject *Sender);
   void __fastcall SerialOpenedSpeedButtonClick(TObject *Sender);
   void __fastcall SerialSettingsSpeedButtonClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall HoldSpeedButtonClick(TObject *Sender);
   void __fastcall CtrlCOutPopupMenuItemClick(TObject *Sender);
   void __fastcall CtrlCInPopupMenuItemClick(TObject *Sender);
   void __fastcall CtrlVOutDataEditPopupMenuItemClick(TObject *Sender);
   void __fastcall TimeSpeedButtonClick(TObject *Sender);
   void __fastcall DelimiterInPopupMenuItemClick(TObject *Sender);
   void __fastcall SendFileSpeedButtonClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall AboutMenuItemClick(TObject *Sender);
   void __fastcall OutDataEditSendSpeedButtonClick(TObject *Sender);
   void __fastcall CaptureResetSpeedButtonClick(TObject *Sender);
   void __fastcall FontMenuItemClick(TObject *Sender);
   void __fastcall SerialMenuItemClick(TObject *Sender);
   void __fastcall TcpServerMenuItemClick(TObject *Sender);
   void __fastcall TcpClientMenuItemClick(TObject *Sender);
   void __fastcall ApplicationEventsException(TObject *Sender,
          Exception *E);
   void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ServerOpenedSpeedButtonClick(TObject *Sender);
   void __fastcall ClientOpenedSpeedButtonClick(TObject *Sender);
   void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
   int captureCount;
   int timeCount;

   int getCaptureChar();

   void putMemoChar(TMemo* memo, int ch);
   void putMemoStr(TMemo* memo, const AnsiString& str);
   
   void sendOutData(const AnsiString& data);
   
   void storeSettings();
   void loadSettings();

   void dtr(bool state);
   void rts(bool state);

   void updateStatusBar();

   AnsiString inifile;

   TCustomWinSocket* endpoint;

   int connectedCount;
   bool connecting;

   void processIncomingData(const AnsiString& data);

public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
   void InvalidateMode();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
