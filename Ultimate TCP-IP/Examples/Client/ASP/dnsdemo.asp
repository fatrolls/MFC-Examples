<%@ Language=VBScript %>
<%
' ===================================================================
' Dundas TCP/IP v3.0
' Copyright © Dundas Software 1995-2000, all rights reserved
' ===================================================================
'
' DNS Lookup Sample using the DNS Control
%>
<HTML>
<HEAD>
<SCRIPT LANGUAGE="VBScript">
'client side scripting to handle disabling of radio buttons

Sub STANDARDPRESSED
  Form1.IncludeMX.disabled=true
End Sub

Sub AUTHORITATIVEPRESSED
  Form1.IncludeMX.disabled = false
End Sub
</SCRIPT>

<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<Title>Dundas Software ASP Demo - Dundas TCP/IP DNS ActiveX Control 3.0</Title>
<META content="Microsoft FrontPage 4.0" name=GENERATOR>
</HEAD>
<BODY>
<IMG align=middle alt="Dundas TCP/IP 3.0" src="headline.gif" >
<FONT Face="Times New Roman">
<OBJECT classid=clsid:86E5D750-02EB-11D3-A464-0080C858F182 id=DNS1 
RUNAT="SERVER" VIEWASTEXT><PARAM NAME="LookupTimeOut" VALUE="20"><PARAM NAME="IncludeDefMX" VALUE="0">
<PARAM NAME="BlockingMode" VALUE="0"><PARAM NAME="Protocol" VALUE="0"></OBJECT>
<H2><CENTER>
<FONT color=blue>Dundas</FONT><font color="blue"> &nbsp;TCP/IP v3.0</font><BR><FONT size=4>DNS 
ActiveX Control&nbsp;</FONT><br><FONT size=3>ASP Demo</FONT>
</CENTER></H2>
<HR>
<% if Request("txtAddress") = "" then %>
<H3>Domain Name Lookup</H3><FONT face="Times New Roman">
<P align=left>Welcome to this demonstration of the Dundas TCP/IP 3.0 DNS ActiveX Control.</P><P align=left>  A domain name lookup operation 
identifies the IP address of a given domain as well as other servers associated with 
the domain.</P>
<P align=left> To use this demo  
	simply enter a valid domain name and click on the Submit button.  You can select various options 
	(protocol to be used, fields to be returned, etc.) in the Options section below.  The results from the 
	lookup operation are then displayed by this self-posting ASP. </P>
<P></P>		
	<FORM Name="Form1" action="dnsdemo.asp" method="post">
	Enter a valid domain name:
	<INPUT id=txtAddress name=txtAddress maxlength="40">
	<INPUT type="submit" value="Submit" id=submit1 name=submit1>
	<BR>
	<H3><font color="blue">Options</font></H3>
	<INPUT TYPE="radio" NAME="Lookup" Value="Standard" ONCLICK="STANDARDPRESSED">Standard Lookup       
    <INPUT TYPE="radio" NAME="Lookup" Value="Authoritative" ONCLICK="AUTHORITATIVEPRESSED" CHECKED>Authoritative Lookup 
    <BR>
    <INPUT TYPE="checkbox" NAME="IncludeMX" CHECKED>Include Domain Host
    <BR><BR>
	Protocol to be used for the lookup operation:
	<INPUT TYPE="radio" NAME="ProtocolType" Value="TCP" CHECKED>TCP
	<INPUT TYPE="radio" NAME="ProtocolType" Value="UDP">UDP
	<BR><BR>
	Lookup timeout (seconds):
	<INPUT id=txtTimeout name=txtTimeout value="10" size="5" maxlength="3">
	<BR><BR>	
	Entry fields to be retrieved:<BR>
	<TABLE BORDER=0 CELLSPACING=1 CELLPADDING=5> 	
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="Host" CHECKED>Host</TD>	
	<TD nowrap><INPUT TYPE="checkbox" NAME="Data" CHECKED>Data</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Data2" CHECKED>Data2</TD>
	</TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="ShortName" CHECKED>Short Name</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="LongName" CHECKED>Long Name</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="EntryType" CHECKED>Entry Type</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="MX_Preference">MX Preference</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Refresh">SOA Refresh</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Expire">SOA Expire</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Retry">SOA Retry</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Serial">SOA Serial</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Minimum">SOA Minimum</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="TimeToLive">Time to Live</TD></TR>
	</TABLE>
	</FORM>	
