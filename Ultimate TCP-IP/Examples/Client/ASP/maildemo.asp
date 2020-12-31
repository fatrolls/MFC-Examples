<%@ Language=VBScript %>
<% option explicit %>
<%
' ===================================================================
' Dundas TCP/IP v3.0
' Copyright © Dundas Software 1995-2000, all rights reserved
' ===================================================================
'
' Email Example Using the Dundas Mail Control
%>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<Title>Dundas TCP/IP Mail Client ActiveX Control 3.0 - ASP Demo</Title>
</HEAD>

<BODY>
<IMG align=middle alt="Dundas TCP/IP 3.0" src="headline.gif" >
<FONT Face="Times New Roman">
<META content="Microsoft Visual Studio 6.0" name=GENERATOR>
<H2>
<CENTER><!--Runat=Server specifies script to be run at the server side-->
<OBJECT classid=clsid:F7FA867E-089C-11D3-A469-0080C858F182 id=Mail 
Runat="Server" VIEWASTEXT><PARAM NAME="ConnectTimeOut" VALUE="10"><PARAM NAME="ReceiveTimeOut" VALUE="10"><PARAM NAME="BlockingMode" VALUE="0"><PARAM NAME="MailHostName" VALUE=""><PARAM NAME="POP3HostName" VALUE=""><PARAM NAME="UserName" VALUE=""><PARAM NAME="Password" VALUE="">
 <!--set the timeout parameters--><!-- set the timeout values--></OBJECT>
