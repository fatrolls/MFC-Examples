Hello Windows Programmers.

I discovered recently that it is possible to create a full
application using the CPropertySheet as the class for the
main window of the application.

If you read the source of the small demo you will understant
better what do i mean.

I created a new class named CSheet that has CPropertySheet as
the base class. CSheet does have four member variables of type
CPropertyPage, named Page1, Page2, Page3 and Page4. It also
contains a CMenu variable.

When the CSheet constructor is called i am creating the four
pages and i am adding them to the property sheet.

CSheet is overloading the virtual OnInitDialog function and
in this function its doing two thinks. 1) Hides the property
sheet buttons OK, CANCEL and APPLY. 2) Loads the applications
menu.

CSheet does have a message map, which redirects the menu message
to the display member function which displays the page selected.

After defining the CSheet class, i am creating a CWinApp derived
class that creates a CSheet Window as its main window and thats
all. I have an application that is based on CPropertySheet as the
main window class.

I hope that my code will help you.
May the SOURCE be with you.

