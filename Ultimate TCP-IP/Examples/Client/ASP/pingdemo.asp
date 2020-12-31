<%@ Language=VBScript %>
<%
' ===================================================================
' Dundas TCP/IP v3.0
' Copyright © Dundas Software 1995-2000, all rights reserved
' ===================================================================
'
' PING and TRACERT Example Using Dundas Ping Control
%>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<Title>Dundas ASP Demo - Ping ActiveX Control</Title>
</HEAD>
<BODY>
<IMG align=middle alt="Dundas TCP/IP 3.0" src="headline.gif" >
<META content="Microsoft Visual Studio 6.0" name=GENERATOR>
<OBJECT classid=clsid:741EFDDE-03DE-11D3-A465-0080C858F182 id=Ping1 
Runat="Server" VIEWASTEXT><PARAM NAME="BlockingMode" VALUE="0"><PARAM NAME="DoLookup" VALUE="0"><PARAM NAME="MaxTimeOuts" VALUE="5"></OBJECT>

<H2><CENTER><Font color=blue>
Dundas TCP/IP v3</font><BR><FONT size=4>Ping 
ActiveX Control 3.0&nbsp;<BR></FONT><FONT size=3>ASP Demo</FONT></CENTER></H2>
<%If Request("submit1") = "" Then %>
	<P ALIGN="left" >Welcome to this demonstration of the Dundas Ping ActiveX Control 3.0.
	To see this demo in action simply enter a valid IP address
	or domain name and click on the Submit button. The results are then displayed by this self-posting ASP. 
	<BR><BR>Please note that the default operation is Ping.  To run a Traceroute select the TraceRoute button in the Options
	section below. 
	</P>  
	</CENTER>
	<HR><FORM action="pingdemo.asp" method="post" id=form1 name=form1>
	Enter a valid address:
	<INPUT id=txtAddress name=txtAddress>
	<INPUT type="submit" value="Submit" id=submit1 name=submit1>
	<BR><BR><HR>
	<H3> 
	&nbsp;Options</H3>
	<INPUT TYPE="radio" NAME="Operation" Value="Ping" CHECKED>Ping Operation       
    <INPUT TYPE="radio" NAME="Operation" Value="TraceRoute">TraceRoute Operation 
    <BR><BR>
    <INPUT TYPE="checkbox" NAME="DoLookup">Include DNS Name Lookup
    <BR><BR>
	Number of allowed timeouts during a ping or traceroute operation:
	<INPUT id="MaxTimeouts" NAME="MaxTimeouts" Value="5" size="2">&nbsp;
	</FORM>
	
<%Else%><CENTER><HR>
<%
	'check to make sure an address has been entered
	If request("txtAddress") <> "" Then
	
		Dim Ret 'return variable, to be tested for initial success/failure
		Dim NumReturns  'will store number of entries returned
		Dim OperationType  'stroes whether Ping or Traceroute needs to be performed
	
		OperationType = Request("Operation")
		strTargetAddress = Request("txtAddress")
		Ping1.BlockingMode = True
	
		'set the number of allowed timeouts
		Ping1.MaxTimeOuts = Request("MaxTimeouts")
	
		'check to see if we should include a Name Dns lookup
		If Request("DoLookup") = "on" Then
			Ping1.DoLookup = True
		End If
	
		'now perform ping or traceroute operation
		If OperationType = "Ping" Then
			  Ret = Ping1.Ping(trim(strTargetAddress))
		Else
			  Ret = Ping1.TraceRoute(trim(strTargetAddress))
		End If
		'do some error trapping
		If Ret <> 0 Then 'return of 0 indicates successful operation
			If Ret = 17 Then
			'error was socket creation failure, prob. due to the registry settings.  Let user know about this
				Response.Write "<p><Font color=red>The socket creation failed, probably due to your permissions.  If your are using Windows NT you can rectify this by creating/modifying the following entry "
				Response.Write "in your registry: HKLM\System\CurrentControlSet\Services\Afd\Parameters\DisableRawSecurity DWORD 1.  Note that this does decrease your security.</p>" 
				Response.Write "<p>There is no way to disable this security setting if you are running Windows 2000.</p></font>"
			Else
			'output error to user
				Response.Write("<Font color=red>Sorry, but the following error occurred: " & Ping1.GetErrorText(Ret) & "</Font>")
			End If
		Else	
			Response.Write("<Font color=blue><b>The " & OperationType & " operation was successful.</b></font><br><br>")
				
			NumReturns = Ping1.GetResponseSize
			Response.Write("<TABLE WIDTH=75% BORDER=1 CELLSPACING=1 CELLPADDING=1>")
			Response.Write("<TR>")
			Response.Write("<TD><B> Sequence</B></TD>")
			Response.Write("<TD><B> Address</B></TD>")
			Response.Write("<TD><B> Code</B></TD>")
			Response.Write("<TD><B> Duration (mS)</B></TD>")
			Response.Write("<TD><B> Name</B></TD>")
			Response.Write("<TD><B> Message</B></TD>")
			Response.Write("<TD><B> Type</B></TD>")
			Response.Write("</TR>")
			for i = 0 to NumReturns -1
				Response.Write("<TR>")
				Response.Write("<TD> " & Ping1.GetResponseSequence (i) & "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseAddress (i)  & "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseCode(i) & "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseDuration(i) & "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseName (i)& "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseMessage (i)& "</TD>")
				Response.Write("<TD> " & Ping1.GetResponseType (i) & "</TD>")
				Response.Write("</TR>")
			next
			Response.Write("</TABLE><br>")
		end if	
	
	Else
	'user did not enter an address
		Response.Write "<Font color=red>Sorry, but you must enter an address to be pinged.</font>"
	End If
	%>
	</CENTER>
	<hr>
	<FORM action="pingdemo.asp" method="post" id=form1 name=form1>
	Please enter a valid address:
	<INPUT id=txtAddress name=txtAddress value="<%=Request("txtAddress")%>">
	<INPUT type="submit" value="Submit" id=submit1 name=submit1><br>
	<BR><hr>		
	<H3>Options</H3>
	<INPUT TYPE="radio" NAME="Operation" Value="Ping" CHECKED>Ping Operation       
	<INPUT TYPE="radio" NAME="Operation" Value="TraceRoute">TraceRoute Operation 
    <BR><BR>
    <INPUT TYPE="checkbox" NAME="DoLookup">Include DNS Name Lookup<BR><BR>
	Number of allowed timeouts during a ping or traceroute operation:
	<INPUT id="MaxTimeouts" NAME="MaxTimeouts" Value="<%=Request("MaxTimeouts")%>" size="3"> </FORM>
	<CENTER>
</CENTER>
<%end if%>
<HR>
<CENTER>Visit Our Website</CENTER>
<A HREF="http://www.dundas.com/"><CENTER><IMG alt="To Dundas Web Site" src="smallogo.gif" >
</CENTER></A>
</BODY>
</HTML>