<font color="blue">Dundas TCP/IP v3</font><BR><FONT size=4>Mail Client
ActiveX Control 3.0&nbsp;<BR></FONT><FONT size=3>ASP Demo</FONT></CENTER></H2>
<HR>
<!-- show the form, get variables and send mail-->
<%
'see if page posted to itself, if so process form elements and send email if required fields are filled out
	if request("submitSend") = "" then
	 %>		
		<P align=left>Welcome to this ASP demonstration of the Dundas TCP/IP Mail 
        ActiveX Control 3.0. The Mail ActiveX control utilizes the Smtp protocol to send email messages and the Pop3 
        protocol to receive messages.
        Full MIME support is encorporated when this control is used in conjunction with the <font color="red">Dundas Message
        ActiveX Control</font>, which also ships with Dundas TCPIP 3.0.  &nbsp; 
        </P>
        <P align=left>Please fill out the following form and click on the "Send Mail" button. The success or failure of the operation will be indicated by this 
         self-posting ASP page. </P>
        <hr>
        <font color="blue" size=4>Smtp Server</font>
        <FORM action="maildemo.asp" method="post" id=form1 name=form1>
		Please enter a valid Smtp server (required):&nbsp;<INPUT id=txtSmtpAddress name=txtSmtpAddress size="30" value="<%=request("txtSmtpAddress")%>"><BR><br>
		<hr><font color="blue" size=4>Message Details</font><br><br>		
		<table cols=4 cellpadding=2 width=560>
			<tr><td align=left width=83>To (required):</td><td align=left width=60><INPUT id=txtTo name=txtTo size="30" value="<%=request("txtTo")%>"></td>
			<td width=10>From:</td><td align=left width=90><INPUT id=txtFrom name=txtFrom size="30" value="<%=request("txtFrom")%>"></td></tr>
			<tr><td align=left width=83>Cc:</td><td align=left width=60><INPUT id=txtCc name=txtCc size="30" align="right" value="<%=request("txtCc")%>"></td>
			<td align=left width=10>Bcc:</td><td align=left width=90><INPUT id=txtBcc name=txtBcc size="30" value="<%=request("txtBcc")%>"></td></tr>
			<tr><td align=left width=83>Subject:</td><td colspan=3 align=left width=60><INPUT id=txtSubject name=txtSubject size="30" value="<%=request("txtSubject")%>"></td></tr>
		</table><BR>		
		Body:<BR><TEXTAREA cols=66 id=textarea1 name=textarea1 rows=10>
		</TEXTAREA>&nbsp;&nbsp;<INPUT type="submit" value="Send Mail" id=submitSend name=submitSend>
		<BR><BR>		
		Connection Attempt Timeout (seconds): <INPUT id="txtTimeOut" name="txtTimeout" size="3" value="5">
		</FORM> 
		
	<% else	
		
		if (Request("txtSmtpAddress") <> "") and (Request("txtTo") <> "") then	
		'send email		
			
			Dim strSmtp 'variable to store Smtp server Dns
			Dim strTo, strCc, strSubject,strBody, strBcc
			Dim Ret, Ret2  'return variable, used for error trapping
					
			'assign text box strings to variables
			Mail.MailHostName = Request("txtSmtpAddress")
			strTo = Request("txtTo")
			strCc = Request("txtCc")
			strBcc = Request("txtBcc")
			strSubject = Request("txtSubject")
			strBody=Request("textarea1")
				
			Mail.BlockingMode = TRUE  'use synchronous communication
			'set the connecttimeout property, if left blank assume a value of 10 seconds
			if request("") <> "" then	
				Mail.ConnectTimeOut = clng(Request("txtTimeout"))
			else
				Mail.ConnectTimeOut = 10
			end if
		
			Ret = Mail.SMTPConnect()	
		
			if Ret = 0 Then
				'now send the email
				Ret2 = Mail.SendMail(strTo,Request("txtFrom"),strSubject,strBody,strCc,strBcc,Request("txtAttach"))
				'indicate success/failure to user
				%><FONT color="#0000ff"><CENTER><b><%Response.Write(Mail.GetErrorText(Ret2))
				%></b></CENTER></FONT><%
			else				
				%><FONT color="#0000ff"><CENTER> <% Response.Write(Mail.GetErrorText(Ret))
				%></CENTER></FONT>
			<% end if  
		
		else
		'one or more required field was left blank
			Response.Write("<font color=#ff0000><center>Sorry, but you did not fill out a required field.  Please try again.</center></font>")   
		end if %>
					
		<font color="blue" size=4>Smtp Server</font>
		<FORM action="maildemo.asp" method="post" id=form1 name=form1>
		Please enter a valid Smtp server (required):&nbsp;<INPUT id=txtSmtpAddress name=txtSmtpAddress size="30" value="<%=request("txtSmtpAddress")%>"><BR><br>
		<hr><font color="blue" size=4>Message Details</font><br><br>		
		<table cols=4 cellpadding=2 width=560>
			<tr><td align=left width=83>To (required):</td><td align=left width=60><INPUT id=txtTo name=txtTo size="30" value="<%=request("txtTo")%>"></td>
			<td width=10>From:</td><td align=left width=90><INPUT id=txtFrom name=txtFrom size="30" value="<%=request("txtFrom")%>"></td></tr>
			<tr><td align=left width=83>Cc:</td><td align=left width=60><INPUT id=txtCc name=txtCc size="30" align="right" value="<%=request("txtCc")%>"></td>
			<td align=left width=10>Bcc:</td><td align=left width=90><INPUT id=txtBcc name=txtBcc size="30" value="<%=request("txtBcc")%>"></td></tr>
			<tr><td align=left width=83>Subject:</td><td colspan=3 align=left width=60><INPUT id=txtSubject name=txtSubject size="30" value="<%=request("txtSubject")%>"></td></tr>
		</table><BR>		
		Body:<BR><TEXTAREA cols=66 id=textarea1 name=textarea1 rows=10>
		</TEXTAREA>&nbsp;&nbsp;<INPUT type="submit" value="Send Mail" id=submitSend name=submitSend>
		<BR><BR>		
		Connection Attempt Timeout (seconds): <INPUT id="txtTimeOut" name="txtTimeout" size="3" value="5"> 
	<%end if%>
<BR>
<CENTER>Visit Our Website</CENTER>
<A HREF="http://www.dundas.com/"><CENTER><IMG alt="To Dundas Web Site" src="smallogo.gif" ></CENTER></A>
</FONT></FORM>
</BODY>
</HTML>