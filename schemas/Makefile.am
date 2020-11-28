desktop_gschemas_in = \
	org.gde2.accessibility-keyboard.gschema.xml.in \
	org.gde2.accessibility-startup.gschema.xml.in \
	org.gde2.applications-at-mobility.gschema.xml.in \
	org.gde2.applications-at-visual.gschema.xml.in \
	org.gde2.applications-browser.gschema.xml.in \
	org.gde2.applications-office.gschema.xml.in \
	org.gde2.applications-terminal.gschema.xml.in \
	org.gde2.background.gschema.xml.in \
	org.gde2.debug.gschema.xml.in \
	org.gde2.file-views.gschema.xml.in \
	org.gde2.interface.gschema.xml.in \
	org.gde2.lockdown.gschema.xml.in \
	org.gde2.peripherals-keyboard.gschema.xml.in \
	org.gde2.peripherals-mouse.gschema.xml.in \
	org.gde2.sound.gschema.xml.in \
	org.gde2.thumbnail-cache.gschema.xml.in \
	org.gde2.thumbnailers.gschema.xml.in \
	org.gde2.typing-break.gschema.xml.in

@INTLTOOL_XML_NOMERGE_RULE@

gsettings_SCHEMAS = $(desktop_gschemas_in:.xml.in=.xml)

@GSETTINGS_RULES@

EXTRA_DIST = \
	$(desktop_gschemas_in)

CLEANFILES = \
	$(gsettings_SCHEMAS) \
	*.gschema.valid
