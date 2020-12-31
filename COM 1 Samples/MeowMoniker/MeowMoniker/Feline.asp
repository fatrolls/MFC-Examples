<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Developer Studio">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE>Document Title</TITLE>
</HEAD>
<BODY>

<object classid="clsid:CB18CB8F-C7CC-11D0-9A44-00008600A105"
        runat=server
        id=feline>
</object>

<object classid="clsid:7CF322E0-29A9-11D0-B367-0080C7BC7884"
        runat=server
        id=pt>
</object>

<object classid="clsid:CB18CB8F-C7CC-11D0-9A44-00008600A105"
        id=feline>
</object>

<script language=vbscript>
    dim pt
    set pt = feline.ParseDisplayName("<%= feline.GetDisplayName(pt) %>")
    pt.x = 100
    pt.y = 200
    document.write pt.x & ", " & pt.y
</script>

</BODY>
</HTML>
