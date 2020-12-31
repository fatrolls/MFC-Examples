#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED

#include "display.h"

class process_enumerator {

    void header() {
        char string[256];
        wsprintf(string, "          %-50s\t%10s", "Executable", "Process ID");
        disp.heading(string);
    }

protected:

    display &disp;
	
    process_enumerator(display &d) : disp(d) {}

    virtual bool real_show() = 0;
	
    void show_task(char const *FileName, DWORD ProcessID) {
        char string[256];

        wsprintf(string, "%-60s\t%#10x", FileName, ProcessID);
        disp << string;
    }

public:

	virtual void show() {
		header();
		real_show();
	}
};

#endif
