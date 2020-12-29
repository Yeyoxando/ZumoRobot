@ Diego Ochando Torres
@ PT module - generate doxygen with .pde files batch script
@ files in .pde are not recognised by Doxygen, they need to be converted.

copy zumoGUI\gui.pde zumoGUI\gui_doxy.java
copy zumoGUI\guiButtonFunctions.pde zumoGUI\guiButtonFunctions_doxy.java
copy zumoGUI\guiHelp.pde zumoGUI\guiHelp_doxy.java
copy zumoGUI\zumoGUI.pde zumoGUI\zumoGUI_doxy.java

D:\ProgramFiles\Doxygen\bin\doxygen.exe doc\Doxyfile

del zumoGUI\gui_doxy.java
del zumoGUI\guiButtonFunctions_doxy.java
del zumoGUI\guiHelp_doxy.java
del zumoGUI\zumoGUI_doxy.java

exit