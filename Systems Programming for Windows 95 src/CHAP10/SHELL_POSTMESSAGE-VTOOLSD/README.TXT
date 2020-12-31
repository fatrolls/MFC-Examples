The SHELL_PostMessage sample is essentially the same as the PostMessage
sample for Chapter 10. It shows how to use the _SHELL_PostMessage service
to post a Window message instead of laboriously scheduling a priority VM
event, building the stack for a nested-execution call to PostMessage, and
so forth.

Build and test this sample by following the directions for this chapter's
PostMessage sample and using the PMSGTEST application that accompanies
that sample. (Obviously, you want to load *this* VxD instead of the one
from PostMessage.)
												  