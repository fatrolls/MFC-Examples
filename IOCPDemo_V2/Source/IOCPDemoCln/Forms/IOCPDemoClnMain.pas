unit IOCPDemoClnMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, BaseForm, StdCtrls, ExtCtrls, ComCtrls, ToolWin, Buttons,
  BaseFrame, LogFrame, ClientsFrame, SQLFrame, UploadFrame, DownloadFrame;

type
  TFmIOCPDemoClnMain = class(TFmBase)
    pnlLeft: TPanel;
    btnConnect: TSpeedButton;
    btnDisconnect: TSpeedButton;
    btnLog: TSpeedButton;
    btnClients: TSpeedButton;
    btnSQL: TSpeedButton;
    btnUpload: TSpeedButton;
    btnDownload: TSpeedButton;
    pnl2: TPanel;
    FamLog: TFamLog;
    FamClients: TFamClients;
    FamSQL: TFamSQL;
    FamUpload: TFamUpload;
    FamDownload: TFamDownload;
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnConnectClick(Sender: TObject);
    procedure btnDisconnectClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure btnLogClick(Sender: TObject);
    procedure btnClientsClick(Sender: TObject);
    procedure btnSQLClick(Sender: TObject);
    procedure btnUploadClick(Sender: TObject);
    procedure btnDownloadClick(Sender: TObject);
  private
    { Private declarations }
    procedure UpdateUI(AValue: Boolean);
  public
    { Public declarations }
  end;

var
  FmIOCPDemoClnMain: TFmIOCPDemoClnMain;

implementation

uses LoginForm, DataMgrCtr;

{$R *.dfm}

procedure TFmIOCPDemoClnMain.FormShow(Sender: TObject);
begin
  inherited;
  PostMessage(Handle, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
end;

procedure TFmIOCPDemoClnMain.UpdateUI(AValue: Boolean);
begin
  btnConnect.Enabled := not AValue;
  btnDisconnect.Enabled := AValue;
  btnLog.Enabled := AValue;
  btnClients.Enabled := AValue;
  btnSQL.Enabled := AValue;
  btnUpload.Enabled := AValue;
  btnDownload.Enabled := AValue;
  if not AValue then
  begin
    FamLog.Visible := AValue;
    FamClients.Visible := AValue;
    FamSQL.Visible := AValue;
    FamUpload.Visible := AValue;
    FamDownload.Visible := AValue;
  end;
end;

procedure TFmIOCPDemoClnMain.FormCreate(Sender: TObject);
begin
  inherited;
  UpdateUI(False);
end;

procedure TFmIOCPDemoClnMain.btnConnectClick(Sender: TObject);
begin
  inherited;
  if TFmLogin.ShowForm(Handle) then
  begin
    Screen.Cursor := crHourGlass;
    try
      GDataMgrCtr.LogSocket.OnLog := FamLog.DoLog;
      GDataMgrCtr.ControlSocket.OnClients := FamClients.DoClients;
      GDataMgrCtr.NotifyHandle := Handle;
      btnLog.Click;
      btnLog.Down := True;
      GDataMgrCtr.Start;
      UpdateUI(True);
    finally
      Screen.Cursor := crDefault;
    end;
  end
  else
    UpdateUI(False);
end;

procedure TFmIOCPDemoClnMain.btnDisconnectClick(Sender: TObject);
begin
  inherited;
  Screen.Cursor := crHourGlass;
  try
    GDataMgrCtr.Stop;
    UpdateUI(False);
  finally
    Screen.Cursor := crDefault;
  end;
end;

procedure TFmIOCPDemoClnMain.FormCloseQuery(Sender: TObject;
  var CanClose: Boolean);
begin
  inherited;
  if btnDisconnect.Enabled then
    btnDisconnectClick(Sender);
end;

procedure TFmIOCPDemoClnMain.btnLogClick(Sender: TObject);
begin
  inherited;
  FamLog.Visible := True;
  FamLog.BringToFront;
end;

procedure TFmIOCPDemoClnMain.btnClientsClick(Sender: TObject);
begin
  inherited;
  FamClients.Visible := True;
  FamClients.BringToFront;
end;

procedure TFmIOCPDemoClnMain.btnSQLClick(Sender: TObject);
begin
  inherited;
  if not GDataMgrCtr.SQLSocket.Connected then
  begin
    if GDataMgrCtr.SQLSocket.Connect(GDataMgrCtr.Host, GDataMgrCtr.Port) then
    begin
      if not GDataMgrCtr.SQLSocket.Login(GDataMgrCtr.User, GDataMgrCtr.Password) then
      begin
        ErrorBox(GDataMgrCtr.SQLSocket.LastError);
        Abort;
      end;
    end
    else
    begin
      ErrorBox(GDataMgrCtr.SQLSocket.LastError);
      Abort;
  end;
  end;
  FamSQL.Visible := True;
  FamSQL.BringToFront;
end;

procedure TFmIOCPDemoClnMain.btnUploadClick(Sender: TObject);
begin
  inherited;
  if not GDataMgrCtr.UploadSocket.Connected then
  begin
    if GDataMgrCtr.UploadSocket.Connect(GDataMgrCtr.Host, GDataMgrCtr.Port) then
    begin
      if not GDataMgrCtr.UploadSocket.Login(GDataMgrCtr.User, GDataMgrCtr.Password) then
      begin
        ErrorBox(GDataMgrCtr.UploadSocket.LastError);
        Abort;
      end;
    end
    else
    begin
      ErrorBox(GDataMgrCtr.UploadSocket.LastError);
      Abort;
    end;
    FamUpload.InitDirectory;
  end;
  FamUpload.Visible := True;
  FamUpload.BringToFront;
end;

procedure TFmIOCPDemoClnMain.btnDownloadClick(Sender: TObject);
begin
  inherited;
  if not GDataMgrCtr.DownloadSocket.Connected then
  begin
    if GDataMgrCtr.DownloadSocket.Connect(GDataMgrCtr.Host, GDataMgrCtr.Port) then
    begin
      if not GDataMgrCtr.DownloadSocket.Login(GDataMgrCtr.User, GDataMgrCtr.Password) then
      begin
        ErrorBox(GDataMgrCtr.DownloadSocket.LastError);
        Abort;
      end;
    end
    else
    begin
      ErrorBox(GDataMgrCtr.DownloadSocket.LastError);
      Abort;
    end;
    FamDownload.InitDirectory;
  end;
  FamDownload.Visible := True;
  FamDownload.BringToFront;
end;

end.
