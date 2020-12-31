The samples for Chapter 10 illustrate how a VxD works with a 16-bit
Windows application:

AppyTime          -- (VxD) shows how to schedule an AppyTime event
                     callback and how to run a Win16 function from
                     inside the callback function.

PostMessage       -- (VtoolsD VxD and Win16 app) uses nested execution
                     to post window messages for consumption by a
                     Win16 application.

SHELL_PostMessage -- (VtoolsD VxD) uses the _SHELL_PostMessage service
                     to post window messages.

(Note: A sample showing how a 32-bit app and a VxD work together is
the ServiceHook example in Chapter 9.)