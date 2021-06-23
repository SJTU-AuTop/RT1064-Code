::del *.opt /s  ::不允许删除JLINK的设置

del *.scvd /s
del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
del *.plg /s
del *.rpt /s
del *.uvgui.* /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.uvgui /s
del *.uvgui* /s
del *.bak /s
del *.tra /s
del *.dep /s
del JLinkLog.txt /s

del *.iex /s
del *.htm /s
del *.sct /s
del *.map /s

rmdir Objects /s /q
rmdir Listings /s /q

pause
exit
