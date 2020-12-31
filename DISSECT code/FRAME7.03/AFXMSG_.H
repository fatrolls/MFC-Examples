enum AfxSig
{
        AfxSig_end = 0,     // [marks end of message map]
        AfxSig_vv,
};

#define ON_COMMAND(id, memberFxn) \
        { WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)id, AfxSig_vv, (AFX_PMSG)memberFxn },
