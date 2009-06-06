object MainForm: TMainForm
  Left = 248
  Top = 81
  Width = 740
  Height = 690
  Caption = 'Smartcom'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  ShowHint = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object OpenComLed: TComLed
    Left = 111
    Top = 0
    Width = 25
    Height = 25
    ComPort = ComPort
    LedSignal = lsConn
    Kind = lkRedLight
  end
  object OpenLabel: TLabel
    Left = 135
    Top = 6
    Width = 26
    Height = 13
    Caption = 'Open'
  end
  object InOutPanel: TPanel
    Left = 0
    Top = 84
    Width = 732
    Height = 533
    Align = alClient
    Constraints.MinWidth = 732
    TabOrder = 0
    object Splitter: TSplitter
      Left = 1
      Top = 328
      Width = 730
      Height = 2
      Cursor = crVSplit
      Align = alBottom
    end
    object InPanel: TPanel
      Left = 1
      Top = 1
      Width = 730
      Height = 327
      Align = alClient
      BevelInner = bvLowered
      BevelOuter = bvNone
      TabOrder = 0
      object InMemo: TMemo
        Left = 1
        Top = 31
        Width = 728
        Height = 295
        Align = alClient
        BevelInner = bvNone
        Color = clBlack
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Fixedsys'
        Font.Style = []
        Lines.Strings = (
          '')
        ParentFont = False
        PopupMenu = InPopupMenu
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object InControlPanel: TPanel
        Left = 1
        Top = 1
        Width = 728
        Height = 30
        Align = alTop
        BevelOuter = bvNone
        Constraints.MaxHeight = 30
        Constraints.MinHeight = 30
        TabOrder = 1
        object InSmartSpeedButton: TSpeedButton
          Left = 582
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 2
          Caption = 'Smart'
          Transparent = False
        end
        object InHexSpeedButton: TSpeedButton
          Left = 547
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 2
          Caption = 'Hex'
          Transparent = False
        end
        object InCharSpeedButton: TSpeedButton
          Left = 512
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 2
          Down = True
          Caption = 'Char'
          Transparent = False
        end
        object HoldSpeedButton: TSpeedButton
          Left = 3
          Top = 3
          Width = 33
          Height = 22
          AllowAllUp = True
          GroupIndex = 5
          Caption = 'Hold'
          Transparent = False
          OnClick = HoldSpeedButtonClick
        end
        object TimeSpeedButton: TSpeedButton
          Left = 40
          Top = 3
          Width = 33
          Height = 22
          AllowAllUp = True
          GroupIndex = 7
          Caption = 'Time'
          Transparent = False
          OnClick = TimeSpeedButtonClick
        end
        object LfSpeedButton: TSpeedButton
          Left = 632
          Top = 3
          Width = 41
          Height = 22
          AllowAllUp = True
          GroupIndex = 8
          Down = True
          Caption = '\n (10)'
          Transparent = False
        end
        object CrSpeedButton: TSpeedButton
          Left = 676
          Top = 3
          Width = 41
          Height = 22
          AllowAllUp = True
          GroupIndex = 9
          Down = True
          Caption = '\r (13)'
          Transparent = False
        end
        object CaptureLabel: TLabel
          Left = 335
          Top = 7
          Width = 40
          Height = 13
          Caption = '&Capture:'
          FocusControl = CaptureEdit
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object CaptureResetSpeedButton: TSpeedButton
          Left = 476
          Top = 3
          Width = 16
          Height = 22
          AllowAllUp = True
          Caption = '&0'
          Transparent = False
          OnClick = CaptureResetSpeedButtonClick
        end
        object CaptureEdit: TEdit
          Left = 378
          Top = 4
          Width = 37
          Height = 21
          TabStop = False
          MaxLength = 3
          TabOrder = 0
          Text = '13'
        end
        object CaptureCountEdit: TEdit
          Left = 419
          Top = 4
          Width = 54
          Height = 21
          Hint = 'Double click to clear the counter'
          TabStop = False
          Color = clMenu
          ReadOnly = True
          TabOrder = 1
        end
        object InLedsPanel: TPanel
          Left = 88
          Top = -1
          Width = 244
          Height = 31
          BevelOuter = bvNone
          TabOrder = 2
          object CtsComLed: TComLed
            Left = 2
            Top = 3
            Width = 25
            Height = 25
            ComPort = ComPort
            LedSignal = lsCTS
            Kind = lkRedLight
          end
          object CtsLabel: TLabel
            Left = 27
            Top = 9
            Width = 21
            Height = 13
            Caption = 'CTS'
          end
          object DsrComLed: TComLed
            Left = 47
            Top = 3
            Width = 25
            Height = 25
            ComPort = ComPort
            LedSignal = lsDSR
            Kind = lkRedLight
          end
          object DsrLabel: TLabel
            Left = 73
            Top = 9
            Width = 23
            Height = 13
            Caption = 'DSR'
          end
          object CdComLed: TComLed
            Left = 97
            Top = 3
            Width = 25
            Height = 25
            ComPort = ComPort
            LedSignal = lsRLSD
            Kind = lkRedLight
          end
          object CdLabel: TLabel
            Left = 123
            Top = 9
            Width = 15
            Height = 13
            Caption = 'CD'
          end
          object RingComLed: TComLed
            Left = 145
            Top = 3
            Width = 27
            Height = 25
            ComPort = ComPort
            LedSignal = lsRing
            Kind = lkRedLight
          end
          object RingLabel: TLabel
            Left = 172
            Top = 9
            Width = 22
            Height = 13
            Caption = 'Ring'
          end
          object RxComLed: TComLed
            Left = 200
            Top = 3
            Width = 25
            Height = 25
            ComPort = ComPort
            LedSignal = lsRx
            Kind = lkGreenLight
          end
          object RxLabel: TLabel
            Left = 225
            Top = 9
            Width = 13
            Height = 13
            Caption = 'Rx'
          end
        end
      end
      object ModeEdit: TEdit
        Left = 16
        Top = 80
        Width = 121
        Height = 21
        TabOrder = 2
        Text = 'Serial'
        Visible = False
      end
    end
    object OutPanel: TPanel
      Left = 1
      Top = 330
      Width = 730
      Height = 202
      Align = alBottom
      BevelInner = bvLowered
      BevelOuter = bvNone
      TabOrder = 1
      object OutPanelSplitter: TSplitter
        Left = 1
        Top = 102
        Width = 728
        Height = 2
        Cursor = crVSplit
        Align = alBottom
      end
      object OutControlPanel: TPanel
        Left = 1
        Top = 1
        Width = 728
        Height = 30
        Align = alTop
        Constraints.MaxHeight = 30
        Constraints.MinHeight = 30
        TabOrder = 1
        object OutCharSpeedButton: TSpeedButton
          Left = 144
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 1
          Down = True
          Caption = 'Char'
          Transparent = False
        end
        object OutHexSpeedButton: TSpeedButton
          Left = 179
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 1
          Caption = 'Hex'
          Transparent = False
        end
        object OutSmartSpeedButton: TSpeedButton
          Left = 214
          Top = 3
          Width = 33
          Height = 22
          GroupIndex = 1
          Caption = 'Smart'
          Transparent = False
        end
        object SendFileSpeedButton: TSpeedButton
          Left = 270
          Top = 3
          Width = 51
          Height = 22
          AllowAllUp = True
          Caption = 'Send &file'
          Transparent = False
          OnClick = SendFileSpeedButtonClick
        end
        object OutLedslPanel: TPanel
          Left = 0
          Top = 0
          Width = 129
          Height = 29
          BevelOuter = bvNone
          TabOrder = 0
          object RtsSpeedButton: TSpeedButton
            Left = 51
            Top = 3
            Width = 33
            Height = 22
            AllowAllUp = True
            GroupIndex = 4
            Caption = 'RTS'
            Transparent = False
            OnClick = RtsSpeedButtonClick
          end
          object DtrSpeedButton: TSpeedButton
            Left = 86
            Top = 3
            Width = 33
            Height = 22
            AllowAllUp = True
            GroupIndex = 3
            Down = True
            Caption = 'DTR'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            Transparent = False
            OnClick = DtrSpeedButtonClick
          end
          object TxComLed: TComLed
            Left = 2
            Top = 3
            Width = 25
            Height = 22
            ComPort = ComPort
            LedSignal = lsTx
            Kind = lkGreenLight
          end
          object TxLabel: TLabel
            Left = 26
            Top = 7
            Width = 12
            Height = 13
            Caption = 'Tx'
          end
        end
      end
      object OutMemo: TMemo
        Left = 1
        Top = 31
        Width = 728
        Height = 71
        Align = alClient
        Color = clBlack
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clLime
        Font.Height = -11
        Font.Name = 'Fixedsys'
        Font.Style = []
        ParentFont = False
        PopupMenu = OutPopupMenu
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
        OnKeyPress = OutMemoKeyPress
      end
      object OutDataEditPanel: TPanel
        Left = 1
        Top = 104
        Width = 728
        Height = 97
        Align = alBottom
        Constraints.MinHeight = 41
        TabOrder = 2
        object OutDataEditMemo: TMemo
          Left = 1
          Top = 31
          Width = 726
          Height = 65
          Align = alClient
          Color = clBlack
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Fixedsys'
          Font.Style = []
          ParentFont = False
          ScrollBars = ssBoth
          TabOrder = 0
        end
        object OutDataEditSerivePanel: TPanel
          Left = 1
          Top = 1
          Width = 726
          Height = 30
          Align = alTop
          Constraints.MaxHeight = 30
          Constraints.MinHeight = 30
          TabOrder = 1
          object OutDataEditHexSpeedButton: TSpeedButton
            Left = 38
            Top = 3
            Width = 33
            Height = 22
            GroupIndex = 9
            Caption = 'Hex'
            Transparent = False
          end
          object OutDataEditCharSpeedButton: TSpeedButton
            Left = 3
            Top = 3
            Width = 33
            Height = 22
            GroupIndex = 9
            Down = True
            Caption = 'Char'
            Transparent = False
          end
          object OutDataEditSmartSpeedButton: TSpeedButton
            Left = 73
            Top = 3
            Width = 33
            Height = 22
            GroupIndex = 9
            Caption = 'Smart'
            Transparent = False
          end
          object OutDataEditSendSpeedButton: TSpeedButton
            Left = 129
            Top = 3
            Width = 48
            Height = 22
            Caption = '&Send'
            Transparent = False
            OnClick = OutDataEditSendSpeedButtonClick
          end
        end
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 617
    Width = 732
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object SerialControlPanel: TPanel
    Left = 0
    Top = 0
    Width = 732
    Height = 28
    Align = alTop
    TabOrder = 2
    object SerialOpenedSpeedButton: TSpeedButton
      Left = 4
      Top = 3
      Width = 53
      Height = 22
      AllowAllUp = True
      GroupIndex = 20
      Caption = '&Open'
      Transparent = False
      OnClick = SerialOpenedSpeedButtonClick
    end
    object SerialSettingsSpeedButton: TSpeedButton
      Left = 60
      Top = 3
      Width = 53
      Height = 22
      AllowAllUp = True
      GroupIndex = 50
      Caption = 'S&ettings'
      Transparent = False
      OnClick = SerialSettingsSpeedButtonClick
    end
    object ManualSerialPortLabeledEdit: TLabeledEdit
      Left = 172
      Top = 4
      Width = 49
      Height = 21
      EditLabel.Width = 47
      EditLabel.Height = 13
      EditLabel.Caption = 'Serial port'
      LabelPosition = lpLeft
      LabelSpacing = 5
      TabOrder = 0
    end
  end
  object TcpServerControlPanel: TPanel
    Left = 0
    Top = 28
    Width = 732
    Height = 28
    Align = alTop
    TabOrder = 3
    Visible = False
    object ServerOpenedSpeedButton: TSpeedButton
      Left = 3
      Top = 3
      Width = 54
      Height = 22
      AllowAllUp = True
      GroupIndex = 20
      Caption = 'S&tart'
      Transparent = False
      OnClick = ServerOpenedSpeedButtonClick
    end
    object ServerPortLabeledEdit: TLabeledEdit
      Left = 88
      Top = 4
      Width = 49
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = '&Port'
      LabelPosition = lpLeft
      LabelSpacing = 5
      TabOrder = 0
    end
  end
  object TcpClientControlPanel: TPanel
    Left = 0
    Top = 56
    Width = 732
    Height = 28
    Align = alTop
    TabOrder = 4
    Visible = False
    object ClientOpenedSpeedButton: TSpeedButton
      Left = 3
      Top = 3
      Width = 54
      Height = 22
      AllowAllUp = True
      GroupIndex = 30
      Caption = 'Co&nnect'
      Transparent = False
      OnClick = ClientOpenedSpeedButtonClick
    end
    object ClientAddressLabeledEdit: TLabeledEdit
      Left = 112
      Top = 4
      Width = 97
      Height = 21
      EditLabel.Width = 38
      EditLabel.Height = 13
      EditLabel.Caption = '&Address'
      LabelPosition = lpLeft
      LabelSpacing = 5
      TabOrder = 0
    end
    object ClientPortLabeledEdit: TLabeledEdit
      Left = 240
      Top = 4
      Width = 49
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = 'Po&rt'
      LabelPosition = lpLeft
      LabelSpacing = 5
      TabOrder = 1
    end
  end
  object ConnectingPanel: TPanel
    Left = 288
    Top = 176
    Width = 185
    Height = 41
    Caption = 'Connecting...'
    TabOrder = 5
    Visible = False
  end
  object ComPort: TComPort
    BaudRate = br57600
    Port = 'COM1'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    Timeouts.ReadInterval = 1
    OnRxChar = ComPortRxChar
    Left = 696
    Top = 104
  end
  object MainMenu: TMainMenu
    Left = 632
    Top = 104
    object ModeMenuItem: TMenuItem
      Tag = -1
      Caption = '&Mode'
      GroupIndex = 1
      object SerialMenuItem: TMenuItem
        AutoCheck = True
        Caption = '&RS232'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = SerialMenuItemClick
      end
      object TcpServerMenuItem: TMenuItem
        AutoCheck = True
        Caption = 'TCP/IP &Server'
        GroupIndex = 1
        RadioItem = True
        OnClick = TcpServerMenuItemClick
      end
      object TcpClientMenuItem: TMenuItem
        AutoCheck = True
        Caption = 'TCP/IP &Client'
        GroupIndex = 1
        RadioItem = True
        OnClick = TcpClientMenuItemClick
      end
      object N1: TMenuItem
        Caption = '-'
        GroupIndex = 1
      end
      object FontMenuItem: TMenuItem
        Tag = -1
        Caption = '&Font'
        GroupIndex = 1
        OnClick = FontMenuItemClick
      end
    end
    object AboutMenuItem: TMenuItem
      Caption = '?'
      GroupIndex = 1
      OnClick = AboutMenuItemClick
    end
  end
  object OutPopupMenu: TPopupMenu
    Left = 664
    Top = 136
    object DelimiterOutPopupMenuItem: TMenuItem
      Caption = '&Delimiter'
      ShortCut = 16460
      OnClick = DelimiterInPopupMenuItemClick
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object OutClearPopupMenuItem: TMenuItem
      Caption = '&Clear'
      OnClick = OutClearPopupMenuItemClick
    end
    object OutSavePopupMenuItem: TMenuItem
      Caption = 'Save to file'
      OnClick = OutSavePopupMenuItemClick
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object CtrlInsOutPopupMenuItem: TMenuItem
      Caption = '&Copy'
      ShortCut = 16429
      OnClick = CtrlCOutPopupMenuItemClick
    end
    object ShiftInsOutPopupMenuItem: TMenuItem
      Caption = '&Paste'
      ShortCut = 8237
      OnClick = CtrlVOutPopupMenuItemClick
    end
  end
  object InPopupMenu: TPopupMenu
    Left = 664
    Top = 104
    object DelimiterInPopupMenuItem: TMenuItem
      Caption = '&Delimiter'
      ShortCut = 16452
      OnClick = DelimiterInPopupMenuItemClick
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object InClearPopupMenuItem: TMenuItem
      Caption = '&Clear'
      OnClick = InClearPopupMenuItemClick
    end
    object InSavePopupMenuItem: TMenuItem
      Caption = '&Save to file'
      OnClick = InSavePopupMenuItemClick
    end
    object N5: TMenuItem
      Caption = '-'
    end
    object CtrlInsInPopupMenuItem: TMenuItem
      Caption = '&Copy'
      ShortCut = 16429
      OnClick = CtrlCInPopupMenuItemClick
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '.log'
    InitialDir = '.'
    Title = 'Select file'
    Left = 696
    Top = 136
  end
  object FontDialog: TFontDialog
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clLime
    Font.Height = -13
    Font.Name = 'Fixedsys'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 632
    Top = 136
  end
  object ApplicationEvents: TApplicationEvents
    OnException = ApplicationEventsException
    Left = 632
    Top = 168
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ServerSocketClientConnect
    OnClientDisconnect = ServerSocketClientDisconnect
    OnClientRead = ServerSocketClientRead
    Left = 664
    Top = 168
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocketConnect
    OnDisconnect = ClientSocketDisconnect
    OnRead = ServerSocketClientRead
    Left = 696
    Top = 168
  end
  object Timer: TTimer
    Interval = 500
    OnTimer = TimerTimer
    Left = 632
    Top = 200
  end
end
