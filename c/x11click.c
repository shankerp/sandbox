#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Command.h>
#include <stdio.h>
#include <stdlib.h>

XtAppContext app_context;

void quit_proc (Widget w, XtPointer client_data, XtPointer call_data)
{
  XtDestroyApplicationContext (app_context);
  exit (0);
}

int main (int argc, char **argv)
{
  Widget toplevel, form, w;
  toplevel = XtOpenApplication (&app_context, "XFirst", NULL, 0, &argc,
                                argv, NULL, applicationShellWidgetClass, NULL,
                                0);
  form = XtVaCreateManagedWidget ("form", formWidgetClass, toplevel, NULL);
  w = XtVaCreateManagedWidget ("quit_button", commandWidgetClass, form,
                               XtNlabel, "Quit", NULL);
  XtAddCallback (w, XtNcallback, quit_proc, NULL);
  XtRealizeWidget (toplevel);
  XtAppMainLoop (app_context);
}
