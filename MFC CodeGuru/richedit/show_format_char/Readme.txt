I wanted an edit that shows format characters ('TAB' and 'CR\LF'). I tried a 
little with an CEdit but it never worked.

The I found CRTFCtrl::GetCharPos() which will give you the coordinates of a 
given character in the control. With this function I was able to determin the
position of the format characters I wanted to be shown.

So all I do is everytime the content of the control alters I redraw every
visible format character.

The approach is very generic and can be used for other effects.

BUGs: If you drag and drop text with format characters, the selection remains
(-> any help with this problem is welcome!)




Tom Moor, Switzerland
e-mail: moor@m-s.ch