<% else %>
	<CENTER>
	<%
	'use synchronous mode, since we can't raise user-defined events with asp's
	DNS1.BlockingMode=TRUE
		
	'find out what button is checked, perform authoritative or standard lookup
	Dim LookupType
	LookupType = Request("Lookup")
	
	'use the protocol specified by the user
	Dim ProtocolToUse
	ProtocolToUse = Request("ProtocolType")
	'set the Protocol property
	if ProtocolToUse = "TCP" then
		DNS1.Protocol = 0 'ptTcp, as listed in ProtocolTypes enum
	else
		DNS1.Protocol = 1 'ptUdp, as listed in ProtocolTypes enum
	end if
	
	'set the LookupTimeout property --> assume 10 seconds if left blank
	if Request("txtTimeout") <> "" then	
		DNS1.LookupTimeOut = clng(Request("txtTimeout"))
	else
		DNS1.LookupTimeOut = 10
	end if	
		
	if LookupType = "Authoritative" then
		Response.Write("Authoritative lookup results for: " & "<Font color=blue><b>" & Request("txtAddress") & "</b></Font>")
	else
		Response.Write("Lookup results for: " & "<Font color=blue>" & Request("txtAddress") & "</Font>")
	end if	
	Response.Write("<BR>")
	Response.Write("<BR>")
	
	'perform either standard or auth. lookup
	if LookupType = "Authoritative" then
		'first check to see if we should include
		'   default MX record, set property accordingly
		if Request("IncludeMX") = "on" then
		  DNS1.IncludeDefaultMX = true
		else
		  DNS1.IncludeDefaultMX = false
		end if   
	    Ret = DNS1.AuthoritativeLookup ("b.root-servers.net", trim(Request("txtAddress")))
	else
		Ret = DNS1.Lookup("b.root-servers.net", trim(Request("txtAddress")))
	end if
	
	if Ret <> 0 Then  'trap for errors
		Response.Write("<font color=red>" & DNS1.GetErrorText(Ret) & "</font>") 'output error text to user
	else
		DNS1.ResetEnumeration() 'successful, continue on with populating table
		Response.Write("<TABLE BORDER=1 CELLSPACING=1 CELLPADDING=2>")
			Response.Write("<TR>")
			if Request("Host") = "on" then
			  Response.Write("<TD nowrap><B>Host</B></TD>")
			end if  
			if Request("Data") = "on" then
			  Response.Write("<TD nowrap><B>Data</B></TD>")
			end if
			if Request("Data2") = "on" then
			  Response.Write("<TD nowrap><B>Data2</B></TD>")
			end if
			if Request("LongName") = "on" then  
			  Response.Write("<TD nowrap><B>Long Name</B></TD>")
			end if
			if Request("ShortName") = "on" then  
			  Response.Write("<TD nowrap><B>Short Name</B></TD>")
			end if
			if Request("EntryType") = "on" then  
			  Response.Write("<TD nowrap><B>Type</B></TD>")
			end if
			if Request("TimeToLive") = "on" then
			  Response.Write("<TD nowrap><B>Time to Live</B></TD>")
			end if
			if Request("MX_Preference") = "on" then  
			  Response.Write("<TD nowrap><B>MX Preference</B></TD>")
			end if
			if Request("Soa_Refresh") = "on" then  
			  Response.Write("<TD nowrap><B>Soa Refresh</B></TD>")
			end if
			if Request("Soa_Expire") = "on" then  
			  Response.Write("<TD nowrap><B>Soa Expire</B></TD>")
			end if
			if Request("Soa_Retry") = "on" then  
			  Response.Write("<TD nowrap><B>Soa Retry</B></TD>")
			end if
			if Request("Soa_Serial") = "on" then  
			  Response.Write("<TD nowrap><B>Soa Serial</B></TD>")
			end if
			if Request("Soa_Minimum") = "on" then  
			  Response.Write("<TD nowrap><B>Soa Minimum</B></TD>")
			end if
			Response.Write("</TR>")
		
		while DNS1.EnumDNSEntry() = 0 
			Response.Write("<TR>")
			if Request("Host") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntryHostName & "</TD>")
			end if  
			if Request("Data") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntryData & "</TD>")
			end if
			if Request("Data2") = "on" then  
			'if Data2 is a zero length string use "na"
			  if DNS1.EntryData2 = "" then
			    Response.Write("<TD nowrap> " & "NA" & "</TD>")
			  else			  
			    Response.Write("<TD nowrap> " & DNS1.EntryData2 & "</TD>")
			  end if
			end if
			if Request("LongName") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.GetEntryLongName(DNS1.EntryType) & "</TD>")
			end if
			if Request("ShortName") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.GetEntryShortName(DNS1.EntryType) & "</TD>")
			end if
			if Request("EntryType") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntryType & "</TD>")
			end if
			if Request("TimeToLive") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntryTimeToLive & "</TD>")
			end if
			if Request("MX_Preference") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntryMX_Preference & "</TD>")
			end if
			if Request("Soa_Refresh") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntrySOA_Refresh & "</TD>")
			end if
			if Request("Soa_Expire") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntrySOA_Expire & "</TD>")
			end if
			if Request("Soa_Retry") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntrySOA_Retry & "</TD>")
			end if
			if Request("Soa_Serial") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntrySOA_Serial & "</TD>")
			end if
			if Request("Soa_Minimum") = "on" then  
			  Response.Write("<TD nowrap> " & DNS1.EntrySOA_Minimum & "</TD>")
			end if
			Response.Write("</TR>")
		wend
		Response.Write("</TABLE>")
		
	end if %>
	</CENTER>
	<BR>
	<hr>
	<form name="Form1" action="dnsdemo.asp" method="post">
	Enter a valid domain name:
	<INPUT id=txtAddress name=txtAddress value=<%=request("txtAddress")%> maxlength="40">
	<INPUT type="submit" value="Submit" id=submit1 name=submit1>
	<BR><BR>
	<H3><font color="blue">Options</font></H3>
	<INPUT TYPE="radio" NAME="Lookup" Value="Standard" ONCLICK="STANDARDPRESSED">Standard Lookup       
    <INPUT TYPE="radio" NAME="Lookup" Value="Authoritative" ONCLICK="AUTHORITATIVEPRESSED" CHECKED>Authoritative Lookup 
    <BR>
    <INPUT TYPE="checkbox" NAME="IncludeMX" CHECKED>Include Domain Host
    <BR><BR>
	Protocol to be used for the lookup operation:
	<INPUT TYPE="radio" NAME="ProtocolType" Value="TCP" CHECKED>TCP
	<INPUT TYPE="radio" NAME="ProtocolType" Value="UDP">UDP
	<BR><BR>
	Lookup timeout (seconds):
	<INPUT id=txtTimeout name=txtTimeout value=<%=request("txtTimeout")%> size="5" maxlength="3">
	<BR><BR>	
	Entry fields to be retrieved:<BR>
	<TABLE BORDER=0 CELLSPACING=1 CELLPADDING=5> 	
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="Host" CHECKED>Host</TD>	
	<TD nowrap><INPUT TYPE="checkbox" NAME="Data" CHECKED>Data</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Data2" CHECKED>Data2</TD>
	</TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="ShortName" CHECKED>Short Name</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="LongName" CHECKED>Long Name</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="EntryType" CHECKED>Entry Type</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="MX_Preference">MX Preference</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Refresh">SOA Refresh</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Expire">SOA Expire</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Retry">SOA Retry</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Serial">SOA Serial</TD>
	<TD nowrap><INPUT TYPE="checkbox" NAME="Soa_Minimum">SOA Minimum</TD></TR>
	<TR><TD nowrap><INPUT TYPE="checkbox" NAME="TimeToLive">Time to Live</TD></TR>
	</TABLE>
	</FORM>

<% end if %>
<HR>
<BR>
<CENTER>Visit Our Website</CENTER>
<A HREF="http://www.dundas.com/"><CENTER><IMG alt="To Dundas Web Site" src="smallogo.gif" ></CENTER></A></FONT>
</BODY>
</HTML>