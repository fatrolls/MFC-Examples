<%@ Language=VBScript %>
<%option explicit%>
<%
' ===================================================================
' Dundas TCP/IP v3.0
' Copyright © Dundas Software 1995-2000, all rights reserved
' ===================================================================
'
' Finger Example Using the Dundas Finger Control
%>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<Title>Dundas Software ASP Demo - Dundas TCP/IP FINGER ActiveX Control 3.0</Title>
</HEAD>
<BODY>
<IMG align=middle alt="Dundas TCP/IP 3.0" src="headline.gif" >
<FONT Face="Times New Roman">
<META content="Microsoft Visual Studio 6.0" name=GENERATOR>
<H2>
<OBJECT classid=clsid:D4A19882-EBE6-11D2-A440-0080C858F182 id=Finger1 
RUNAT="Server" VIEWASTEXT><PARAM NAME="ConnectTimeOut" VALUE="10"><PARAM NAME="ReceiveTimeOut" VALUE="10"><PARAM NAME="BlockingMode" VALUE="0"></OBJECT>
<CENTER><font color=blue>
Dundas TCP/IP v3.0</font><BR><FONT size=4>Finger 
ActiveX Control<BR></FONT><FONT size=3>ASP Demo</FONT></CENTER></H2>
<HR>

<P>
<% if Request("txtAddress") = "" then %>
	Welcome to this demonstration of the Dundas TCP/IP Finger ActiveX Control. 
</P>
<P>A finger operation&nbsp;returns information about one or more users on a 
specific host, and&nbsp;is commonly used to see if someone is logged on. The 
client sends a request to the server for a particular user or domain, and the 
server returns the available information.</P>
<P>             To see this demo  
	in action enter a valid finger server and click on the Submit button.  The results from the 
	finger operation are then displayed by this self-posting ASP page. 
	<BR>
	<BR></P>
	<P ALIGN="left" >
	<FORM action="finger.asp" method="post" id=form1 name=form1>
	Please enter address (e.g. [finger_text_file]@fingerserver):
	<INPUT id=txtAddress name=txtAddress>
	<INPUT type="submit" value="Submit" id=submit1 name=submit1>
	<BR><br>
	</FORM>
	<HR>
	
<%else%>
	<% 
	Dim Ret
	Finger1.BlockingMode=TRUE
	Ret =  Finger1.Finger(Request("txtAddress"))
	if Ret <> 0 Then
		Response.Write("<Center><Font Color=blue>" & Finger1.GetErrorText(Ret) & "</font></center>")
	else
		Dim NumRetLines
		Dim i 
		Dim strTemp
		Response.Write("Finger results for <font color=blue><b>" & Request("txtAddress") & "</font></b>")
		Response.Write("<BR>")
		Response.Write("<BR>")
		NumRetLines = Finger1.NumberReturnLines
		for i = 0 to NumRetLines - 1 
			strTemp = Finger1.GetReturnLine(i)
			Response.Write(strTemp)
			Response.Write("<BR>")
			if i = 0 then 
				Response.Write("<BR>")
			end if	
		next 
		
	end if %>
	<BR>
	<FORM action="finger.asp" method="post" id=form1 name=form1>
	Please enter address (e.g. [finger_text_file]@fingerserver):
	<INPUT id=txtAddress name=txtAddress value=<%=request("txtAddress")%>>
	<INPUT type="submit" value="Submit" id=submit1 name=submit1>
	<br><BR>
	</FORM>
	<HR>

<%end if%>

<BR>
<CENTER>Visit Our Website</CENTER>
<A HREF="http://www.dundas.com/"><CENTER><IMG alt="To Dundas Web Site" src="smallogo.gif" ></CENTER></A>
</FONT>
</BODY>
</HTML>
